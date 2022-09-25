#include "object_types.h"
#include<opencv2/opencv.hpp>
using namespace cv;

#define SAMPLING_POINTS_OBST 10
#define NUMBER_OF_FALSE 1
#define NUMBER_OF_FALSE_RIGHT 4
#define CHECK_RIGHT_PIXEL 10
#define OBSTACLE_CHECK_HEIGHT 80

#define SAMPLING_POINTS_START 70
#define MINIMUM_TRUES_START 3
#define HEIGHT_OF_STARTLINE 50	// This might need to be changed. Depending on the distortion of the image
								// This is for safety. if you are not sure you have a completly undistorted image leave it at a high number
								// If you have a high quality picture you can change this value to the true height of the startline
								// then the detection function wont recognize a double lane obsta cle for example

// This function determines whether the detected object is an obstacle or not
bool obstacle::detection(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[]) 
{
	// This function looks at the Area above the start line. If the majority of the area is white it returns true
	// if not it returns false

	int false_checks = 0;
	for (int i = 0; i < (OBSTACLE_CHECK_HEIGHT / SAMPLING_POINTS_OBST); i++) {
		if (!check_pixels(img, coefficients1, coefficients2, coefficients3, START_HEIGHT-(i*(OBSTACLE_CHECK_HEIGHT / SAMPLING_POINTS_OBST)), false) > TRIGGER_PERC) {
			false_checks++;
		}
	}
	if (false_checks <= NUMBER_OF_FALSE) {
		putText(*img, "Obstacle detected", cvPoint(230, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
		if (mtracking == false) { // if an obstacle is already being tracked dont start tracking a new obstacle
			mheight = START_HEIGHT; // Change variables to indicate that the obstacle was found
			mtracking = true;	// Start tracking the Obstacle
			mout_of_start = false; // Indicates that the object possibly will trigger the detection function again
		}
		return true; // Area is mostly white so an Obstacle is detected
	}
	else{
		putText(*img, "No Obstacle detected", cvPoint(230, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
		return false; // Area is mostly dark so no Obstacle is detected
	}

}

bool startline::detection(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[]) 
{
	int true_checks = 0; // Check how many white lines there are. If there are too many it indicates that the found object is not a startline
	for (int i = 0; i < SAMPLING_POINTS_START / 2; i++) {
		if (check_pixels(img, coefficients1, coefficients2, coefficients3, START_HEIGHT - i, false, 12) > TRIGGER_PERC) {
			true_checks++;
		}
	}
	for (int i = 0; i < SAMPLING_POINTS_START / 2; i++) {
		if (check_pixels(img, coefficients1, coefficients2, coefficients3, START_HEIGHT + i, false, 12) > TRIGGER_PERC) {
			true_checks++;
		}
	}
	if (true_checks <= HEIGHT_OF_STARTLINE && true_checks >= MINIMUM_TRUES_START) {
		putText(*img, "Startline detected", cvPoint(230, 50), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
		if (mtracking == false) {
			mheight = START_HEIGHT; // Change variables to indicate that the obstacle was found
			mtracking = true;	// Start tracking the Obstacle
			mout_of_start = false; // Indicates that the object possibly will trigger the detection function again
		}
		return true; // Area has a good amount of white detected lines
	}
	else 
	{
		putText(*img, "No Startline detected", cvPoint(230, 50), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
		return false; // Area has to many or not enough detected lines
	}
}

// stop line has another kind of detection function because of the exclusion principle
// if the detected object isnt an obstacle nor a startline it has to be a stopline
// so the function below only changes the state of the object but doesnt actually check
bool stopline::detection(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[]) {
	putText(*img, "Stopline detected", cvPoint(230, 70), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
	if (mtracking == false) {
		mheight = START_HEIGHT; // Change variables to indicate that the obstacle was found
		mtracking = true;	// Start tracking the Obstacle
		mout_of_start = false; // Indicates that the object possibly will trigger the detection function again
	}
	return true; // Area has a good amount of white detected lines
}


//Extension
bool obstacle_left::detection(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[])
{
	// This function looks at the Area above the start line. If the majority of the area is white it returns true
	// if not it returns false

	int false_checks = 0;
	for (int i = 0; i < (OBSTACLE_CHECK_HEIGHT / SAMPLING_POINTS_OBST); i++) {
		if (!(check_pixels(img, coefficients1, coefficients2, coefficients3, START_HEIGHT - (i * (OBSTACLE_CHECK_HEIGHT / SAMPLING_POINTS_OBST)), false, 12) > TRIGGER_PERC)) {
			false_checks++;
		}
	}
	if (false_checks <= NUMBER_OF_FALSE) {
		putText(*img, "Left-Obstacle detected", cvPoint(230, 90), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
		if (mtracking == false) { // if an obstacle is already being tracked dont start tracking a new obstacle
			mheight = START_HEIGHT; // Change variables to indicate that the obstacle was found
			mtracking = true;	// Start tracking the Obstacle
			mout_of_start = false; // Indicates that the object possibly will trigger the detection function again
		}
		return true; // Area is mostly white so an Obstacle is detected
	}
	else {
		putText(*img, "No Left-Obstacle detected", cvPoint(230, 90), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
		return false; // Area is mostly dark so no Obstacle is detected
	}

}