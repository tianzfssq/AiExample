/*
1. 视频采集(取到视频中当前帧图像)
2. 图像预处理
3. 提取特征点
4. 使用光流法估计特征点运动
5. 相邻帧及特征点交换
*/
#include <iostream>
#include <sstream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

const int MAX_POINT_COUNT = 200;

int main()
{
	//! [create]
	//create Background Subtractor objects
	Ptr<BackgroundSubtractor> pBackSub = createBackgroundSubtractorMOG2();
	//! [create]

	//! [capture]
	VideoCapture capture("../Pics/vtest.avi");
	if (!capture.isOpened())
	{
		cout << "打开视频失败" << endl;
	}
	//! [capture]

	Mat curFrame, prevFrame, curGray, prevGray, result;
	vector<Point2f> curPoint2f, prevPoint2f;
	vector<uchar> status;
	vector<float> err;

	bool bFirst = true;

	while (true) 
	{
		//prevFrame = curFrame.clone();
		//prevGray = curGray.clone();
		//prevPoint2f = curPoint2f;
		//curPoint2f.clear();

		capture >> curFrame;
		if (curFrame.empty())
		{
			break;
		}
		cvtColor(curFrame, curGray, COLOR_BGR2GRAY);
			

		if (curPoint2f.empty() < 10)
		{
			//开始进行强角点检测
			//先配置需要的函数参数
			goodFeaturesToTrack(curGray, curPoint2f, MAX_POINT_COUNT, 0.01, 10);
		}

		if (prevGray.empty())
		{
			prevGray = curGray.clone();
		}

		if (prevPoint2f.empty() && !curPoint2f.empty())
		{
			prevPoint2f = curPoint2f;
		}

		/*
		InputArray prevImg, InputArray nextImg,
		InputArray prevPts, InputOutputArray nextPts,
		OutputArray status, OutputArray err,
		Size winSize = Size(21,21), int maxLevel = 3,
		TermCriteria criteria = TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, 0.01),
		int flags = 0, double minEigThreshold = 1e-4
		*/
		// 光流金字塔
		calcOpticalFlowPyrLK(prevGray, curGray, prevPoint2f, curPoint2f, status, err);

		//! [删除误判点]
		int counter = 0;
		for (int i = 0; i < prevPoint2f.size(); i++)
		{
			double dist = norm(prevPoint2f[i] - curPoint2f[i]);

			if (status[i] && dist >= 2 && dist <= 20)
			{
				curPoint2f[counter] = curPoint2f[i];
				prevPoint2f[counter++] = prevPoint2f[i];
			}
		}

		cout << "counter : " << counter << endl;
		curPoint2f.resize(counter);
		prevPoint2f.resize(counter);
		//! [删除误判点]

		curFrame.copyTo(result);

		for (int i = 0; i < prevPoint2f.size(); i++)
		{
			line(result, curPoint2f[i], prevPoint2f[i], Scalar(0,0,255));
			circle(result, prevPoint2f[i], 3, Scalar(0, 255, 0));
		}

		swap(curPoint2f, prevPoint2f);
		swap(curGray, prevGray);

		//imshow("src", curFrame);
		imshow("dst", result);

		int keyboard = waitKey(30);
		if (keyboard == 'q' || keyboard == 27)
			break;
	}

}