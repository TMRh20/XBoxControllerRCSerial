
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
 Code base is MultiWii_dev_r1240

 Slightly modified version included:  (main changes on TMRh20 tab, others marked with tmrh)
  - Supports serial rc cmds with smaller payloads
  - Supports failsafe when using serial RC
  - Supports basic monitoring during flight via processing gui (prev. post)
  - Still unsure whether to remove or work with test code to provide sound output from alarm triggers etc. so I left it in
  - Modified ESC calibration code specific to MultiStar ESCs
  
************************************************************************************

--Controls--

Joysticks:
R: Pitch/Roll
L: Yaw


Triggers:
R: Throttle
L: n/a


Buttons:

Mode 0 (Start Button):

//Trimming this way is only good when maintaining a fixed heading.
//Will probably do custom commands for easy trim control
A: Wake Up
B: Yaw Trim +
Y: n/a
X: Yaw Trim -
U: Trim Pitch +
D: Trim Pitch -
R: Trim Roll +
L: Trim Roll -

Mode 1 (Back Button):

A: Wake Up
B: n/a
Y: aux1 = 1500
X: aux2 = 1500
U: aux1 = 2000
D: aux1 = 1000;
R: aux2 = 1000;
L: aux2 = 2000;

Mode 3 (Black Button)

A: Wake Up
B: n/a
Y: aux3 = 1500
X: aux4 = 1500
U: aux3 = 2000
D: aux3 = 1000;
R: aux4 = 1000;
L: aux4 = 2000;


************************************************************************************


Details at http://TMRh20.blogspot.com

************************************************************************************
