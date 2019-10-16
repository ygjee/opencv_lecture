
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
	cuda::add(gimg, Scalar(0, 0, 100), gout1);
	gout1.download(img_add);
	BBtime = getTickCount();
	printf("cuda add %.3lf sec \n", (BBtime - AAtime) / getTickFrequency());

	putText(img, "Source", Point(20, 30), 2, 1, Scalar(255, 0, 0));
	putText(img_add, "Result", Point(20, 30), 2, 1, Scalar(0, 0, 255));

	hconcat(img, img_add, img_result);

	imshow("img", img_result);
	waitKey(0);

	return 0;
}
