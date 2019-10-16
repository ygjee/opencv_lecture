
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	float AAtime = 0, BBtime = 0;

	Mat img = imread("E:\\999_Work\\수지.jpg");
	Mat img_add;
	Mat img_result(img.size(), CV_8UC3);

	namedWindow("img", 0);

	AAtime = getTickCount();
	add(img, Scalar(100, 100, 100), img_add);
	BBtime = getTickCount();
	printf("cpu add %.3lf sec \n", (BBtime - AAtime) / getTickFrequency());
	//img_add = img + Scalar(0, 0, 100);

	cuda::GpuMat gimg;
	cuda::GpuMat gout1, gout2;

	AAtime = getTickCount();
	gimg.upload(img);
	cuda::add(gimg, Scalar(100, 100, 100), gout1);
	gout1.download(img_add);
	BBtime = getTickCount();
	printf("cuda add %.3lf sec \n", (BBtime - AAtime) / getTickFrequency());

	Mat img_subtract;
	//subtract(img, Scalar(100, 100, 100), img_subtract);
	//img_subtract = img - Scalar(100, 100, 100);
	cuda::subtract(gimg, Scalar(100, 100, 100), gout1);
	gout1.download(img_subtract);

	Mat img_mul, img_div;
	multiply(img, 5, img_mul);
	divide(img, 5, img_div);
	//img_mul = img * 5;
	//img_div = img / 5;
	//cuda::multiply(gimg, 5, gout1);
	//cuda::divide(gimg, 5, gout2);
	//gout1.download(img_mul);
	//gout2.download(img_div);

	Mat img_absdiff;
	absdiff(img, Scalar(255, 255, 255), img_absdiff);

	putText(img, "Source", Point(20, 30), 1, 1, Scalar(255, 0, 0));
	putText(img_add, "Result - add", Point(20, 30), 1, 1, Scalar(0, 0, 255));
	putText(img_subtract, "Result - subtract", Point(20, 30), 1, 1, Scalar(0, 0, 255));
	putText(img_mul, "Result - img_mul", Point(20, 30), 1, 1, Scalar(0, 0, 255));
	putText(img_div, "Result - img_div", Point(20, 30), 1, 1, Scalar(0, 0, 255));
	putText(img_absdiff, "Result - img_absdiff", Point(20, 30), 1, 1, Scalar(0, 0, 255));

	hconcat(img, img_add, img_result);
	hconcat(img_result, img_subtract, img_result);
	hconcat(img_result, img_mul, img_result);
	hconcat(img_result, img_div, img_result);
	hconcat(img_result, img_absdiff, img_result);

	imshow("img", img_result);
	waitKey(0);

	return 0;
}
