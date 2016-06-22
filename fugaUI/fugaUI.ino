/*---------------------//
                      //
  UI for the FUGA    //
                    //
 ------------------*/

#include <FiniteStateMachine.h>
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <Button.h>
#include <FugaGraphics.h>
#include <Metro.h>

#define button_up 14
#define button_down 15
#define button_left 16
#define button_right 17
#define button_confirm 18
#define button_back 19

#define pi 3.14159265358979323846

int sysStat;

// Hardware constants and initializations
////////// CSM //////////
int Mode = 6; //phase/enbl mode
int APhase = 5; // CSM direction control
int AEnbl = 4; // CSM speed control
int Adir = HIGH; // CSM default direction (CCW?)

int encoderPinOutA = 20; // interrupt pin
int encoderPinOutB = 7;

float TurnsAngle, prevTurnsAngle, errorAngle, setAngle;
const float angle0 = 0; // syringe to external
const float angle1 = pi/2; // syringe to lung
volatile signed long Rotor = 0;

int CSMstat; // LOW is stationary, HIGH is moving

////////// Stepper Motor LA /////////
int dirPin  = 1;
int stepPin = 2;
int Enable  = 0;  // Active Low to enable
int Sleep   = 3;  // Active Low to sleep - A logic high allows normal operation and startup of the device in the home position
//int M1      = 6;  // default HIGH:  LL 1, HL 2, LH 4, HH 8
//int M2      = 7;  // default HIGH
const int microsteps = 8; // 1, 2, 4, 8 microsteps (must align with M1 and M2 wiring)
int revSign = 1;

// 1ml = 3.15mm
const double distPerml = 0.00315;
const double pitch = 0.00254; // m - of the lead screw              !!change when the lead screw is here
const double maxml = 20; // max draw volume in ml

// Getting values from UI library
// these values are set in Page_5_confirm
int drawStart = 0;
double distTotal, cycle_num, rpm;

int LAstat; // LOW is stationary, HIGH is moving

////////// Buttons and Switch //////////
int CSMswitch = 21;
int buttonFront = 22;
int buttonBack = 23;

/////////// Update Rotation //////////

void UpdateRotation(){
  if (sysStat){
    if (digitalRead(encoderPinOutB)){
      Rotor++;
    }
    else {
      Rotor--;
      }
  }
}

////////// variables for PID //////////

float csmP, csmI, csmD, csmint, csmControl;

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
  // only proceed to page 3 if "new drain" is selected
  if (Page_2.box_sel == 0) {
    fuga.transitionTo(State_3);
  }
}

void Page_5_confirm() {

  // SET MOTOR VALUES HERE

  distTotal = Book::target_volume * distPerml;
  cycle_num = distTotal / (maxml * distPerml);
  rpm = (distTotal * 60 / (((Book::target_duration * 60) - 6 * cycle_num) / 2)) / pitch; // target_duration is in mins
  drawStart = 1;
  digitalWrite(Enable, LOW);

  Book::remaining_duration = Book::target_duration;
  fuga.transitionTo(State_6);
}

void Page_6_confirm() {
  // if no terminate popup, move to page 7
  if (Page_6.box_sel == 0) {
    fuga.transitionTo(State_7);
  // else dismiss the terminate popup
  } else if (Page_6.box_sel == 1) {
    Page_6.box_sel = 0;
    Page_6.disp_dyn_GFX();
  }
}

void Page_6_back() {
  // if no terminate popup, display it
  if (Page_6.box_sel == 0) {
    Page_6.box_sel = 1;
    Page_6.disp_dyn_GFX();
  // else, actually cancel the drain and go to page 5
  } else if (Page_6.box_sel == 1) {

    // TODO: CANCEL DRAIN LOGIC HERE

    Page_6.box_sel = 0;
    fuga.transitionTo(State_5);
  }
}

void Page_7_confirm() {
  if (Page_7.box_sel == 0) {
    fuga.transitionTo(State_6);
  } else if (Page_7.box_sel == 1) {
    Page_7.box_sel = 0;
    Page_7.disp_dyn_GFX();
  }
}

