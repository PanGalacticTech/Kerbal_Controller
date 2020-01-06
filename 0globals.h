
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### Global Variables ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// HEADER & VARIABLES DECLARATIONS:


// Mostly char strings and OLED function
// to keep them away from main page.



// MATRIX REPLACEMENT CONCEPT

// To simplify this code a totally new way of organising this table could be

//####################################################################################################################

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~###### MODE Arrays ########~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Simpler way of laying out the data saved in the matrices below.

// All of these variables are user editable.
// While powered on the menu can change these arrays, and the results saved to an SD card.
// On boot up if there is no previously avalaible config file to read from the SD card,
// these arrays are used to populate the config file with factory default settings.

// The default restore function, once implimented, simply deletes the config file, then reboots the unit
// which will re-write these values into a new config file.

int MasterintcontrolArray[9] = { /// This has a slot for each output in order. ints 0 to 9 are saved 10 is null     // This is the active array.
  4, 5, 3, 0, 1, 7, 10, 10, 10             // this has an extra space used because the menu has a blank space to fill in slot 9.  
};

int RocketintcontrolArray[9] = {  /// This has a slot for each output in order. ints 0 to 9 are saved 10 is null
  4, 5, 3, 0, 1, 7, 10, 10, 10   
};

int PlaneintcontrolArray[9] = {  /// This has a slot for each output in order. ints 0 to 9 are saved 10 is null
  4, 3, 8, 0, 1, 7, 10, 10, 10   
};

int RoverintcontrolArray[9] = {  /// This has a slot for each output in order. ints 0 to 9 are saved 10 is null
  7, 6, 8, 10, 10, 10, 3, 1, 10   
};



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Invert Arrays ###~~~~~~~~~~~~~~~~~~~~~
// These set control inversions

bool rocketInvertArray[9] {
  false, false, true,
  false, false, false,
  false, false, false 
};


bool planeInvertArray[9] {
  false, true, false,
  false, false, false,
  false, false , false                     //the last false statement is a null
};


bool roverInvertArray[9] {
  true, false, false,
  false, false, false,
  true, true, false
};

//########################################################################################################################################


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~###### MODE MATRICIES ########~~~~~~~~~~~~~~~~~~~~~~~~~~~
// All these matrices have been depreciated, included as its a much easier way to visulise how the control matrix functions.
// This matrix is no longer referenced directly in the code,
// but the arrays use the same number.
// So Pitch control is 0 on the control Output array
// Assigning this as (4) means that input (By) - y Axis of the B joystick is assigned to the Pitch Control

//~~~~~~~~~~~~~~~~~~~~~~~~~~~### Rocket Matrix ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int stockRocketMatrix[][10] { //[outputs][inputs]  // First array no of rows should be undeclared // coloumns need to be declared apparently

  //x > outputs( for loop j)                    // v y inputs(for loop i)

  // 0, 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8, 9
// Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Dx, Dy
  {0,  0,  0,  0,  1,  0,  0,  0,  0,  0},  // 0 Pitch
  {0,  0,  0,  0,  0,  1,  0,  0,  0,  0},  // 1 Roll
  {0,  0,  0,  1,  0,  0,  0,  0,  0,  0},  // 2 Yaw

  {1,  0,  0,  0,  0,  0,  0,  0,  0,  0},  // 3 Trans X
  {0,  1,  0,  0,  0,  0,  0,  0,  0,  0},  // 4 Trans Y
  {0,  0,  0,  0,  0,  0,  0,  1,  0,  0},  // 5 Trans Z

  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  // 6 Steering (Rover)
  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0}   // 7 Throttle (Rover)
};





//~~~~~~~~~~~~~~~~~~~~~~~~~~~### Plane Matrix ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int stockPlaneMatrix[][10] { //[outputs][inputs]  // First array no of rows should be undeclared // coloumns need to be declared apparently

  //x > outputs( for loop j)                    // v y inputs(for loop i)

  // 0, 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8, 9
  // Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Dx, Dy
  {0,  0,  0,  0,  1,  0,  0,  0,  0,  0},  // 0 Pitch
  {0,  0,  0,  1,  0,  0,  0,  0,  0,  0},  // 1 Roll
  {0,  0,  0,  0,  0,  0,  0,  0,  1,  0},  // 2 Yaw

  {1,  0,  0,  0,  0,  0,  0,  0,  0,  0},  // 3 Trans X
  {0,  1,  0,  0,  0,  0,  0,  0,  0,  0},  // 4 Trans Y
  {0,  0,  0,  0,  0,  0,  0,  1,  0,  0},  // 5 Trans Z

  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  // 6 Steering (Rover)
  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0}   // 7 Throttle (Rover)
};





//~~~~~~~~~~~~~~~~~~~~~~~~~~~### Rover Matrix ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int stockRoverMatrix[][10] { //[outputs][inputs]  // First array no of rows should be undeclared // coloumns need to be declared apparently

  //x > outputs( for loop j)                    // v y inputs(for loop i)

  // 0, 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8, 9
// Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Dx, Dy
  {0,  0,  0,  0,  0,  0,  0,  1,  0,  0},  // 0 Pitch
  {0,  0,  0,  0,  0,  0,  1,  0,  0,  0},  // 1 Roll
  {0,  0,  0,  0,  0,  0,  0,  0,  1,  0},  // 2 Yaw

  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  // 3 Trans X
  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  // 4 Trans Y
  {0,  0,  0,  0,  0,  0,  0,  0,  0,  1},  // 5 Trans Z

  {0,  0,  0,  1,  0,  0,  0,  0,  0,  0},  // 6 Steering (Rover)
  {0,  1,  0,  0,  0,  0,  0,  0,  0,  0}   // 7 Throttle (Rover)
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~###### MODE MATRICIES ########~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MATRIX & Control Variables~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool controlsUnassigned = true;       // can be set false to run for loops used to assign inputs and outputs based on updates to
// the Matrix

bool wipeMatrix = true;              // not used at the moment. could be used later to completely wipe matrix and start from scratch

bool testOutput = false;             // if true function also prints debugging output to serial monitor


// NAMES of INPUT pins (just used for serial printing may also be useful for OLED later
char aXname[5] = {"  Ax"};
char aYname[5] = {"  Ay"};
char aZname[5] = {"  Az"};
char bXname[5] = {"  Bx"};
char bYname[5] = {"  By"};
char bZname[5] = {"  Bz"};
char CXname[5] = {"  Cx"};
char CYname[5] = {"  Cy"};
char DXname[5] = {"  Dx"};
char DYname[5] = {"  Dy"};
char NAname[5] = {" N/A"};

// array of names above, required for for loops & testing
char *inputNames[12] {
  aXname, aYname, aZname,
  bXname, bYname, bZname,
  CXname, CYname,
  DXname, DYname, NAname
};



// NAMES of OUTPUT variables (just used for serial printing) also may be useful for OLED later
char      pitchName[10] = {"Pitch   "};
char       rollName[10] = {"Roll    "};
char        yawName[10] = {"Yaw     "};
char     transXName[10] = {"TransX  "};
char     transYName[10] = {"TransY  "};
char     transZName[10] = {"TransZ  "};
char   steeringName[10] = {"Steering"};
char   throttleName[10] = {"Throttle"};
char   blank[10]        = {"N/A     "};   // added see if fucks up


// array of names above, required for for loops & testing
char *outputNames[10] {                           // changed from 9 to 10
  pitchName, rollName, yawName,
  transXName, transYName, transZName,
  steeringName, throttleName, blank
};




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### General OLED Char Arrays ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// KERBAL SPACE PROGRAM/Preloading Opening PAGE
char oledLine0[23] = {" Kerbal Space Program "}; // Title / Page   // 128 pixles, 5/6 pxl per character
char oledLine1[23] = {"    Action Groups    "}; //  SAS/RCS Status
char oledLine2[23] = {"                     "}; //  Action triggered or SAS heading
char oledLine3[23] = {" !Waiting for Launch!"}; //  Staging

// This array holds the 4 lines of text that are to be printed onto the OLED.
// Replace the contents of each line to update new messages on the screen
char *oledArray[5] = {oledLine0 , oledLine1, oledLine2 , oledLine3};


// Previous Screen Buffers;
char PoledLine0[23];
char PoledLine1[23]; 
char PoledLine2[23];
char PoledLine3[23];

char *PoledArray[5] = {PoledLine0, PoledLine1, PoledLine2, PoledLine3};



const char            lineWipe[23] = {"                     "};  // used to wipe old messages line by line


//~~~~~~~~~~## OLED Display Variables ##~~~~~~~~~~~~~~~~~~~~

int line0colour = 1;
int line1colour = 1;
int line2colour = 1;
int line3colour = 1;

int lineColours[4] = {line0colour, line1colour, line2colour, line3colour};  // this can be used to pass
// line colour info to oledUpdate
//if set at 1, Text is WHITE with black background,
//if set to 0, Text is BLACK with a WHITE background


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Char Strings for different menu pages~~~~~~~~~~~~~~~~~~~~~
// KERBAL SPACE PROGRAM PAGE:
char   kerbalTitle[23] = {"Kerbal Space Program "};








// SETTINGS PAGE:
char       settingsTitle[23] = {"Settings             "};
char        setJoysticks[23] = {"Set Flight Controls  "};
char          setInverts[23] = {"Set Control Inversion"};
char        setCalibrate[23] = {"Calibration          "};

char     setSaveSettings[23] = {"Save Settings        "};
char    setFactoryRecall[23] = {"Factory Recall       "};



char  calibrationStarted[23] = {"Calibration Started  "};
char calibrationComplete[23] = {"Calibration Complete "};





