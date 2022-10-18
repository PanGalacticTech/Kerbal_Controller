//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~##### Kerbal Space Program Controller #####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*

  This software is licenced for free distribution under Creative Commons Licence.

  Created by Pan Galactic Tech

  07/12/2019 Imogen Wren

  Uses Kerbal Simpit Library

  Download the Kerbal Simpit mod to interface with Kerbal Space Program

  Ensure com port is set correctly in gamedata file.

*/

#include "KerbalSimpit.h"
#include "0globals.h"

bool testOUTPUT = false;                         //bool testOUTPUT = true;
//bool testOUTPUT = true;

bool simpleTestOUTPUT = false;                   // if true turns off analog readout entirely to simplify debugging
//bool simpleTestOUTPUT = true;

//----------------------------------------------------OLED Variables & Settings--------------------------
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// #include <Fonts/FreeMonoBold9pt7b.h >


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels



//------------------------------Added from Hackster------------------------
//https://www.hackster.io/yilmazyurdakul/arduino-oled-encoder-simple-menu-system-f9baa1

#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16


#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif





//~~~~~~~~~~~~~~~~~~~~~~~##### Operation modes --- More could be added #####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

///~~~~ KSP Flight Modes ~~~     // Will be used to help assign matrices
bool rocketMode = true; //
bool planeMode = false; //
bool roverMode = false;  //

bool flightModeChange = false;   // if an action has changed the flightmode, this sets true and the matrix is updated based on the mode set.

//####~~~~~~~~~~~~~~~Analog & Joystick INPUTS ~~~~~~~~~~~~~~~####

//~#~~~~~ Analogue/Joysticks Pinouts/Pin ins ~~~~~~~#~
// These variables are held in inputArray[10] which is referenced directly

// Left Hand Stick A
const unsigned int Ax            = A4;
const unsigned int Ay            = A3;
const unsigned int Az            = A5;


// Right Hand Stick B
const unsigned int Bx            = A1;
const unsigned int By            = A0;
const unsigned int Bz            = A2;

// Left Hand Stick C
const unsigned int Cx            = A10;
const unsigned int Cy            = A11;

// Right Hand Stick D
const unsigned int Dx            = A8;
const unsigned int Dy            = A9;

const unsigned int flapsPin      = A13;   // not currently used

const unsigned int throttlePin   = A14;

// This array holds all the named input pins for flight controls
// this is referenced directly as an array in controlAssignment.
unsigned int *inputArray[10] {
  Ax, Ay, Az,
  Bx, By, Bz,
  Cx, Cy,
  Dx, Dy
};


//Input Calibration factors

int AxCal = 0;
int AyCal = 0;
int AzCal = 0;

int BxCal = 0;
int ByCal = 0;
int BzCal = 0;

int CxCal = 0;
int CyCal = 0;

int DxCal = 0;
int DyCal = 0;

