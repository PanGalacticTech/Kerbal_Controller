

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Menu Pages ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




char     controlHeading[23] = {"Control Assignments  "};

// use invertHeadings for control assignments too

char    inversionHeading[23] = {"Control Inversions   "};

char rocketInvertHeading[23] = {"Rocket               "};
char  planeInvertHeading[23] = {"Plane                "};
char  roverInvertHeading[23] = {"Rover                "};

char          invertTrue[10] = {"  True    "};
char         invertFalse[10] = {"  False   "};
char          invertNull[10] = {"          "};

//bool rkt = false;
//bool pln = false;
//bool rvr = false;
//bool inversionPage1;
//bool inversionPage2;

bool rocketControlEdit = false;
bool planeControlEdit = false;
bool roverControlEdit = false;

int numberOfItems = 3;    //Number of items on any menu page

int lineAdjust;    // This variable makes sure correct line is highlighted on OLED, while itemNumber is pointing to the item that is currently selected.

//bool inversionAdjusted = false; // variable goes true on making an edit to control inversions. Triggers  controlsUnassigned = true to run controls assigned when page navigates away from control inverts;


void staticMenu() {                     // Function to replace the OLED buffer with the page information, based on pagenumber

  // Serial.println(pageNumber);

  // Clear the text buffer if page number has changed, before printing new pages
  if (previousPage != pageNumber) {
    messageReplace(0 , lineWipe);   // recently addedm remove if problems occur
    messageReplace(1 , lineWipe);
    messageReplace(2 , lineWipe);
    messageReplace(3 , lineWipe);

  }

  if (pageNumber == 0) {                                                            // Page 0 = Kerbal Space Program Homepage

    itemNumber = 0;   /// bug fix sets itemNumber as always 0 on page 1

    messageReplace(0 , kerbalTitle);

    /*
        if (previousPage != pageNumber) {
          messageReplace(0 , lineWipe);   // recently addedm remove if problems occur
          messageReplace(1 , lineWipe);
          messageReplace(2 , lineWipe);
          messageReplace(3 , lineWipe);

        }
    */


  }
  if (pageNumber == 1) {                                        // Page 1 = Settings Page
    numberOfItems = 5;

    /*
      messageReplace(0 , settingsTitle);
      messageReplace(1 , setJoysticks);                   // change to set rotations
      messageReplace(2 ,  setInverts);                       // change to set control inversions
      messageReplace(3 , setCalibrate);                     // activate calibration
    */



    messageReplace(0 , settingsTitle);
    // scrolls lines and outPut names
    if (itemNumber <= 3) {

      messageReplace(1 , setJoysticks);                   // change to set rotations
      messageReplace(2 ,  setInverts);                       // change to set control inversions
      messageReplace(3 , setCalibrate);

    }

    else if (itemNumber > 3 && itemNumber <= 6) {
      messageReplace(1 , setSaveSettings);                   // change to set rotations
      messageReplace(2 ,  setFactoryRecall);
      messageReplace(3 , lineWipe);

    }







  }



  if (pageNumber == 2) {                                                     // Page 2 = INVERSIONS Page
    numberOfItems = 3;
    messageReplace(0 , inversionHeading);
    messageReplace(1 , rocketInvertHeading);                   //
    messageReplace(2 , planeInvertHeading);                       //
    messageReplace(3 , roverInvertHeading);                     //



  }
  if (pageNumber == 3) {                                                     // Page 3 = Rocket Control Inverts

    // messageReplace(1 , lineWipe);                                           //
    //  messageReplace(2 , lineWipe);                                                 //            outputNames[9]
    // messageReplace(3 , lineWipe);

    messageReplace(0 , rocketInvertHeading);                                        /// rocketInvertArray[]

    numberOfItems = 6;
    for (int i = 0; i < 3; i++) {
      if (itemNumber <= 3) {
        if (rocketInvertArray[i] == true) {
          lineDualreplace(i + 1 , outputNames[i],  invertTrue);
        } else {
          lineDualreplace(i + 1 , outputNames[i], invertFalse);
        }
      } else if (itemNumber > 3) {
        if (rocketInvertArray[i + 3] == true) {
          lineDualreplace(i + 1 , outputNames[i + 3],  invertTrue);
        } else {
          lineDualreplace(i + 1 , outputNames[i + 3], invertFalse);
        }
      }

    }
  }
  if (pageNumber == 4) {                                                     // Page 4 = Plane Control Inverts


    messageReplace(0 , planeInvertHeading);
    numberOfItems = 6;
    for (int i = 0; i < 3; i++) {
      if (itemNumber <= 3) {
        if (planeInvertArray[i] == true) {
          lineDualreplace(i + 1 , outputNames[i],  invertTrue);
        } else {
          lineDualreplace(i + 1 , outputNames[i], invertFalse);
        }
      } else if (itemNumber > 3) {
        if (planeInvertArray[i + 3] == true) {
          lineDualreplace(i + 1 , outputNames[i + 3],  invertTrue);
        } else {
          lineDualreplace(i + 1 , outputNames[i + 3], invertFalse);
        }
      }

    }


  }
  if (pageNumber == 5) {                                                     // Page 5 = Rover Control Inverts


    messageReplace(0 , roverInvertHeading);
    numberOfItems = 9;

    for (int i = 0; i < 3; i++) {
      if (itemNumber <= 3) {
        if (roverInvertArray[i] == true) {
          lineDualreplace(i + 1 , outputNames[i],  invertTrue);
        } else {
          lineDualreplace(i + 1 , outputNames[i], invertFalse);
        }
      } else if (itemNumber > 3 && itemNumber <= 6) {
        if (roverInvertArray[i + 3] == true) {
          lineDualreplace(i + 1 , outputNames[i + 3],  invertTrue);
        } else {
          lineDualreplace(i + 1 , outputNames[i + 3], invertFalse);
        }
      } else if (itemNumber > 6 && itemNumber <= 8) {
        if (roverInvertArray[i + 6] == true) {
          lineDualreplace(i + 1 , outputNames[i + 6],  invertTrue);
        } else  {
          lineDualreplace(i + 1 , outputNames[i + 6], invertFalse);
        }
      }

      //else if (itemNumber > 8) {
      //   lineDualreplace(i + 1 , outputNames[i + 6], invertNull);
      //  }

    }
  }

  if (pageNumber == 6) {                                                     // Page 6 = Control Assignment

    numberOfItems = 3;
    messageReplace(0 , controlHeading);
    messageReplace(1 , rocketInvertHeading);                   //
    messageReplace(2 , planeInvertHeading);                       //
    messageReplace(3 , roverInvertHeading);

  }

  if (pageNumber == 7) {                                                     // Page 7 = Rocket Control Assignment

    numberOfItems = 9;
    messageReplace(0 , rocketInvertHeading);


    //RocketintcontrolArray[8]

    for (int i = 0; i < 3; i++) {     // scrolls lines and outPut names
      if (itemNumber <= 3) {
        lineDualreplace(i + 1 , outputNames[i],  inputNames[RocketintcontrolArray[i]]);
      }

      else if (itemNumber > 3 && itemNumber <= 6) {
        lineDualreplace(i + 1 , outputNames[i + 3],  inputNames[RocketintcontrolArray[i + 3]]);
      }

      else if (itemNumber > 6 && itemNumber <= 9) {
        lineDualreplace(i + 1 , outputNames[i + 6],  inputNames[RocketintcontrolArray[i + 6]]);

      }
    }

  } // End of Page 7


  if (pageNumber == 8) {                                                     // Page 8 = Plane Control Assignment

    numberOfItems = 9;
    messageReplace(0 , planeInvertHeading);


    //PlaneintcontrolArray[8]

    for (int i = 0; i < 3; i++) {     // scrolls lines and outPut names
      if (itemNumber <= 3) {
        lineDualreplace(i + 1 , outputNames[i],  inputNames[PlaneintcontrolArray[i]]);
      }

      else if (itemNumber > 3 && itemNumber <= 6) {
        lineDualreplace(i + 1 , outputNames[i + 3],  inputNames[PlaneintcontrolArray[i + 3]]);
      }

      else if (itemNumber > 6 && itemNumber <= 9) {
        lineDualreplace(i + 1 , outputNames[i + 6],  inputNames[PlaneintcontrolArray[i + 6]]);

      }
    }


  } // End of Page 8


  if (pageNumber == 9) {                                                     // Page 8 = Rover Control Assignment

    numberOfItems = 9;
    messageReplace(0 , roverInvertHeading);


    //RoverintcontrolArray[8]

    for (int i = 0; i < 3; i++) {     // scrolls lines and outPut names
      if (itemNumber <= 3) {
        lineDualreplace(i + 1 , outputNames[i],  inputNames[RoverintcontrolArray[i]]);
      }

      else if (itemNumber > 3 && itemNumber <= 6) {
        lineDualreplace(i + 1 , outputNames[i + 3],  inputNames[RoverintcontrolArray[i + 3]]);
      }

      else if (itemNumber > 6 && itemNumber <= 9) {
        lineDualreplace(i + 1 , outputNames[i + 6],  inputNames[RoverintcontrolArray[i + 6]]);

      }
    }



  }


  previousPage = pageNumber;
  // screenUpdate = true;

}




