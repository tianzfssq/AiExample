/*
1. ��Ƶ�ɼ�(ȡ����Ƶ�е�ǰ֡ͼ��)
2. ͼ��Ԥ����
3. ������ȡ
4. ǰ���ָ�
5. ͼ������������Ŀ�����
6. �õ����ս��
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

		// ͼ��󣬴���̫������Сͼ����д����Լ��ٴ���ʱ��
		resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));

		//! [apply]
		//update the background model
		//fgMask: an 8-bit binary image,�Ҷ�ͼ��
		pBackSub->apply(frame, fgMask);
		//threshold(fgMask, fgMask, 30, 255, THRESH_BINARY);
		//imshow("test", fgMask);

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

		//! [display_frame_number]
		//get the frame number and write it on the current frame
		//rectangle(frame, cv::Point(10, 2), cv::Point(100, 20),
		//	cv::Scalar(255, 255, 255), -1);
		//stringstream ss;
		//ss << capture.get(CAP_PROP_POS_FRAMES);
		//string frameNumberString = ss.str();
		//putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
		//	FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
		//! [display_frame_number]

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