
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	Mat img = Mat(10, 10, CV_8UC1);
	randu(img, 0, 10);

	cout << "origin" << endl << img << endl;

	int x = 3, y = 4, w = 4, h = 4;

	int sum = 0;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			sum = sum + img.at<unsigned char>((y + j), (x + i));
		}
	}

	printf("for loop : sum = %d \n", sum);

	Mat integralImg;
	integral(img, integralImg, CV_64F);

	cout << endl << "integral" << endl << integralImg << endl;

	double p1 = integralImg.at<double>((y), (x));
	double p2 = integralImg.at<double>((y), (x + w));
	double p3 = integralImg.at<double>((y + h), (x));
	double p4 = integralImg.at<double>((y + h), (x + w));

	printf("\n p1:%lf, p2:%lf, p3:%lf, p4:%lf\n", p1, p2, p3, p4);
	printf("integral : sum = %lf \n", (p1 + p4) - (p2 + p3));

	imshow("img", 0);
	waitKey(0);
	
	return 0;
}

