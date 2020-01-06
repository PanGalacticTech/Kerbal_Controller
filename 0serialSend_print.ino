
// These scripts use structured Messages generated from the analogueControl, package them into kerbal simpit commands
/// and/or Print to Serial monitor for Debugging 




// Structure ---- dataSendAnalogue(true, false);    // allows serial comms to KSP and/or printout of data to serial monitor
// this should not break if both are set to false

void dataSendAnalogue(bool sendSerial, bool printSerial) { // Single script to send all analogue/flight control data based on variables set elsewhere?


  if (sendSerial) {

 //   mySimpit.send(THROTTLE_MESSAGE, throttleValue);
    mySimpit.send(THROTTLE_MESSAGE, smoothThrottle);     // test value for smoothed throttle output
    

    mySimpit.send(ROTATION_MESSAGE, PITCH);  //1 bitmasks pitch, max 32 bits, each value is 16bits so can only send 2 per time.
    mySimpit.send(ROTATION_MESSAGE, ROLL);  // 4 bitmasks roll, max 32 bits, each value is 16bits so can only send 2 per time.
    mySimpit.send(ROTATION_MESSAGE, YAW);  // 4 bitmasks roll, max 32 bits, each value is 16bits so can only send 2 per time.

    mySimpit.send(TRANSLATION_MESSAGE, XAXIS);  // 1 bitmasks X, max 32 bits, each value is 16bits so can only send 2 per time.
    mySimpit.send(TRANSLATION_MESSAGE, YAXIS);  // 2 bitmasks Y, max 32 bits, each value is 16bits so can only send 2 per time.
    mySimpit.send(TRANSLATION_MESSAGE, ZAXIS);  // 4 bitmasks Z, max 32 bits, each value is 16bits so can only send 2 per time.

    if (roverMode == true) {
      mySimpit.send(WHEEL_MESSAGE, WHEELDATA);     // only send wheel data if rovermode is set true.

    }


  }


  if (printSerial) {

    Serial.print(" Throttle: ");
    Serial.print(throttleValue);
    Serial.print("  ");
    Serial.print(smoothThrottle);  // allows comparason between throttle & smoothed throttle variable
    Serial.print("     ");

    Serial.print("  Pitch: ");
    Serial.print(PITCH.pitch);
    Serial.print("  Roll: ");
    Serial.print(ROLL.roll);
    Serial.print("  Yaw: ");
    Serial.print(YAW.yaw);
    Serial.print("          ");

    Serial.print("  Trans X: ");
    Serial.print(XAXIS.X);
    Serial.print("  Trans Y: ");
    Serial.print(YAXIS.Y);
    Serial.print("  Trans Z: ");
    Serial.print(ZAXIS.Z);
    Serial.print("          ");

    Serial.print("  Rover Steering: ");
    Serial.print(WHEELDATA.steer);
    Serial.print("  Rover Throttle: ");
    Serial.print(WHEELDATA.throttle);

    Serial.println(" ");




  }

}





// Structure ---- dataSendDigital(true, false);    // allows serial comms to KSP and/or printout of data to serial monitor
// this should not break if both are set to false

