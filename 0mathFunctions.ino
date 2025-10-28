



//  void send(byte messageType, byte msg[], byte msgSize)

/*Send a formatted KSPit packet.

  Sends the given message as payload of a KSPit message.

  Parameters
  messageType: The ID of the message channel.
  msg: A byte array representing the message contents.
  msgSize: The size of msg.

*/


// Example

//mySimpit.send(THROTTLE_MESSAGE,


// CALIBRATION IDEA

// 10-15 Samples, calculate average then use this as offset value in
// flight maths




/*  //~~~~~~~~~~~~~~~~~~ RECURSIVE FILTER FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~


     oh hell to the yes maths. yes.

*/

/*
   The last filter is a recursive filter. A recursive filter is just one that calculates a new, smoothed value (yn) by using the last smoothed value (yn – 1) and a new measurement (xn):

  yn = w × xn + (1 – w) × yn – 1
  The amount of smoothing is controlled by a weighting parameter (w). The weight is a value between 0% and 100%. When the weight is high (say 90%), the filter doesn’t smooth the measurements very much but responds quickly to changes. If the weight is low (say 10%), the filter smooths the measurements a lot but doesn’t respond very quickly to changes.

  This is my favorite filter because:

  it doesn’t need much memory (just enough to store the last measurement)
  you can control how much filtering is applied with a single parameter (the weight)
  it works well in battery powered applications because you don’t need to make many measurements at once
*/

float Yn;   //New smoothed value (Named in function)

//int w = 85; // weighting factor  value from 0% to 100%

int Xn; //New measured value

int Ypre;  // previous Measured value

int recursiveFilter(int Xn, int w, int Ypre) {

  Yn = (w * Xn) + ((1 - w) * Ypre);



  return Yn;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### FLIGHT CONTROL MATHS ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



// This function produces an offset exponential function from an input value

// if input is 10 bit resolution int from 0 to 1024, then Output = ((input-512)/16)^3
// Output is int range -32768 to + 32768 . Sized to fit an int16_t that the wire. library can handle


// could this same function be accomplished without the float and dividing by 16?







//~~~~#### Flight Control Maths LINEAR VERSION 2 ####~~~~~~~~~~~~~~~~ Input is Pre Calibrated values centered on 0. Range -512 to +512

// This version is based on x = y with a deadspace in the middle

int flightMathsPostCal(int inputValue ) {     // // input is expecting 10bit int from 0 to 1024 

 // inputValue = inputValue - calibrationOffset;                              // generates int from -512 to + 512  // CAL OFFSET could be subtracted here

  inputValue = constrain(inputValue, -512, 511);                            // Pre constrain at this stage? No Do this later // No do it now!

  //  32767 / 512 = 63.998
  //
  // so divide 512 by 3 = 170.66666
  //170 Squared = 28900   /// better example 181^2 = 32761 very much close enough
  // Serial.println(inputValue);


  long longMath = inputValue * 64;                       // 512*64 = 32768

  //~~~~~~~~~~~~~~~## Set Up Deadspace ##~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/* Imogen - October 2025, removed deadspace and test
 if (longMath < 0) {                           // if value is less than 0
  longMath = longMath + 2000;                   // add 1000,
    if (longMath > 0) {                            // if now it is more than 0, it equals zero/
      longMath = 0;
    }
  } else if (longMath > 0) {                  // otherwise, if value is over 0
    longMath = longMath - 2000;              // subtract 1000
    if (longMath < 0) {                        // if it now is less than zero
      longMath = 0;                              // it equals 0
    }
  }
*/

  /*
    if (longMath > 0) {
    longMath = longMath + 500;
    } else if (longMath < 0) {
    longMath = longMath - 500;
    }

  */


  int outputValue = int(longMath);                              // cast long to int    ( int output = int(float + 0.5) ) << not used for non float


  constrain(outputValue, -32768, 32767);                         // constrain value to fit int16_t for return value

  return outputValue;

}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### Flight Control Maths Version 3 ~~~~~~~~~ y=x^2 ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// This version is based on x^2 rather than a cubed function, as control response seemed unusualy with V2

int flightMathsV3(int inputValue, int calibrationOffset ) {     // // input is expecting 10bit int from 0 to 1024, calibrationOffset, expecting figures close to 512

  inputValue = inputValue - calibrationOffset;                              // generates int from -512 to + 512  // CAL OFFSET could be subtracted here

  //inputValue = constrain(inputValue, -512, 511);                            // Pre constrain at this stage? No Do this later

  // Square root of 32767 is roughly 181
  // 512 / 181 = 3
  // so divide 512 by 3 = 170.66666
  //170 Squared = 28900   /// better example 181^2 = 32761 very much close enough
  // Serial.println(inputValue);


  long longMath = inputValue * 100;                       // This will range from -51200 to +51200

  //  Serial.print("|longMath:  ");
  // Serial.print(longMath);

  longMath = longMath / 28;                             //  divide by 28 = 1828

  longMath = constrain(inputValue, -1810, 1810);       // Constrain here because this will round better later


  // Serial.print("|longMath/16:  ");
  //  Serial.print(longMath);

  longMath = (longMath * longMath);           // y = x^2  Generates long from -3,276,100 to + 3,276,100. within bounds of a long +-(2,147,483,647)

  // Serial.print("|    y = x^3:  ");
  // Serial.print(longMath);
  // Serial.print("                ");
  // Should add 500 at this point, as dividing by 1000 into an int lowers resolution,

  // longMath = longMath + 500;                                                            // for accuracy add 500 so it rounds correctly?

  // this does not work hmm needs an IF statement


  if (longMath > 0) {
    longMath = longMath + 500;
  } else if (longMath < 0) {
    longMath = longMath - 500;
  }

  longMath = longMath / 10;                             // divide by 100 (10^2)

  // Serial.print("|    /1000:  ");

  // Serial.println(longMath);


  int outputValue = int(longMath);                              // cast long to int    ( int output = int(float + 0.5) ) << not used for non float


  constrain(outputValue, -32768, 32767);                         // constrain value to fit int16_t for return value


  //  Serial.print("|    outputValue:  ");

  // Serial.println(outputValue);


  return outputValue;

}







//~~~~#### Flight Control Maths LINEAR ####~~~~~~~~~~~~~~~~

// This version is based on x = y with a deadspace in the middle

int flightMathsLinear(int inputValue, int calibrationOffset ) {     // // input is expecting 10bit int from 0 to 1024, calibrationOffset, expecting figures close to 512

  inputValue = inputValue - calibrationOffset;                              // generates int from -512 to + 512  // CAL OFFSET could be subtracted here

  inputValue = constrain(inputValue, -512, 511);                            // Pre constrain at this stage? No Do this later

  //  32767 / 512 = 63.998
  //
  // so divide 512 by 3 = 170.66666
  //170 Squared = 28900   /// better example 181^2 = 32761 very much close enough
  // Serial.println(inputValue);


  long longMath = inputValue * 64;                       // 512*64 = 32768

  //~~~~~~~~~~~~~~~## Set Up Deadspace ##~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  if (longMath < 0) {                           // if value is less than 0
    longMath = longMath + 2000;                   // add 1000,
    if (longMath > 0) {                            // if now it is more than 0, it equals zero/
      longMath = 0;
    }
  } else if (longMath > 0) {                  // otherwise, if value is over 0
    longMath = longMath - 2000;              // subtract 1000
    if (longMath < 0) {                        // if it now is less than zero
      longMath = 0;                              // it equals 0
    }
  }


  /*
    if (longMath > 0) {
    longMath = longMath + 500;
    } else if (longMath < 0) {
    longMath = longMath - 500;
    }

  */


  int outputValue = int(longMath);                              // cast long to int    ( int output = int(float + 0.5) ) << not used for non float


  constrain(outputValue, -32768, 32767);                         // constrain value to fit int16_t for return value

  return outputValue;

}





















