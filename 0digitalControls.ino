





//~~~~~~~ MOMENTARY BUTTONS ~~~~~~~~~


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STAGING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void stageButtonv2() {


  // Read stage lock state. IF HIGH, Stage is UNLOCKED:
  if (stageLockState == HIGH) {   // if HIGH then staging is UNLOCKED

    if (stageLockbit == true) {           // if stagelock bit has been set true then turned off, this wipes the message from screen

     
      messageReplace(3, lineWipe);

      stageLockbit = false;

    }


    // this is the debounce bit

    // after staging event, want to make sure stagePin is sent LOW before retriggering.
    if ((millis() - lastStagetime) > stagingTimeout) {          // if button is not timed out, read it (timeout  can be very short)

      stageState = digitalRead(stagePin);                       // read the staging button

      if (stageState == LOW && stagingARMED == false) {         // if staging has been disarmed, but pin has been read low (unpressed)

        stagingARMED = true;                                     // re-arm the staging

      }


    }

    if (stageState == HIGH && stagingARMED == true) {             // if staging is armed & stageState is HIGH

      stageACTIVATE = true;                                        // activate staging  this bool triggers action in sendSerial

      lastStagetime = millis();                                // record the time staging has happened
      stagingARMED = false;                                     // dis-arm staging

      stageState = LOW;   // reset stageState to low after staging command is sent


      if (launchedBit == false) {                 // probably useless get rid of later

        //    messageReplace(2, lineWipe);
      }


      lastMessage = millis();                         // Code to print timed staging message to OLED
      timedMessageset = true;
      messageReplace(3, stagingMessage);


    }

  } else if (digitalRead(stagePin) == HIGH) {           // if stage pin is read high again while stage lock is in place,

    messageReplace(3, staginglockMessage);                 // reiterate stage lock message

  }
}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SAS Button~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void sasButton() {

  int reading = digitalRead(SASdown);

  if (reading != lastSASstate) {
    // reset the debouncing timer
    lastSASDebounceTime = millis();
  }


  if ((millis() - lastSASDebounceTime) > debounceDelay) {

    if (reading != SASdownState) {
      SASdownState = reading;


      if (SASdownState == HIGH) {

        if (sasActive == true) {

          sasDEACTIVATE = true;

          line1Replace(1, 0 , 0, blank3Message);

          sasActive = false;

        } else if (sasActive == false) {

          sasACTIVATE = true;

          line1Replace(1, 0 , 0, sasMessage);

          sasActive = true;
        }

      }
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastSASstate = reading;

}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SASup Button~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This changes Action Button Mode

// Toggles between Actions 1-10 and Actions 11 - 20 (SAS DIRECTION CONTROLS)

void sasUPButton() {

  int reading = digitalRead(SASup);

  // Serial.println(SASup);

  if (reading != lastSASupstate) {
    // reset the debouncing timer
    lastSASupDebounceTime = millis();
  }


  if ((millis() - lastSASupDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != SASupState) {
      SASupState = reading;

      // If the new button state is HIGH, that means the button
      // has just been pressed.
      if (SASupState == HIGH) {

        if (actionButtonMode == 0) {

          actionButtonMode = 1;                // action buttons set to SAS mode

          line1Replace( 1, 0 , actionSASMessage, 0);


        } else if (actionButtonMode == 1) {

          actionButtonMode = 0;                // action Buttons set to Action Buttons Mode

          line1Replace(1, 0 , actionMessage , 0);

        }

        //  Serial.println("SAS Activated");
      }
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastSASupstate = reading;

}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RCS Button~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void rcsButton() {

  int reading = digitalRead(RCSdown);

  if (reading != lastRCSstate) {
    // reset the debouncing timer
    lastRCSDebounceTime = millis();
  }


  if ((millis() - lastRCSDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != RCSdownState) {
      RCSdownState = reading;

      // If the new button state is HIGH, that means the button
      // has just been pressed.
      if (RCSdownState == HIGH) {

        if (rcsActive == true) {

          rcsDEACTIVATE = true;

          //    mySimpit.deactivateAction(RCS_ACTION);


          line1Replace( 1, blank3Message , 0, 0);


          rcsActive = false;

        } else if (rcsActive == false) {

          //  mySimpit.activateAction(RCS_ACTION);

          rcsACTIVATE = true;

          line1Replace( 1, rcsMessage , 0, 0);

          rcsActive = true;
        }

      }
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastRCSstate = reading;

}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~## ACTION BUTTONS ##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void actionButtons() {

  for (int i = 0; i < 10; i++) {                                         // loops through all 10 action button pins

    //  actionStateArray[i] = digitalRead(actionArray[i]);                 // Read the pin and save to array moved this line to first
    // if statement. Could move back if problems


    // this is the debounce bit

    // after action event, want to make sure actionArray Pin is sent LOW before retriggering.

    if ((millis() - lastActiontime) > stagingTimeout) {          // if button is not timed out, read it (timeout  can be very short)

      actionStateArray[i] = digitalRead(actionArray[i]);                      // read the staging button



      if (actionStateArray[i] == LOW && actionsARMED[i] == false) {         // if staging has been disarmed, but pin has been read low (unpressed)

        actionsARMED[i] = true;                                     // re-arm the staging

      }
    }

    if (actionStateArray[i] == HIGH && actionsARMED[i] == true) {           // if pin was recorded as high & actions are armed




      //~~~~~~~~~~~~~~~ if ACTION BUTTON MODE IS ACTIVE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      if (actionButtonMode == 0) {                   // if action buttons are ACTIVE

        // mySimpit.toggleCAG(i + 1);                 // toggle custom action groups

    //    actiongroupTOGGLE = i + 1;                     // save number of active button to byte  // Toggle seems to be producing software crashes.

        actiongroupACTIVATE = i + 1;                     // save number of active button to byte

       line1Replace(2, 0, actionTextArray[i], 0);                                                                                                                       //// TESTING LINE REMOVED 004


        //~~~~~~~~~~~~~~~ if SAS DIRECTION MODE IS ACTIVE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      } else if ( actionButtonMode == 1) {             // toggles SAS modes

        // mySimpit.toggleCAG(i + 11);                 // Needs to change to send SAS commands at the moment set to custom action groups 11 to 21. set these to the SAS action groups for a workaround

        // this line below is KEY VVV

        // THIS LINE WILL ACTIVATE ACTION GROUPS 11 - 20 if SAS commands are handled elsewhere:
        //  actiongroupACTIVATE = i + 11;   // COMMENT IN THIS LINE FOR ACTION GROUPS 11 - 20
        // if commented in, also comment out sasDEACTIVATE below


        // THIS LINE WILL ACTIVATE SAS MODE, WHICH IS STILL TRIGGERED BY ACTION GROUPS 11 - 20 BUT ALSO SHOWS CUSTOM SAS MESSAGES
        sasdirectionACTIVATE = i + 1; // COMMENT IN THIS LINE FOR SAS ACTIONS


        if (i < 9) {                                    // All these modes from 0 - 9 should display active SAS

          line1Replace(1, 0, 0, sasMessage);            // Add SAS Flag
          sasActive = true;                                // set bool to false so system "knows" SAS is set
          // could cause problems? who knows? lets see

          //  mySimpit.activateAction(SAS_ACTION);  // probably unnessissary but worth reiterating !! this shouldnt do anything
          // comment out unless needed


        } else if (i == 9) {                             // added code for SAS cancel on action button 20

          line1Replace(1, 0, 0, blank3Message);           // Remove SAS Flag

          // mySimpit.deactivateAction(SAS_ACTION);        // probably unnessissary but worth reiterating

          sasDEACTIVATE = true;

          sasActive = false;                    // set bool to false so system "knows" SAS is unset


        }

        line1Replace(2, 0, SASTextArray[i], 0);

      }

      lastActiontime = millis();                                // record the time action has happened
      actionsARMED[i] = false;                                     // dis-arm staging

      actionStateArray[i] = LOW;                            // reset actionStateArray[] to low after action commands have been set.

    }

  }
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~ Non-Momentary Buttons: ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~## Staging Lock Script ##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void stageLocked() {  // constantly checks the stageLock button and updates the status of stageLockState;  // this should help simplify the staging button script

  // Read stage lock button. IF HIGH, Stage is UNLOCKED:
  // if (abortTriggered == false) {                             // this if statement kinda screwed some things up


  int reading = digitalRead(stageLock);

  if (reading != lastStageLockState) {
    // reset the debouncing timer
    lastStageLockDebounceTime = millis();
  }

  if ((millis() - lastStageLockDebounceTime) > debounceDelay) {


    // if the button state has changed:
    if (reading != stageLockState) {
      stageLockState = reading;

      // If the new button state is HIGH, that means the button
      // has just been pressed.
      if (stageLockState == HIGH) {              // if stageLockState is HIGH, staging is unlocked


        if (launchedBit == false) {

          messageReplace(3, lineWipe);  // changed from line 2

        }



      } else if (stageLockState == LOW) {   // If stagelock is active display stage lock message

        messageReplace(3, staginglockMessage);

        stageLockbit = true;

      }

    }

  }

  lastStageLockState = reading;


  //  }
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~GEAR CONTROL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void gearControl() {


  int reading = (digitalRead(gear));

  if (reading != lastGearState) {
    // reset the debouncing timer
    lastGearDebounceTime = millis();
  }

  if ((millis() - lastGearDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != gearState) {
      gearState = reading;

      if (gearState == LOW) {


        gearACTIVATE = true;

        //  mySimpit.activateAction(GEAR_ACTION);

      } else if (gearState == HIGH) {

        //    mySimpit.deactivateAction(GEAR_ACTION);

        gearDEACTIVATE = true;

      }
    }
  }


  lastGearState = reading;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~GEAR CONTROL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void brakeControl() {


  int reading = (digitalRead(brakes));

  if (reading != lastBrakeState) {
    // reset the debouncing timer
    lastBrakeDebounceTime = millis();
  }

  if ((millis() - lastBrakeDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != brakeState) {
      brakeState = reading;

      if (brakeState == LOW) {

        //   mySimpit.activateAction(BRAKES_ACTION);

        brakeACTIVATE = true;


      } else if (brakeState == HIGH) {

        //  mySimpit.deactivateAction(BRAKES_ACTION);

        brakeDEACTIVATE = true;

      }
    }
  }


  lastBrakeState = reading;
}


// This Script manages the display of gear and brake symbols
void brakegearMessage() {

  if (pageNumber == 0) {
    if (gearState == HIGH && brakeState == HIGH) {                      // When state is LOW it is ACTIVE!!! haha
      line1Replace(2, 0 , 0, blank3Message);
    } else if (gearState == LOW && brakeState == HIGH) {
      line1Replace(2, 0 , 0, gearMessage);
    } else if (gearState == HIGH && brakeState == LOW) {
      line1Replace(2, 0 , 0, brakeMessage);
    } else if (gearState == LOW && brakeState == LOW) {
      line1Replace(2, 0 , 0, gearbrakeMessage);
    }

  }

}




bool rollActive = true;    // not used yet

bool roverTrigger = false;   // trigger for rover mode. Not sure about this one chief.
bool modeChangeTrigger = false;  // trigger for other mode changes?


int joystickButtonState[4];   // holds 4 bits for current state of joystick buttons


unsigned long lastJoystickPress;

unsigned long currentJoystickPress;

unsigned long longPressTime = 3000;  // time needed to hold buttons 1.5 s?

//~~~~~~~~~~~~~~~~~~~~~~~~Joystick Button Reading~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void joystickButtons() {

  for (int i = 0; i < 4; i++) {                                        // loops through all 10 action button pins

    joystickButtonState[i] = digitalRead(inputPinArray[i]);                // First 4 items in array are joystick buttons A - D

  }


  // this produces the array joystickButtonState.
  //if no buttons are pressed this will read:
  // NORMALITY (0, 0, 1 ,1); // as joystick buttons A & B are normally low, C & D are normally high


  //~~~~~~~~~~~~~~~~~~~~~~ ROVER MODE SELECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Not totally sure about how to structure this

  if (joystickButtonState[0] == HIGH && joystickButtonState[1] == HIGH) {                  // if bits 0 && 1 are HIGH, save state

    currentJoystickPress = millis();

    if ((currentJoystickPress - lastJoystickPress) > longPressTime) {                  // if both buttons have been held down

      if (roverMode == false) {                                                          // if rover mode was OFF, trigger on

        //   roverTrigger = true;                                                           // trigger doesnt do anything I dont think
        roverMode = true;
        rocketMode = false;
        planeMode = false;
        flightModeChange = true;
        Serial.println("Rover Mode Active");

        messageReplace(3,  rovermodeONMessage);


      } else if (roverMode == true) {                                              // if rover mode was ON trigger OFF

        //   modeChangeTrigger = true;                                                // trigger doesnt do anything I dont think       // this triggers the checks in mode selection
        roverMode = false;                                                                       // this whole sequence may move to mode selection at some point
        rocketMode = true;
        flightModeChange = true;
        Serial.println("Rover Mode Disable");
        messageReplace(3,  rovermodeOFFMessage);

        //  WHEELDATA.steer = 0;      // this is done elsewhere I think no need to do it here
        //  WHEELDATA.throttle = 0;

        lastMessage = millis();
        timedMessageset = true;

      }
      lastJoystickPress = currentJoystickPress;
    }
    //  lastJoystickPress = currentJoystickPress;
  }


}
