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

//#define sd_cs  4
#define cs   10
#define dc   9
#define rst  8

TFT screen = TFT(cs, dc, rst);

//public helper functions

void Book::updateTime(unsigned long startTime, unsigned long currentTime) {
	minutes = ((currentTime - startTime)/1000) / 60;
	hours = minutes / 60;
	minutes = minutes - (hours * 60);
}

void Book::resetSettings(){
  screen.fill(0,0,0);
  screen.setTextSize(1);
  screen.stroke(0,0,0);
}

void Book::drawBorder(){
  // draw a rectangle with a black border with thickness 3 around the edge of the screen
  screen.stroke(0, 0, 0);
  screen.fill(255,255,255);
  screen.rect(1, 1, screen.width()-2, screen.height()-2);
  screen.rect(2, 2, screen.width()-4, screen.height()-4);
  screen.rect(3, 3, screen.width()-6, screen.height()-6);
}

void Book::drawBox(int x, int y, int width, int height, int thickness = 0) {
  //draw a box
  screen.fill(255,255,255);
  for (int i = thickness-1; i >= 0; i--){
    screen.rect(x-i,y-i,width+2*i,height+2*i);
  }
}

int Book::alignCenter (String text, int textSize) {  //centers text in X axis
  int stringLength = text.length() * textSize*5 + ((text.length()-1)*textSize); //in pixels
  return (int) (80 - stringLength*0.5);
}


//Page declarations
//Page1
Page1::Page1() {
}

void Page1::startScreen() {			//start up function to start screen
	screen.begin();					//only Page1 has this function
}
void Page1::disp_static_GFX() {
  // clear the screen with white
  screen.background(255, 255, 255);

  drawBorder();

  //title
  screen.stroke (0,0,0);
  screen.setTextSize(4);
  screen.text("FUGA", 35, 30);
  screen.setTextSize(3);
  screen.text("1.0", 53, 60);

  delay(1000);
  screen.stroke (0,0,0);
  screen.setTextSize(1);
  screen.text("Initializing", 35, 90);
  delay(800);
  screen.stroke (255, 0,0);
  screen.fill(255,0,0);
  screen.rect(110, 93, 4, 4);
  delay(1000);
  screen.stroke (255, 0,0);
  screen.fill(255,0,0);
  screen.rect(118, 93, 4, 4);
  delay(1000);
  screen.stroke (255, 0,0);
  screen.fill(255,0,0);
  screen.rect(126, 93, 4, 4);
  delay(1000);

  resetSettings();
}

//Page2
Page2::Page2() {
  box_sel = 0;
  num_box = 2;
}

void Page2::next() {
  box_sel = (box_sel + 1) % num_box;
  disp_dyn_GFX();
}

void Page2::disp_static_GFX() {
  // setup
  screen.background(255, 255, 255);
  drawBorder();

  screen.stroke(0,0,0);
  screen.setTextSize(2);

  drawBox(20, 29, 120, 30, 2); //dynamic value
  drawBox(20, 69, 120, 30, 2); //dynamic value

  screen.text("NEW DRAIN", alignCenter("new drain",2), 37);
  screen.text("LOG", alignCenter("log",2), 77);

  resetSettings();
}

void Page2::disp_dyn_GFX() {

	if (box_sel == 0) {	//NEW DRAIN selected
		//clear previous graphics
		screen.stroke(255,255,255);
		screen.fill(255,255,255);
		screen.rect(17, 66, 126, 36);
		screen.stroke(0,0,0);
		screen.setTextSize(2);
		drawBox(20, 69, 120, 30, 2);
		screen.text("LOG", alignCenter("log",2), 77);

		//draw new graphics
		screen.stroke(255,0,0);
		screen.setTextSize(2);
		drawBox(18, 27, 124, 34, 2);	//draw a red border
		drawBox(20, 29, 120, 30, 2);
		screen.text("NEW DRAIN", alignCenter("new drain",2), 37);
		resetSettings();

	} else {		//LOG selected
		//clear previous graphics
		screen.stroke(255,255,255);
		screen.fill(255,255,255);
		screen.rect(17, 26, 126, 36);
		screen.stroke(0,0,0);
		screen.setTextSize(2);
		drawBox(20, 29, 120, 30, 2);
		screen.text("NEW DRAIN", alignCenter("new drain",2), 37);

		//draw new graphics
		screen.stroke(255,0,0);
		screen.setTextSize(2);
		drawBox( 18, 67, 124, 34, 2);
		drawBox(20, 69, 120, 30, 2);
		screen.text("LOG", alignCenter("log",2), 77);
		resetSettings();
	}
}


