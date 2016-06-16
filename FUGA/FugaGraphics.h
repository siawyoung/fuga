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
#include <FiniteStateMachine.h>
#include <TFT.h>		//include the graphics library for the display

class Book {

public:
	//void disp_static_GFX();
	void resetSettings();
	void drawBorder();
	void drawBox(int x, int y, int width, int height, int thickness);
	int alignCenter (String text, int textSize);
	
	//variables
	unsigned _num_box = 0;			//# of boxes
	unsigned _num_scroll = 0;		//# of scroll wheels	//use as boolean
	unsigned box_count = 0;			//box accumulator
	unsigned box_selector = 0;		//current box selected

};

class Page1 : public Book {
public:
	Page1();
	void startScreen();
	void disp_static_GFX();
};

class Page2 : public Book {
public:
	Page2();
	 void disp_static_GFX();
};

class Page3 : public Book {
public:
	Page3();
	void disp_static_GFX();
};

class Page4 : public Book {
public:
	Page4();
	void disp_static_GFX();
};

class Page5 : public Book {
public:
	Page5();
	void disp_static_GFX();
};

class Page6_0 : public Book {
public:
	Page6_0();
	void disp_static_GFX();
};

class Page6_3 : public Book {
public:
	Page6_3();
	void disp_static_GFX();
};


#endif