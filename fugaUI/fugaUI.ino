/*

  UI for the FUGA
  
 */
#include <FiniteStateMachine.h>
#include <SD.h>    //SD library MUST be declared BEFORE TFT!!!!
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <Button.h>


// pin definition for the MEGA
#define sd_cs  4
#define cs   53
#define dc   9
#define rst  8

#define button_pin 2
Button button = Button(button_pin,PULLUP);

//additional pin definitions
const int stateButton = 2;

TFT screen = TFT(cs, dc, rst);

// this variable represents the image to be drawn on screen
PImage logo;

//global variables
const byte NUMBER_OF_STATES = 2; 

//int state;    //startup() will initialise the state at the end of its function
//bool stateToggle = false; //second condition for changing states

//initialize states
State Splash (&state_1);
State Idle (&noop);
State Page_2 (&state_2);
State Page_3 (&state_3);

//initialize FSM
FSM fuga (Splash);

//Idle state 
void noop() {    //DONE
  screen.setTextSize(1);
  screen.text("L",150,115);
}; //no operation function (do nothing)

//Page 1: Splash screen
void state_1() {      //DONE
  
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
  fuga.immediateTransitionTo(Page_2);

}

//Page 2: Start menu, NEW DRAIN and LOG
void state_2(){

  // setup
  screen.background(255, 255, 255);
  drawBorder();

  screen.setTextSize(3);
  screen.text("2", 50, 50);

  resetSettings();
  fuga.immediateTransitionTo(Idle);
}

//Page 3: Set TARGET DURATION
void state_3(){      //DONE
  //setup
  screen.background(255, 255, 255);
  drawBorder();

  //title
  screen.stroke (0,0,0);
  screen.setTextSize(2);
  screen.text("TARGET", alignCenter("target",2), 13);
  screen.text("DURATION", alignCenter("duration",2), 30);
  drawBox(13, 62, 5*5*2 + 9, 40, 2);
  drawBox(88, 62, 5*5*2 + 9, 40, 2);
  screen.setTextSize(5);
  screen.text("00", 15, 64);
  screen.text("00", 90, 64);
  
  screen.setTextSize(1);
  screen.text("HH",37,113);
  screen.text("MM",112,113);
  
  screen.stroke(255,0,0);
  screen.fill (255,0,0);
  screen.rect (78, 74, 4,4);
  screen.rect (78, 84, 4,4);

  resetSettings();
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
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(sd_cs)) {
    Serial.println(F("failed!"));
    return;
  }
  Serial.println(F("OK!"));

  //startup();
  initSD();
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
        case 0: Serial.println("IDLING"); fuga.transitionTo(Idle); break;
        case 1: fuga.transitionTo(Page_2); break; //first press
        case 2: fuga.transitionTo(Page_3); break; //second press
      }
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


//****************---HELPER FUNCTIONS---****************

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

void drawBox(int x, int y, int width, int height, int thickness) {
  //draw a box
  screen.fill(255,255,255);
  for (int i = thickness-1; i >= 0; i--){
    screen.rect(x-i,y-i,width+2*i,height+2*i);
  }
}

void drawBox(int x, int y, int width, int height) {
  //draw a box
  screen.fill(255,255,255);
    screen.rect(x,y,width,height);
}

int alignCenter (String text, int textSize){  //centers text in X axis
  int stringLength = text.length() * textSize*5 + ((text.length()-1)*textSize);	//in pixels
  return (int) (80 - stringLength*0.5);
}



