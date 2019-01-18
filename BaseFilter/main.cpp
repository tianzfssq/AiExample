/*

以Lena为原始图像，通过OpenCV实现平均滤波，高斯滤波及中值滤波，比较滤波结果。

*/

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void blurTest(Mat img)
{
	imshow("原图", img);

	// 均值滤波
	Mat imageBlur;
	blur(img, imageBlur, Size(5,5));
	imshow("均值滤波", imageBlur);


	// 高斯滤波
	Mat imageGauss;
	/*
	第三个参数，Size类型的ksize高斯内核的大小。其中ksize.width和ksize.height可以不同，但他们都必须为正数和奇数。或者，它们可以是零的，它们都是由sigma计算而来。
	第四个参数，double类型的sigmaX，表示高斯核函数在X方向的的标准偏差。
	第五个参数，double类型的sigmaY，表示高斯核函数在Y方向的的标准偏差。若sigmaY为零，就将它设为sigmaX，如果sigmaX和sigmaY都是0，那么就由ksize.width和ksize.height计算出来。
	为了结果的正确性着想，最好是把第三个参数Size，第四个参数sigmaX和第五个参数sigmaY全部指定到。
	第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_DEFAULT。
	*/
	GaussianBlur(img, imageGauss, Size(5, 5), 0);
	imshow("高斯滤波", imageBlur);

	// 中值滤波
	Mat imageMedian;
	medianBlur(img, imageMedian, 5);
	imshow("中值滤波", imageBlur);

	waitKey(0);
}

int main()
{
	Mat img = imread("../Pics/Lena.png");
	
	blurTest(img);

	return 0;
}