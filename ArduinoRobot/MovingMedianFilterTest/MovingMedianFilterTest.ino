/*
 Name:		MovingMedianFilterTest.ino
 Created:	12/22/2017 2:27:07 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Purpose:	The following program test the moving median filter.
 */
#include "ArduinoRobot.h"
#include "MovingMedianFilterFixed.h"

MovingMedianFilterFixed<int> filt(5);

void setup() {
	Serial.begin(115200);
	// Show size of the filter
	Serial.println(sizeof(filt));
	// Display empty array
	filt.show();
	// Populate with random sample between 0 and 10
	for (int i = 0; i < filt.getWinSize(); i++) {
		filt.filter(random(0, 10));
		filt.show();
	}
	// Reduce the filtering window
	filt.resize(3);
	filt.show();
	// Increase the filtering window size
	filt.resize(15);
	filt.show();
}

void loop() {
  
}
