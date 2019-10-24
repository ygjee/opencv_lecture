
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
	float hranges[] = { 0, 180 };
	const float* ranges[] = { hranges };

	Mat patch_HSV;
	MatND HistA, HistB;

	cvtColor(img, patch_HSV, CV_BGR2HSV);

	calcHist(&patch_HSV, 1, channels, Mat(), HistA, 1, histSize, ranges, true, false);
	normalize(HistA, HistA, 0, 255, CV_MINMAX);

	Mat histimg = Mat::zeros(200, 320, CV_8UC3);
	int binW = histimg.cols / hbins;

	Mat buf(1, hbins, CV_8UC3);

	for (int i = 0; i < hbins; i++)
		buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i * 180. / hbins), 255, 255);
	cvtColor(buf, buf, CV_HSV2BGR);

	for (int i = 0; i < hbins; i++)
	{
		int val = HistA.at<float>(i) * histimg.rows / 255;
		rectangle(histimg, Point(i * binW, histimg.rows), 
			Point((i + 1) * binW, histimg.rows - val), 
			Scalar(buf.at<Vec3b>(i)), -1, 8);

			int r, g, b;
			b = buf.at<Vec3b>(i)[0];
			g = buf.at<Vec3b>(i)[1];
			r = buf.at<Vec3b>(i)[2];

			printf("[%d] r=%d, g=%d, b=%d, bins = %d \n", i, r, g, b, val);
	}

	namedWindow("Hist", 0);
	imshow("Hist", histimg);

	waitKey(0);
	
	return 0;
}

