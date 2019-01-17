#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std;

using namespace cv;


// %THIRDPARTY%\opencv\build\include
// %THIRDPARTY%\opencv\build\x64\vc15\lib
// opencv_world344d.lib

// RGB������ʾ
void showRGB(Mat img)
{

	/*
	Ϊʲô�������ͨ�����Ǻڰ׻ң������Ǻ�������
	ԭ���Ƿ����Ϊ��ͨ�����൱�ڷ���ͨ����ͬʱ����������ͨ���������ͬ����ֵ��
	�����ɫͨ�����������ɫͨ����ͬʱ����ɫ����ɫ�����Ϊ�ͺ�ɫ��ͬ����ֵ������һ����ֻ�кڰ׻��ˡ�
	��ô��ɫ���������أ����Խ��й۲죬�ᷢ��ԭͼ����ɫԽ�ӽ���ɫ�ĵط��ں�ɫͨ��Խ�ӽ���ɫ��
	�ڴ���ĵط��ں�ɫͨ������ִ��ס�
	*/
	Mat rgbCH[3];

	split(img, rgbCH);
	imshow("B", rgbCH[0]);
	moveWindow("B", 50, 51 + 350);
	imshow("G", rgbCH[1]);
	moveWindow("G", 50 + 350, 51 + 350);
	imshow("R", rgbCH[2]);
	moveWindow("R", 50 + 700, 51 + 350);
	waitKey(0);
}

// HSL������ʾ
void showHSV(Mat img)
{

	Mat hsvCH[3];

	split(img, hsvCH);
	imshow("Hue", hsvCH[0]);
	moveWindow("Hue", 50, 51 + 350);
	imshow("Stauration", hsvCH[1]);
	moveWindow("Stauration", 50 + 350, 51 + 350);
	imshow("Value", hsvCH[2]);
	moveWindow("Value", 50 + 700, 51 + 350);

	waitKey(0);
}

int main()
{
	Mat img_LOGO = imread("../Pics/Lena.png");
	resize(img_LOGO, img_LOGO, Size(img_LOGO.cols*0.75, img_LOGO.rows*0.75));
	imshow("Source Image", img_LOGO);
	moveWindow("Source Image", 50, 50);


	showRGB(img_LOGO);

	Mat img_HSV;
	cvtColor(img_LOGO, img_HSV, COLOR_BGR2HSV);
	showHSV(img_HSV);

	return 0;
}