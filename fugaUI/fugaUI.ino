/*

  UI for the FUGA
  
 */
#include <FiniteStateMachine.h>
#include <SD.h>    //SD library MUST be declared BEFORE TFT!!!!
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>


// pin definition for the MEGA
#define sd_cs  4
#define cs   53
#define dc   9
#define rst  8

//additional pin definitions
//hello
const int stateButton = 2;

TFT screen = TFT(cs, dc, rst);

// this variable represents the image to be drawn on screen
PImage logo;

//global variables
const byte NUMBER_OF_STATES = 1; 

//int state;    //startup() will initialise the state at the end of its function
//bool stateToggle = false; //second condition for changing states

void startup() {
  //start screen

  // initialize the display
  screen.begin();
  
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

 // stateToggle = true;
 // state = 0; 
}

void noopUpdate() {}; //no operation function (do nothing)

void state_2(){         //Start menu, NEW DRAIN and LOG
  // clear the screen with white
  screen.background(255, 255, 255);
  
  drawBorder();

  screen.setTextSize(3);
  screen.text("1", 50, 50);

  resetSettings();
}

//initialize states
State Splash (&startup);
State idle (&noopUpdate);
State start (&state_2);

//initialize FSM
FSM fuga (Splash);

void setup() {
  // initialize the serial port
  Serial.begin(9600);
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB port only
  }

  //initialise buttons
  pinMode(stateButton, INPUT);
  
  // try to access the SD card. If that fails (e.g.
  // no card present), the setup process will stop.
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(sd_cs)) {
    Serial.println(F("failed!"));
    return;
  }
  Serial.println(F("OK!"));

  //startup();
  initSD();

  /*
  //draw a green rectangle with a black border
  screen.stroke(0,0,0);
  screen.fill(102, 188, 70);  //green fill
  screen.rect(20,45, 123, 19);
  
  //test text
  screen.stroke(0,0,0);
  screen.setTextSize(1);
  screen.text("---STATUS---", 43,35);
  
  screen.stroke(0, 0, 0);  //green
  screen.setTextSize(2);
  screen.text("ACCEPTABLE", 22, 47);
  
  //draw the image
  screen.image(logo, 45,65);

 */
}

void loop() {

/*  // read the sensor and map it to the screen height
  int sensor = analogRead(A0);
  int drawHeight = map(sensor, 0, 1023, 0, TFTscreen.height());

  // print out the height to the serial monitor
  Serial.println(drawHeight);

*/
 fuga.update();
}

void dyn_graphics () {
  
}


/*

void state_0(){
  
  // clear the screen with white
  screen.background(255, 255, 255);
  
  drawBorder();

  //title
  screen.stroke (0,0,0);
  screen.setTextSize(4);
  screen.text("FUGA", 35, 30);
  screen.setTextSize(3);
  screen.text("1.0", 53, 60);

  resetSettings();
  stateToggle = false;

  state += 1;
  delay(2000);

}

void state_2(){

  // clear the screen with white
  screen.background(255, 255, 255);
  
  drawBorder();

  screen.setTextSize(3);
  screen.text("2", 50, 50);

  resetSettings();
  stateToggle = false;

  state += 1;
  delay(2000);
  
}

void state_3(){

  // clear the screen with white
  screen.background(255, 255, 255);
  
  drawBorder();

  screen.setTextSize(3);
  screen.text("3", 50, 50);

  resetSettings();
  stateToggle = false;

  state += 1;
  delay(2000);
  
}

void state_4(){

  // clear the screen with white
  screen.background(255, 255, 255);
  
  drawBorder();

  screen.setTextSize(3);
  screen.text("4", 50, 50);

  resetSettings();
  stateToggle = false;

  state += 1;
  delay(2000);
  
}

void state_5(){

  // clear the screen with white
  screen.background(255, 255, 255);
  
  drawBorder();

  screen.setTextSize(3);
  screen.text("5", 50, 50);

  resetSettings();
  stateToggle = false;

  state += 1;
  delay(2000);
  
}

*/

void initSD(){
  logo = screen.loadImage("terry.bmp");
  if (!logo.isValid()) {
    Serial.println(F("error while loading terry.bmp"));
  }
}

void resetSettings(){
  screen.fill(0,0,0);
  screen.setTextSize(1);
  screen.stroke(0,0,0);
}

void drawBorder(){
  // draw a rectangle with a black border with thickness 3 around the edge of the screen
  screen.stroke(0, 0, 0);
  screen.fill(255,255,255);
  screen.rect(1, 1, screen.width()-2, screen.height()-2);
  screen.rect(2, 2, screen.width()-4, screen.height()-4);
  screen.rect(3, 3, screen.width()-6, screen.height()-6);
}