void dataSendDigital(bool sendSerial, bool printSerial) {  // Single script to send all data based on bools set elsewhere?


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~Stage~~~~~~~~~~~~~~~~~
  if (stageACTIVATE) {
    
    if (sendSerial) {
      mySimpit.activateAction(STAGE_ACTION);
    }
    if (printSerial) {
      Serial.println("!!- STAGE ACTIVATED -!!");
    }
    
    // could add in a check clause here, if check fails then ACTIVE could be left high to force a resend of the data/action
    stageACTIVATE = false;
  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~SAS Active~~~~~~~~~~~~~~~~~
  if (sasACTIVATE) {

    if (sendSerial) {
      mySimpit.activateAction(SAS_ACTION);
    }
    if (printSerial) {
      Serial.println("SAS Enabled");
    }

    sasACTIVATE = false;
  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~SAS Deactivate~~~~~~~~~~~~~~~~~
  if (sasDEACTIVATE) {

    if (sendSerial) {
      mySimpit.deactivateAction(SAS_ACTION);
      mySimpit.toggleCAG(20);   // this is a hack line to deactivate custom action group 20, which needs to be assigned SAS 20
    }
    if (printSerial) {
      Serial.println("SAS Disabled");
    }

    sasDEACTIVATE = false;
  }



  // ~~~~~~~~~~~~~~~~~~~~~~~~~~RCS Activate~~~~~~~~~~~~~~~~
  if (rcsACTIVATE) {
    if (sendSerial) {
      mySimpit.activateAction(RCS_ACTION);
    }
    if (printSerial) {
      Serial.println("RCS Enabled");
    }
    rcsACTIVATE = false;
  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~RCS Deactivate~~~~~~~~~~~~~~~~
  if (rcsDEACTIVATE) {

    if (sendSerial) {
      mySimpit.deactivateAction(RCS_ACTION);
    }
    if (printSerial) {
      Serial.println("RCS Disabled");
    }
    rcsDEACTIVATE = false;
  }



  // ~~~~~~~~~~~~~~~~~~~~~~~~~~Gear Activate~~~~~~~~~~~~~~~~
  if (gearACTIVATE) {
    if (sendSerial) {
      mySimpit.activateAction(GEAR_ACTION);
    }
    if (printSerial) {
      Serial.println("Gear Deployed");
    }
    gearACTIVATE = false;

  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~Gear Deactivate~~~~~~~~~~~~~~~~
  if (gearDEACTIVATE) {

    if (sendSerial) {
      mySimpit.deactivateAction(GEAR_ACTION);
    }

    if (printSerial) {
      Serial.println("Gear Retracted");
    }

    gearDEACTIVATE = false;
  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~Brakes Activate~~~~~~~~~~~~~~~~
  if (brakeACTIVATE) {

    if (sendSerial) {
      mySimpit.activateAction(BRAKES_ACTION);
    }
    if (printSerial) {
      Serial.println("Brakes Engaged");
    }

    brakeACTIVATE = false;

  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~Brakes Deactivate~~~~~~~~~~~~~~~~
  if (brakeDEACTIVATE) {
    if (sendSerial) {
      mySimpit.deactivateAction(BRAKES_ACTION);
    }
    if (printSerial) {
      Serial.println("Brakes Released");
    }

    brakeDEACTIVATE = false;

  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~Lights Activate~~~~~~~~~~~~~~~~ //Not set up yet
  if (lightsACTIVATE) {
    if (sendSerial) {

    }
    if (printSerial) {
    }

  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~LightsDeactivate~~~~~~~~~~~~~~~~//Not set up yet
  if (lightsDEACTIVATE) {
    if (sendSerial) {
    }
    if (printSerial) {
    }
  }



  //--------------------------------------ACTION GROUPS------------------------------------
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~Actions Activate~~~~~~~~~~~~~~~~
  if (actiongroupACTIVATE > 0) {    // while set to zero, no command. Otherwise accepts values 1 - 20;


    if (sendSerial) {
      mySimpit.toggleCAG(actiongroupACTIVATE);   // this may need to change to activate later
    }
    if (printSerial) {
      Serial.print("Action: ");
      Serial.println(actiongroupACTIVATE);
    }
    
    actiongroupACTIVATE = 0;   // resets this function, equivilent of actiongroupACTIVATE = false;
  }



  // ~~~~~~~~~~~~~~~~~~~~~~~~~~Actions Deactivate~~~~~~~~~~~~~~~~ // Not Set up yet
  if (actiongroupDEACTIVATE > 0) {     // This Probably does nothing
  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~Actions TOGGLE~~~~~~~~~~~~~~~~
  if (actiongroupTOGGLE > 0) {

    if (sendSerial) {
      mySimpit.toggleCAG(actiongroupTOGGLE);
    }
    if (printSerial) {
      Serial.print("Action: ");
      Serial.println(actiongroupTOGGLE);
    }
    
    actiongroupTOGGLE = 0;   // resets this function, equivilent of actiongroupACTIVATE = false;
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SAS Directions Commands~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (sasdirectionACTIVATE > 0) {

    if (sendSerial) {
      mySimpit.toggleCAG(sasdirectionACTIVATE + 10);
    }
    if (printSerial) {
      Serial.print("SAS Action: ");
      Serial.println(SASTextArray[sasdirectionACTIVATE - 1]); // does this need a -1?  I think so!
    }

    sasdirectionACTIVATE = 0;
  }
}
