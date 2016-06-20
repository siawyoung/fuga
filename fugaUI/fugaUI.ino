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


//global variables
const byte NUMBER_OF_STATES = 7;

//initialize states
State Idle (&noop);
State Splash (&state_1);
State State_2 (&state_2);
State State_3 (&state_3);
State State_4 (&state_4);
State State_5 (&state_5);
State State_6_0 (&state_6_0);
State State_6_3 (&state_6_3);
//initialize pages
Page1 Page_Splash = Page1();
Page2 Page_2 = Page2();
Page3 Page_3 = Page3();
Page4 Page_4 = Page4();
Page5 Page_5 = Page5();
Page6_0 Page_6_0 = Page6_0();
Page6_3 Page_6_3 = Page6_3();
//initialize FSM
FSM fuga (Splash);

//Idle state
void noop() {    //DONE
}; //no operation function (do nothing)

//Page 1: Splash screen
void state_1() {      //DONE
  Page_Splash.startScreen();
  fuga.immediateTransitionTo(State_3);      //testing state 6_3
  //Page_Splash.disp_static_GFX();
  //fuga.immediateTransitionTo(State_2); 
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
void state_6_0(){      //DONE
  Page_6_0.disp_static_GFX();
  Page_6_0.disp_dyn_GFX();
  fuga.immediateTransitionTo(Idle);
}

void state_6_3() {      // DONE
  Page_6_3.disp_static_GFX();
  fuga.immediateTransitionTo(Idle);
}


void setup() {
  // initialize the serial port
  Serial.begin(9600);
}

void loop() {

  static byte buttonPresses = 0; //only accessible from this function, value is kept between iterations

  if (!fuga.isInState(Splash)) {
    if (confirm.uniquePress()){
      //increment buttonPresses and constrain it to [0, NUMBER_OF_SELECATBLE_STATES-1]
      buttonPresses = ++buttonPresses % (NUMBER_OF_STATES+1);
    /*
      manipulate the state machine by external input and control
    */
    //CONTROL THE STATE
      switch (buttonPresses){
        case 0: fuga.transitionTo(Idle); break;
        case 1: fuga.transitionTo(State_2); break; //first press
        case 2: fuga.transitionTo(State_3); break; //second press
        case 3: fuga.transitionTo(State_4); break;
        case 4: fuga.transitionTo(State_5); break;
        case 5: fuga.transitionTo(State_6_0); break; 
        case 6: fuga.transitionTo(State_6_3); break;
      }
    }
    //test selector
    if (up.uniquePress()){Page_3.up();}
    if (down.uniquePress()){Page_3.down();}
    if (left.uniquePress()){Page_3.left();}
    if (right.uniquePress()){Page_3.right();}
  }
  

/*
  if (!fuga.isInState(Splash)) {
    if (button.uniquePress()){
      //Page_6_0.back();
    }
    if (selector.uniquePress()){
      //Page_4.right();
    }
  }
  
  */
/*  // read the sensor and map it to the screen height
  int sensor = analogRead(A0);
  int drawHeight = map(sensor, 0, 1023, 0, TFTscreen.height());

  // print out the height to the serial monitor
  Serial.println(drawHeight);

*/
 fuga.update();
}

