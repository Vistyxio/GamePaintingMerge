#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	string path1, path2, filepath, filename;
	Mat src, mask;
	int n = 0;
	cout << "立绘合成" << endl;
	cout << "1.明日方舟" << endl;
	cout << "2.少女前线" << endl;
	cin >> n;
	cin.ignore(1);
	cout << "输入Q退出" << endl << endl;

	
	while (true) {

		cout << "待处理立绘: ";
		getline(cin, path1);

		if (path1 == "Q") return 0;

		cout << "alpha通道: ";
		getline(cin, path2);

		if (path1[0] == '"') {
			path1 = path1.substr(1, path1.length() - 2);
		}
		if (path2[0] == '"') {
			path2 = path2.substr(1, path2.length() - 2);
		}
		for (long long i = path1.length() - 1; i >= 0; i--) {
			if (path1[i] == '.') {
				filepath = path1.substr(0, i);
				filename = path1.substr(i);
				break;
			}
		}
		src = imread(path1);
		if (n == 1) {
			mask = imread(path2, 0);
		} else if (n == 2) {
			mask = imread(path2, -1);
		}

		cout << "立绘尺寸" << src.size() << " " << "透明通道" << mask.size() << endl;

		if (src.size() != mask.size()) {
			cout << "尺寸不一致，是否继续？" << endl << "Y/N: ";
			char c;
			cin >> c;
			if (c == 'Y') {
				resize(mask, mask, src.size(), INTER_CUBIC); //INTER_LINEAR or INTER_CUBIC
			} else {
				continue;
			}
		}

		Mat dst(src.size(), CV_8UC4);

		vector<Mat> chann, maskch;

		split(src, chann);

		if (n == 1) {
			chann.emplace_back(mask);
		} else if (n == 2) {
			split(mask, maskch);
			chann.emplace_back(maskch[3]);
		}
		
		merge(chann, dst);
		imwrite(filepath + "_group" + filename, dst);

		cout << "完成" << endl << endl;
	}

	return 0;
}
