// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#### ABORT SEQUENCE ####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// This function constantly polls the RCS up button
// to see if it has been pulled HIGH.

// If high this triggers  abort sequence [ STAGE ONE ],
// warning message is printed to the OLED
// Pilot is prompted with a warning and asked to
// STAGE to proceed with abort sequence.

// if RCSup Button is released while abort sequence [ STAGE ONE ] is active
// ABORT sequence is [ CANCELLED ]


// if, WHILE abort sequence [ STAGE ONE ], is active &&
// STAGE is pulled HIGH.
// abort sequence [ STAGE TWO ] is triggered. At this stage ABORT sequence is engaged and cannot be cancelled

// Abort Sequence [ STAGE TWO ] runs untill Abort Sequence [ COMPLETE ]




void abortSequence(bool sendSerial, bool printSerial) {

  // This is polling the RCS up button and waiting for trigger
  if (millis() - lastABORTtime >= abortTimeout) {

    if (abortTriggered == true) {
      display.clearDisplay();
      abortTriggered = false;
      abortStarted = false;
    }

    RCSupState = digitalRead(RCSup);

    if (RCSupState == HIGH) {
      display.clearDisplay();
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### ABORT Sequence [ STAGE ONE ] ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    while (RCSupState == HIGH && stageState == LOW) {            // While loops infinitly untill RCSup button is released

      abortStarted = true;                                         // Abort Sequence STARTED

      if (printSerial) {
        Serial.println(" ABORT SEQUENCE INITIATED!! ");
        Serial.println("         ");
        Serial.println("  AWAITING CONFIRMATION  ");
        Serial.println("         ");
      }
      RCSupState = digitalRead(RCSup);                              // Keep reading the RCSup (abort) button
      stageState = digitalRead(stagePin);                          // Keep reading the staging button


      display.setTextColor(0, 1);
      display.setCursor(0, 0);

      display.print("   !!! WARNING !!!   ");                       // DISPLAY WARNING
      display.setTextSize(2);
      display.setTextColor(1, 0);
      display.setCursor(12, 8);
      display.print(" ABORT ?");                                   // ARE YOU SURE YOU WISH TO ABORT?
      display.setCursor(0, 24);
      display.setTextSize(1);
      display.print("Press Stage To Abort");                       // INSTRUCT PILOT TO STAGE TO CONFIRM ABORT SEQUENCE
      display.display();


    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### ABORT Sequence [ STAGE TWO ] ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    if (RCSupState == HIGH && stageState == HIGH) {                 // ABORT SEQUENCE ENGAGED - No turning back now
      display.clearDisplay();
      abortStarted = false;

      if (printSerial) {
        Serial.println("ABORT SEQUENCE ENGAGED!!");
        Serial.println("!!! ABORT !!!");
        Serial.println("!!! ABORT !!!");
        Serial.println("!!! ABORT !!!");
      }


      display.fillRoundRect(0, 0, 128, 32, 4, WHITE);             //(x , y, width, height, cornerRadius, color)

      display.setTextColor(0, 1);
      display.setCursor(12, 0);
      display.setTextSize(1);
      display.print(" Don't Panic! ");                                // Don't Panic!

      display.setTextColor(0, 1);
      display.setTextSize(2.8);
      display.setCursor(12, 9);
      display.print("! ABORT !");                                       // ABORT SEQUENCE INITIALISED
      display.setTextSize(1);
      display.setCursor(12, 25);
      display.print("INITIALIZED");

      display.display();

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!~~ABORT COMMAND SENT HERE~~!!~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if (sendSerial) {
        mySimpit.activateAction(ABORT_ACTION);                         // ABORT COMMAND SENT
      }
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~The Rest is just Fluff~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      RCSupState = 0;
      stageState = 0;
      stageLockState = 0;                                       // this line makes sure stage lock is turned off
      lastStageLockState = 1;                         //   << bug fix line? try 1 or 0

      lastABORTtime = millis();                            // save time abort happened.
      abortTriggered = true;                                // SAVES trigger condition, could be useful

      for (int i = 0; i < 18; i++) {                      // ABORTING LOOP - SET TIMESPAN (loops 18 times)

        stageButtonv2();                                  // carry on reading the stage button for additional presses
        dataSendDigital(true, false);                   // if staging has been retriggered this sends additional commands

        display.invertDisplay(true);                   // flash display

        delay(100);
        display.invertDisplay(false);                        // flash display

        delay(100);
      }
      display.clearDisplay();                                    // clear up warning messages
      // messageReplace(1, lineWipe);
      messageReplace(2, lineWipe);
      messageReplace(3, lineWipe);                             // Prepare for Parachute Deployment and Crash Landing (mentally)
      screenUpdate = true;
      if (printSerial) {
        Serial.println("Abort Sequence finished!");
        Serial.println("Don't Panic");
        Serial.println("Prepare for Crash Landing");
      }
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### ABORT Sequence [ COMPLETED ] ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### ABORT Sequence [ CANCELLED ] ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    } else if (RCSupState == LOW && stageState == LOW) {    // if while loop was exited without triggering abort

      if (abortStarted == true) {                            // clear up any trigger conditions
        abortStarted = false;

        if (printSerial) {
          Serial.println("ABORT SEQUENCE CANCELLED");
          Serial.println("Resume Normal Flight");
        }

        pageNumber = 0;                                                  // this makes abort stage one/ ABORT Ready switch a handy "return to main page" button
        itemNumber = 0;
         pageScroll = false;              // sets this ready to scroll through menu items again
        display.clearDisplay();                               // clear display to return to normal operation
        screenUpdate = true;
      }
    }
  }
}
