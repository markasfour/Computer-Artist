#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct my_rectangle
{
	Point p1;
	Point p2;
	Scalar color;

	my_rectangle()
	{
		p1 = Point(0, 0);
		p2 = Point(0, 0);
		color = Scalar(0, 0, 0);
	}
	my_rectangle(Point a, Point b, Scalar c)
	{
		p1 = a;
		p2 = b; 
		color = c;
	}
	my_rectangle(Point a, int w, int l)
	{
		p1 = a;
		int x = -1;
		while (x <= a.x)
			x = rand() % int(1.5 * l);
		int y = -1;
		while (x <= a.y)
			y = rand() % int(1.5 * w);
		p2 = Point(x, y);
		color = Scalar(rand()%255,rand()%255,rand()%255);
	}
};

#endif