// This function produces an offset exponential function from an input value

// if input is 10 bit resolution int from 0 to 1024, then Output = ((input-512)/16)^3
// Output is int range -32768 to + 32768 . Sized to fit an int16_t that the wire. library can handle


// could this same function be accomplished without the float and dividing by 16?

int flightMathsV2(int inputValue, int calibrationOffset ) {     // // input is expecting 10bit int from 0 to 1024, calibrationOffset, expecting figures close to 512

  inputValue = inputValue - calibrationOffset;                              // generates int from -512 to + 512  // CAL OFFSET could be subtracted here

  inputValue = constrain(inputValue, -512, 511);                            // Pre constrain at this stage?

  // Serial.println(inputValue);


  long longMath = inputValue * 10;                       // This will range from -5120 to +5120

  //  Serial.print("|longMath:  ");
  // Serial.print(longMath);

  longMath = longMath / 16;                             // /16 generates long from -320 to + 320

  // Serial.print("|longMath/16:  ");
  //  Serial.print(longMath);

  longMath = (longMath * longMath * longMath);           // y = x^3  Generates long from -32768000 to + 32768000. one order of magnitude within
  // bounds of a long +-(2,147,483,647)

  // Serial.print("|    y = x^3:  ");
  // Serial.print(longMath);
  // Serial.print("                ");
  // Should add 500 at this point, as dividing by 1000 into an int lowers resolution,

  // longMath = longMath + 500;                                                            // for accuracy add 500 so it rounds correctly?

  // this does not work hmm needs an IF statement


  if (longMath > 0) {
    longMath = longMath + 500;
  } else if (longMath < 0) {
    longMath = longMath - 500;
  }

  longMath = longMath / 1000;                             // divide by 1000 (10^3)

  // Serial.print("|    /1000:  ");

  // Serial.println(longMath);


  int outputValue = int(longMath);                              // cast long to int    ( int output = int(float + 0.5) ) << not used for non float


  constrain(outputValue, -32768, 32767);                         // constrain value to fit int16_t for return value


  //  Serial.print("|    outputValue:  ");

  // Serial.println(outputValue);


  return outputValue;

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### OLD Flight Control Maths####~~~~~~~~~~~~~#### DEPRECIATED!!! ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// OLD flightMaths algorithm << DEPRECIATED

int flightMaths(int inputValue, int calibrationOffset) {   // input is expecting 10bit int from 0 to 1024, calibrationOffset, expecting figures close to 512


  inputValue = inputValue - calibrationOffset;                             // generates int from -512 to + 512

  // Pre constrain at this stage?

  float inputFloat = float(inputValue);                     // cast int to a float?

  float floatMath = inputFloat / 16.0;                                  // generates float from -32 to + 32

  //  Serial.print("floatMath:  ");

  //  Serial.print(floatMath);

  floatMath = (floatMath * floatMath * floatMath);                 // y = x^3  Generates float from -32768 to + 32768.

  //  Serial.print("    y = x^3:  ");

  //  Serial.print(floatMath);

  int outputValue = int(floatMath + 0.5);                            // Simple way to do rounding. Add 0.5 and cast to int     int output = int(float + 0.5)
  // if input is 2.3 // 2.3+0.5 = 2.7.    int(2.7)= 2
  // if input is 2.7 // 2.7+0.5 = 3.2.    int(3.2)= 3     // Both answers are rounded correctly.

  constrain(outputValue, -32768, 32767);                         // constrain value to fit int16_t for return value


  // Serial.print("    outputValue:  ");

  // Serial.println(outputValue);


  return outputValue;
}
