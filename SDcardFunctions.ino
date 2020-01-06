
struct configStore {     // structure to save all of the config data

  uint8_t rocketControlConfig[8] =  {
    4, 5, 3, 0, 1, 7, 10, 10            // this has an extra space used because the menu has a blank space to fill in slot 9.
  };                                           // uint8 = 1 byte so this array is 8 bytes, the last one is always null   8 bytes


  bool rocketInvertConfig[8] = {          // bool actually holds one BYTE of memory, not 1 bit!!                          16 bytes
    false, false, true,
    false, false, false,
    false, false
  };


  uint8_t planeControlConfig[8] = {  /// This has a slot for each output in order. ints 0 to 9 are saved
    4, 3, 8, 0, 1, 7, 10, 10
  };                                    // uint8 = 1 byte so this array is 8 bytes, the last one is always null        24 bytes


  bool planeInvertConfig[8] = {           // bool actually holds one BYTE of memory, not 1 bit!!                          32 bytes
    false, true, false,
    false, false, false,
    false, false                       //
  };      //


  uint8_t roverControlConfig[8] = {           /// This has a slot for each output in order. ints 0 to 9 are saved 10 is null  40 bytes
    7, 6, 8, 10, 10, 10, 3, 1
  };                                              // uint8 = 1 byte so this array is 8 bytes, the last one is always null


  bool roverInvertConfig[8] = {             // bool actually holds one BYTE of memory, not 1 bit!!                         48 bytes
    true, false, false,
    false, false, false,
    true, true
  };              //

};


struct configStore savedSettings;  // variable to store the saved settings

// this can be accessed now as

// savedSettings.rocketControlConfig[0] = whatever(uint8_t)w   --- I think, haha
//

/*
   There is another very useful function in C called “sizeof(var)”. That tells you how big variables are.
   For instance it would return 2 for a uint16_t, 4 for a float, etc. For our struct it would return 12.

    Atchully, I think for this structure it should return 27 bytes the text above is just copied. Helpful I know.
*/




File configFile;







