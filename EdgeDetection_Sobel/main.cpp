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
	Mat img = imread("../Pics/Lena.png");
	imshow("Source Image", img);


	waitKey(0);


	return 0;
}