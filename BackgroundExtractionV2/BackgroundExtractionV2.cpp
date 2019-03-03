/*
1. ʵ��������
2. ʵ�ֹ켣����(ʶ���˶������·��)
3. ��ǰ��Ŀ����з���(Ŀ��ʶ�������)
4. ����Ч��(������Ӱ/Ŀ��ճ��)

	δ���
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
	//ͼ��ָ�
	vector<vector<Point>> cnts;
	findContours(maskFrame, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (int i = cnts.size() - 1; i >= 0; i--)
	{
		// ����
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
		cout << "����Ƶʧ��" << endl;
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
		//fgMask: an 8-bit binary image,�Ҷ�ͼ��
		pBackSub->apply(frame, fgMask);
		
		//adaptiveThreshold(fgMask, fgMask, 255, THRESH_BINARY);
		//imshow("test", fgMask);

		// ��Ƶ�л�ȡ��ǰ��������ںܶཷ�β���
		// ʹ����ֵ�˲���һ��
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