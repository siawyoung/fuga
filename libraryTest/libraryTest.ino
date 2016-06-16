/*

  UI for the FUGA

 */
#include <FiniteStateMachine.h>
#include <SD.h>    //SD library MUST be declared BEFORE TFT!!!!
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <Button.h>
#include <FugaGraphics.h>

//global variables
const byte NUMBER_OF_STATES = 2;

//initialize states
State Splash (&startup);

//initialize FSM
FSM fuga (Splash);

Page1 page1 = Page1();
Page2 page2 = Page2();

void startup() {
  page1.disp_static_GFX();
  delay(2000);
  page2.disp_static_GFX();
  delay(2000);
}


void setup() {
  // initialize the serial port
  Serial.begin(9600);
   while (!Serial) {
     // wait for serial port to connect. Needed for native USB port only
   }
   page1.startScreen();
}

void loop() {
  
  fuga.update();
}
