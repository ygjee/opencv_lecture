#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)		// Lecture 3, 4번
{
	namedWindow("show1", 0);
	namedWindow("threshold", 0);
	namedWindow("contours", 0);

	Mat img;
	img = imread("E:\\999_Work\\up.jpg");

	cvtColor(img, img, CV_RGB2GRAY);

	imshow("show1", img);

	threshold(img, img, 128, 255, CV_THRESH_BINARY);
	imshow("threshold", img);

	Mat dst = Mat::zeros(img.rows, img.cols, CV_8UC3);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(img.clone(), contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

//	drawContours(dst, contours, -1, CV_RGB(255, 0, 0), 1, 8, hierarchy);

	//int idx = 0;
	//for (; idx >= 0; idx = hierarchy[idx][0])
	//{
	//	Scalar color(rand() & 255, rand() & 255, rand() & 255);
	//	drawContours(dst, contours, idx, color, 1, 8, hierarchy);
	//}

	//for (int i = 0; i < contours.size(); i++)
	//{
	//	Scalar color(rand() & 255, rand() & 255, rand() & 255);
	//	for (int j = 0; j < contours[i].size() - 1; j++)
	//		line(dst, contours[i][j], contours[i][j + 1], color, 1);

	//	line(dst, contours[i][0], contours[i][contours[i].size() - 1], color, 1);
	//}

	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		
		drawContours(dst, contours, i, color, 1, 8, hierarchy);
	}

	imshow("contours", dst);

	waitKey(0);

	return 0;
}
