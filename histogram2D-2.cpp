
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	Mat srcA = Mat(500, 500, CV_8UC1);
	randn(srcA, 128, 20);

	Mat srcB = Mat(500, 500, CV_8UC1);
	randn(srcB, 128, 50);

	int aBin = 50, bBin = 50;
	int histSize[] = { aBin, bBin };
	float aranges[] = { 0, 256 };
	float branges[] = { 0, 256 };
	const float* ranges[] = { aranges, branges };

	MatND hist;
	int channels[] = { 0, 1 };

	Mat mat2ch[2];
	mat2ch[0] = srcA;
	mat2ch[1] = srcB;

	calcHist(mat2ch, 2, channels, Mat(), hist, 2, histSize, ranges, true, false);
	double maxVal = 0;
	minMaxLoc(hist, 0, &maxVal, 0, 0);

	int scale = 10;
	Mat histImg = Mat::zeros(aBin * scale, bBin * scale, CV_8UC3);

	for (int h = 0; h < aBin; h++)
	{
		for (int s = 0; s < bBin; s++)
		{
			float binVal = hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(histImg, Point(h * scale, s * scale),
				Point((h + 1) * scale - 1, (s + 1) * scale - 1),
				Scalar::all(intensity), CV_FILLED);
		}
	}

	namedWindow("SourceA", 0);
	imshow("SourceA", srcA);
	namedWindow("SourceB", 0);
	imshow("SourceB", srcB);

	namedWindow("H-S Histogram", 1);
	imshow("H-S Histogram", histImg);
	
	waitKey(0);
	
	return 0;
}

