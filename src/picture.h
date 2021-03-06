#ifndef PICTURE_H
#define PICTURE_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "square.h"
#include "rectangle.h"
#include "circle.h"
#include "ellipse.h"

using namespace std;
using namespace cv;

struct picture
{
	Mat img;
	float fitness;
	vector <my_square> squares;
	vector <my_rectangle> rectangles;
	vector <my_circle> circles;
	vector <my_ellipse> ellipses;

	picture()
	{
		Mat i(0, 0, CV_8UC3, Scalar(0, 0, 0));
		img = i;
		fitness = -1;
	};
	picture(Mat i, float f, vector <my_square> s)
	{
		img = i;
		fitness = f;
		squares = s;
	}
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
	picture(Mat i, float f, vector <my_ellipse> e)
	{
		img = i;
		fitness = f;
		ellipses = e;
	}
};

#endif
