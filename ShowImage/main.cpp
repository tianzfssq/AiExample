#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

// D:\ThirdParty\opencv\build\include
// D:\ThirdParty\opencv\build\x64\vc15\lib
// opencv_world344d.lib

int main()
{
	//��ȡ���ص�һ��ͼƬ����ʾ����
	Mat img = imread("./1.jpg");


	Mat imageGauss, image_1, image_2, gray, gray_1, hsv, hsvChannels[3];

	GaussianBlur(img, imageGauss, Size(5, 5), 0);
	imshow("MM Viewer", img);
	imshow("MM imageGauss", imageGauss);
	//�ȴ��û�����
	waitKey(0);

	return 0;
}