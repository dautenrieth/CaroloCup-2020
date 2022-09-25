#include "object.h"


object::object() : mtracking(false), mheight(0), mout_of_start(true) {}

#define NUMBER_PIXELS_TRACKING 70 // Number of Pixels to check in the loop
#define SAFETY_PIXELS  5// Pixels to check above the last known position
#define STOP_HEIGHT_DIFF 20 // Pixels above the lower edge of the picture where the function will stop tracking the object

void object::track(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[], bool right) {

	bool current_result = false; 
	bool last_result = false;
	bool last_result2 = false;
	bool object_found = false;

	for (int i = -SAFETY_PIXELS; i < NUMBER_PIXELS_TRACKING; i++) {
		last_result2 = last_result;
		last_result = current_result;
		if (right) {
			if (check_pixels(img, coefficients1, coefficients2, coefficients3, mheight + i, false) > TRIGGER_PERC) {
				current_result = true;
			}
			else {
				current_result = false;
			}
		}
		else { // left lane
			if (check_pixels(img, coefficients1, coefficients2, coefficients3, mheight + i, false, 12) > TRIGGER_PERC) {
				current_result = true;
			}
			else {
				current_result = false;
			}
		}

		if (current_result == false && last_result == true && last_result2 == true) {
			mheight = mheight + i;
			object_found = true;
			//Visualise height on picture
			for (int a = 0; a < 10; a++) {
				img->at<uchar>(mheight, 0+a) = 255;
			}
			break;
		}
		if (mheight + i > IMAGE_HEIGHT-STOP_HEIGHT_DIFF) {
			cout << "Limit reached" << endl;
			break;
		}
	}
	if (!object_found) {
		cout << "Stopped tracking object" << endl;
		mtracking = false;
		mheight = 0;
	}
}

bool object::get_tracking_status() {
	return mtracking;
}

int object::get_height() {
	return mheight;
}

void object::set_out_of_start(bool value) {
	mout_of_start = value;
}

bool object::get_out_of_start() {
	return mout_of_start;
}