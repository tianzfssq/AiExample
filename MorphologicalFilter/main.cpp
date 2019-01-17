#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

// D:\ThirdParty\opencv\build\include
// D:\ThirdParty\opencv\build\x64\vc15\lib
// opencv_world344d.lib

Mat g_srcImage, g_dstImage;     //原始图和效果图
int g_nTrackbarNumer = 0;       //0表示腐蚀，1表示膨胀
int g_nSructElementSize = 3;    //结构元素（内核矩阵）尺寸


void Process();                 //腐蚀和膨胀的处理函数
void on_TrackbarNumChange(int, void *); //回调函数
void on_ElementSizeChange(int, void *); //回调函数

int main()
{
	system("color 5E");

	//载入原图
	g_srcImage = imread("../Pics/Lena.png");
	if (!g_srcImage.data)
	{
		printf("读取srcImage错误~!\n");
		return false;
	}

	//显示原图
	namedWindow("【原始图】");
	imshow("【原始图】", g_srcImage);

	//进行腐蚀和膨胀操作并显示效果图
	namedWindow("【效果图】");

	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nSructElementSize + 1, 2 * g_nSructElementSize + 1), Point(g_nSructElementSize, g_nSructElementSize));
	erode(g_srcImage, g_dstImage, element);
	imshow("【效果图】", g_dstImage);

	//创建轨迹条
	createTrackbar("腐蚀/膨胀", "【效果图】", &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("内核尺寸", "【效果图】", &g_nSructElementSize, 21, on_ElementSizeChange);

	//按键q退出
	while (char(waitKey(1)) != 'q') {}
	return 0;
}

//  描述：进行自定义的腐蚀核膨胀操作
void Process()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nSructElementSize + 1, 2 * g_nSructElementSize + 1), Point(g_nSructElementSize, g_nSructElementSize));

	if (g_nTrackbarNumer == 0)
	{
		erode(g_srcImage, g_dstImage, element);
	}
	else
	{
		dilate(g_srcImage, g_dstImage, element);
	}

	//显示效果图
	imshow("【效果图】", g_dstImage);
}

//  描述：腐蚀核膨胀之间切换开关回调函数
void on_TrackbarNumChange(int, void *)
{
	Process();
}


//  描述：腐蚀核膨胀内核改变回调函数
void on_ElementSizeChange(int, void *)
{
	Process();
}