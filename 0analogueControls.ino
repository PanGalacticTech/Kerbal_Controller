
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### ANALOG CONTROLS ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// THESE SCRIPTS: use outputArray[0-7] pointers that should contain the pin info to the analogRead commands,
// do maths to sort the data into the correct formats, then return structured messages ready to plug into
// serialPrint functions, or commands sent to KSP/ other device

//
/*
  int unsigned outputArray[8] {
  0  pitchMaster,
  1  rollMaster,
  2  yawMaster,
  3  transXmaster,
  4  transYmaster,
  5  transZmaster,
  6  wheelSteerMaster,
  7  wheelThrottleMaster
  };

*/


// These arrays are used for the readJoystics function;

/*

  unsigned int *inputArray[10] {
  Ax, Ay, Az,
  Bx, By, Bz,
  Cx, Cy,
  Dx, Dy
  };


  int analogReadings[10] = {

  axReading, ayReading, azReading,
  bxReading, byReading, bzReading,
  cxReading, cyReading,
  dxReading, dyReading

  };


  int inputCalArray[10] {
  AxCal, AyCal, AzCal,
  BxCal, ByCal, BzCal,
  CxCal, CyCal,
  DxCal, DyCal
  };


  int controlMatrix[][10] = {     //[outputs][inputs]  // First array no of rows should be undeclared // coloumns need to be declared apparently

  //x > outputs( for loop j)                    // v y inputs(for loop i)

  //  0, 1 , 2 , 3 , 4 ,  5 , 6 , 7 , 8, 9
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




*/


// Function to read all analogue inputs, save them into an array and recenter the readings at zero using the calibration factors.

void readJoysticks(bool printSerial) {                     //  Returns the analogReadings array with values from -512 to + 512



  for (int i = 0; i < 10; i++) {



    analogReadings[i] = analogRead(inputArray[i]);


    // Pre Calibration Serial readout
    /*
         Serial.print(inputNames[i]);
         Serial.print(":  ");
         Serial.print(analogReadings[i]);
         Serial.print("  Cal =");
         Serial.print(inputCalArray[i]);
    */


    analogReadings[i] = (analogReadings[i] - inputCalArray[i]);

    // Post Calibration Serial readout
    /*

        if (printSerial) {
          Serial.print(inputNames[i]);
          Serial.print(":  ");
          Serial.print(analogReadings[i]);
          Serial.print("  Cal =");


          Serial.print(inputCalArray[i]);
          Serial.print("   ");
          }

    */

    constrain(analogReadings[i], -512 , 512);    // probably good practice




  }
  //  Serial.println("   ");

}



//######
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Rotation Control  VERSION 2 ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Controls Vessel Rotation

// This is now fed pre-calibrated values from -512 to +512 centered on zero.
// flight maths script needs to be V2 to account for pre-calibration

//int currentPitchinput;   // this holds the number of the input array which holds the assigned pitch reading