//Page3
Page3::Page3() {
	box_sel = 0;
	num_box = 4;
	scroll_sel_0 = 0;
	scroll_sel_1 = 0;
	scroll_sel_2 = 0;
	scroll_sel_3 = 0;
}

void Page3::up() {
	switch (box_sel) {
		case 0: 
			scroll_sel_0 = (scroll_sel_0 + 1) % scroll_max;
			disp_dyn_GFX(); break;
		case 1:
			scroll_sel_1 = (scroll_sel_1 + 1) % scroll_max;
			disp_dyn_GFX(); break;
		case 2:
			scroll_sel_2 = (scroll_sel_2 + 1) % scroll_max;
			disp_dyn_GFX(); break;
		case 3:
			scroll_sel_3 = (scroll_sel_3 + 1) % scroll_max;
			disp_dyn_GFX(); break;
	}
}

void Page3::down() {
	switch (box_sel) {
		case 0: 
			scroll_sel_0 = (scroll_sel_0 - 1) % scroll_max;
			disp_dyn_GFX(); break;
		case 1:
			scroll_sel_1 = (scroll_sel_1 - 1) % scroll_max;
			disp_dyn_GFX(); break;
		case 2:
			scroll_sel_2 = (scroll_sel_2 - 1) % scroll_max;
			disp_dyn_GFX(); break;
		case 3:
			scroll_sel_3 = (scroll_sel_3 - 1) % scroll_max;
			disp_dyn_GFX(); break;
	}
}

void Page3::left() {
	box_sel = (box_sel - 1) % num_box;
	disp_dyn_GFX();
}

void Page3::right() {
	box_sel = (box_sel + 1) % num_box;
	disp_dyn_GFX();
}

void Page3::disp_static_GFX() {
  //setup
  screen.background(255, 255, 255);
  drawBorder();

  //title
  screen.stroke (0,0,0);
  screen.setTextSize(2);
  screen.text("TARGET", alignCenter("target",2), 13);
  screen.text("DURATION", alignCenter("duration",2), 30);

  drawBox(13, 62, 5*4 + 9, 40, 2);				//dynamic value
  drawBox(13+5*4 + 10, 62, 5*4 + 9, 40, 2);		//dynamic value
  drawBox(88, 62, 5*4 + 9, 40, 2);				//dynamic value
  drawBox(88+5*4 + 10, 62, 5*4 + 9, 40, 2);		//dynamic value

  screen.setTextSize(5);
  screen.text(itoa(scroll_sel_0, buffer, 10), 15, 64);		
  screen.text(itoa(scroll_sel_1, buffer, 10), 45, 64);
  screen.text(itoa(scroll_sel_2, buffer, 10), 90, 64);
  screen.text(itoa(scroll_sel_3, buffer, 10), 120, 64);

  screen.setTextSize(2);
  screen.text("HH",32,106);
  screen.text("MM",107,106);

  screen.stroke(255,0,0);
  screen.fill (255,0,0);
  screen.rect (78, 74, 4,4);
  screen.rect (78, 84, 4,4);

  resetSettings();
}

