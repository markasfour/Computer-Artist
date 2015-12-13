#ifndef PICTURE_H
#define PICTURE_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "rectangle.h"
#include "circle.h"

using namespace std;
using namespace cv;

struct picture
{
	Mat img;
	float fitness;
	vector <my_rectangle> rectangles;
	vector <my_circle> circles;

	picture()
	{
		Mat i(0, 0, CV_8UC3, Scalar(0, 0, 0));
		img = i;
		fitness = -1;
	};
	picture(Mat i, float f, vector <my_rectangle> r)
	{
		img = i;
		fitness = f;
		rectangles = r;
	};
	picture(Mat i, float f, vector <my_circle> c)
	{
		img = i;
		fitness = f;
		circles = c;
	}
};

#endif
