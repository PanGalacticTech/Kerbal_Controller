


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### controlAssign ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/* This function assigns control INPUTS from inputArray to outputArray

   via controlMatrix.

   This lets users assign controls whereever they like

   This page may also handle control inverting arrays

*/



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### MATRICES ####~~~~~~~~~~~~~~~~~~~~~~~~~~
// This section may contain lots of notes as it is a confusing subject.

//      int array[y][x]
//      int array[i][j]

// This is the stock rocket matrix
int controlMatrix[][10] = {     //[outputs][inputs]  // First array no of rows should be undeclared // coloumns need to be declared apparently

  //x > outputs( for loop j)                    // v y inputs(for loop i)

  // ` 0, 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8, 9
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





// Function needs to go here to do control assignments in new simplified system


void controlAssignment(bool printSerial) {

  // for loop cycles through matrix and assigns active controls where it finds 1

  // the problem here is this cannot unassign things where it finds a zero

  // this can be solved by running through array first & assigning a null

  // probably other stuff that doesnt work either.



  if (controlsUnassigned) {

    for (int i = 0; i < 8; i++) {   // first clear out any previous assignments to the output variables
      outputArray[i] = 0;

      if (printSerial) {
        Serial.println(outputArray[i]);        // serial print a list of 0s to test. Can null be assigned to an int? I doubt it.
      }

    }


    for (int i = 0; i < 8; i++) {         // this cycles through output array                // if this works I am a so happy
      for (int j = 0; j < 10; j++) {        // this cycles through inputs


        if (printSerial) {
          Serial.print(outputNames[i]);
          Serial.print(" i:[");                           // this list here prints all the output variables from each loop
          Serial.print(i);                                // and prints the input variables both with the number of their
          Serial.print("][");                              // position in the array.
          // this displays similar to ( int array[i][j] )
          Serial.print(j);
          Serial.print("]:j ");
          Serial.print(inputNames[j]);
          Serial.print("    ");
          Serial.print(controlMatrix[i][j]);
        }


        if (controlMatrix[i][j] == 1) {                       // where 1 is found in matrix

          
          
          outputArray[i] = inputArray[j];                   // current output array == current input
          
          outputCalArray[i] = inputCalArray[j];              // assigns the correct calibration to the correct input/output
         
          if (printSerial) {
            Serial.print("  << ASSIGNED  ");               // print assigned to show which input has been set to an output.
             Serial.print(outputCalArray[i]);
          }
        }
        if (printSerial) {
          Serial.println("    ");
        }
      }
    }
    controlsUnassigned = false;                               // Controls are now assigned so this script will only run once

  }

}
