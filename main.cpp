#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "rectangle.h"
#include "circle.h"
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
	return f;
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
	
	int ROWS = mainImage.rows;
	int COLS = mainImage.cols;

	//set up display windows
	//namedWindow("Original Image", WINDOW_AUTOSIZE);
	//imshow("Original Image", mainImage);
	//waitKey(0);		
	namedWindow("Evolving Image", WINDOW_AUTOSIZE);
	//set rand seed
	srand(time(NULL));
	
	vector<picture> current(POPULATION);

	//generate random images
	for (int i = 0; i < POPULATION; i++)
	{
		Mat curModel(ROWS, COLS, CV_8UC3, Scalar(0,0,0));
		current.at(i).img = curModel;
		current.at(i).fitness = 0;

		Mat buf(ROWS, COLS, CV_8UC3, Scalar(0,0,0));
		//RECTANGLE
		//int x1 = rand() % COLS, y1 = rand() % ROWS;
		//int x2 = rand() % COLS, y2 = rand() % ROWS;
		//while (x2 <= x1	|| y2 <= y1)
		//{
		//	x2 = rand() % COLS; 
		//	y2 = rand() % ROWS;
		//}
		//cout << "P1(" << x1 << "," << y1 << ")" << endl;
		//cout << "P2(" << x2 << "," << y2 << ")" << endl;
		//my_rectangle R(Point(x1, y1),
		//			   Point(x2, y2),
		//			   Scalar(rand() % 255, rand() % 255, rand() % 255));
		//rectangle(current.at(i).img, R.p1, R.p2, R.color, -1, 8, 0);
		//current.at(i).rectangles.push_back(R);
		
		//CIRCLE
		my_circle C(Point(rand() % COLS, rand() % ROWS),
					rand() % 100 + 20,
					Scalar(rand() % 255, rand() % 255, rand() % 255));
		circle(current.at(i).img, C.center, C.radius, C.color, -1, 9, 0);
		current.at(i).circles.push_back(C);
	}

	picture bestPicture;
	Mat curModel(ROWS, COLS, CV_8UC3, Scalar(0,0,0));
	bestPicture.img = curModel;
	bestPicture.fitness = 9999;

	for (int k = 0; k < 10000; k++)
	{
		cout << "Number of shapes = " << k << endl;
		for (int n = 0; n < 100; n++)
		{
			//calculate image fitness level for all in population
			for (int i = 0; i < POPULATION; i++)
			{
				current.at(i).fitness = 0;
				for (int x = 0; x < current.at(i).img.rows; x++)
				{
					for (int y = 0; y < current.at(i).img.cols; y++)
					{
						Vec3b bgrMainPic = mainImage.at<Vec3b>(x, y);
						Vec3b bgrCurrPic = current.at(i).img.at<Vec3b>(x, y);
						
						current.at(i).fitness += abs(bgrCurrPic.val[0] - bgrMainPic.val[0]);	//b
						current.at(i).fitness += abs(bgrCurrPic.val[1] - bgrMainPic.val[1]);	//g
						current.at(i).fitness += abs(bgrCurrPic.val[2] - bgrMainPic.val[2]);	//r
					}
				}
				current.at(i).fitness /= (current.at(i).img.rows * current.at(i).img.cols) * 3;
				//imshow("Evolving Image", current.at(i).img);
				//waitKey(1);
			}

			float bestFitness = 9999;
			int bestPic = -1;

			//select best image generated
			for (int i = 0; i < POPULATION; i++)
			{
				if (current.at(i).fitness < bestFitness)
				{
					bestFitness = current.at(i).fitness;
					bestPic = i;
				}
			}
			cout << "Mutation # = " << n << endl;
			cout << "bestPic = " << bestPic << endl;
			cout << "bestFitnes = " << bestFitness << endl;
			

			//generate new population by mutating the best image
			//my_rectangle R = current.at(bestPic).rectangles.at(current.at(bestPic).rectangles.size() - 1);
			my_circle C = current.at(bestPic).circles.at(current.at(bestPic).circles.size() - 1);
			for (int i = 0; i < POPULATION; i++) //mutate
			{
				current.at(i) = current.at(bestPic);
				if (i != bestPic)
				{
					//RECTANGLE
					//R.p1 += Point((rand() % 15) - 15/2, (rand() % 15) - 15/2);
					//R.p2 += Point((rand() % 15) - 15/2, (rand() % 15) - 15/2);
					//while (R.p2.x <= R.p1.x || R.p2.x >= COLS || R.p2.y <= R.p1.y || R.p2.y >= ROWS)
					//{
					//	R.p2 += Point((rand() % 15) - 15/2, (rand() % 15) - 15/2);
					//}
					//R.color += Scalar((rand() % 20) - 20/2, (rand() % 20) - 20/2, (rand() % 20) - 20/2);
					
					//CIRCLE
					C.center += Point((rand() % 15) - 15/2, (rand() % 15) - 15/2);
					C.radius += (rand() % 15) - 15/2;
					C.color += Scalar((rand() % 30) - 30/2, (rand() % 30) - 30/2, (rand() % 30) - 30/2);

					Mat buf(ROWS, COLS, CV_8UC3, Scalar(0,0,0)) ;
					bestPicture.img.copyTo(buf) ;																		
					//rectangle(buf , R.p1 , R.p2 , R.color, -1, 8, 0) ;
					circle(buf, C.center, C.radius, C.color, -1, 8, 0);
					current.at(i).img = buf;
					//current.at(i).rectangles.at(current.at(i).rectangles.size() - 1) = R;
					current.at(i).circles.at(current.at(i).circles.size() - 1) = C;
				}
			}

			if (n == 99)
			{
				//change bestPicture if new picture is an improvement
				if (bestPicture.fitness > current.at(bestPic).fitness)
				{
					bestPicture = current.at(bestPic);
					stringstream path;
					path << k << ".jpg";
					string savePath = path.str();
					if (k % 5 == 0)
					{
						imwrite(savePath, bestPicture.img);
					}
				}
				//stringstream path;
				//path << k << ".jpg";
				//string savePath = path.str();
				//if (k % 5 == 0)
				//{
				//	imwrite(savePath, bestPicture.img);
				//}
				cout << "Best fitness = " << bestFitness << endl;
			}
		}
		for (int i = 0; i < POPULATION; i++) //create new shapes
		{
			Mat buf(mainImage.rows, mainImage.cols, CV_8UC3, Scalar(0,0,0));
			bestPicture.img.copyTo(buf);
			current.at(i).fitness = bestPicture.fitness;
			//current.at(i).rectangles = bestPicture.rectangles;
			current.at(i).circles = bestPicture.circles;
			
			//RECTANGLES
			//int x1 = rand() % mainImage.cols, y1 = rand() % mainImage.rows;
			//int x2 = rand() % mainImage.cols, y2 = rand() % mainImage.rows;
			//while (x2 <= x1	|| y2 <= y1)
			//{
			//	x2 = rand() % mainImage.cols; 
			//	y2 = rand() % mainImage.rows;
			//}
			//my_rectangle R(Point(x1, y1),
			//		   	   Point(x2, y2),
			//		   	   Scalar(rand() % 255, rand() % 255, rand() % 255));
			//rectangle(buf, R.p1, R.p2, R.color, -1, 8, 0);
			
			//CIRCLE
			my_circle C(Point(rand() % COLS, rand() % ROWS),
						rand() % 100 + 20,
						Scalar(rand() % 255, rand() % 255, rand() % 255));

			current.at(i).img = buf;
			//current.at(i).rectangles.push_back(R);
			current.at(i).circles.push_back(C);
			//cout << "# of rects = " << current.at(i).rectangles.size() << endl;
		}
	}
	
	waitKey(0);
	return 0;

}
