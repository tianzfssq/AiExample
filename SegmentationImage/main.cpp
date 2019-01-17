#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

using namespace std;

using namespace cv;


// %THIRDPARTY%\opencv\build\include
// %THIRDPARTY%\opencv\build\x64\vc15\lib
// opencv_world344d.lib

//----------------大津算法-------------------
void showThreshold(Mat srcImg)
{
	Mat imgThreshold;
	/*
	src：源图像，可以为8位的灰度图，也可以为32位的彩色图像。（两者由区别）
	dst：输出图像
	thresh：阈值
	maxval：dst图像中最大值
	type：阈值类型，可以具体类型如下
	*/
	threshold(srcImg, imgThreshold, 100, 255, CV_THRESH_OTSU);
	imshow(string("imgThreshold"), imgThreshold);
}

// 区域生长
void showFloodFill(Mat srcImg, int iDiff = 100)
{
	Mat imgFloodFill;
	/*
	image    【输入/输出】 1或者3通道、 8bit或者浮点图像。仅当参数flags的FLOODFILL_MASK_ONLY标志位被设置时image不会被修改，否则会被修改。
	mask     【输入/输出】 操作掩码，必须为单通道、8bit，且比image宽2个像素、高2个像素。使用前必须先初始化。
	          Flood-filling无法跨越mask中的非0像素。例如，一个边缘检测的结果可以作为mask来阻止边缘填充。
			  在输出中，mask中与image中填充像素对应的像素点被设置为1，或者flags标志位中设置的值(详见flags标志位的解释)。
			  此外，该函数还用1填充了mask的边缘来简化内部处理。因此，可以在多个调用中使用同一mask，以确保填充区域不会重叠。
	seedPoint 起始像素点
	newVal    重绘像素区域的新的填充值(颜色)
	rect      可选输出参数，返回重绘区域的最小绑定矩形。
	loDiff    当前选定像素与其连通区中相邻像素中的一个像素，或者与加入该连通区的一个seedPoint像素，二者之间的最大下行差异值。
	upDiff    当前选定像素与其连通区中相邻像素中的一个像素，或者与加入该连通区的一个seedPoint像素，二者之间的最大上行差异值。
	flags     flags标志位是一个32bit的int类型数据，其由3部分组成： 0-7bit表示邻接性(4邻接、8邻接)；8-15bit表示mask的填充颜色；16-31bit表示填充模式（详见填充模式解释）
	*/
	
	Rect ccomp;
	//floodFill(srcImg, Point(10, 10), Scalar(92, 2, 79), 
	//		  &ccomp, Scalar(iDiff, iDiff, iDiff), Scalar(iDiff, iDiff, iDiff), 8);

	floodFill(srcImg, Point(10, 10), Scalar(92, 2, 79));

	imshow(string("imgFloodFill"), srcImg);
}

void showImage(const String& filename)
{
	//读取本地的一张图片便显示出来
	Mat img = imread(filename);
	imshow("Source Image", img);

	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);

	showThreshold(gray);
	//showFloodFill(gray);
}

int main()
{
	//showImage("./Pic2.png");

	//读取本地的一张图片便显示出来
	//Mat img = imread("./Pic2.png");
	//imshow("Source Image", img);

	//Mat gray;
	//cvtColor(img, gray, CV_BGR2GRAY);
	//showThreshold(gray);
	//
	//showFloodFill(img);

	//waitKey(0);

	//showImage("./Pic6.png");
	Mat img = imread("./Pic6.png");
	imshow("Source Image", img);

	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);
	showThreshold(gray);

	showFloodFill(img);

	waitKey(0);
	return 0;
}