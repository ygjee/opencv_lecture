
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	Mat img = imread("E:\\999_Work\\수지.jpg");
	namedWindow("img", 0);

	Mat noiseGray = img.clone();
	cvtColor(noiseGray, noiseGray, CV_RGB2GRAY);
	Mat Gaussian_noise = Mat(noiseGray.size(), noiseGray.type(), noiseGray.type());
	double mean = 0;
	double std = 30;
	randn(Gaussian_noise, mean, std);
	double minV, maxV;
	minMaxIdx(Gaussian_noise, &minV, &maxV);
	cout << "min : " << minV << " max : " << maxV << endl;

	threshold(Gaussian_noise, Gaussian_noise, (minV + maxV) / 2, 255, CV_THRESH_BINARY);

	noiseGray = noiseGray + Gaussian_noise;

	imshow("img", noiseGray);

	waitKey(0);

	return 0;
}

