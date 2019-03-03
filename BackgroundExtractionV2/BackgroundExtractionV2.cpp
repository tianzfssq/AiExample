/*
1. 实现区域检测
2. 实现轨迹分析(识别运动方向和路线)
3. 对前景目标进行分析(目标识别与分类)
4. 改善效果(减少阴影/目标粘连)

	未完成
*/

#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

void markTarget(Mat& srcFrame, Mat& maskFrame)
{
	//图像分割
	vector<vector<Point>> cnts;
	findContours(maskFrame, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (int i = cnts.size() - 1; i >= 0; i--)
	{
		// 过滤
		double area = contourArea(cnts[i]);
		if (area < 10)
		{
			continue;
		}

		vector<Point> &c = cnts[i];
		Rect rect = boundingRect(c);
		rectangle(srcFrame, rect, Scalar(0, 0, 0xff), 1);
	}
}

int main(int argc, char* argv[])
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

	Mat frame, fgMask, foreGround, backGround;
	while (true) {
		capture >> frame;
		if (frame.empty())
			break;

		resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));

		//! [apply]
		//update the background model
		//fgMask: an 8-bit binary image,灰度图像
		pBackSub->apply(frame, fgMask);
		
		//adaptiveThreshold(fgMask, fgMask, 255, THRESH_BINARY);
		//imshow("test", fgMask);

		// 视频中获取的前景掩码存在很多椒盐操作
		// 使用中值滤波滤一下
		medianBlur(fgMask, fgMask, 3);
		//! [apply]

		//! [foreGround]
		//  Greate ForeGround Frame
		if (foreGround.empty())
		{
			foreGround.create(frame.size(), frame.type());
		}
		foreGround = Scalar::all(0);
		frame.copyTo(foreGround, fgMask);
		//! [foreGround]

		pBackSub->getBackgroundImage(backGround);

		markTarget(frame, fgMask);


		//! [show]
		//show the current frame and the fg masks
		imshow("Frame", frame);
		imshow("FG Mask", fgMask);
		imshow("foreGround", foreGround);
		imshow("backGround", backGround);
		//! [show]

		//get the input from the keyboard
		int keyboard = waitKey(30);
		if (keyboard == 'q' || keyboard == 27)
			break;
	}

	return 0;
}