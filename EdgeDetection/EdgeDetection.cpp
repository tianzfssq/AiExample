/*

以Lena为原始图像，通过OpenCV实现平均滤波，高斯滤波及中值滤波，比较滤波结果。

*/

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void testSobel(Mat img, int type = 0)
{
	Mat imageGray, imageGauss;

	cvtColor(img, imageGray, COLOR_BGR2GRAY);
	GaussianBlur(imageGray, imageGauss, Size(3, 3), 0);

	if (type == 1)
	{
		img = imageGray;
	}
	else if (type == 2)
	{
		img = imageGauss;
	}
	imshow("原图", img);

	// Sobel算子

	//【3】求 X方向梯度  
	Mat imageSobel_x, abs_grad_x;
	Sobel(img, imageSobel_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(imageSobel_x, abs_grad_x);
	imshow("【效果图】 X方向Sobel", abs_grad_x);

	//【4】求Y方向梯度  
	Mat imageSobel_y, abs_grad_y;
	Sobel(img, imageSobel_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(imageSobel_y, abs_grad_y);
	imshow("【效果图】Y方向Sobel", abs_grad_y);

	//【5】合并梯度(近似)  
	Mat imageSobel;
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, imageSobel);
	imshow("【效果图】整体方向Sobel", imageSobel);

	// Canny算法
	//blur(imageGauss, imageCanny, Size(5, 5));
	//imshow("imageSobel", imageCanny);

	waitKey(0);
}

void testCanny(Mat img, int type = 0)
{
	Mat imageGray, imageGauss;

	cvtColor(img, imageGray, COLOR_BGR2GRAY);
	GaussianBlur(imageGray, imageGauss, Size(3, 3), 0);

	if (type == 1)
	{
		img = imageGray;
	}
	else if (type == 2)
	{
		img = imageGauss;
	}

	imshow("原图", img);

	// Canny算子
	Mat imageCandy;
	Canny(img, imageCandy, 100, 200, 3);
	imshow("Canny算子", imageCandy);
	waitKey(0);
}

int main()
{
	Mat img = imread("../Pics/Lena.png");

	testSobel(img, 1);
	testCanny(img, 1);

	return 0;
}