void Page_7_back() {
  if (Page_7.box_sel == 0) {
    Page_7.box_sel = 1;
    Page_7.disp_dyn_GFX();
  } else if (Page_7.box_sel == 1) {

    // TODO: CANCEL DRAIN LOGIC HERE

    Page_7.box_sel = 0;
    fuga.transitionTo(State_5);
  }
}

void setup() {
  // initialize the serial port
  Serial.begin(9600);
  pinMode(Mode, OUTPUT);
  pinMode(APhase, OUTPUT);
  pinMode(AEnbl, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(Enable, OUTPUT);
  pinMode(Sleep, OUTPUT);

  pinMode(encoderPinOutA, INPUT);
  pinMode(encoderPinOutB, INPUT);
  pinMode(CSMswitch, INPUT);
  pinMode(buttonFront, INPUT);
  pinMode(buttonBack, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderPinOutA), UpdateRotation, RISING);

  digitalWrite(Mode, HIGH);
  digitalWrite(Enable, LOW);
  digitalWrite(Sleep, HIGH);
  CSMstat = HIGH;
  LAstat = HIGH;
  sysStat = 0;                  // 0: initializing 1: working
  drawStart = 0;
  //Serial.println("setup");
}

Metro serialMetro = Metro(60000);

void loop() {
  Serial.print("LAstat: "); Serial.println(LAstat);
  /////// MOTOR LOOP /////////
  if ((rpm > 200) || (rpm < 10)) {

    digitalWrite(Enable, HIGH);
    Serial.print("rpm: ");
    Serial.print(rpm);
    Serial.println(", too fast or too slow");

  } else {

//     Serial.println(rpm);

    if (sysStat == 0) {

      if (LAstat) {
        Serial.println("initializing...");
        // rotateDeg(-3*360, 120);                       // uncomment with buttons
        rotateDeg(0,0);                                 // comment this out with buttons
      }

      if (CSMstat){
        Serial.println("initializing...");
        // setAngle = -2*pi;                             // uncomment with switch
        // int reachCSM = digitalRead(CSMswitch);        // uncomment with switch
        int reachCSM = 1;                               // comment out with switch

        if (reachCSM) {
          CSMstat = LOW;
        }

      } else if ((CSMstat == LOW) && (LAstat == LOW)) {
        Serial.println("initialized");

        if (drawStart) {
//          Serial.println("HIIIIII");
          sysStat = 1;
          CSMstat = HIGH;
          setAngle = angle1;
        }
      }

    } else if (sysStat == 1) {
      TurnsAngle = calcAngle(Rotor);
      ////////// LA //////////
      if (LAstat) {
        delay(1000);
        Serial.print("cycle left: ");
        Serial.println(cycle_num);
        LArun();
        delay(500);
      }
    } else if (sysStat == 2) {
      CSMstat = LOW;
      LAstat = LOW;
      Serial.println("Done");
      digitalWrite(Sleep, LOW);
    }

    ////////// CSM error //////////
    errorAngle = setAngle - TurnsAngle;
    //Serial.println(errorAngle);
    if (abs(errorAngle) < pi / 4) {
      csmint = csmint + errorAngle;
    } else {
      csmint = 0;
    }

    csmP = 10 * errorAngle; // set Kp
    csmI = 0 * csmint; //set Ki
    csmD = (prevTurnsAngle - TurnsAngle)* 0.1; // set Kd
    csmControl = csmP + csmI + csmD;
    csmControl = abs(csmControl) + 150;

    if (abs(errorAngle) <= 0.05) {
      CSMstat = LOW;

      if (sysStat == 1) {

        if (setAngle == angle0){
          setAngle = angle1;
          Serial.println("current state: syringe -> external");
        } else {
          setAngle = angle0;
          Serial.println("current state: lung -> syringe");
        }
        LAstat = HIGH;
      }
    } else if (errorAngle > 0) {
      digitalWrite(APhase, Adir);
    } else {
      digitalWrite(APhase, !Adir);
    }

    if (abs(csmControl) > 255) {
      csmControl = 255;
    }

    prevTurnsAngle = TurnsAngle;
  }

  ////////// condition for CSM to stop //////////
  if (CSMstat == LOW) {
    csmControl = 0;
  }
  //  Serial.println(errorAngle);
  ///////// run the CSM //////////
  analogWrite(AEnbl, csmControl); Serial.print("sysStat: ");Serial.println(sysStat);
  delay(10);

  /////// END MOTOR LOOP /////////


  ////////// UI LOOP //////////////

  if (confirm.uniquePress() && !fuga.isInState(Splash)) {
    switch (Book::pageState) {
      case 1: fuga.transitionTo(State_2); break;
      case 2: Page_2_confirm(); break;
      case 3: fuga.transitionTo(State_4); break;
      case 4: fuga.transitionTo(State_5); break;
      case 5: Page_5_confirm(); break;
      case 6: Page_6_confirm(); break;
      case 7: Page_7_confirm(); break;
    }
  } else if (back.uniquePress() && !fuga.isInState(Splash)) {
    switch (Book::pageState) {
      case 1: break;
      case 2: break;
      case 3: fuga.transitionTo(State_2); break;
      case 4: fuga.transitionTo(State_3); break;
      case 5: fuga.transitionTo(State_4); break;
      case 6: Page_6_back(); break;
      case 7: Page_7_back(); break;
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

 // Timer check if interval has passed
 if (serialMetro.check() == 1 && Book::remaining_duration > 0) {
   Book::remaining_duration--;
   // if we're on page 6, update the graphics
   if (Book::pageState == 6) {
    Page_6.disp_timer_GFX();
   }
 }

 ///////// END UI LOOP /////////////

}

float calcAngle(volatile signed long Rotor) {
  float Turns;
  float Turnsangle;
  Turns = (Rotor)/297.92/3.5/(56/12);
  Turnsangle = Turns * 2 * pi;

  if (Turnsangle >= 2*pi) {
    Turnsangle = Turnsangle - 2 * pi;
  }

  return Turnsangle;
}

void LArun() {
  double rev = cycle_num * distPerml * maxml / pitch;

  if ( rev >= distPerml * maxml / pitch ) {
    rev = revSign*distPerml*maxml/pitch;
    if (rev < 0) {
      cycle_num--;
      if (cycle_num == 0) {
        sysStat = 2;
      }
    }
  } else {
    rev = revSign * cycle_num * distPerml * maxml / pitch;
    if (rev < 0) {
      cycle_num = 0;
      sysStat = 2;
    }
  }

  if (revSign > 0) {
    Serial.println("Status: drawing...");
  } else {
    Serial.println("Status: draining...");
  }

  revSign = -revSign;
  rotateDeg(rev*360, rpm);
}

void rotateDeg(float deg, float speed) {
  float speed1 = ((speed / 60) * microsteps * 200); // step/s ==> 1/speed1 = s/step
  int dir = (deg > 0) ? HIGH : LOW;
  digitalWrite(dirPin,dir);

  unsigned int steps = abs(deg) * (microsteps/1.8);
//  Serial.print("steps: "); Serial.println(steps);
  float usDelay = (1 / speed1) / 2 * 1000000;

  CSMstat = HIGH;

  for (int i=0; i < steps; i++) {
//    Serial.print("i: ");Serial.println(i);
    if (deg < 0){
      int reachFront = digitalRead(buttonFront);
      //Serial.println(reachFront);
      if (sysStat == 0) {
        if (reachFront == 0) {
          i = 0;
        }
      }
      if (reachFront) {
        break;
      }
    }

    if (deg > 0){
      int reachBack = digitalRead(buttonBack);
      if (reachBack) {
        digitalWrite(Sleep, LOW);
        CSMstat = LOW;
        break;
      }
    }

    digitalWrite(stepPin, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(usDelay);

  }
  LAstat = LOW;
}

