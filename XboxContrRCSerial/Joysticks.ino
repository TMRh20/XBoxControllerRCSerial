



//Read Joysticks, map to values 1000-2000, and fix center values

void getRollPitchYawThrottle( ){
  
    //Values must be adjusted in both sections below to provide a reading closest to 1000-2000
    // each potentiometer/joystick gives slightly different readings
    // ie: for roll, adjust the numbers 220,860 to match min and max readings from that joystick
    unsigned int rol = constrain(analogRead(A3), 220,860);   
    unsigned int pit = constrain(analogRead(A2), 160,860);
    unsigned int yw = constrain(analogRead(A1),200,800);    
    unsigned int thrt = constrain(analogRead(A6),110,trigZero[0]-10);

    //need to adjust these ones to match:
    *roll = map(rol,220,860,950,2050);
    *pitch = map(pit,160,860,2050,950);
     *yaw = map(yw,200,800,2050,950);
    
    centerFix(yaw);
    centerFix(pitch);
    centerFix(roll);   
    
    if(altHold == 0){
      *throttle = map(thrt,110,trigZero[0]-10,2000,1000); 
    }else{
      int tmpThr = map(thrt,110,trigZero[0]-10,2000,1000);
      if(tmpThr > altThrottle + 50 || tmpThr < altThrottle - 50){ ledBlink(20); } else { }
      *throttle=altThrottle;
    }
}
  

//Create a 'zero point' or 'center area' to allow for play in the joysticks
//Any small movements around center will not affect output
void centerFix(int *what){

  if(*what >= 1500 -50 && *what <= 1500  +50){ 
      *what = 1500;
    }else
    if(*what <= 1500 -50){*what += 50;
    }else
    if(*what >= 1500 +50){*what -= 50 ;
    }
    *what = constrain(*what,1000,2000);
}
