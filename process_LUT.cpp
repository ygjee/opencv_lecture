
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int lookupEx()
{
	unsigned long AAtime = 0, BBtime = 0;
	unsigned char O[1000][1000] = { 1, 2, };

	AAtime = getTickCount();
	for (int i = 0; i < 1000; ++i)
	{
		for (int j = 0; j < 1000; ++j)
		{
			int t = O[i][j] * 1.14;
			t = (t > 255) ? 255 : t;
			O[i][j] = t;
		}
	}
	BBtime = getTickCount();
	printf("just loop %.5lf sec \n", (BBtime - AAtime) / getTickFrequency());

	// fase
	unsigned char LUT[256];

	AAtime = getTickCount();
	for (int i = 0; i < 255; ++i)
	{
		int t = i * 1.14;
		t = (t > 255) ? 255 : t;
		LUT[i] = t;
	}

	for (int i = 0; i < 1000; ++i)
	{
		for (int j = 0; j < 1000; ++j)
		{
			O[i][j] = LUT[O[i][j]];
		}
	}
	BBtime = getTickCount();
	printf("using lut %.5lf sec \n", (BBtime - AAtime) / getTickFrequency());

	return 0;
}

int LUTexample()
{
	Mat img = imread("E:\\999_Work\\수지.jpg");

	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	int factor = 256 / 10;
	for (int i = 0; i < 256; ++i)
	{
		p[i] = factor * (i / factor);
		//printf("[%d] = %d \n", i, p[i]);
	}

	Mat reduced;
	LUT(img, lookUpTable, reduced);

	namedWindow("img", 0);
	imshow("img", img);
	namedWindow("reduced", 0);
	imshow("reduced", reduced);

	return 0;
}

int main(int, char)
{
	Mat img_result;
	namedWindow("img", 0);

	//Mat img = imread("E:\\999_Work\\수지.jpg");

	//Mat im_color;
	//applyColorMap(img, im_color, COLORMAP_AUTUMN);

	//Mat img_gray;
	//cvtColor(img, img_gray, CV_RGB2GRAY);
	//Mat im_color2;
	//applyColorMap(img_gray, im_color2, COLORMAP_AUTUMN);

	//hconcat(img, im_color, img_result);
	//hconcat(img_result, im_color2, img_result);

	//imshow("img", img_result);

	//Mat img2(100, 100, CV_8UC3);
	//img2.setTo(Scalar(0, 128, 255));
	//Mat im_color3;
	//applyColorMap(img2, im_color3, COLORMAP_JET);

	//Mat img2_gray;
	//cvtColor(img2, img2_gray, CV_BGR2GRAY);
	//Mat im_color4;
	//applyColorMap(img2, im_color4, COLORMAP_JET);

	//hconcat(img2, im_color3, img_result);
	//hconcat(img_result, im_color4, img_result);

	//imshow("img", img_result);

	LUTexample();

	waitKey(0);
	
	return 0;
}

