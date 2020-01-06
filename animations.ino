

/*
    Scripts to Run animations



*/





void settingsSavedAnimation() {
  display.clearDisplay();


  display.setTextColor(1, 0);
  display.drawRoundRect(0, 8, 128, 24, 4, WHITE);    // (x , y, width, height, cornerRadius, color)
  // display.setTextSize(2);
  // display.invertDisplay(true);
  display.setCursor(4, 11);
  display.print("Settings Saved");
  display.setCursor(4, 19);
  display.print("to SD Card");


  display.display();
  delay (700);
  //  display.invertDisplay(false);
  // display.setTextSize(1);


}


void factoryRecallAnimation() {
  display.clearDisplay();


  display.setTextColor(1, 0);
  // display.setTextSize(2);
  // display.invertDisplay(true);
   display.drawRoundRect(0, 8, 128, 24, 4, WHITE);    // (x , y, width, height, cornerRadius, color)
  display.setCursor(4, 11);
  display.print("Recall Factory");
  display.setCursor(4, 19);
  display.print("Settings");


  display.display();
  delay (700);
  //  display.invertDisplay(false);
  // display.setTextSize(1);

}


/*

   display.clearDisplay() – all pixels are off
  display.drawPixel(x,y, color) – plot a pixel in the x,y coordinates
  display.setTextSize(n) – set the font size, supports sizes from 1 to 8
  display.setCursor(x,y) – set the coordinates to start writing text
  display.print(“message”) – print the characters at location x,y
  display.display() – call this method for the changes to make effect
*/



/*
    display.clearDisplay();


    display.invertDisplay(true);
    delay(500);
    display.invertDisplay(false);
    delay(500);


     display.setFont(&FreeSansBold12pt7b);
*/

/*

    Guide for Drawing Shapes


*/


/*



  The drawRect(x, y, width, height, color) provides an easy way to draw a rectangle.
  The (x, y) coordinates indicate the top left corner of the rectangle.
  Then, you need to specify the width, height and color:

  display.drawRect(10, 10, 50, 30, WHITE);

  You can use the fillRect(x, y, width, height, color)
  to draw a filled rectangle.
  This method accepts the same arguments as drawRect().

  The library also provides methods to displays rectangles with round corners:
  drawRoundRect() and fillRoundRect().
  These methods accepts the same arguments as previous methods plus the radius of the corner.

  For example:

  display.drawRoundRect(10, 10, 30, 50, 2, WHITE);    // (x , y, width, height, cornerRadius, color)

  display.fillRoundRect(10, 10, 30, 50, 2, WHITE);  //(x , y, width, height, cornerRadius, color)

*/
