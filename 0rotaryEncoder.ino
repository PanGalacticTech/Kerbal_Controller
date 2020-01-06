

void clickCheck() {

  clk = digitalRead(encoderButton);   //Code from hackster

  if (clk == HIGH) {

    if (pageScroll == false) {                // If button has been pressed and pageScroll was not active

      pageScroll = true;                                      // Activate pageScrolling

      itemSelected = true;

      // lineColours[itemNumber] = 0;
      lineColours[lineAdjust] = 0;
      screenUpdate = true;
      itemSelect();                                            // runs through all possible selectable items and runs whatever is active, if nothing relavent then its passed
      // though and turns itemSelected to false;




      clk = LOW;
      delay(50);

    } else if (pageScroll == true) {      // if button has been presed and pageScroll was active

      pageScroll = false;                                // pageScroll is now inactive
      // this may need an additional SELECTED bool.



   if (rocketControlEdit == true) {             // its awkward this being here but it does work. 

    rocketControlEdit = false;

   }

   
   if (planeControlEdit == true) {

    planeControlEdit = false;

   }

     
   if (roverControlEdit == true) {

    roverControlEdit = false;

   }

   

      // lineColours[itemNumber] = 1;
      lineColours[lineAdjust] = 1;
      screenUpdate = true;

      clk = LOW;
      delay(50);
    }
  }

}

//----------------------------------------------------------------------------------


bool rotaryButton() {


  clk = digitalRead(encoderButton);   //Code from hackster


}





/*


   Checks to see if rotary encoder has moved.


    Returns Values:

   prevCount

   rotaryCount


  // */


int counter2 = 0;

void encodeDirection() {

  prevCount = rotaryCount;
  if (fired)  {
    counter2++;                     // This nerfs the rotary and makes it 1 click for every 2 clicks. Not nessissary with all rotary encoders.
    if (counter2 > 2) {
      counter2 = 0;

      if (up)
        rotaryCount--;
      else
        rotaryCount++;
      fired = false;
      screenUpdate = true;
    }

  }  // end if fired

}




//-----------------------------------------------------




// ------------------------Rotary Turn Direction--------------------------------

// Wiring: Connect common pin of encoder to ground. <<< Accidently connected to +5v seems to work well
// Connect pin A (one of the outer ones) to a pin that can generate interrupts (eg. D2)
// Connect pin B (the other outer one) to another free pin (eg. D3)

void isr ()
{
  if (digitalRead (encoderPinA))
    up = digitalRead (encoderPinB);
  else
    up = !digitalRead (encoderPinB);
  fired = true;


}  // end of isr
