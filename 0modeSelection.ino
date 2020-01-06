//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### modeSelect ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This function sets mode bools true & false
/*
   ///~~~~ KSP Mode ~~~     // Will be used to help assign matrices
  bool rocketMode = true; //
  bool planeMode = false; //
  bool roverMode = false;  //



   // This is the stock rocket matrix
  int controlMatrix[][10] = {     //[outputs][inputs]  // First array no of rows should be undeclared // coloumns need to be declared apparently

  //x > outputs( for loop j)                    // v y inputs(for loop i)

  // 0, 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8, 9
  // Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Dx, Dy
  0  {0,  0,  0,  0,  1,  0,  0,  0,  0,  0},  // 0 Pitch
  1  {0,  0,  0,  0,  0,  1,  0,  0,  0,  0},  // 1 Roll
  2  {0,  0,  0,  1,  0,  0,  0,  0,  0,  0},  // 2 Yaw

  3  {1,  0,  0,  0,  0,  0,  0,  0,  0,  0},  // 3 Trans X
  4  {0,  1,  0,  0,  0,  0,  0,  0,  0,  0},  // 4 Trans Y
  5  {0,  0,  0,  0,  0,  0,  0,  1,  0,  0},  // 5 Trans Z

  6  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  // 6 Steering (Rover)
  7  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0}   // 7 Throttle (Rover)

  };


   This Function will manipulate this matrix directly

  // Invert control array now needs to be updated along with the mode
  bool controlInvertArray[] = {
  invertPitch, invertRoll, invertYaw,
  invertX, invertY, invertZ,
  invertWheel, invertThrottle
  };





*/


/*

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

  bool rocketInvertArray[] {
  false, false, true,
  false, false, false,
  false, false
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


  bool planeInvertArray[] {
  false, true, false,
  false, false, false,
  false, false
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

  bool roverInvertArray[] {
  true, false, false,
  false, false, false,
  true, true
  };



*/




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FLIGHT MODE SELECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This Script sets the KSP flight mode depending on various states.

// this script can be used to change and set different modes, Matrix will then update based
// on bools set here

void modeSelect2() {

  if (roverMode == false) {  // rover mode is set and unset elsewhere so ignore all of this if roverMode is active

    int reading = (digitalRead(mode));   // read the mode pin

    if (reading != lastModeState) {        // if the pin state has changed

      lastModeDebounceTime = millis();    // save the time it changed

    }

    if ((millis() - lastModeDebounceTime) > debounceDelay) {


      if (reading != modeState) {

        modeState = reading;

        //  if (modeChangeTrigger == true) {                                     /// Not sure whether to use this trigger.

        if (modeState == HIGH) {  // if the MODE is high then ROCKET MODE


          Serial.println("Rocket Mode Active");
          line1Replace(2, rocketMessage , 0, 0);

          rocketMode = true;
          planeMode = false;
          roverMode = false;

        } else if (modeState == LOW) { // IF MODE is LOW then Plane Mode

          Serial.println("Plane Mode Active");
          line1Replace(2, planeMessage , 0, 0);
          rocketMode = false;
          planeMode = true;
          roverMode = false;

        }

        flightModeChange = true;
        //  }
      }
    }

    lastModeState = reading;
  }
}






// This lets other functions update specific items in the matrix and call (controlsUnassigned = true) to update the controlMatrix
// without refering to these complete stock changeds.


void modeArrayUpdate() {  // this function give updates the MasterintcontrolArray[9] with values for the other control arrays arrays

  //RocketintcontrolArray[9]
  //PlaneintcontrolArray[9]
  //RoverintcontrolArray[9]

  //MasterintcontrolArray[9]

  if (flightModeChange) {

    if (rocketMode) {

      for (int i = 0; i < 8; i++) {
        MasterintcontrolArray[i] = RocketintcontrolArray[i];
           controlInvertArray[i] = rocketInvertArray[i]; 
      }

    }  else if (planeMode) {

   for (int i = 0; i < 8; i++) {
        MasterintcontrolArray[i] = PlaneintcontrolArray[i];
           controlInvertArray[i] = planeInvertArray[i]; 
      }

    }  else if (roverMode) {

         for (int i = 0; i < 8; i++) {
        MasterintcontrolArray[i] = RoverintcontrolArray[i];
           controlInvertArray[i] = roverInvertArray[i]; 
      }
    }

       //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of Mode Matrix Assignments ~~~~~~~~~~~~~~~~~~~~~~~~~

    flightModeChange = false;  // flight mode has been changed, just need to update the outputs from the matrix
   controlsUnassigned = true; // controlMatrix has been updated, so now output array needs to have inputs reassigned to it in its new configuration  // Is this needed now?!?!?
  }

}








//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Mode Matrix Assignments ~~~~~~~~~~~~~~~~~~~~~~~~~

void modeMatrixUpdate() { // This function updates controlMatrix[][10] with the stock OR saved matrices depending on which mode have been set as TRUE


  if (flightModeChange) {     // If the flight mode has been changed set to true

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Rocket Mode Matrix Assignment ~~~~~~~~~~~~~~~~~~~~~~~~~
    if (rocketMode) {

      for (int i = 0; i < 8; i++) {                         // this cycles through output & input array
        for (int j = 0; j < 10; j++) {
          controlMatrix[i][j] = stockRocketMatrix[i][j];   // re assigns entire matrix to stock Rover matrix
        }
        controlInvertArray[i] = rocketInvertArray[i];     // This then cycles through the controlInvertArray[8] and reassigns it values from the roverInvertArray[8]
      }
    }



    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Plane Mode Matrix Assignment ~~~~~~~~~~~~~~~~~~~~~~~~~
    else if (planeMode) {

      for (int i = 0; i < 8; i++) {                         // this cycles through output & input array
        for (int j = 0; j < 10; j++) {
          controlMatrix[i][j] = stockPlaneMatrix[i][j];   // re assigns entire matrix to stock Rover matrix
        }
        controlInvertArray[i] = planeInvertArray[i];     // This then cycles through the controlInvertArray[8] and reassigns it values from the roverInvertArray[8]
      }
    }



    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Rover Mode Matrix Assignment ~~~~~~~~~~~~~~~~~~~~~~~~~
    else if (roverMode) {

      for (int i = 0; i < 8; i++) {                         // this cycles through output & input array
        for (int j = 0; j < 10; j++) {
          controlMatrix[i][j] = stockRoverMatrix[i][j];   // re assigns entire matrix to stock Rover matrix
        }
        controlInvertArray[i] = roverInvertArray[i];     // This then cycles through the controlInvertArray[8] and reassigns it values from the roverInvertArray[8]
      }
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of Mode Matrix Assignments ~~~~~~~~~~~~~~~~~~~~~~~~~

    flightModeChange = false;  // flight mode has been changed, just need to update the outputs from the matrix
    controlsUnassigned = true; // controlMatrix has been updated, so now output array needs to have inputs reassigned to it in its new configuration
  }
}