void Page3::disp_dyn_GFX() {
	if (box_sel == 0) {
		//clear
		screen.stroke(255,255,255);
		screen.fill(255,255,255);
		screen.rect(7, 47, 148, 12);
		screen.stroke (0,0,0);
		drawBox(13, 62, 5*4 + 9, 40, 2);				
		drawBox(13+5*4 + 10, 62, 5*4 + 9, 40, 2);		
		drawBox(88, 62, 5*4 + 9, 40, 2);				
		drawBox(88+5*4 + 10, 62, 5*4 + 9, 40, 2);		
		screen.setTextSize(5);
		screen.stroke(0,0,0);
		screen.text(itoa(scroll_sel_0, buffer, 10), 15, 64);		
		screen.text(itoa(scroll_sel_1, buffer, 10), 45, 64);
		screen.text(itoa(scroll_sel_2, buffer, 10), 90, 64);
		screen.text(itoa(scroll_sel_3, buffer, 10), 120, 64);

		screen.stroke (0,0,0);
		screen.fill(255,0,0);
		screen.circle (27,53, 4);
		//draw number
		screen.stroke(255,0,0);
		drawBox(13, 62, 5*4 + 9, 40, 2);
		screen.setTextSize(5);
		screen.text(itoa(scroll_sel_0, buffer, 10), 15, 64);

		resetSettings();

	} else if (box_sel == 1) {
		//clear
		screen.stroke(255,255,255);
		screen.fill(255,255,255);
		screen.rect(7, 47, 148, 12);
		screen.stroke (0,0,0);
		drawBox(13, 62, 5*4 + 9, 40, 2);				
		drawBox(13+5*4 + 10, 62, 5*4 + 9, 40, 2);		
		drawBox(88, 62, 5*4 + 9, 40, 2);				
		drawBox(88+5*4 + 10, 62, 5*4 + 9, 40, 2);		
		screen.setTextSize(5);
		screen.stroke(0,0,0);
		screen.text(itoa(scroll_sel_0, buffer, 10), 15, 64);		
		screen.text(itoa(scroll_sel_1, buffer, 10), 45, 64);
		screen.text(itoa(scroll_sel_2, buffer, 10), 90, 64);
		screen.text(itoa(scroll_sel_3, buffer, 10), 120, 64);

		screen.stroke (0,0,0);
		screen.fill(255,0,0);
		screen.circle (13+5*4 + 10 +14, 53, 4);
		//draw number
		screen.stroke(255,0,0);
		drawBox(13+5*4 + 10, 62, 5*4 + 9, 40, 2);
		screen.setTextSize(5);
		screen.text(itoa(scroll_sel_1, buffer, 10), 45, 64);

		resetSettings();

	} else if (box_sel == 2) {
		//clear
		screen.stroke(255,255,255);
		screen.fill(255,255,255);
		screen.rect(7, 47, 148, 12);
		screen.stroke (0,0,0);
		drawBox(13, 62, 5*4 + 9, 40, 2);				
		drawBox(13+5*4 + 10, 62, 5*4 + 9, 40, 2);		
		drawBox(88, 62, 5*4 + 9, 40, 2);				
		drawBox(88+5*4 + 10, 62, 5*4 + 9, 40, 2);		
		screen.setTextSize(5);
		screen.stroke(0,0,0);
		screen.text(itoa(scroll_sel_0, buffer, 10), 15, 64);		
		screen.text(itoa(scroll_sel_1, buffer, 10), 45, 64);
		screen.text(itoa(scroll_sel_2, buffer, 10), 90, 64);
		screen.text(itoa(scroll_sel_3, buffer, 10), 120, 64);

		screen.stroke (0,0,0);
		screen.fill(255,0,0);
		screen.circle (88 + 14, 53, 4);
		//draw number
		screen.stroke(255,0,0);
		drawBox(88, 62, 5*4 + 9, 40, 2);
		screen.setTextSize(5);
		screen.text(itoa(scroll_sel_2, buffer, 10), 90, 64);

		resetSettings();

	} else if (box_sel == 3) {
		//clear
		screen.stroke(255,255,255);
		screen.fill(255,255,255);
		screen.rect(7, 47, 148, 12);
		screen.stroke (0,0,0);
		drawBox(13, 62, 5*4 + 9, 40, 2);				
		drawBox(13+5*4 + 10, 62, 5*4 + 9, 40, 2);		
		drawBox(88, 62, 5*4 + 9, 40, 2);				
		drawBox(88+5*4 + 10, 62, 5*4 + 9, 40, 2);		
		screen.setTextSize(5);
		screen.stroke(0,0,0);
		screen.text(itoa(scroll_sel_0, buffer, 10), 15, 64);		
		screen.text(itoa(scroll_sel_1, buffer, 10), 45, 64);
		screen.text(itoa(scroll_sel_2, buffer, 10), 90, 64);
		screen.text(itoa(scroll_sel_3, buffer, 10), 120, 64);

		screen.stroke (0,0,0);
		screen.fill(255,0,0);
		screen.circle (88+5*4 + 10 + 14, 53, 4);
		//draw number
		screen.stroke(255,0,0);
		drawBox(88+5*4 + 10, 62, 5*4 + 9, 40, 2);
		screen.setTextSize(5);
		screen.text(itoa(scroll_sel_3, buffer, 10), 120, 64);

		resetSettings();
	}
}

