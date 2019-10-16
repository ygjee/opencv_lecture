#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	Mat img = imread("E:\\999_Work\\up.jpg");
	Mat img2 = img.clone();

	//bitwise_not(img, img);


	Rect r(img.cols / 4, img.rows / 4, img.cols / 4 * 2, img.rows / 4 * 2);
	cout << r << endl;

	Mat img5 = img(r).clone();

	Mat cimg;
	img.copyTo(cimg);

	Mat cimg2;
	img(r).copyTo(cimg2);
	
	Mat cimg3(Size(img.cols * 2, img.rows), img.type());
	cimg3.setTo(255);
	img.copyTo(cimg3(Range::all(), Range(0, img.cols)));
	bitwise_not(img2, img2);
	img2.copyTo(cimg3(Range::all(), Range(img2.cols, img2.cols * 2)));

	Mat roi(img, r);
	bitwise_not(roi, roi);

	imshow("img", img);
	//imshow("img2", img2);
	//imshow("img5", img5);
	//imshow("cimg", cimg);
	imshow("cimg2", cimg2);
	imshow("cimg3", cimg3);
	imshow("roi", roi);


	waitKey(0);

	return 0;
}
