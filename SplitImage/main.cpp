#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std;

using namespace cv;


// %THIRDPARTY%\opencv\build\include
// %THIRDPARTY%\opencv\build\x64\vc15\lib
// opencv_world344d.lib

// RGB分量显示
void showRGB(Mat img)
{

	/*
	为什么分离出的通道都是黑白灰，而不是红绿蓝。
	原因是分离后为单通道，相当于分离通道的同时把其他两个通道填充了相同的数值。
	比如红色通道，分离出红色通道的同时，绿色和蓝色被填充为和红色相同的数值，这样一来就只有黑白灰了。
	那么红色体现在哪呢？可以进行观察，会发现原图中颜色越接近红色的地方在红色通道越接近白色。
	在纯红的地方在红色通道会出现纯白。
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

// HSL分量显示
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