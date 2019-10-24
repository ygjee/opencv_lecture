
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	Mat src = imread("E:\\999_Work\\goonies.jpg");
	Mat hsv;

	cvtColor(src, hsv, CV_BGR2HSV);

	int hbins = 30, sbins = 32;
	int histSize[] = { hbins, sbins };
	float hranges[] = { 0, 180 };
	float sranges[] = { 0, 256 };
	const float* ranges[] = { hranges, sranges };
	MatND hist;
	int channels[] = { 0, 1 };

	calcHist(&hsv, 1, channels, Mat(), hist, 2, histSize, ranges, true, false);
	double maxVal = 0;
	minMaxLoc(hist, 0, &maxVal, 0, 0);

	int scale = 10;
	Mat histImg = Mat::zeros(200, 320, CV_8UC3);

	for (int h = 0; h < hbins; h++)
	{
		for (int s = 0; s < sbins; s++)
		{
			float binVal = hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(histImg, Point(h * scale, s * scale),
				Point((h + 1) * scale - 1, (s + 1) * scale - 1),
				Scalar::all(intensity), CV_FILLED);
		}
	}

	namedWindow("Source", 0);
	imshow("Source", src);

	namedWindow("H-S Histogram", 1);
	imshow("H-S Histogram", histImg);
	
	waitKey(0);
	
	return 0;
}

