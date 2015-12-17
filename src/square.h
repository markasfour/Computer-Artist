#ifndef SQUARE_H 
#define SQUARE_H

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct my_square
{
	Point pos;
	Size size;
	Scalar color;

	my_square()
	{
		pos = Point(0, 0);
		size = Size(0, 0);
		color = Scalar(0, 0, 0);
	}
	my_square(Point x)
	{
		pos = x;
		int temp = rand()%100+20;
		size = Size(temp, temp);
		color = Scalar(rand()%255,rand()%255,rand()%255);
	}

	void mutate()
	{
		pos += Point(rand()%15-15/2,rand()%15-15/2) ; 
		color += Scalar(rand()%50-50/2,rand()%50-50/2,rand()%50-50/2);
		int temp = rand()%15-15/2;
		size += Size(temp, temp);
		size.width = abs(size.width) ;
		size.height = abs(size.height) ;
	}
};

#endif