// Navigation for menu items





void itemNav() {   // Function to select active ITEM NUMBER

  // Serial.println("    ");
  // Serial.println(pageNumber);
  //  Serial.println(planeInvertHeading);
  // Serial.println(pageScroll);
  // Serial.println("    ");


  // Could add in IF statement for if pageNumber > 0, else itemNumber = 0
  // single click to get to settings menu.

  if (pageNumber > 0) {

    if (pageScroll == false) {                 // If Menu Heading item is selected, scroll through pages
      if (millis() - lastRotaryfire >= rotaryTimeout) {

        if (rotaryCount > prevCount) {

          itemNumber++;

        }

        else if (rotaryCount < prevCount) {
          itemNumber--;

        }
      }

      if (itemNumber > numberOfItems) {

        itemNumber = 0;

      } else if (itemNumber < 0) {

        itemNumber = numberOfItems;

      }

      if (itemNumber <= 3) {
        lineAdjust = itemNumber;
        display.fillRoundRect(120, 8 * (itemNumber - 4), 8, 32, 2, BLACK); //(x , y, width, height, cornerRadius, color)
        display.fillRoundRect(120, 8 * itemNumber, 8, 8, 2, WHITE); //(x , y, width, height, cornerRadius, color)
        display.fillRoundRect(120, 8 * (itemNumber + 1), 8, 32, 2, BLACK); //(x , y, width, height, cornerRadius, color)

      } else if (itemNumber > 3 && itemNumber <= 6) {

        lineAdjust = itemNumber - 3;

        display.fillRoundRect(120, 8 * (lineAdjust - 4), 8, 32, 2, BLACK); //(x , y, width, height, cornerRadius, color)
        display.fillRoundRect(120, (8 * lineAdjust), 8, 8, 2, WHITE); //(x , y, width, height, cornerRadius, color)
        display.fillRoundRect(120, 8 * (lineAdjust + 1), 8, 32, 2, BLACK); //(x , y, width, height, cornerRadius, color)

      } else if (itemNumber > 6) {

        lineAdjust = itemNumber - 6;

        display.fillRoundRect(120, 8 * (lineAdjust - 4), 8, 32, 2, BLACK); //(x , y, width, height, cornerRadius, color)
        display.fillRoundRect(120, (8 * lineAdjust), 8, 8, 2, WHITE); //(x , y, width, height, cornerRadius, color)
        display.fillRoundRect(120, 8 * (lineAdjust + 1), 8, 32, 2, BLACK); //(x , y, width, height, cornerRadius, color)
      }


      //  screenUpdate = true;

    }

  } else {
    itemNumber = 0;
    lineAdjust = itemNumber;  // bug fix
  }
} //--------------------------








