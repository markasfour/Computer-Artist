#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct my_rectangle
{
	Point pos;
	Size size;
	Scalar color;

	my_rectangle()
	{
		pos = Point(0, 0);
		size = Size(0, 0);
		color = Scalar(0, 0, 0);
	}
	my_rectangle(Point x)
	{
		pos = x;
		size = Size(rand()%100+20, rand()%100+20);
		color = Scalar(rand()%255,rand()%255,rand()%255);
	}

	void mutate()
	{
		pos += Point(rand()%15-15/2,rand()%15-15/2) ; 
		color += Scalar(rand()%50-50/2,rand()%50-50/2,rand()%50-50/2) ;
		size += Size(rand()%15-15/2,rand()%15-15/2) ;
		size.width = abs(size.width) ;
		size.height = abs(size.height) ;

	}
};

#endif
