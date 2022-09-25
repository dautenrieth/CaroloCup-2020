#pragma once
#include<iostream>
using namespace std;
#include<opencv2/opencv.hpp>
using namespace cv;

#include "auxiliary_functions.h"
#include "defines.h"

// the parent class of all possible object types
class object {
public:        
	object();
	void track(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[], bool right = true);
	void set_out_of_start(bool value);
	bool get_tracking_status();
	bool get_out_of_start();
	int get_height();

protected:
	bool mtracking; // whether the object is currently being tracked or not
	int mheight; // The last known height of the object
	bool mout_of_start; //whether a new object can be tracked or the object is still on the startline and triggers the function
};