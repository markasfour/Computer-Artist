#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "rectangle.h"
#include "picture.h"

using namespace std;
using namespace cv;

const int POPULATION = 5;

float getFitness (picture curr, Mat mainImage)
{
	float f = 0.0;
	for (int x = 0; x < curr.img.rows; x++)
	{
		for (int y = 0; y < curr.img.cols; y++)
		{
			Vec3b bgrMainPic = mainImage.at<Vec3b>(x, y);
			Vec3b bgrCurrPic = curr.img.at<Vec3b>(x, y);
			
			f += abs(bgrCurrPic.val[0] - bgrMainPic.val[0]);	//b
			f += abs(bgrCurrPic.val[1] - bgrMainPic.val[1]);	//g
			f += abs(bgrCurrPic.val[2] - bgrMainPic.val[2]);	//r
		}
	}
	return 100 - (f / (curr.img.rows * curr.img.cols * 3));
}

int main (int argc, char** argv)
{
	//get main image
	Mat mainImage = imread(argv[1], IMREAD_UNCHANGED);
	if (!mainImage.data)
	{
		cout << "Could not open image" << endl;
		return 0;
	}

	//set up display windows
	namedWindow("Original Image", WINDOW_AUTOSIZE);
	imshow("Original Image", mainImage);

	//set rand seed
	srand(time(NULL));

	
	vector<picture> current(POPULATION);

	//generate random images
	for (int i = 0; i < POPULATION; i++)
	{
		Mat curModel(mainImage.rows, mainImage.cols, CV_8UC3, Scalar(0,0,0));
		current.at(i).img = curModel;
		current.at(i).fitness = 0;

		Mat buf(mainImage.rows, mainImage.cols, CV_8UC3, Scalar(0,0,0));
		my_rectangle R(Point(rand() % mainImage.cols, rand() % mainImage.rows),
					   Point(rand() % mainImage.cols, rand() % mainImage.rows),
					   Scalar(rand() % 255, rand() % 255, rand() % 255),
					   rand() % 100 / 100.f);
		rectangle(current.at(i).img, R.p1, R.p2, R.color, -1, 8, 0);
		current.at(i).rectangles.push_back(R);
	}

	picture bestPicture;
	Mat curModel(mainImage.rows, mainImage.cols, CV_8UC3, Scalar(0,0,0));
	bestPicture.img = curModel;
	bestPicture.fitness = 0;
	int screenshotCounter = 0;


	for (int k = 0; k < 10000; k++)
	{
		cout << "Number of rectangles = " << k << endl;
		for (int n = 0; n < 100; n++)
		{
			for (int i = 0; i < POPULATION; i++)
			{
				current.at(i).fitness = getFitness(current.at(i), mainImage);
				cout << current.at(i).fitness << endl;
			}
		}
	}
	
	

	waitKey(0);
	return 0;

}