void readConfigSD() {

  if (settingsRecall) {


    /*
           So now we are filling our SD card with raw binary data.
           But what can we do with it? We can’t look at it, it will just be meaningless to us.
           So we need the Arduino to read it for us. And that is just as simple.
           There is a “read” equivalent to the “write” function we used above where we
           can tell it to read bytes into an array – and that array can be our struct cast as before:


      myFile.read((uint8_t *)&myData, sizeof(myData));

           That will read the 12 bytes from the SD card and reconstruct your structure for you,
           all magically and without you needing to do any interpreting of numbers or symbols


    */

    if (!noSDcard) {
      display.setTextColor(1, 0);
      display.setCursor(0, 8);
      display.print("Reading SD Card...");
      display.display();
    }
    delay(500);

    File configFile = SD.open("config.txt", FILE_READ);    // open the config file




    // if the file is available, read from it:
    if (configFile) {
      while (configFile.available()) {

        struct configStore readConfig;    // Read data is into a new instance of the previous configStore structure.

        configFile.read((uint8_t *)&readConfig, sizeof(readConfig));


        Serial.print("rocketControlConfig = ");
        for (int i = 0; i < 8; i++) {
          Serial.print(readConfig.rocketControlConfig[i]);
          RocketintcontrolArray[i] = readConfig.rocketControlConfig[i]; // read the values read back from the SD card into the correct array
          Serial.print(", ");
        }
        Serial.println(" ");
        Serial.print("rocketInvertConfig = ");
        for (int i = 0; i < 8; i++) {
          Serial.print(readConfig.rocketInvertConfig[i]);
          rocketInvertArray[i] = readConfig.rocketInvertConfig[i]; // read the values read back from the SD card into the correct array
          Serial.print(", ");
        }
        Serial.println(" ");
        Serial.print("planeControlConfig = ");
        for (int i = 0; i < 8; i++) {
          Serial.print(readConfig.planeControlConfig[i]);
          PlaneintcontrolArray[i] = readConfig.planeControlConfig[i]; // read the values read back from the SD card into the correct array
          Serial.print(", ");
        }
        Serial.println(" ");
        Serial.print("planeInvertConfig = ");
        for (int i = 0; i < 8; i++) {
          Serial.print(readConfig.planeInvertConfig[i]);
          planeInvertArray[i] = readConfig.planeInvertConfig[i]; // read the values read back from the SD card into the correct array
          Serial.print(", ");
        }
        Serial.println(" ");
        Serial.print("roverControlConfig = ");
        for (int i = 0; i < 8; i++) {
          Serial.print(readConfig.roverControlConfig[i]);
          RoverintcontrolArray[i] = readConfig.roverControlConfig[i]; // read the values read back from the SD card into the correct array
          Serial.print(", ");
        }
        Serial.println(" ");
        Serial.print("roverInvertConfig = ");
        for (int i = 0; i < 8; i++) {
          Serial.print(readConfig.roverInvertConfig[i]);
          roverInvertArray[i] = readConfig.roverInvertConfig[i]; // read the values read back from the SD card into the correct array
          Serial.print(", ");
        }
        Serial.println(" ");
        Serial.println(" ");

      }
      configFile.close();

      settingsRecall = false;   // settings have been recalled from the config.txt file, so set the flag false
      Serial.println("Settings Updated from config.txt");
      
      display.setTextColor(1, 0);
      display.setCursor(0, 8);
      display.print("Settings Recalled");
      display.display();
      delay (500);
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening config.txt");
      Serial.println("Reverting To Factory Config");
      display.setTextColor(1, 0);
      display.setCursor(0, 8);
      display.print("error opening config.txt");
      display.setCursor(0, 16);
      display.print( "Reverting To Factory Config");
      display.display();
      restoreFactory = true;
      delay (500);
    }


  }

}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### SD Card Setup ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void sdSetup() {                                         // Sets up SD card functions
  //                                                        // checks to see if config.txt file exists.
  //                                                         // If it does not exist it creates the file.
  while (!Serial) {
    ;                                                       // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(sdSelectpin)) {

    Serial.println("initialization failed!");

    noSDcard = true;
    display.setTextColor(1, 0);
    display.setCursor(0, 8);
    display.print("No SD Card");
    display.display();
    delay(500);
    // while (1);
    // break;
  }
  Serial.println("initialization done.");

  if (SD.exists("config.txt")) {
    Serial.println("config.txt  exists.");
    settingsRecall = true;                                     // config file exists, so we will update all our control arrays
    //                                                        // from the file instead of writing a new config file.
  }

  else {
    Serial.println("config.txt doesn't exist.");            // if the config.txt file does not exist

    // open a new file and immediately close it:
    Serial.println("Creating config.txt...");
    configFile = SD.open("config.txt", FILE_WRITE);           // greate the config file
    configFile.close();

    saveSettings = true;                                // this file is empty so this bool triggers a script to write the factory values into
    //                                                       //the file that has been created.
  }

}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### SD Card Write Settings Data to SD ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void sdWriteSavedSettings() {                                           // This script writes settings data saved in configStore savedSettings;
  //                                                                   //to the config.txt file


  if (saveSettings) {



    configFile = SD.open("config.txt", FILE_WRITE);                     // open the file. note that only one file can be open at a time,
    //                                                                        // so you have to close this one before opening another.



    if (configFile) {                                        // if configFile is avaliable


      /*
        All the magic happens when you tell it to just write a bunch of bytes instead of text:
      */
      int sizeofSettings = sizeof(savedSettings);



      configFile.write((const uint8_t *)&savedSettings, sizeof(savedSettings));

      /*
            “&myData” gets the address in memory where the data is stored.
            It is intrinsically a “struct datastore *” type. The write function doesn’t like that type,
            so we need to change it. That is called casting,
            and we want to cast it to an unsigned byte pointer type, so prepend it with:

            (const uint8_t *) &myData
      *   *
            The write function now sees it as an array of bytes. Clever, eh?
            Along side that we need to tell the write function how many bytes to write,
             and for that we can use the handy sizeof() function I mentioned before.
      */
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Factory Values Written~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


      configFile.close();                                                              // Close the configFile
      Serial.println("Settings Saved to SD Card");                                // serial print factory settings restore
      //  >> nice try but nahh      Serial.printf("%u Bytes Written. \n", sizeof(savedSettings) );             //   %[flags][width][.precision][length]specifier
      Serial.print(sizeofSettings);
      Serial.println(" Bytes Written");

      saveSettings = false;                                                             // factory settings have been restored so
      //                                                                              // flag is set false
    }

    else {                                                                       // if there is an error opening the file
      Serial.println("error opening config.txt");                                 // display error, might make it display on screen
    }                                                                                // but otherwise I want the program to
    // carry on regardless.


  }

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~### SD Card Delete config File ###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void deleteConfig() { // When called this script wipes the config file


  // Check to see if the file exists:
  if (SD.exists("config.txt")) {
    Serial.println("config.txt exists.");
    // delete the file:
    Serial.println("Removing config.txt...");
    SD.remove("config.txt");

  } else {
    Serial.println("config.txt doesn't exist.");
  }




  if (SD.exists("config.txt")) {
    Serial.println("config.txt exists.");
  } else {
    Serial.println("config.txt doesn't exist.");
  }

}



void updateDataStructure() {   // Updates data structure ready to write to the SD card


  for (int i = 0; i < 8; i++) {

    savedSettings.rocketControlConfig[i] = RocketintcontrolArray[i];

    savedSettings.rocketInvertConfig[i] = rocketInvertArray[i];


    savedSettings.planeControlConfig[i] = PlaneintcontrolArray[i];

    savedSettings.planeInvertConfig[i] = planeInvertArray[i];


    savedSettings.roverControlConfig[i] = RoverintcontrolArray[i];

    savedSettings.roverInvertConfig[i] = roverInvertArray[i];


  }






}
