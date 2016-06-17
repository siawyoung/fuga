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

// this variable represents the image to be drawn on screen
PImage logo;

//global variables
const byte NUMBER_OF_STATES = 7;

//int state;    //startup() will initialise the state at the end of its function
//bool stateToggle = false; //second condition for changing states

//initialize states
State Idle (&noop);
State Splash (&state_1);
//initialize pages
Page6_3 Page_Splash = Page6_3();
//initialize FSM
FSM fuga (Splash);

//Idle state
void noop() {    //DONE
  //screen.setTextSize(1);
  //screen.text("L",150,115);
}; //no operation function (do nothing)

//Page 1: Splash screen
void state_1() {      //DONE
  Page_Splash.disp_static_GFX();
  fuga.immediateTransitionTo(Idle);
}

void setup() {
  // initialize the serial port
  Serial.begin(9600);
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
 fuga.update();
}

