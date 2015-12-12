#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct my_rectangle
{
	Point position;
	Size size;
	Scalar color;
	float transparency;

	my_rectangle()
	{
		position = Point(0, 0);
		size = Size(0, 0);
		color = Scalar(0, 0, 0);
	}
	my_rectangle(Point p, Size s, Scalar c, float t)
	{
		position = p;
		size = s; 
		color = c;
		transparency = t;
	}
};

#endif
