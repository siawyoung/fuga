/* 

FUGA Graphics Library implementation
This library stores all the information required for graphics in each of the pages of the UI
This includes the static graphics as well as the dynamic graphics

All required variables for the graphics to work are also found here

The variables are all initialised at startup

Variables will be referenced by checking the current state the device is at using FSM.isInState()

*/


#ifndef FUGAGRAPHICS_H
#define FUGAGRAPHICS_H

#include <Arduino.h>
//#include <TFT.h>		//include the graphics library for the display

class Page {
	public:
		Page( unsigned num_box, unsigned num_scroll );

	private:
		unsigned num_box;
		unsigned num_scroll;
};



#endif