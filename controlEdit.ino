//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### Controls Edit ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
    When triggered this routine edits the assignment of controls to

    the "stock" matricies

    This will be changed later so a standard recall can still be triggered


*/


void controlsEdit() {

  //  Serial.println(rocketControlEdit);

  if (rocketControlEdit) {


    if (rotaryCount > prevCount) {
      RocketintcontrolArray[itemNumber - 1] = (RocketintcontrolArray[itemNumber - 1] + 1);
    } else if (rotaryCount < prevCount) {
      RocketintcontrolArray[itemNumber - 1] = (RocketintcontrolArray[itemNumber - 1] - 1);
    }



    if (RocketintcontrolArray[itemNumber - 1] > 10) {                            /// Makes sure values dont roll over and read from the wrong memory locations
      RocketintcontrolArray[itemNumber - 1] = 0;
    } else if (RocketintcontrolArray[itemNumber - 1] < 0) {
      RocketintcontrolArray[itemNumber - 1] = 10;

    }
  }


  if (planeControlEdit) {


    if (rotaryCount > prevCount) {
      PlaneintcontrolArray[itemNumber - 1] = (PlaneintcontrolArray[itemNumber - 1] + 1);
    } else if (rotaryCount < prevCount) {
      PlaneintcontrolArray[itemNumber - 1] = (PlaneintcontrolArray[itemNumber - 1] - 1);
    }



    if (PlaneintcontrolArray[itemNumber - 1] > 10) {                            /// Makes sure values dont roll over and read from the wrong memory locations
      PlaneintcontrolArray[itemNumber - 1] = 0;
    } else if (PlaneintcontrolArray[itemNumber - 1] < 0) {
      PlaneintcontrolArray[itemNumber - 1] = 10;

    }
  }




  if (roverControlEdit) {


    if (rotaryCount > prevCount) {
      RoverintcontrolArray[itemNumber - 1] = (RoverintcontrolArray[itemNumber - 1] + 1);
    } else if (rotaryCount < prevCount) {
      RoverintcontrolArray[itemNumber - 1] = (RoverintcontrolArray[itemNumber - 1] - 1);
    }



    if (RoverintcontrolArray[itemNumber - 1] > 10) {                            /// Makes sure values dont roll over and read from the wrong memory locations
      RoverintcontrolArray[itemNumber - 1] = 0;
    } else if (RoverintcontrolArray[itemNumber - 1] < 0) {
      RoverintcontrolArray[itemNumber - 1] = 10;

    }
  }





} // End of Control Edit
