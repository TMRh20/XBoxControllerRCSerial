
************************************************************************************

XBox Controller: RCSerial

Sketch for using an Arduino-converted XBox Controller to control multirotor craft using
MultiWii flight control software.


************************************************************************************

Requirements:

  XBox controller:
  Embedded Arduino Nano/Mini/etc.
  Serial Based Wireless Module (APC220, XBee, etc)


************************************************************************************

MultiWii:
 Code base is MultiWii_dev_r1349 pre 2.2

 Slightly modified version included:  (main changes on TMRh20 tab, others marked with tmrh)
  - Supports serial rc cmds with smaller payloads
  - Supports failsafe when using serial RC
  - Supports basic monitoring during flight via Custom Arduino-based Wireless LCD
  - Supports configuration and tuning via Custom Arduino-based Wireless LCD
  - Modified ESC calibration code specific to MultiStar ESCs
  
************************************************************************************

--Controls--

Joysticks:
Left: Pitch/Roll
Right: Yaw


Triggers:
Right: Throttle
Left: n/a


Buttons:

Mode 0 (Default):

//Trimming this way is only good when maintaining a fixed heading.
//Will probably do custom commands for easy trim control
A: Disable Alt Hold
B: Enable MAG mode, Disable HeadFree Mode
Y: Enable Alt Hold 
X: Enable HeadFree Mode, Disable MAG Mode
U: Stable/Angle Mode
D: Horizon Mode
R: n/a
L: n/a

Start: Enter LCD Menu after hold for 3 Seconds
Back: Toggle Control Mode
Black: Save and Exit LCD Menu

************************************************************************************


Details at http://TMRh20.blogspot.com

************************************************************************************