int inputCalArray[10] {
  AxCal, AyCal, AzCal,
  BxCal, ByCal, BzCal,
  CxCal, CyCal,
  DxCal, DyCal
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Analogue & Joystick VARIABLES ###~~~~~~~~~~~~~~~~~

//~~~~~~~~~ These FLIGHT CONTROL Variables form the outputArray[8] ~~~~~~~~~~~                                             /// ALL OF THIS IS SHIT. Better Version Exists now I think

// this is referenced directly as an array in controlAssignment && analogControl

int unsigned pitchMaster;   // use this to assign different controls to movement axis
int unsigned yawMaster;      // these variables will hold the address of the analogue pin to read to the function
int unsigned rollMaster;

int unsigned transXmaster;
int unsigned transYmaster;
int unsigned transZmaster;

int unsigned wheelSteerMaster;  // this is the value that is read into rover wheel commands
int unsigned wheelThrottleMaster;  // this is the value that is read into rover wheel commands

// Array of output variables. These need to end up holding the value
//and/or reference to the input pin assigned to each specific output
// this is directly passed as an array to the analogRead functions.

int unsigned outputArray[8] {
  pitchMaster, rollMaster, yawMaster,
  transXmaster, transYmaster, transZmaster,
  wheelSteerMaster, wheelThrottleMaster
};

int pitchCal = 0;                                                                                                                          /// also shite
int rollCal = 0;
int yawCal = 0;

int Xcal = 0;
int Ycal = 0;
int Zcal = 0;

int wheelCal = 0;
int throttleCal = 0;

int outputCalArray[8] { // This array holds the calibration offset for the same input as assigned by the control matrix. // Simples HAHAHAH does not work
  pitchCal, rollCal, yawCal,
  Xcal, Ycal, Zcal,
  wheelCal, throttleCal,
};



//~~~~~~~~~~~ Joystick Deadspace
int deadSpace = 1600;  // "dead" Space for Joystick center, +- value so true deadspace is 2 times deadSpace value
// this is depreciated (I think)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Control Invert Settings ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///  bools for assigning control inverts
bool invertPitch = false;
bool invertRoll  = false;
bool invertYaw   = false;
bool invertArray[3] = {invertPitch, invertRoll, invertYaw};   // This may be changed

///
bool  invertX = false;
bool invertY  = false;
bool invertZ  = false;
bool invertTransArray[3] = {invertX, invertY, invertZ};   // this may be changed

///  Rover Specific Controls
bool    invertWheel = false;
bool invertThrottle = false;
bool invertRoverArray[2] = {invertWheel, invertThrottle};   // this may be changed

bool controlInvertArray[8] = {                           // this is the master array which all other values are read into
  invertPitch, invertRoll, invertYaw,
  invertX, invertY, invertZ,
  invertWheel, invertThrottle
};  // array of 8 values




//~~~~~~~~~~ Rocket Engine Throttle Variables~~~~~~~~~~~~~~~~~~~~
int throttleValue  = 0;
int previousThrottle;
int smoothThrottle;


// ~~~~~~~~~~~~~~~~~~~~~Flight Control Variables & Modifyers:~~~~~~~~~~~~~~~~~~~~~~

int pitchReading;
int rollReading;
int yawReading;

int XReading;
int YReading;
int ZReading;

int wheelReading;        // variables for reading rover controls
int throttleReading;


// ~~~~~~~~~~~~~~~~~~~~~Flight Control Variables & Modifyers; VERSION 2:~~~~~~~~~~~~~~~~~~~~~~

// To simplify the program, all analogue Joystick inputs will be read first, then the appropriate values assigned to
// the correct flight controls.

int axReading;
int ayReading;
int azReading;

int bxReading;
int byReading;
int bzReading;

int cxReading;
int cyReading;

int dxReading;
int dyReading;

// These analogue reads from 0 to 1024 are stored in their own array which can be accessed from this point on.

// Calibrations can be added directly to this value and function will pass on signed int from -512 to +512


int analogReadings[10] = {

  axReading, ayReading, azReading,
  bxReading, byReading, bzReading,
  cxReading, cyReading,
  dxReading, dyReading

};




//~~~~~~~~~~~~~~~~~~~~~~~~~~SimPit  VARIABLES FOR Analogue Actions~~~~~~~~~~~~~~~~~~~~~~~
// This is specifically structured for Kerbal Simpit, but the same variables could be used to send to other devices

// set up rotationMessage data structures containing Rotation Data Variables
rotationMessage PITCH = {};
rotationMessage ROLL = {};
rotationMessage YAW = {};

// set up translationMessage data structures containing  Translation Data Variables
translationMessage XAXIS = {};
translationMessage YAXIS = {};
translationMessage ZAXIS = {};

// set up wheel message data structure
wheelMessage WHEELDATA = {};





//###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Switches & Digital INPUTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~###

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Momentary Buttons ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~ STAGE BUTTON ~~

const int stagePin = 5;    // the number of the pushbutton pin

//~~~~~ Joystick Buttons~~~~~
const int Abutton       = 42; // Normally LOW
const int Bbutton       = 40; // Normally LOW
const int Cbutton       = 46; // Normally HIGH
const int Dbutton       = 44;    // Normally HIGH



// ~ Momentary up/down ~
const int SASdown = 32;
const int RCSdown = 34;
const int SASup = 38;
const int RCSup = 36;

// ~~~~~~~~~~~~~~~~~~ Action Groups ~~~~~~~~~~~~

const int action1 = 23;
const int action2 = 30;
const int action3 = 25;
const int action4 = 28;
const int action5 = 27;
const int action6 = 26;
const int action7 = 29; //
const int action8 = 24;
const int action9 = 31;
const int action10 = 22;

// Array for the action buttons
int actionArray[] = {
  action1, action2, action3,
  action4, action5, action6,
  action7, action8, action9,
  action10
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SPST SINGLE ACTION BUTTON PINS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~ SPST ~
const int stageLock = 33;
const int gear = 37;
const int brakes = 35;
const int mode = 39;


// array of all input pins, used in setup to change pinmode to INPUT
int inputPinArray[] = {
  Abutton, Bbutton, Cbutton, Dbutton,
  SASdown, RCSdown, SASup, RCSup,
  stageLock, gear, brakes, mode,
  action1, action2, action3, action4,
  action5, action6, action7, action8,
  action9, action10

};  // array of 22 const ints (byte?)


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### SWITCH VARIABLES ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~ Action Group State ~~

int action1State;
int action2State;
int action3State;
int action4State;
int action5State;
int action6State;
int action7State;
int action8State;
int action9State;
int action10State;


// Array for the state of action buttons
int actionStateArray[] = {
  action1State, action2State, action3State,
  action4State, action5State, action6State,
  action7State, action8State, action9State,
  action10State
};



//###~~~~~~~~~~Other Switches Variables ~~~~~~~~~~###


bool sasActive = false; // set to true if SAS is active
bool rcsActive = false; // set to true if RCS is active

int actionButtonMode = 0;   // When set to 0 action buttons control action groups
// When set to 1 action buttons control SAS direction


int stageState;             // the current reading from the Stage pin

// ~ Momentary up/down State ~
int SASdownState;
int RCSdownState;
int SASupState;
int RCSupState;

// ~ SPST State ~
int stageLockState;
int gearState;
int brakeState;
int modeState;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~LED / Output Pins~~~~~~~~~~~~~~~~~~~~~~
const int ledPin = 13;      // the number of the LED pin
int ledState = HIGH;         // the current state of the output pin






//~~~~~~~~~~~~~~~~~~~~~~#### BOOLEANS FOR ACTION TRIGGERS ####~~~~~~~~~~~~~~~~~~~~
bool stageACTIVATE;

bool sasACTIVATE;

bool sasDEACTIVATE;

bool rcsACTIVATE;

bool rcsDEACTIVATE;

bool gearACTIVATE;

bool gearDEACTIVATE;

bool brakeACTIVATE;

bool brakeDEACTIVATE;

bool lightsACTIVATE;

bool lightsDEACTIVATE;

byte actiongroupACTIVATE = 0;  // while set to zero, no command. Otherwise accepts values 1 - 20;

byte actiongroupDEACTIVATE = 0;  // same as above, zero = No command. Otherwise accepts values 1 - 20;

byte actiongroupTOGGLE = 0;  // same as above, zero = No command. Otherwise accepts values 1 - 20;

byte sasdirectionACTIVATE = 0; // 0 is off, 1 - 10 activate action groups 11 to 20, 20 also deactivates SAS action





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Debouncing stuff~~~~~~~~~


// Much of this is being changed or depreciated

int lastStageState = LOW;   // the previous reading from the input pin
int lastSASstate = LOW;
int lastSASupstate = LOW;

int lastRCSstate = LOW;
int lastStageLockState = LOW;
int lastModeState = LOW;
int lastGearState = LOW;
int lastBrakeState = LOW;

unsigned long lastStageDebounceTime = 0;

unsigned long lastSASDebounceTime = 0;
unsigned long lastSASupDebounceTime = 0;
unsigned long lastRCSDebounceTime = 0;
unsigned long lastStageLockDebounceTime = 0;
unsigned long lastModeDebounceTime = 0;
unsigned long lastGearDebounceTime = 0;
unsigned long lastBrakeDebounceTime = 0;


// New debounce variables for MOMENTARY switches.

// These time a single sent command then timeout that control for a certain time period

unsigned long stagingTimeout = 1; //staging times out for 1/4 of a second  (this can be used for all debounces?)

unsigned long  lastStagetime = 0;
unsigned long lastActiontime = 0;


bool stagingARMED = true;


bool actionsARMED[10] = {true, true, true, true, true, true, true, true, true, true}; // is this used yet? I dont think so but it probably should be


unsigned long lastABORTtime = 0;
unsigned long abortTimeout = 3000; // 10s timeout for abort commands
bool abortTriggered = false; // when = 1 abort has been triggered

bool abortStarted = false; // triggers if abort started and not completed

unsigned long debounceDelay = 1;    // the debounce time; increase

unsigned long currentRotaryfire;   // this not used atm
unsigned long lastRotaryfire;
unsigned long rotaryTimeout = 200;












// Declare a KerbalSimpit object that will
// communicate using the "Serial" device.
KerbalSimpit mySimpit(Serial);






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### SETUP ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {

  Serial.begin(115200);                                     // Open the serial connection.


  OLEDsetupSimple();                                          // OLED setup & Splash Screen

  sdSetup();                 // sets up the SD card, creates a config file if it does not exist, sets appropriate flags depending on
  //                         // whether a config file exists to read settings from.

  sdWriteSavedSettings();    // only runs if restoreFactory is true, writes factory settings to the SD card config.txt file


readConfigSD();    // if config file was found, read settings from config file


  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(ledPin, HIGH);                         // Set initial pin states, and turn on the LED



  //~~~~~~~~~~~~~~~~~~~~~~~Use a for loop to set all inputs to INPUT mode~~~~~~~~~~~~~~~~

  for (int i = 0; i < 21; i++) {  // for loop sets all input pins to INPUT. // Set Up Inputs & Output pins.

    pinMode(inputPinArray[i], INPUT);

    if (testOUTPUT) {
      Serial.print(i);
      Serial.print("   ");
      Serial.println(inputPinArray[i]);
    }

  }
  //~~~~~~~~~~~~~~~~~~~~~~~Use a for loop to set all inputs to INPUT mode~~~~~~~~~~~~~~~~



  if (testOutput) {                           // (printSerial)
    calibration(true);                         // Cycles through all analog inputs and generates calibration array
  } else {
    calibration(false);
  }




  //  while (!mySimpit.init()) {                                        // This loop continually attempts to handshake with the plugin.
  // It will keep retrying until it gets a successful handshake.
  //  Serial.println("Cannot Initialise mySimpit");                       // Seems to work even if uncommented
  delay(100);
  // }

  digitalWrite(LED_BUILTIN, LOW);                                                    // Turn off the built-in LED to indicate handshaking is complete.


  //    // set up inputs & outputs Matrix


  modeSelect2();                                                       // test mode switch and set mode
  modeArrayUpdate();                                                    // Assign the correct mode to the master array

  // modeMatrixUpdate();                                                 // updates controlMatrix, invertArray & calibration array << This line should not be required any longer



  /*
    if (testOUTPUT) {
    controlAssignment(true);                                          //        Assigns controls based on matrix << NO LONGER REQUIRED AT ALL?!
    } else {
    controlAssignment(false);
    }

  */

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### end of SETUP ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~













//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### MAIN LOOP ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Rotary Controls~~~~~~~~~~~
  clickCheck(); // check to see if encoder button has been pressed
  encodeDirection();  // dicerns the direction of any encoder turn

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ OLED CONTROl ~~~~~~~~~~
  globalPageNav();    // this Sets Page Number (maybe also Item Number
  staticMenu();        // Changes displayed text to fit current Page.
  itemNav();            // scrolls through menu items.
  // itemSelect();         // function to select menu items and trigger responses     // this is done within click check function

  //  oledChanged();              // Check to see if contents of OLED buffer has actually changed

  oledUpdate(lineColours[0], lineColours[1], lineColours[2], lineColours[3]);  // updates Oled with contents of buffer if it has changed. needs 4 bits 1 or 0 for colour

  timedMessageClear(3);       // clears timed messages on line 3


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STAGING ~~~~~~~~~~
  stageLocked();            // Checks status of stage lock

  stageButtonv2();           // Checks staging button

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Analogue Controls~~~~~~~~~~~
  throttleControl();        // analogue controls


  /*  // Dont think this is needed any longer
    if (testOUTPUT) {
      controlAssignment(true);   //(printSerial)  true = test output on
    } else {
      controlAssignment(false);   //(printSerial)  true = test output on
    }
  */

  // modeMatrixUpdate();       // updates controlMatrix and invertArray




  readJoysticks(testOUTPUT);           // read all of the joystick inputs, subtract the calibration factor from each input value. Should return values from -512 to +512 centered at 0.

  modeArrayUpdate();            // new control assignment script


  rotateControlV2(controlInvertArray[0], controlInvertArray[1], controlInvertArray[2]);     // analogue controls inver  Pitch, Roll, Yaw  controlInvertArray[0-2]

  translationControlV2(controlInvertArray[3], controlInvertArray[4], controlInvertArray[5]);     // analogue controls

  wheelControlV2(controlInvertArray[6], controlInvertArray[7]);


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Send & or Print Data ~~~~~~~~~~

  if (simpleTestOUTPUT) {
  dataSendAnalogue(false, false);
  } else if (testOUTPUT) {
  dataSendAnalogue(false, true);
  } else {                                                                    // if both statements false then normal output is selected
    dataSendAnalogue(true, false);    // this sends all the analogue controls
  }



  if (testOUTPUT) {
  dataSendDigital(false, true);   // << This one PRINTS (bool sendSerial, bool printSerial) this sends all data to KSP & OR Prints to Serial Monitor
  } else {
    dataSendDigital(true, false);   // << This one SENDS (bool sendSerial, bool printSerial) this sends all data to KSP & OR Prints to Serial Monitor
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Digital/ Button Controls ~~~~~~~~~~
  sasButton();              //
  rcsButton();
  sasUPButton();
  actionButtons();

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ABORT SEQUENCE CHECK ~~~~~~~~~~

  if (testOUTPUT) {
  abortSequence(true, true);
  } else {
    abortSequence(true, false);           // Checks for abort, triggered from RCS UP Switch // (sendSerial, printSerial)
  }

  //---------------------- MODE & NON MOMENTARY Scripts
  //  modeSelect();
  gearControl();
  brakeControl();
  brakegearMessage();

  joystickButtons();

  modeSelect2();

  controlsEdit();   // script to allow menu editing of control assignments.




  // Other Test Outputs
  // Serial.println(sasActive);

  // Serial.println(" ");   // for testing makes readout better

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### - END OF MAIN LOOP - ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### Scripts ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