void rotateControlV2(bool invertPitch, bool invertRoll, bool invertYaw) {

  // bitmasks
  //     - 1: pitch
  //     - 2: roll
  //     - 4: yaw
  /*
    // set up rotationMessage data structures containing Rotation Data Variables                 // Could this be moved to setup so only runs once?
    rotationMessage PITCH = {};                                                                  // actually is declared in variables before setup
    rotationMessage ROLL = {};
    rotationMessage YAW = {};

  */
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Pitch Control~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // if (invertPitch == false) {

  pitchReading =  analogReadings[MasterintcontrolArray[0]];               // reads the value held in the array position selected by the value set in the mastercontrolArray Position 0 = pitch

  //  pitchReading = pitchReading;    // - *outputCalArray[0];




  if (invertPitch == true) {
    pitchReading = map((pitchReading), -512, 512, 512, -512);                // if pitch inversion true, (multiply result by -1)< NO stop thinking this will work!! this should be as simple as this now
  }

  pitchReading  = flightMathsPostCal(pitchReading);                       // This returns int16_t from -32768 to 32767

  PITCH.pitch = constrain(pitchReading, -32768, 32767);
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Roll Control~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //if (invertRoll == false) {

  rollReading = analogReadings[MasterintcontrolArray[1]];                              // reads the value held in the array position selected by the value set in the mastercontrolArray Position 1 = roll

  // rollReading = rollReading;     // - *outputCalArray[1];


  if (invertRoll == true) {
    rollReading = map((rollReading), -512, 512, 512, -512);                    // if pitch inversion true, multiply result by -1 this should be as simple as this now  }
  }

  rollReading = flightMathsPostCal(rollReading);

  // Serial.println("   ");
  //Serial.println(rollReading);

  ROLL.roll = constrain(rollReading, -32768, 32767);

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Yaw Control~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //  if (invertYaw == false) {

  yawReading = analogReadings[MasterintcontrolArray[2]];                               // reads the value held in the array position selected by the value set in the mastercontrolArray Position 2 = yaw

  //yawReading = yawReading;   //// - *outputCalArray[2];

  if (invertYaw == true) {
    yawReading = map((yawReading), -512, 512, 512, -512);
  }

  yawReading = flightMathsPostCal(yawReading);         //// << THIS LINE IS BROKEN??!?!? WHY>!?!?!

  YAW.yaw = constrain(yawReading, -32768, 32767);

  //~~~~~~------------------~~~~~ Joystick Deadspace~~~~~~~~--------------------~~~~~~~~~  // This probably is not needed now thanks
  // to the algorithm
  // added deadspace
  //  if (PITCH.pitch >= (0 - deadSpace) && PITCH.pitch <= (0 + deadSpace)) {            // does this need to change to && ??
  //    PITCH.pitch = 0;
  //  }

  //  if (ROLL.roll >= (0 - deadSpace) && ROLL.roll <= (0 + deadSpace)) {
  //    ROLL.roll = 0;
  //  }

  //  if (YAW.yaw >= (0 - deadSpace) && YAW.yaw <= (0 + deadSpace)) {                     // HOLY SHIT yes it most probably should. DO TONIGHT!!! 05/12/19
  //   YAW.yaw = 0;
  //  }

  // bitmasks
  //     - 1: pitch
  //     - 2: roll
  //     - 4: yaw

  PITCH.mask = 1;                                                                  // could this also just be done once in the setup?
  ROLL.mask = 2;
  YAW.mask = 4;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ send rotation messages // Depreciated -- Handled by serialSend ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // mySimpit.send(ROTATION_MESSAGE, PITCH);  //1 bitmasks pitch, max 32 bits, each value is 16bits so can only send 2 per time.
  //  mySimpit.send(ROTATION_MESSAGE, ROLL);  // 4 bitmasks roll, max 32 bits, each value is 16bits so can only send 2 per time.
  //  mySimpit.send(ROTATION_MESSAGE, YAW);  // 4 bitmasks roll, max 32 bits, each value is 16bits so can only send 2 per time.

}










//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Translation Control VERSION 2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Translation controls become active when RCS control is active.
void translationControlV2(bool invertX, bool invertY, bool invertZ) {


  /*
    translationMessage XAXIS = {};                                                              // this is designated outside of this script
    translationMessage YAXIS = {};
    translationMessage ZAXIS = {};

  */


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~X-Translation Control~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  XReading = analogReadings[MasterintcontrolArray[3]];                               // reads the value held in the array position selected by the value set in the mastercontrolArray Position 3 = Xtranslation
  

  if (invertX == true) {
    XReading = map((XReading), -512, 512, 512, -512);
  }

  XReading = flightMathsPostCal(XReading);         //// << THIS LINE IS BROKEN??!?!? WHY>!?!?!

 
  XAXIS.X  = constrain(XReading , -32768, 32767);

//Serial.println(XAXIS.X);

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Y-Translation Control~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  YReading = analogReadings[MasterintcontrolArray[4]];                               // reads the value held in the array position selected by the value set in the mastercontrolArray Position 4 = Ytranslation


  if (invertY == true) {
    YReading = map((YReading), -512, 512, 512, -512);
  }

  YReading = flightMathsPostCal(YReading);         //// << THIS LINE IS BROKEN??!?!? WHY>!?!?!

  YAXIS.Y  = constrain(YReading , -32768, 32767);


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Z-Translation Control~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  ZReading = analogReadings[MasterintcontrolArray[5]];                               // reads the value held in the array position selected by the value set in the mastercontrolArray Position 4 = Ytranslation


  if (invertZ == true) {
    ZReading = map((ZReading), -512, 512, 512, -512);
  }

  ZReading = flightMathsPostCal(ZReading);         //// << THIS LINE IS BROKEN??!?!? WHY>!?!?!

  ZAXIS.Z  = constrain(ZReading , -32768, 32767);






  /*
    // added deadspace
    if (XAXIS.X >= (0 - deadSpace) && XAXIS.X <= (0 + deadSpace)) {                            // does this need to change to && ??
      XAXIS.X = 0;
    }

    if (YAXIS.Y >= (0 - deadSpace) && YAXIS.Y <= (0 + deadSpace)) {                               // YES!!! I THINK DEFO NEEDS TO CHANGE!!! HOLY CRAP WTF HOW
      YAXIS.Y = 0;                                                                              // DID THIS EVEN WORK IN THE FIRST PLACE?!?!?!?
    }

    if (ZAXIS.Z >= (0 - deadSpace) && ZAXIS.Z <= (0 + deadSpace)) {
      ZAXIS.Z = 0;
    }

  */



  XAXIS.mask = 1;                                                                         // could this also just be done once in the setup?
  YAXIS.mask = 2;
  ZAXIS.mask = 4;

  /*
    mySimpit.send(TRANSLATION_MESSAGE, XAXIS);  // 1 bitmasks X, max 32 bits, each value is 16bits so can only send 2 per time.
    mySimpit.send(TRANSLATION_MESSAGE, YAXIS);  // 2 bitmasks Y, max 32 bits, each value is 16bits so can only send 2 per time.
    mySimpit.send(TRANSLATION_MESSAGE, ZAXIS);  // 4 bitmasks Z, max 32 bits, each value is 16bits so can only send 2 per time.

  */

}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Wheel Controls~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    wheelMessage STEER = {};            // depreciated values as this can be handled with a single message
//    wheelMessage THROTTLE = {};          // this is set up before setup


