/*
问题描述
（本周共计4个作业，一个扩展作业）
1. 以Lena为原始图像，通过OpenCV实现平均滤波，高斯滤波及中值滤波，比较滤波结果。
2. 以Lena为原始图像，通过OpenCV使用Sobel及Canny算子检测，比较边缘检测结果。
3. 在OpenCV安装目录下找到课程对应演示图片(安装目录\sources\samples\data)，首先计算灰度直方图，进一步使用大津算法进行分割，并比较分析分割结果。
4. 使用米粒图像，分割得到各米粒，首先计算各区域(米粒)的面积、长度等信息，进一步计算面积、长度的均值及方差，分析落在3sigma范围内米粒的数量。

扩展作业：
5. 使用棋盘格及自选风景图像，分别使用SIFT、FAST及ORB算子检测角点，并比较分析检测结果。
(可选)使用Harris角点检测算子检测棋盘格，并与上述结果比较。

解题提示
1. 参考CSDN相关文章。
2. 角点检测利用Feature2D类。

*/

// D:\ThirdParty\opencv\build\include
// D:\ThirdParty\opencv\build\x64\vc15\lib
// opencv_world344d.lib


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
	Mat img = imread("./Lena.png");
	
	//blurTest(img);
	//testSobel(img, 1);
	testCanny(img, 1);

	return 0;
}