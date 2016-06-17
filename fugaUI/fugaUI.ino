/*---------------------//
                      //
  UI for the FUGA    //
                    //
 ------------------*/
 
#include <FiniteStateMachine.h>
#include <SD.h>    //SD library MUST be declared BEFORE TFT!!!!
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <Button.h>
#include <FugaGraphics.h>

#define button_pin 2
Button button = Button(button_pin,PULLUP);

#define button_selector 3
Button selector = Button(button_selector, PULLUP);

// this variable represents the image to be drawn on screen
PImage logo;

//global variables
const byte NUMBER_OF_STATES = 7;

//int state;    //startup() will initialise the state at the end of its function
//bool stateToggle = false; //second condition for changing states

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
  //Page_2.disp_dyn_GFX();
}; //no operation function (do nothing)

//Page 1: Splash screen
void state_1() {      //DONE
  Page_Splash.startScreen();
  Page_Splash.disp_static_GFX();
  fuga.immediateTransitionTo(State_2); 
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
  fuga.immediateTransitionTo(Idle);
}

//Page 4: Set TARGET VOLUME
void state_4(){      //DONE
  Page_4.disp_static_GFX();
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
  fuga.immediateTransitionTo(Idle);
}

void state_6_3() {      // DONE
  Page_6_3.disp_static_GFX();
  fuga.immediateTransitionTo(Idle);
}


void setup() {
  // initialize the serial port
  Serial.begin(9600);
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB port only
  }
  // try to access the SD card. If that fails (e.g.
  // no card present), the setup process will stop.
}

void loop() {

  static byte buttonPresses = 0; //only accessible from this function, value is kept between iterations

  if (!fuga.isInState(Splash)) {
    if (button.uniquePress()){
      Serial.println("INSIDE");
      //increment buttonPresses and constrain it to [0, NUMBER_OF_SELECATBLE_STATES-1]
      buttonPresses = ++buttonPresses % (NUMBER_OF_STATES+1);
      Serial.println(buttonPresses);
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
    if (selector.uniquePress()){
        Page_2.down();
    }
  }

/*  // read the sensor and map it to the screen height
  int sensor = analogRead(A0);
  int drawHeight = map(sensor, 0, 1023, 0, TFTscreen.height());

  // print out the height to the serial monitor
  Serial.println(drawHeight);

*/
 fuga.update();
}

