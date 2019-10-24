
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	Mat img = imread("E:\\999_Work\\goonies.jpg");
//	imshow("img", img);
	Mat gray_img;
	cvtColor(img, gray_img, CV_BGR2GRAY);

	int hbins = 255;

	int channels[] = { 0 };
	int histSize[] = { hbins };
	float hranges[] = { 0, 255 };
	const float* ranges[] = { hranges };

	MatND HistB, HistG, HistR;
	vector<Mat> bgr_planes;
	split(img, bgr_planes);

	calcHist(&bgr_planes[0], 1, 0, Mat(), HistB, 1, histSize, ranges, true, false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), HistG, 1, histSize, ranges, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), HistR, 1, histSize, ranges, true, false);

	normalize(HistB, HistB, 0, 255, CV_MINMAX);
	normalize(HistG, HistG, 0, 255, CV_MINMAX);
	normalize(HistR, HistR, 0, 255, CV_MINMAX);

	int hist_w = 500;
	int hist_h = 255;
	int ratio = cvRound((double)hist_w / hbins);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	int x1, y1;
	int x2, y2;
	for (int i = 1; i < hbins; i++)
	{
		x1 = ratio * (i - 1);
		y1 = hist_h - cvRound(HistB.at<float>(i - 1));
		x2 = ratio * (i);
		y2 = hist_h - cvRound(HistB.at<float>(i));
		line(histImage, Point(x1, y1), Point(x2, y2),
			Scalar(0, 0, 255), 2, 8, 0);

		y1 = hist_h - cvRound(HistG.at<float>(i - 1));
		y2 = hist_h - cvRound(HistG.at<float>(i));
		line(histImage, Point(x1, y1), Point(x2, y2),
			Scalar(0, 255, 0), 2, 8, 0);

		y1 = hist_h - cvRound(HistR.at<float>(i - 1));
		y2 = hist_h - cvRound(HistR.at<float>(i));
		line(histImage, Point(x1, y1), Point(x2, y2),
			Scalar(255, 0, 0), 2, 8, 0);
	}

	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);

	waitKey(0);
	
	return 0;
}