// Selection scrip for menu items

// This checks if the button has been switched and then enacts commands based on what item was selected.

void itemSelect() {         // script for triggering actions based on menu item selected.   // generate bools, then use bools to trigger actions elsewhere

  //~~~~~~~~~~~~~~~~~~~~~~~Page 0~~~~~~~~~~~~~~~~~~~~
  if (itemSelected) {                          // if the rotary button has been clicked



    // on click// These scripts will turn off any bools set elsewhere that need to be turned off on a second clock of the rotary switch  <<< NOPE put this in rotary scrip page

    //    if (rocketControlEdit == true) {

    //     rocketControlEdit = false;

    //   }





    if (pageNumber == 0) {                     // when clicked go directly to settings.
      pageNumber = 1;
      pageScroll = false;
      lineColours[0] = 1;
    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Page 1 ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    else if (pageNumber == 1) {            // Page 1 settings

      if (itemNumber == 0) {
        pageNumber = 0;                     // this whole if may need to be changed if another scrollable page is created later. But it makes it feel more natural if there are only
        pageScroll = false;                  // two pages. This makes clicking the rotary enter and exit the settings menu instead of scrolling.
        lineColours[0] = 1;

      }

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Item 1 ###~~~~~~~~~~~~~~~~~~~~~~~~~Control Assign~~~~~~~~~~~~~
      if (itemNumber == 1) {
        pageNumber = 6;                        // if item number 1 is selected, navigate to page 6
        pageScroll = false;              // sets this ready to scroll through menu items again
        itemNumber = 1;                       // Set item back to 1, this makes it feel much more natural.
        itemSelected = false;           // This resets the rotary Button push, ready for retrigger
        lineColours[1] = 1;

      }

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Item 2 ###~~~~~~~~~~~~~~~~~~~~~~~~ INVERSION SELECT ~~~~~~

      if (itemNumber == 2) {                 // item 2, Inversion Setup
        pageNumber = 2;                        // if item number 2 is selected, navigate to page 2
        pageScroll = false;              // sets this ready to scroll through menu items again
        itemNumber = 1;                       // Set item back to 1, this makes it feel much more natural.
        itemSelected = false;           // This resets the rotary Button push, ready for retrigger
        //  pageScroll = false;              // sets this ready to scroll through menu items again
        lineColours[2] = 1;                     // Resets line colour  << Eventually this could be done right at end of routein, It depends on if it works with others
      }


      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Item 3 ###~~~~~~~~~~~~~~~~~~~~~~~~

      if (itemNumber == 3) {                 // item 3, Calibration
        calibrationCall();                         // Call calibration script
        itemSelected = false;           // This resets the rotary Button push, ready for retrigger
        pageScroll = false;              // sets this ready to scroll through menu items again
        lineColours[3] = 1;                     // Resets line colour  << Eventually this could be done right at end of routein, It depends on if it works with others
      }


      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Item 4 ###~~~~~~~~~~~~~~~~~~~~~~~~

      if (itemNumber == 4) {                 // item 4, save settings

        updateDataStructure();                                // Update struct configStore savedSettings;  // variable to store the saved settings
        // this can be accessed now as
        // savedSettings.rocketControlConfig[0]
        saveSettings = true;                              // Call the Save to SD Card Script
        sdWriteSavedSettings();                           // Call the Save to SD Card Script
        settingsSavedAnimation();
        itemSelected = false;           // This resets the rotary Button push, ready for retrigger
        pageScroll = false;              // sets this ready to scroll through menu items again
        lineColours[1] = 1;                     // Resets line colour  << Eventually this could be done right at end of routein, It depends on if it works with others
      }

      if (itemNumber == 5) {                 // item 4, Factory Recalll

        // updateDataStructure();                                // Update struct configStore savedSettings;  // variable to store the saved settings
        // this can be accessed now as
        // savedSettings.rocketControlConfig[0]
        //  saveSettings = true;                              // Call the Save to SD Card Script
        deleteConfig();                           //Delete  the config file
        factoryRecallAnimation();
        itemSelected = false;           // This resets the rotary Button push, ready for retrigger
        pageScroll = false;              // sets this ready to scroll through menu items again
        lineColours[2] = 1;                     // Resets line colour  << Eventually this could be done right at end of routein, It depends on if it works with others
      }




    }   //###~~~~~~~ End of Page 1 ~~~~~~~~~###



    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Page 2 ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    else if (pageNumber == 2) {            // Page 2 Inversions

      if (itemNumber == 0) {              // back

        pageNumber = 1;
        pageScroll = false;
        lineColours[0] = 1;

      }


      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Item 1 ###~~~~~~~~~~~~~~~~~~~~~~~~
      if (itemNumber == 1) {
        pageNumber = 3;                        // Rocket Mode go to page 3
        pageScroll = false;              // sets this ready to scroll through menu items again
        itemSelected = false;
        lineColours[1] = 1;                     // Resets lin
      }
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Item 2 ###~~~~~~~~~~~~~~~~~~~~~~~~
      if (itemNumber == 2) {
        pageNumber = 4;                        // Plane Mode go to page 4
        pageScroll = false;              // sets this ready to scroll through menu items again
        itemSelected = false;
        lineColours[2] = 1;
        itemNumber = 1;                       // Set item back to 1, this makes it feel much more natural.
      }

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Item 3 ###~~~~~~~~~~~~~~~~~~~~~~~~
      if (itemNumber == 3) {
        pageNumber = 5;                        // Rover Mode go to page 3
        pageScroll = false;              // sets this ready to scroll through menu items again
        itemSelected = false;
        lineColours[3] = 1;
        itemNumber = 1;                       // Set item back to 1, this makes it feel much more natural.
      }

    }

    //###~~~~~~~ End of Page 2 ~~~~~~~~~###

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Page 3  Rocket Inversions ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    else if (pageNumber == 3) {            // Page 3 Rocket Control Inversion

      if (itemNumber == 0) {           // back button

        pageNumber = 2;

      }

      if (rocketInvertArray[itemNumber - 1] == true) {
        rocketInvertArray[itemNumber - 1] = false ;
      } else {
        rocketInvertArray[itemNumber - 1] = true ;
      }
      controlsUnassigned = true;     // triggers controls reassign
      pageScroll = false;
      itemSelected = false;
      lineColours[lineAdjust] = 1;

    }
    //###~~~~~~~ End of Page 3 ~~~~~~~~~###

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Page 4 Plane Inversions ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    else if (pageNumber == 4) {            // Page 4 Plane Control Inversion

      if (itemNumber == 0) {           // back button

        pageNumber = 2;

      }

      if (planeInvertArray[itemNumber - 1] == true) {
        planeInvertArray[itemNumber - 1] = false ;
      } else {
        planeInvertArray[itemNumber - 1] = true ;
      }
      controlsUnassigned = true;     // triggers controls reassign
      pageScroll = false;
      itemSelected = false;
      lineColours[lineAdjust] = 1;

    }
    //###~~~~~~~ End of Page 4~~~~~~~~~###

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Page 5 Rover Inversions ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    else if (pageNumber == 5) {            // Page 5 Rover Control Inversion

      if (itemNumber == 0) {           // back button

        pageNumber = 2;

      }

      if (roverInvertArray[itemNumber - 1] == true) {
        roverInvertArray[itemNumber - 1] = false ;
      } else {
        roverInvertArray[itemNumber - 1] = true ;
      }
      controlsUnassigned = true;     // triggers controls reassign
      pageScroll = false;
      itemSelected = false;
      lineColours[lineAdjust] = 1;

    }
    //###~~~~~~~ End of Page 5~~~~~~~~~###


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Page 6 Control Assignment Top Menu ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    else if (pageNumber == 6) {            // Page 6 Control Assignment Top Menu

      if (itemNumber == 0) {           // back button

        pageNumber = 1;               // make sure this reverts to the correct page.
        pageScroll = false;
        lineColours[0] = 1;
      }

      if (itemNumber == 1) {
        pageNumber = 7;                        // Rocket Mode go to page 7
        pageScroll = false;              // sets this ready to scroll through menu items again
        itemSelected = false;
        lineColours[1] = 1;
      }
      if (itemNumber == 2) {
        pageNumber = 8;                        // Plane Mode go to page 8
        pageScroll = false;              // sets this ready to scroll through menu items again
        itemSelected = false;
        lineColours[2] = 1;

      }
      if (itemNumber == 3) {
        pageNumber = 9;                        // Rover Mode go to page 9
        pageScroll = false;              // sets this ready to scroll through menu items again
        itemSelected = false;
        lineColours[3] = 1;

      }

    }
    //###~~~~~~~ End of Page 6~~~~~~~~~###

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Page 7 ROCKET Control Assignment ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    else if (pageNumber == 7) {            // Page 7 ROCKET Assignment

      if (itemNumber == 0) {           // back button
        pageNumber = 6;                     // this whole if may need to be changed if another scrollable page is created later. But it makes it feel more natural if there are only
        pageScroll = false;                  // two pages. This makes clicking the rotary enter and exit the settings menu instead of scrolling.
        lineColours[0] = 1;           // make sure this reverts to the correct page.
      }

      else if (itemNumber > 0 && itemNumber < 9) {
        if (rocketControlEdit == false) {
          rocketControlEdit = true;
        }

      } //else if (itemNumber < 0){ itemNumber = 10; }  // see if required.
    }
    //###~~~~~~~ End of Page 7~~~~~~~~~###

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Page 8 PLANE Control Assignment ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    else if (pageNumber == 8) {            // Page 8 PLANE Control Assignment
      if (itemNumber == 0) {           // back button
        pageNumber = 6;                     // this whole if may need to be changed if another scrollable page is created later. But it makes it feel more natural if there are only
        pageScroll = false;                  // two pages. This makes clicking the rotary enter and exit the settings menu instead of scrolling.
        lineColours[0] = 1;           // make sure this reverts to the correct page.
      }

      else if (itemNumber > 0 && itemNumber < 9) {
        if (planeControlEdit == false) {
          planeControlEdit = true;
        }

      } //else if (itemNumber < 0){ itemNumber = 10; }  // see if required.
    }
    //###~~~~~~~ End of Page 8~~~~~~~~~###

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### Page 9 Rover Control Assignment ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    else if (pageNumber == 9) {            // Page 9 Rover Control Assignment

      if (itemNumber == 0) {           // back button
        pageNumber = 6;                     // this whole if may need to be changed if another scrollable page is created later. But it makes it feel more natural if there are only
        pageScroll = false;                  // two pages. This makes clicking the rotary enter and exit the settings menu instead of scrolling.
        lineColours[0] = 1;           // make sure this reverts to the correct page.
      }

      else if (itemNumber > 0 && itemNumber < 9) {
        if (roverControlEdit == false) {
          roverControlEdit = true;
        }
      }
    }  //###~~~~~~~ End of Page 9~~~~~~~~~###




  }// end of (IF  item selected)
} // End of item Select Script
