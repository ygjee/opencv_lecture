
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	Mat img = imread("E:\\999_Work\\수지.jpg");

	Mat gray_img;
	cvtColor(img, gray_img, CV_RGB2GRAY);
	int width = img.cols;
	int height = img.rows;
	const int bufferSize = 256;

	unsigned int Histogram_buffer[bufferSize];
	memset(Histogram_buffer, 0, sizeof(unsigned int) * bufferSize);

	int maxValue = 0;
	for (int i = 0; i < gray_img.rows; ++i)
	{
		for (int j = 0; j < gray_img.cols; ++j)
		{
			unsigned char v = gray_img.at<unsigned char>(i, j);
			Histogram_buffer[v]++;

			if (maxValue < Histogram_buffer[v])
				maxValue = Histogram_buffer[v];
		}
	}

	Mat histo = Mat::zeros(Size(bufferSize, maxValue + 1), CV_8U);

	for (int i = 0; i < bufferSize; ++i)
	{
		for (int j = 0; j < Histogram_buffer[i]; ++j)
		{
			histo.at<unsigned char>(maxValue - j, i) = 255;
		}
	}

	//for (int i = 1; i < bufferSize; ++i)
	//{
	//	int y1 = maxValue - Histogram_buffer[i - 1];
	//	int x1 = i - 1;
	//	int y2 = maxValue - Histogram_buffer[i];
	//	int x2 = i;
	//	line(histo, Point(x1, y1), Point(x2, y2), CV_RGB(255, 255, 255), 1);
	//}

	namedWindow("histo", 0);
	imshow("histo", histo);

	imshow("img", img);
	imshow("gray_img", gray_img);

	waitKey(0);
	
	return 0;
}

