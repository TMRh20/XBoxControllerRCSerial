



//Read Joysticks, map to values 1000-2000, and fix center values

void getRollPitchYawThrottle( ){
  
    *roll = constrain(analogRead(A1), 220,800);   
    *pitch = constrain(analogRead(A0), 190,800);
    *yaw = constrain(analogRead(A3),290,800);
    *throttle = constrain(analogRead(A6),50,trigZero[0]-15);
    
    //Values must be adjusted to provide a reading closest to 1000-2000
    *roll = map(*roll,220,800,2000,1000);
    *pitch = map(*pitch,190,800,1000,2000);
    *yaw = map(*yaw,290,800,1000,2000);
    
    centerFix(yaw, trimYaw);
    centerFix(pitch, trimPitch);
    centerFix(roll, trimRoll);   
    
    
    *throttle = map(*throttle,50,trigZero[0]-15,2000,1000); 
}
  

//Create a 'zero point' or 'center area' to allow for play in the joysticks
//Any small movements around center will not affect output
void centerFix(int *what, int trim){

  if(*what >= jCenter -50 && *what <= jCenter  +50){ 
      *what = jCenter;
    }else
    if(*what < jCenter -50){*what += 50;
    }else
    if(*what > jCenter +50){*what -= 50 ;
    }
    *what = constrain(*what+trim,1000,2000);
}
