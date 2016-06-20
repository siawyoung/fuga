/*---------------------//
                      //
  UI for the FUGA    //
                    //
 ------------------*/

#include <FiniteStateMachine.h>
//#include <SD.h>    //SD library MUST be declared BEFORE TFT!!!!
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <Button.h>
#include <FugaGraphics.h>

#define button_up 14
#define button_down 15
#define button_left 16
#define button_right 17
#define button_confirm 18
#define button_back 19

//initialise buttons
Button up = Button(button_up, PULLUP);
Button down = Button(button_down, PULLUP);
Button left = Button(button_left, PULLUP);
Button right = Button(button_right, PULLUP);
Button confirm = Button(button_confirm, PULLUP);
Button back = Button(button_back, PULLUP);

//initialize states
State Idle (&noop);
State Splash (&state_1);
State State_2 (&state_2);
State State_3 (&state_3);
State State_4 (&state_4);
State State_5 (&state_5);
State State_6 (&state_6);
State State_7 (&state_7);

//initialize pages
Page1 Page_Splash = Page1();
Page2 Page_2 = Page2();
Page3 Page_3 = Page3();
Page4 Page_4 = Page4();
Page5 Page_5 = Page5();
Page6 Page_6 = Page6();
Page7 Page_7 = Page7();
//initialize FSM
FSM fuga (Splash);

//Idle state
void noop() {    //DONE
}; //no operation function (do nothing)

//Page 1: Splash screen
void state_1() {      //DONE
  Page_Splash.startScreen();
  fuga.immediateTransitionTo(State_2);      //testing state 7
}

//Page 2: Start menu, NEW DRAIN and LOG
void state_2(){    //DONE
  Page_2.disp_static_GFX();
  Page_2.disp_dyn_GFX();
  fuga.immediateTransitionTo(Idle);
}

//Page 3: Set TARGET DURATION
void state_3(){      //DONE
  Page_3.disp_static_GFX();
  Page_3.disp_dyn_GFX();
  fuga.immediateTransitionTo(Idle);
}

//Page 4: Set TARGET VOLUME
void state_4(){      //DONE
  Page_4.disp_static_GFX();
  Page_4.disp_dyn_GFX();
  fuga.immediateTransitionTo(Idle);
}

//Page 5: Summary menu before starting drain
void state_5(){      //DONE
  Page_5.disp_static_GFX();
  fuga.immediateTransitionTo(Idle);
}

//Page 6.0: Main Draining Page
void state_6(){      //DONE
  Page_6.disp_static_GFX();
  Page_6.disp_dyn_GFX();
  fuga.immediateTransitionTo(Idle);
}

void state_7() {      // DONE
  Page_7.disp_static_GFX();
  fuga.immediateTransitionTo(Idle);
}

void Page_2_confirm() {
  if (Page_2.box_sel == 0) {
    fuga.transitionTo(State_3);
  }
}


void setup() {
  // initialize the serial port
  Serial.begin(9600);
}

void loop() {

  if (confirm.uniquePress() && !fuga.isInState(Splash)) {
    switch (Book::pageState) {
      case 1: fuga.transitionTo(State_2); break;
      case 2: Page_2_confirm(); break;
      case 3: fuga.transitionTo(State_4); break;
      case 4: fuga.transitionTo(State_5); break;
      case 5: fuga.transitionTo(State_6); break;
      case 6: fuga.transitionTo(State_7); break;
      default: fuga.transitionTo(State_2); break;
    }
  } else if (back.uniquePress() && !fuga.isInState(Splash)) {
    switch (Book::pageState) {
      case 1: break;
      case 2: break;
      case 3: fuga.transitionTo(State_2); break;
      case 4: fuga.transitionTo(State_3); break;
      case 5: fuga.transitionTo(State_4); break;
      case 6: fuga.transitionTo(State_5); break;
      default: fuga.transitionTo(State_2); break;
    }
  } else if (up.uniquePress() && !fuga.isInState(Splash)) {
    switch (Book::pageState) {
      case 1: Page_Splash.up(); break;
      case 2: Page_2.up(); break;
      case 3: Page_3.up(); break;
      case 4: Page_4.up(); break;
      case 5: Page_5.up(); break;
      case 6: Page_6.up(); break;
      case 7: Page_7.up(); break;
    }
  } else if (down.uniquePress() && !fuga.isInState(Splash)) {
    switch (Book::pageState) {
      case 1: Page_Splash.down(); break;
      case 2: Page_2.down(); break;
      case 3: Page_3.down(); break;
      case 4: Page_4.down(); break;
      case 5: Page_5.down(); break;
      case 6: Page_6.down(); break;
      case 7: Page_7.down(); break;
    }
  } else if (left.uniquePress() && !fuga.isInState(Splash)) {
    switch (Book::pageState) {
      case 1: Page_Splash.left(); break;
      case 2: Page_2.left(); break;
      case 3: Page_3.left(); break;
      case 4: Page_4.left(); break;
      case 5: Page_5.left(); break;
      case 6: Page_6.left(); break;
      case 7: Page_7.left(); break;
    }
  } else if (right.uniquePress() && !fuga.isInState(Splash)) {
    switch (Book::pageState) {
      case 1: Page_Splash.right(); break;
      case 2: Page_2.right(); break;
      case 3: Page_3.right(); break;
      case 4: Page_4.right(); break;
      case 5: Page_5.right(); break;
      case 6: Page_6.right(); break;
      case 7: Page_7.right(); break;
    }
  }

 fuga.update();
}