// These variables are used for time specific messages on the OLED
unsigned long lastMessage = 0; // Time since last message
unsigned long messageTimeout = 2500;  // Time messages should remain on screen before wipe
bool timedMessageset = false;        // true if timed message has been set to be wiped after delay



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Kerbal Space Program Specific OLED Char Strings ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//      {" Kerbal Space Program "};
char      stagingMessage[23] = {" !! Staging Event !! "};
char  staginglockMessage[23] = {"!! Staging  Locked !!"};

char     rovermodeONMessage[23] = {"| Rover Mode Active |"};
 char    rovermodeOFFMessage[23] = {"Rover Mode Disengaged"};




//const char oledMessages[3] = {stagingMessage, staginglockMessage};    //  this doesnt seem useful to me right now



// These are for line 1
char sasMessage[4] = {"SAS"};
char rcsMessage[4] = {"RCS"};
char blank3Message[4] = {"   "};
char    actionMessage[15] = {"Action Groups "};
char actionSASMessage[15] = {"  Action SAS  "};
char   blank14Message[15] = {"              "};


// these are for line 2
char     gearMessage[4] = {"  G"};
char     brakeMessage[4] = {"B  "};    // this will need to trigger a custom action group
char gearbrakeMessage[4] = {"B G"};    // this will need to trigger a custom action group

char     rocketMessage[4] = {"Ro "};
char      planeMessage[4] = {"Pl "};

// other char strings for line 2 found with action groups and SAS headings


bool stageLockbit = false;  // this is set to true, used to wipe message on unlock
bool launchedBit = false;    // set to true once ship has been staged once // gets rid of ready to launch message


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### Action OLED Char Arrays ####~~~~~~~~~~~~~~~~~~~~

// these all change to 14 char long
char  actionText1[15] = {"   Action 1   "};
char  actionText2[15] = {"   Action 2   "};
char  actionText3[15] = {"   Action 3   "};
char  actionText4[15] = {"   Action 4   "};
char  actionText5[15] = {"   Action 5   "};
char  actionText6[15] = {"   Action 6   "};
char  actionText7[15] = {"   Action 7   "};
char  actionText8[15] = {"   Action 8   "};
char  actionText9[15] = {"   Action 9   "};
char actionText10[15] = {"   Action 10  "};


char *actionTextArray[] = {
  actionText1, actionText2, actionText3,
  actionText4, actionText5, actionText6,
  actionText7, actionText8, actionText9,
  actionText10
};


//~~~~~~~~~~~~~~~~~~#### SAS Commands OLED Chars ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~

char     progradeText[15] = {"   Prograde   "};
char   retrogradeText[15] = {"  Retrograde  "};

char    radialOUTText[15] = {"  Radial Out  "};
char     radialINText[15] = {"  Radial In   "};

char       normalText[15] = {"    Normal    "};
char   antinormalText[15] = {"  Anti-Normal "};

char       targetText[15] = {"    Target    "};
char   antitargetText[15] = {"  Anti-Target "};

char     maneuverText[15] = {"   Maneuver   "};
char    stabilityText[15] = {"  SAS Cancel  "};   // should be stability but is actually now cancel

// Array for char strings above
char *SASTextArray[] = {
  progradeText, retrogradeText, radialOUTText,
  radialINText, normalText, antinormalText,
  targetText, antitargetText, maneuverText,
  stabilityText
};







//----------------------------------------------
// ~~ ENCODER INPUT ~~

byte clk;

bool runState = false;

int encoderPinA = 2;
int encoderPinB = 3;
volatile unsigned int encoderPos = 0;
int encoderButton = 4; // user comment

//--------New code from stackexchange----------
volatile bool fired;
volatile bool up;

byte rotaryCount = 0;    // acc for rotary movement
byte prevCount = 1;              // stores value of the previous count to compare to the next count    Setting zero here breaks menu scrolling, 1 sets menu scroll first, then page nav on click
byte flashCounter = 0;               // Counter to flash Cusor


byte upScroll = 0;               // Modifyer to make menu items scroll up when end reached. Each line +8  // PROBABLY DELETE


int pageNumber = 0;    //Stores the variable for Page Number
//byte dir = 0;
int itemNumber = 0;                // Variable to store current Hightlighted Line

bool itemScroll = false;        // If true scrolls ITEMS

bool pageScroll = false; // while true menu scrolls PAGES

bool pageChanged = false;  // sets true when page has been changed to do a one time wipe of previous page.

byte previousPage = 0;   // sets the previous page for comparison to see if page has changed.


bool screenUpdate = true; // when set true OLED is updated. Otherwise changes are ignored.


// ^^ Encoder Variables ^^------------------------------------

// New OLED and Encoder Variables.

bool itemSelected = false;



// ~~~~~~~~~~~~~~~~~~~~#SD Card Variables#~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int sdSelectpin = 53;   // cs pin for chipselect



bool restoreFactory = false;   // if true runs script to re-write factory settings
bool settingsRecall = true;
bool saveSettings;          // if true runs script to save savedSettings data to the SD card
bool noSDcard;

bool cancelled = true;  // if true, delete file.
