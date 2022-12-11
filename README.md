# Kerbal_Controller
 Firmware for Kerbal Space Program Controller
 
Project to interface Arduino Mega with Kerbal Space Program, and create an adaptable controller to suit different vehicles and flying styles.

The scope for this project was to replace the typical keyboard game controls, with a far more interactive, intuitive and fun Analogue Stick control layout. I wanted to be able to assign different controls depending on whether a Rocket is being flown to orbit, a Spaceplane is lining up on final approach to a runway, or a Rover is being driven across the surface of The Mun.

The controller runs off an Arduino Mega 2560 and uses the Kerbal SimPit Mod installed in the Game Data folder of Kerbal Space Program. The ready-made Arduino library, Kerbal SimPit is available from the Arduino Library Manager, and this handles all the communication between the controller and the game.


 
 ![image](https://user-images.githubusercontent.com/53580358/206912537-e18d3d79-3960-4bf2-8c9b-c4c2af90c7ae.png)

## Menu

_The menu allows the user to assign any Joystick Axis to any of the in-game controls for each mode, allowing different joystick setups for different vehicles or playing styles._

Settings are saved and recalled from an SD card, if a save file does not exist, it is created during the power on and setup routine


## Wiring Diagram

![image](https://user-images.githubusercontent.com/53580358/206912552-0b4ada9a-1cd7-4da0-8fd1-c3510bb7b330.png)


Post on IMGUR with Schematics
https://imgur.com/gallery/eJXh0af

Blog entry:
https://pangalactictech.com/kerbal-space-program-10-axis-controller/

https://medwaymakers.wordpress.com/2020/01/13/kerbal-space-program-10-axis-controller-with-arduino-mega/

## Internal Pictures

![image](https://user-images.githubusercontent.com/53580358/206912562-36122170-28bc-4c3e-9b1c-ddb63569b5ca.png)
