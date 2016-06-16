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

Page page = Page(2,3);

void startup() {
  page.disp_static_GFX();
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
