
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	Mat img = imread("E:\\999_Work\\스포츠카.jpg");
	Mat img2 = imread("E:\\999_Work\\전투기.jpg");
	Mat img_add, img_sub, img_mul, img_div, img_wadd;
	Mat img_result(img.size(), CV_8UC3);

	namedWindow("img", 0);

	resize(img2, img2, Size(img.size().width, img.size().height));
	//add(img, img2, img_add);
	img_add = img + img2;

	subtract(img, img2, img_sub);
	multiply(img, img2, img_mul);
	divide(img, img2, img_div);

	double alpha = 0.5;
	double beta;
	double input;

	cout << "Enter a real number between 0 and 1 : ";
	cin >> input;

	if (input < 0.0)	input = 0;
	else if (input > 1.0) input = 1.0;

	alpha = input;
	beta = (1.0 - alpha);

	addWeighted(img, alpha, img2, beta, 0.0, img_wadd);

	putText(img, "Source1", Point(20, 30), 1, 1, Scalar(255, 0, 0));
	putText(img2, "Source2", Point(20, 30), 1, 1, Scalar(255, 0, 0));
	putText(img_add, "Result - add", Point(20, 30), 1, 1, Scalar(0, 0, 255));
	putText(img_sub, "Result - sub", Point(20, 30), 1, 1, Scalar(0, 0, 255));
	putText(img_mul, "Result - mul", Point(20, 30), 1, 1, Scalar(0, 0, 255));
	putText(img_div, "Result - div", Point(20, 30), 1, 1, Scalar(0, 0, 255));
	putText(img_wadd, "Result - wadd", Point(20, 30), 1, 1, Scalar(0, 0, 255));

	hconcat(img, img2, img_result);
	hconcat(img_result, img_add, img_result);
	hconcat(img_result, img_sub, img_result);
	hconcat(img_result, img_mul, img_result);
	hconcat(img_result, img_div, img_result);
	hconcat(img_result, img_wadd, img_result);

	imshow("img", img_result);

	for(float w = 0; w < 1; w += 0.1)
	{
		alpha = 1.0 - w;
		beta = (1.0 - alpha);

		addWeighted(img, alpha, img2, beta, 0.0, img_wadd);
		imshow("img_wadd", img_wadd);

		waitKey(500);
	}

	waitKey(0);

	return 0;
}

