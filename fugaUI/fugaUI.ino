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
const byte NUMBER_OF_STATES = 6;

//int state;    //startup() will initialise the state at the end of its function
//bool stateToggle = false; //second condition for changing states

//initialize states
State Splash (&state_1);
State Idle (&noop);
State Page_2 (&state_2);
State Page_3 (&state_3);
State Page_4 (&state_4);
State Page_5 (&state_5);
State Page_6_0 (&state_6_0);
State Page_6_3 (&state_6_3);

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

  screen.stroke(0,0,0);
  screen.setTextSize(2);

  drawBox(20, 29, 120, 30, 2); //dynamic value
  drawBox(20, 69, 120, 30, 2); //dynamic value

  screen.text("NEW DRAIN", alignCenter("new drain",2), 37);
  screen.text("LOG", alignCenter("log",2), 77);

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

//Page 4: Set TARGET VOLUME
void state_4(){      //DONE

  // setup
  screen.background(255, 255, 255);
  drawBorder();

  //title
  screen.stroke (0,0,0);
  screen.setTextSize(2);
  screen.text("TARGET", alignCenter("target",2), 13);
  screen.text("VOLUME", alignCenter("volume",2), 30);
  drawBox(11, 62, 5*5*2 + 9, 40, 2);
  //drawBox(88, 62, 5*5*2 + 9, 40, 2);
  screen.setTextSize(5);
  screen.text("00", 13, 64);
  screen.text("00", 77, 64);

  screen.setTextSize(2);
  screen.stroke(255,0,0);
  screen.text("ml",135, 85);

  resetSettings();
  fuga.immediateTransitionTo(Idle);
}

//Page 5: Summary menu before starting drain
void state_5(){      //DONE

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
  fuga.immediateTransitionTo(Idle);
}

//Page 6.0: Main Draining Page
void state_6_0(){      //DONE

  // setup
  screen.background(255, 255, 255);
  drawBorder();

  //text: Draining
  screen.stroke(0,0,0);
  screen.setTextSize(2);
  screen.text("DRAINING   ", alignCenter("draining   ",2), 13);

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
  fuga.immediateTransitionTo(Idle);
}

void state_6_3() {      // DONE
  // setup
  screen.background(255, 255, 255);
  drawBorder();

  screen.stroke (0,0,0);
  screen.setTextSize(2);
  screen.text("TIME ELAPSED", alignCenter("time elapsed",2), 13);

  screen.setTextSize(5);
  screen.text("00", 13, 64); //dynamic value
  screen.text("00", 77, 64); //dynamic value

  screen.stroke (0,255,0);
  screen.setTextSize(2);
  screen.text("IN PROGRESS", alignCenter("in progress",2), 90);

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
        case 3: fuga.transitionTo(Page_4); break;
        case 4: fuga.transitionTo(Page_5); break;
        case 5: fuga.transitionTo(Page_6_0); break;
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
  int stringLength = text.length() * textSize*5 + ((text.length()-1)*textSize); //in pixels
  return (int) (80 - stringLength*0.5);
}








