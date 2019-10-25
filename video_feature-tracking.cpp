
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

void draw_rect(Mat& img, vector<Rect>& v_rect)
{
	for (auto it : v_rect)
	{
		rectangle(img, it, CV_RGB(255, 0, 0), 2);
	}
}

int main(int, char)
{
	int TH1 = 100;
	int TH_WIDTH, TH_HEIGHT, TH_AREA;
	float detection_ratio = 0.05;
	float detection_area = 0.001;

	Mat frame, frame_binary;
	Mat old_frame, bg_frame_binary;
	Mat sub_frame;
	Mat result;

	VideoCapture stream1(0);

	if (!stream1.isOpened())
		cout << "cannot open camera 0";

	int count = 0;
	int SKIP = 20;

	while (1)
	{
		if (!(stream1.read(frame)))
			break;

		count++;
		if (count < SKIP)
		{
			printf("skip %d\n", count);
			continue;
		}

		if (old_frame.empty())
		{
			old_frame = frame.clone();
			cvtColor(old_frame, bg_frame_binary, COLOR_BGR2GRAY);
			TH_WIDTH = int(old_frame.cols * detection_ratio);
			TH_HEIGHT = int(old_frame.rows * detection_ratio);
			TH_AREA = int((old_frame.cols * old_frame.rows) * detection_area);

			continue;
		}

		cvtColor(frame, frame_binary, COLOR_BGR2GRAY);
		//subtract(old_frame, frame, sub_frame);
		absdiff(bg_frame_binary, frame_binary, sub_frame);
		threshold(sub_frame, sub_frame, TH1, 255, THRESH_BINARY);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(sub_frame.clone(), contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
		//drawContours(frame, contours, -1, CV_RGB(255, 0, 0), 5, 8, hierarchy);

		vector<Rect> v_rect;
		for (auto it : contours)
		{
			Rect mr = boundingRect(Mat(it));
			//if (mr.width > TH_WIDTH || mr.height > TH_HEIGHT)
			//	v_rect.push_back(mr);

			double area = contourArea(it, false);
			if (area > TH_AREA)
			{
				v_rect.push_back(mr);
			}
		}

		draw_rect(frame, v_rect);

		hconcat(frame_binary, sub_frame, result);
		imshow("frame", result);
		imshow("contours", frame);

		//old_frame = frame.clone();

		if (waitKey(5) >= 0)
			break;
	}
	
	return 0;
}

