import cv2
import sys

print("立绘合成")
print("输入Q退出\n")
print("1.明日方舟")
print("2.少女前线")
num = int(input())

while(1):

    path1 = input("待处理立绘")
    if(path1 == 'Q'): sys.exit()
    if(path1[0] == '"'):
        path1 = path1[1:len(path1) - 1]
    path2 = input("alpha通道")
    if(path2[0] == '"'):
        path2 = path2[1:len(path2) - 1]
    for i in range(len(path1) - 1, -1, -1):
        if(path1[i] == '.'):
            filepath = path1[0:i]
            filename = path1[i:]
            break
    
    if(num == 1):
        src = cv2.imread(path1)
        alpha = cv2.imread(path2, 0)
        h1, w1, _ = src.shape
        h2, w2 = alpha.shape

        if(h1 != h2 | w1 != w2):
            c = input("尺寸不一致，是否继续？\nY/N: ")
            if(c == 'Y'):
                alpha = cv2.resize(alpha, (h1, w1), cv2.INTER_CUBIC)
            else:
                continue
        dst = cv2.merge((src, alpha))
        cv2.imwrite(filepath + "_group" + filename, dst)
        

    elif(num == 2):
        src = cv2.imread(path1)
        alpha = cv2.imread(path2, -1)
        h1, w1, _ = src.shape
        h2, w2, _ = alpha.shape

        if(h1 != h2 | w1 != w2):
            c = input("尺寸不一致，是否继续？\nY/N: ")
            if(c == 'Y'):
                alpha = cv2.resize(alpha, (h1, w1), cv2.INTER_CUBIC)
            else:
                continue
        alphach = cv2.split(alpha)
        dst = cv2.merge((src, alphach[3]))
        cv2.imwrite(filepath + "_group" + filename, dst)

    

sys.exit()