//Page4
Page4::Page4() {
	box_sel = 1;
	num_box = 2;
	scroll_sel_0 = 0;
	scroll_sel_1 = 0;
}

void Page4::up() {
	switch (box_sel) {
		case 0: 
			scroll_sel_0 = (scroll_sel_0 + 1) % scroll_max;
			disp_dyn_GFX(); break;
		case 1:
			scroll_sel_1 = (scroll_sel_1 + 1) % scroll_max;
			disp_dyn_GFX(); break;
	}
}

void Page4::down() {
	switch (box_sel) {
		case 0: 
			scroll_sel_0 = (scroll_sel_0 - 1) % scroll_max;
			disp_dyn_GFX(); break;
		case 1:
			scroll_sel_1 = (scroll_sel_1 - 1) % scroll_max;
			disp_dyn_GFX(); break;
	}
}

void Page4::left() {
	box_sel = (box_sel - 1) % num_box;
	disp_dyn_GFX();
}

void Page4::right() {
	box_sel = (box_sel + 1) % num_box;
	disp_dyn_GFX();
}

void Page4::disp_static_GFX() {
  // setup
  screen.background(255, 255, 255);
  drawBorder();

  //title
  screen.stroke (0,0,0);
  screen.setTextSize(2);
  screen.text("TARGET", alignCenter("target",2), 13);
  screen.text("VOLUME", alignCenter("volume",2), 30);
  drawBox(11, 62, 5*4 + 9, 40, 2);
  drawBox(13+5*4 + 10, 62, 5*4 + 9, 40, 2);				
  screen.setTextSize(5);
  screen.text(itoa(scroll_sel_0, buffer, 10), 13, 64);					//dynamic value
  screen.text(itoa(scroll_sel_1, buffer, 10), 13+5*4 + 12, 64);			//dynamic value
  screen.text("00", 77, 64);

  screen.setTextSize(2);
  screen.stroke(255,0,0);
  screen.text("ml",135, 85);

  resetSettings();
}

void Page4::disp_dyn_GFX() {
	if (box_sel == 0) {
		//clear
		screen.stroke(255,255,255);
		screen.fill(255,255,255);
		screen.rect(7, 47, 148, 12);
		screen.stroke (0,0,0);
		drawBox(11, 62, 5*4 + 9, 40, 2);
		drawBox(13+5*4 + 10, 62, 5*4 + 9, 40, 2);				
		screen.setTextSize(5);
		screen.text(itoa(scroll_sel_0, buffer, 10), 13, 64);					
		screen.text(itoa(scroll_sel_1, buffer, 10), 13+5*4 + 12, 64);	

		screen.stroke (0,0,0);
		screen.fill(255,0,0);
		screen.circle (25,53, 4);
		//draw number
		screen.stroke(255,0,0);
		drawBox(11, 62, 5*4 + 9, 40, 2);
		screen.setTextSize(5);
		screen.text(itoa(scroll_sel_0, buffer, 10), 13, 64);

		resetSettings();

	} else if (box_sel == 1) {
		//clear
		screen.stroke(255,255,255);
		screen.fill(255,255,255);
		screen.rect(7, 47, 148, 12);
		screen.stroke (0,0,0);
		drawBox(11, 62, 5*4 + 9, 40, 2);
		drawBox(13+5*4 + 10, 62, 5*4 + 9, 40, 2);				
		screen.setTextSize(5);
		screen.text(itoa(scroll_sel_0, buffer, 10), 13, 64);					
		screen.text(itoa(scroll_sel_1, buffer, 10), 13+5*4 + 12, 64);	

		screen.stroke (0,0,0);
		screen.fill(255,0,0);
		screen.circle (13+5*4 + 10 +14, 53, 4);
		//draw number
		screen.stroke(255,0,0);
		drawBox(13+5*4 + 10, 62, 5*4 + 9, 40, 2);	
		screen.setTextSize(5);
		screen.text(itoa(scroll_sel_1, buffer, 10), 13+5*4 + 12, 64);

		resetSettings();
	}
}

//Page5
Page5::Page5() {
}

