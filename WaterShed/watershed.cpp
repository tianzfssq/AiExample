#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "watershed_opencv.h"


using namespace std;
using namespace cv;


// 参考： 
// https://blog.csdn.net/Dangkie/article/details/77806211


Vec3b RandomColor(int val)
{
	val = val % 255;
	RNG rng;
	int a = rng.uniform(0, val);
	int b = rng.uniform(0, val);
	int c = rng.uniform(0, val);

	return Vec3b(a, b, c);
}


int main(int argc, char* argv[])
{
	watershedTest("../Pics/test.png");
	//Mat img = imread("../Pics/test.png"); 
	//imshow("Source Image", img);

	//Mat imgRst;
	//// 转灰度图
	//cvtColor(img, imgRst, CV_BGR2GRAY);
	//// 高斯滤波
	//GaussianBlur(imgRst, imgRst, Size(5,5), 2);
	//// Canny边缘检测
	//Canny(imgRst, imgRst, 80, 150);
	//imshow("效果图", imgRst);
	//waitKey(0);


	//// 查找轮廓
	//vector<vector<Point>> contours;
	//vector<Vec4i> hierarchy;

	//findContours(imgRst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());

	//// 其他使用例子：
	//// 建一个5*5的2维矩阵，数据类型为8bit的无符号数，数据为3个通道，初始值都为(0,0,255)
	//// cv::Mat M(5, 5, CV_8UC3, cv::Scalar(0, 0, 255));
	//// cout << "M = " << endl << " " << imgContours << endl << endl;
	//
	//// 创建一个与图像一样大图像，采用8位1通道，每位都是0；
	//Mat imgContours = Mat::zeros(img.size(), CV_8UC1);

	//// 这里为什么用 CV_32S
	//
	//// 创建一个与图像一样大图像，采用32位单通道，每位都是0，可添加第四个参数赋值为0实现；
	//Mat marks(5,5, CV_32S);
	//marks = Scalar::all(0);

	//int index = 0;
	//int compCount = 0;

	//for (; index >=0; index = hierarchy[index][0], compCount++ )
	//{
	//	drawContours(marks, contours, index, Scalar::all(compCount+1), 1, 8, hierarchy);
	//	drawContours(imgContours, contours, index, Scalar(255), 1, 8, hierarchy);
	//}



	//Mat marksMat;
	//convertScaleAbs(marks, marksMat);
	////imshow("marks Show", marksMat);
	//imshow("轮廓", imgContours);
	//waitKey(0);


	//watershed(imgRst, marks);
	//Mat afterWatershedMat;
	//convertScaleAbs(marks, afterWatershedMat);
	//imshow("After Watershed", afterWatershedMat);

	//waitKey(0);
}