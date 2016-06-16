/*

FUGA Graphics Library implementation
This library stores all the information required for graphics in each of the pages of the UI
This includes the static graphics as well as the dynamic graphics

All required variables for the graphics to work are also found here

The variables are all initialised at startup

Variables will be referenced by checking the current state the device is at using FSM.isInState()

*/

#include "FugaGraphics.h"
#include "FiniteStateMachine.h"
#include "TFT.h"

#define sd_cs  4
#define cs   53
#define dc   9
#define rst  8

TFT screen = TFT(cs, dc, rst);

Page::Page(unsigned num_box, unsigned num_scroll) {
	_num_box    = num_box;
	_num_scroll = num_scroll;
}

void Page::disp_static_GFX() {
  screen.begin();
  screen.background(255, 255, 255);
  screen.stroke (0,0,0);
  screen.setTextSize(4);
  screen.text("AHHH",0,0);
}