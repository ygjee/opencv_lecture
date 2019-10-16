#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)	// Lecture - 2강 5번
{
	namedWindow("img", 1);
	Mat img = imread("E:\\999_Work\\up.jpg");
	
	Rect r;
	
	r = Rect(50, 50, 50, 50);
	for (int i = r.y; i < r.y + 50; i++)
	{
		for (int j = r.x; j < r.x + 50; j++)
		{
			unsigned char r, g, b;
			b = img.data[i * img.step + j * img.elemSize() + 0];
			g = img.data[i * img.step + j * img.elemSize() + 1];
			r = img.data[i * img.step + j * img.elemSize() + 2];

			img.data[i * img.step + j * img.elemSize() + 0] = unsigned char(255 - b);
			img.data[i * img.step + j * img.elemSize() + 1] = unsigned char(255 - g);
			img.data[i * img.step + j * img.elemSize() + 2] = unsigned char(255 - r);
		}
	}

	r = Rect(150, 150, 50, 50);
	for (int i = r.y; i < r.y + 50; i++)
	{
		for (int j = r.x; j < r.x + 50; j++)
		{
			unsigned char b = img.at<cv::Vec3b>(i, j)[0];
			unsigned char g = img.at<cv::Vec3b>(i, j)[1];
			unsigned char r = img.at<cv::Vec3b>(i, j)[2];

			img.at<cv::Vec3b>(i, j)[0] = unsigned char(255 - b);
			img.at<cv::Vec3b>(i, j)[1] = unsigned char(255 - g);
			img.at<cv::Vec3b>(i, j)[2] = unsigned char(255 - r);
		}
	}

	r = Rect(50, 250, 50, 50);
	for (int i = r.y; i < r.y + 50; i++)
	{
		Vec3b* ptr = img.ptr<Vec3b>(i);

		for (int j = r.x; j < r.x + 50; j++)
		{
			unsigned char b1 = (ptr[j][0]);
			unsigned char g1 = (ptr[j][1]);
			unsigned char r1 = (ptr[j][2]);

			Vec3b bgr = ptr[j];
			unsigned char b2 = (bgr[0]);
			unsigned char g2 = (bgr[1]);
			unsigned char r2 = (bgr[2]);

			ptr[j] = Vec3b(255 - b1, 255 - g1, 255 - r1);
		}
	}

	r = Rect(250, 250, 50, 50);
	MatIterator_<Vec3b> itd;
	for (int i = r.y; i < r.y + 50; i++)
	{
		for (int j = r.x; j < r.x + 50; j++)
		{
			itd = img.begin<Vec3b>() + (i * img.step / img.elemSize()) + j;

			Vec3b bgr = (*itd);

			(*itd)[0] = 255 - bgr[0];
			(*itd)[1] = 255 - bgr[1];
			(*itd)[2] = 255 - bgr[2];
		}
	}

	imshow("img", img);

	waitKey(0);

	return 0;
}