void wheelControlV2(bool invertWheel, bool invertThrottle) {

  if (roverMode == false) {

    WHEELDATA.steer = 0;
    WHEELDATA.throttle = 0;

  } else if (roverMode == true) {

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~## Wheel Steer ##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    wheelReading = analogReadings[MasterintcontrolArray[6]];                               // reads the value held in the array position selected by the value set in the mastercontrolArray Position 4 = Ytranslation


    if (invertWheel == true) {
      wheelReading = map((wheelReading), -512, 512, 512, -512);
    }

    wheelReading = flightMathsPostCal(wheelReading);                       //// << THIS LINE IS BROKEN??!?!? WHY>!?!?! ?!?! is it maybve not now

    WHEELDATA.steer = constrain(wheelReading , -32768, 32767);



    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~## Wheel Throttle ##~~~~~~~~~~~~~~~~~~~~~~~~~

    throttleReading = analogReadings[MasterintcontrolArray[7]];                               // reads the value held in the array position selected by the value set in the mastercontrolArray Position 4 = Ytranslation


    if (invertThrottle == true) {
      throttleReading = map((throttleReading), -512, 512, 512, -512);
    }

    throttleReading = flightMathsPostCal(throttleReading);                       //// << THIS LINE IS BROKEN??!?!? WHY>!?!?! ?!?! is it maybve not now

    WHEELDATA.throttle = constrain(throttleReading , -32768, 32767);




    // DONT THINK THIS IS NEEDED ANY LONGER>

    //    if (WHEELDATA.steer >= (0 - deadSpace) && WHEELDATA.steer <= (0 + deadSpace)) {                  // does this need to change to && ??
    //     WHEELDATA.steer = 0;
    //    }

    //   if (WHEELDATA.throttle >= (0 - deadSpace) && WHEELDATA.throttle <= (0 + deadSpace)) {                  // does this need to change to && ??
    ////     WHEELDATA.throttle = 0;
    ///    }
    //
    //  }

    // STEER.mask = 1;                                                                         // could this also just be done once in the setup?
    // THROTTLE.mask = 2;
    // I dont understand how the mask works with 2 values, are they added?

    WHEELDATA.mask = 3;  //????    This does seem to work                    // otherwise try setting this before writing data?

  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Wheel Message Info ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  struct wheelMessage {
//  int16_t steer;      //< Wheel steer.
//  int16_t throttle;    //< Wheel throttle.
/** The mask indicates which elements are intentionally set. Unset elements
    should be ignored. It should be one or more of:

    - 1: steer
    - 2: throttle
*/
//  byte mask;
























//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Throttle Control ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Controls Vessel Throttle
void throttleControl() {

  //  throttleValue = constrain(map(analogRead(throttlePin), 1024, 0, 0, 32767), 0 , 32767);   // arduino guide says to avoid this method!!!

  // Try this code instead!!!!
  throttleValue =  map(analogRead(throttlePin), 1024, 0, 0, 32767);

  throttleValue = constrain(throttleValue, 0 , 32767);


  // This code below is a bit of a hack to stop spurious readings of the throttle up to about +200

  if (throttleValue < 32600) {     // Arbritary value, aim is more control low down the throttle range, but opening the taps
    throttleValue =  (throttleValue - 200);                  // will enable full throttle.

    if (throttleValue <= 0) {                                // this slightly less linear response is probably more accurate to real
      throttleValue = 0;                                     // engines anyway. HA
    }
  }



  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Set up throttle deadspace. Without this, throttle never reaches zero
  if (throttleValue < 40) {
    throttleValue = 0;
  }

  // This does need some filtering. Cap over input?

  // First attempt at some filtering using algorithm. Lets see how do.      recursiveFilter on Notes Page
  smoothThrottle = recursiveFilter(throttleValue, 1, previousThrottle);

  previousThrottle = smoothThrottle;

  // mySimpit.send(THROTTLE_MESSAGE, throttleValue);   // Command Depreciated, handled by serialSend
}



//######
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Rotation Control ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Controls Vessel Rotation
void rotateControl(bool invertPitch, bool invertRoll, bool invertYaw) {

  // bitmasks
  //     - 1: pitch
  //     - 2: roll
  //     - 4: yaw
  /*
    // set up rotationMessage data structures containing Rotation Data Variables                 // Could this be moved to setup so only runs once?
    rotationMessage PITCH = {};                                                                  // actually is declared in variables before setup
    rotationMessage ROLL = {};
    rotationMessage YAW = {};

  */
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Pitch Control~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // if (invertPitch == false) {

  pitchReading = (analogRead(outputArray[0]));                 // Generates int from 0 to 1024

  //  pitchReading = pitchReading;    // - *outputCalArray[0];

  if (invertPitch == true) {
    pitchReading = map((pitchReading), 0, 1024, 1024, 0);                // if pitch inversion true, (multiply result by -1)< NO stop thinking this will work!! this should be as simple as this now
  }

  pitchReading  = flightMathsLinear(pitchReading, outputCalArray[0]);                       // This returns int16_t from -32768 to 32767

  PITCH.pitch = constrain(pitchReading, -32768, 32767);
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Roll Control~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //if (invertRoll == false) {

  rollReading = (analogRead(outputArray[1]));

  // rollReading = rollReading;     // - *outputCalArray[1];


  if (invertRoll == true) {
    rollReading = map((rollReading), 0, 1024, 1024, 0);                    // if pitch inversion true, multiply result by -1 this should be as simple as this now  }
  }

  rollReading = flightMathsLinear(rollReading, outputCalArray[1]);

  // Serial.println("   ");
  //Serial.println(rollReading);

  ROLL.roll = constrain(rollReading, -32768, 32767);

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Yaw Control~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //  if (invertYaw == false) {

  yawReading = (analogRead(outputArray[2]));

  //yawReading = yawReading;   //// - *outputCalArray[2];

  if (invertYaw == true) {
    yawReading = map((yawReading), 0, 1024, 1024, 0);
  }

  yawReading = flightMathsLinear(yawReading, outputCalArray[2]);         //// << THIS LINE IS BROKEN??!?!? WHY>!?!?!

  YAW.yaw = constrain(yawReading, -32768, 32767);

  //~~~~~~------------------~~~~~ Joystick Deadspace~~~~~~~~--------------------~~~~~~~~~  // This probably is not needed now thanks
  // to the algorithm
  // added deadspace
  //  if (PITCH.pitch >= (0 - deadSpace) && PITCH.pitch <= (0 + deadSpace)) {            // does this need to change to && ??
  //    PITCH.pitch = 0;
  //  }

  //  if (ROLL.roll >= (0 - deadSpace) && ROLL.roll <= (0 + deadSpace)) {
  //    ROLL.roll = 0;
  //  }

  //  if (YAW.yaw >= (0 - deadSpace) && YAW.yaw <= (0 + deadSpace)) {                     // HOLY SHIT yes it most probably should. DO TONIGHT!!! 05/12/19
  //   YAW.yaw = 0;
  //  }

  // bitmasks
  //     - 1: pitch
  //     - 2: roll
  //     - 4: yaw

  PITCH.mask = 1;                                                                  // could this also just be done once in the setup?
  ROLL.mask = 2;
  YAW.mask = 4;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ send rotation messages // Depreciated -- Handled by serialSend ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // mySimpit.send(ROTATION_MESSAGE, PITCH);  //1 bitmasks pitch, max 32 bits, each value is 16bits so can only send 2 per time.
  //  mySimpit.send(ROTATION_MESSAGE, ROLL);  // 4 bitmasks roll, max 32 bits, each value is 16bits so can only send 2 per time.
  //  mySimpit.send(ROTATION_MESSAGE, YAW);  // 4 bitmasks roll, max 32 bits, each value is 16bits so can only send 2 per time.

}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Translation Control~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Translation controls become active when RCS control is active.
void translationControl() {


  /*
    translationMessage XAXIS = {};                                                              // this is designated outside of this script
    translationMessage YAXIS = {};
    translationMessage ZAXIS = {};

  */


  // This should all change to match other flight controls, but It kinda works alright already so untill I need to it STAYS goddamnit.

  XAXIS.X = constrain(map(analogRead(outputArray[3]), 0, 1024, -32768, 32767), -32768, 32767);
  YAXIS.Y = constrain(map(analogRead(outputArray[4]), 0, 1024, -32768, 32767), -32768, 32767);
  ZAXIS.Z = constrain(map(analogRead(outputArray[5]), 0, 1024, -32768, 32767), -32768, 32767);

  // added deadspace
  if (XAXIS.X >= (0 - deadSpace) && XAXIS.X <= (0 + deadSpace)) {                            // does this need to change to && ??
    XAXIS.X = 0;
  }

  if (YAXIS.Y >= (0 - deadSpace) && YAXIS.Y <= (0 + deadSpace)) {                               // YES!!! I THINK DEFO NEEDS TO CHANGE!!! HOLY CRAP WTF HOW
    YAXIS.Y = 0;                                                                              // DID THIS EVEN WORK IN THE FIRST PLACE?!?!?!?
  }

  if (ZAXIS.Z >= (0 - deadSpace) && ZAXIS.Z <= (0 + deadSpace)) {
    ZAXIS.Z = 0;
  }



  XAXIS.mask = 1;                                                                         // could this also just be done once in the setup?
  YAXIS.mask = 2;
  ZAXIS.mask = 4;

  /*
    mySimpit.send(TRANSLATION_MESSAGE, XAXIS);  // 1 bitmasks X, max 32 bits, each value is 16bits so can only send 2 per time.
    mySimpit.send(TRANSLATION_MESSAGE, YAXIS);  // 2 bitmasks Y, max 32 bits, each value is 16bits so can only send 2 per time.
    mySimpit.send(TRANSLATION_MESSAGE, ZAXIS);  // 4 bitmasks Z, max 32 bits, each value is 16bits so can only send 2 per time.

  */

}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Wheel Controls~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    wheelMessage STEER = {};            // depreciated values as this can be handled with a single message
//    wheelMessage THROTTLE = {};          // this is set up before setup


void wheelControl() {

  if (roverMode == false) {

    WHEELDATA.steer = 0;
    WHEELDATA.throttle = 0;

  } else if (roverMode == true) {

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~## Wheel Steer ##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    wheelReading = (analogRead(outputArray[6]));                 // Generates int from 0 to 1024

    // if (invertWheel == true) {
    //    wheelReading = map((wheelReading), 0, 1024, 1024, 0);                // if wheel inversion true, (multiply result by -1)< NO stop thinking this will work!! this should be as simple as this now
    //  }

    wheelReading  = flightMathsLinear(wheelReading, outputCalArray[6]);                       // This returns int16_t from -32768 to 32767

    WHEELDATA.steer = constrain(wheelReading, -32768, 32767);



    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~## Wheel Throttle ##~~~~~~~~~~~~~~~~~~~~~~~~~

    throttleReading = (analogRead(outputArray[7]));                 // Generates int from 0 to 1024

    // if (invertWheel == true) {
    //    wheelReading = map((wheelReading), 0, 1024, 1024, 0);                // if wheel inversion true, (multiply result by -1)< NO stop thinking this will work!! this should be as simple as this now
    //  }

    throttleReading  = flightMathsLinear(throttleReading, outputCalArray[7]);                       // This returns int16_t from -32768 to 32767

    WHEELDATA.throttle = constrain(throttleReading, -32768, 32767);




    // DONT THINK THIS IS NEEDED ANY LONGER>

    //    if (WHEELDATA.steer >= (0 - deadSpace) && WHEELDATA.steer <= (0 + deadSpace)) {                  // does this need to change to && ??
    //     WHEELDATA.steer = 0;
    //    }

    //   if (WHEELDATA.throttle >= (0 - deadSpace) && WHEELDATA.throttle <= (0 + deadSpace)) {                  // does this need to change to && ??
    ////     WHEELDATA.throttle = 0;
    ///    }
    //
    //  }

    // STEER.mask = 1;                                                                         // could this also just be done once in the setup?
    // THROTTLE.mask = 2;
    // I dont understand how the mask works with 2 values, are they added?

    WHEELDATA.mask = 3;  //????    This does seem to work                    // otherwise try setting this before writing data?

  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Wheel Message Info ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  struct wheelMessage {
//  int16_t steer;      //< Wheel steer.
//  int16_t throttle;    //< Wheel throttle.
/** The mask indicates which elements are intentionally set. Unset elements
    should be ignored. It should be one or more of:

    - 1: steer
    - 2: throttle
*/
//  byte mask;