void Page5::disp_static_GFX() {
  // setup
  screen.background(255, 255, 255);
  drawBorder();

  //title
  screen.stroke (0,0,0);
  screen.setTextSize(3);
  drawBox(alignCenter("summary",3)-2, 11, 5*3*7+3*6+4, 26, 2);
  screen.text("SUMMARY", alignCenter("summary",3), 13);

  screen.setTextSize(1);
  screen.text("DURATION :", 13, 47);
  screen.text("VOLUME   :", 13, 70);

  screen.stroke(255,0,0);
  screen.setTextSize(2);
  screen.text("00 00 ", 75, 44);    //dynamic value
  screen.text("0000 ", 75, 65);    //dynamic value
  screen.stroke(0,0,0);
  screen.text("  h", 75, 44);
  screen.text("     m", 75, 44);
  screen.text("    ml", 75, 65);

  screen.setTextSize(4);
  screen.stroke(255,0,0);
  drawBox(alignCenter("start",4)-2, 88, 5*4*5+4*4+4, 33, 2);
  screen.text("START", alignCenter("start",4), 90);

  resetSettings();
}

//Page6_0
Page6_0::Page6_0() {
	box_sel = 0;
	num_box = 2;
}

void Page6_0::back() {
	box_sel = (box_sel + 1) % num_box;
	disp_dyn_GFX();
}

void Page6_0::disp_static_GFX() {
  // setup
  screen.background(255, 255, 255);
  drawBorder();

  //text: Draining
  screen.stroke(0,0,0);
  screen.setTextSize(2);
  screen.text("<DRAINING>", alignCenter("<DRAINING>",2), 13);

  //text: Status
  screen.stroke(0,0,0);
  screen.setTextSize(1);
  screen.text("---STATUS---", alignCenter("---status---",1), 35);

  //text: ACCEPTABLE
  screen.stroke(0,0,0);
  screen.fill(102, 188, 70);  //green fill
  screen.rect(alignCenter("acceptable ",2), 48, 133, 30);
  screen.setTextSize(2);
  screen.text("ACCEPTABLE", alignCenter("acceptable",2), 55);

  //text: Time Remaining
  screen.stroke(0,0,0);
  screen.setTextSize(1);
  screen.text("T. Remain:", alignCenter("acceptable ",2), 97);
  screen.setTextSize(2);
  screen.stroke(255,0,0);
  screen.text("00    ", 75, 90);    //dynamic value
  screen.text("   00 ", 75, 90);    //dynamic value
  screen.stroke(0,0,0);
  screen.text("  h  m", 75, 90);

  resetSettings();
}

void Page6_0::disp_dyn_GFX() {
	if (box_sel == 1) {
		screen.stroke(0,0,0);
		screen.fill(255,0,0);
		screen.rect(alignCenter("terminate?  ",2), 40, 142, 47);
		screen.setTextSize(2);
		screen.text("TERMINATE?", alignCenter("terminate?", 2), 55);

		resetSettings();
	} else {
		//clear
		screen.stroke(255,255,255);
		screen.fill(255,255,255);
		screen.rect(alignCenter("terminate?  ",2), 40, 142, 47);

		//text: Status
		screen.stroke(0,0,0);
		screen.setTextSize(1);
		screen.text("---STATUS---", alignCenter("---status---",1), 35);

		//text: ACCEPTABLE
		screen.stroke(0,0,0);
		screen.fill(102, 188, 70);  //green fill
		screen.rect(alignCenter("acceptable ",2), 48, 133, 30);
		screen.setTextSize(2);
		screen.text("ACCEPTABLE", alignCenter("acceptable",2), 55);

		resetSettings();
	}
}

//Page6_3
Page6_3::Page6_3() {
}

void Page6_3::disp_static_GFX() {
  // setup
  screen.background(255, 255, 255);
  drawBorder();

  screen.stroke (0,0,0);
  screen.setTextSize(2);
  screen.text("TIME ELAPSED", alignCenter("time elapsed",2), 13);

  screen.setTextSize(5);
  if (hours < 10) {
	  screen.text("0", 7, 46);
	  screen.text(itoa(hours, buffer, 10), 37, 46); //dynamic value
  } else { screen.text(itoa(hours, buffer, 10), 7, 46); }

  if (minutes < 10) {
	  screen.text("0", 82, 46);
	  screen.text(itoa(minutes, buffer, 10), 112, 46); //dynamic value
  } else { screen.text(itoa(minutes, buffer, 10), 82, 46); }

  screen.setTextSize(3);
  screen.text("h", 64, 55); 
  screen.text("m", 139, 55); 

  screen.stroke (0,255,0);
  screen.setTextSize(2);
  screen.text("IN PROGRESS", alignCenter("in progress",2), 95);

  resetSettings();
}
