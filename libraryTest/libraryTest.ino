

/*

  UI for the FUGA
  
 */

#include <FiniteStateMachine.h>
#include <SD.h>    //SD library MUST be declared BEFORE TFT!!!!
#include <TFT.h>  // Arduino TFT library
#include <SPI.h>
#include <Button.h>
#include <FugaGraphics.h>


// pin definition for the MEGA
#define sd_cs  4
#define cs   53
#define dc   9
#define rst  8

// this variable represents the image to be drawn on screen
PImage logo;

TFT screen = TFT(53, 9, 8);

Page page = Page( 1, 1, screen);

//global variables
const byte NUMBER_OF_STATES = 2; 

/*
//initialize states
State Splash (&startup);
State Idle (&noopUpdate);

//initialize FSM
FSM fuga (Splash);
 
 */
void startup() {
  
}

void noopUpdate() {
}; //no operation function (do nothing)


void setup() {
  // initialize the serial port
  Serial.begin(9600);
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB port only
  }
  
  // try to access the SD card. If that fails (e.g.
  // no card present), the setup process will stop.
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(sd_cs)) {
    Serial.println(F("failed!"));
    return;
  }
  Serial.println(F("OK!"));
  
  screen.begin();

}

void loop() { 
  page.disp_static_GFX ();
  
  
 //fuga.update();
}

void dyn_graphics () {
  
}


