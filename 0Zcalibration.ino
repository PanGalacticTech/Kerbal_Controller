
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Calibration ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~



//
/*  This can be run once during the setup routine, or called again later when prompted



*/



// This script runs when the calibration function is called.

void calibrationCall() {

  messageReplace(3 , calibrationStarted);                     // Replace message calibration started
  flightModeChange = true;                                         // this bool sets controls as needing assignment
  oledUpdate(1, 1, 1, 0);

  delay(500);  // delay to make sure sticks are level
  calibration(testOUTPUT);   // if rotary is clicked, start calibration routine
  delay(500);

  // All commented out bits run anyway, just need to make sure flightModechange bool is set true to trigger them

  //    modeMatrixUpdate();       // updates controlMatrix and invertArray   // MUST DO THIS TO UPDATE CALIBRATION

  //  if (testOUTPUT) {
  //     controlAssignment(true);                                          //        Assigns controls based on matrix
  //  MUST DO THIS TO UPDATE CALIBRATION
  //    } else {
  //       controlAssignment(false);
  //   }

  messageReplace(3 , calibrationComplete);
  delay(500);
 // oledUpdate(1, 1, 1, 1);                  // resets screen colors that may have changed.
  
 // messageReplace(1 , lineWipe);


}
















//inputCalArray[10]

int sampleSize = 15; // variable for number of samples

// Calibration runs through all inputs and generates an average offset value for the Neutral/Middle position.
// Saves these results into an Array to be used in analogueControls

void calibration(bool printSerial) {

  for (int i = 0; i < 10; i++) {   // Cycle through all inputs and generate an array of cal factors


  int calFactor  = averageSample(inputArray[i], sampleSize, printSerial);            // run averageSample for each of the inputArray, and save to Cal array of

 // int calFactor  = analogRead(inputArray[i]);    // simplified version as averages didnt seem to be working out for input 0   Ax

 // Serial.print(calFactor);
    
    
    inputCalArray[i] = calFactor;   // Dont know why line above was returning odd values << Think fixed. Loop elsewhere may have been writing over this location.



    // inputCalArray[i] = analogRead(inputArray[i]);
    // same size

    if (printSerial) {
      Serial.print("   In: ");
      Serial.print(inputNames[i]);
      Serial.print("   Cal: ");
      Serial.println(inputCalArray[i]);
    }

  }



  // invert the answer *(-1) so it can be added as an offset to


}


// Generates an average from multiple quick readings of an analog Input pin
int averageSample(int samplePin, int noofSamples, bool printSerial) {

  int w = 0;  // start with calibration at zero


  // wait this can be done without the array
  for (int i = 0; i < noofSamples; i++) {

    int r = analogRead(samplePin);

    w = w + r;

    if (printSerial) {
   //   Serial.print("   r:");
   //   Serial.print(r);
   //   Serial.print("   w1:");
   //   Serial.print(w);
    }
  }

  w = (w / noofSamples); // average out all the readings.

  if (printSerial) {
  //  Serial.print("   w2:");
  //  Serial.println(w);
  }

  return w;

}
