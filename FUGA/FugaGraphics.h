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
	void resetSettings();
	void drawBorder();
	void drawBox(int x, int y, int width, int height, int thickness);
	int alignCenter (String text, int textSize);
	void updateTime (unsigned long startTime, unsigned long currentTime);

	//variables
	unsigned num_box = 0;			//# of boxes
	unsigned num_scroll = 0;		//# of scroll wheels	//use as boolean
	unsigned box_sel = 0;		//current box selected
	unsigned scroll_sel_0 = 0;	//scroll value per scroll wheel
	unsigned scroll_sel_1 = 0;
	unsigned scroll_sel_2 = 0;
	unsigned scroll_sel_3 = 0;
	const unsigned scroll_max = 10;		//max single digit for scrolling (0 to 9)

	unsigned long startTime = 0;
	unsigned long hours = 0;
	unsigned long minutes = 0;

	char buffer [5];				//buffer for int to String conversion


	// GLOBAL STATIC STATE
	static int pageState;					//state tracker

	static int target_duration;

};

class Page1 : public Book {
public:
	Page1();
	void startScreen();
	void disp_static_GFX();
	void up();
	void down();
	void left();
	void right();
};

class Page2 : public Book {
public:
	Page2();
	 void disp_static_GFX();
	 void disp_dyn_GFX();
	 void up();
	 void down();
	 void left();
	 void right();
};

class Page3 : public Book {
public:
	Page3();
	void disp_static_GFX();
	void disp_dyn_GFX();
	void up();
	void down();
	void left();
	void right();
private:
	void update_duration();
};

class Page4 : public Book {
public:
	Page4();
	void disp_static_GFX();
	void disp_dyn_GFX();
	void up();
	void down();
	void left();
	void right();
};

class Page5 : public Book {
public:
	Page5();
	void disp_static_GFX();
	void up();
	void down();
	void left();
	void right();
};

class Page6 : public Book {
public:
	Page6();
	void disp_static_GFX();
	void disp_dyn_GFX();
	void up();
	void down();
	void left();
	void right();
};

class Page7 : public Book {
public:
	Page7();
	void disp_static_GFX();
	void up();
	void down();
	void left();
	void right();
};


#endif