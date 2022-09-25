#pragma once
#include<opencv2/opencv.hpp>
#include "defines.h"
#include<iostream>
#include <math.h>
using namespace std;
using namespace cv;


Mat drawLines(Mat img, double coefficients[], double coefficients2[], double coefficients3[]); // Not necessary in car

float check_pixels(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[], int height, bool show, int mode = 23, int pixels = 1000);