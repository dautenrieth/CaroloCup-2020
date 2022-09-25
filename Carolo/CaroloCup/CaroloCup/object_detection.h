#pragma once
#include<opencv2/opencv.hpp>
#include "defines.h"
#include<iostream>
#include "object_types.h"
using namespace std;
using namespace cv;

void object_detection(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[]);