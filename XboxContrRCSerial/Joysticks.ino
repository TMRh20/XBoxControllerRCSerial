



//Read Joysticks, map to values 1000-2000, and fix center values

void getRollPitchYawThrottle( ){
    
    //values used when creating a null space in the center area of the joystick
    //defines how big it is (out of 1024)  
    int rZp = 50; //roll
    int pZp = 50; //pitch
    int yZp = 60; //yaw
  
    //Values must be adjusted in both sections below to provide a reading closest to 1000-2000
    // each potentiometer/joystick gives slightly different readings
    // ie: for roll, adjust the numbers 220,860 to match min and max readings from that joystick
    unsigned int rol = constrain(analogRead(A3), 90,990);   
    unsigned int pit = constrain(analogRead(A2), 160,860);
    unsigned int yw = constrain(analogRead(A1),200,800);    
    unsigned int thrt = constrain(analogRead(A6),110,trigZero[0]-10);

    //need to adjust these ones to match the above:
    *roll = map(rol,90,990,1000-rZp,2000+rZp);
    *pitch = map(pit,160,860,2000+pZp,1000-pZp);
     *yaw = map(yw,200,800,2000+yZp,1000-yZp);
    
    centerFix(yaw,yZp);
    centerFix(pitch,pZp);
    centerFix(roll,rZp);   
    
    *throttle = map(thrt,110,trigZero[0]-10,2000,1000); 

}
  

//Create a 'zero point' or 'center area' to allow for play in the joysticks
//Any small movements around center will not affect output
void centerFix(int *what, int val){

  
  if(*what >= 1500 -val && *what <= 1500  +val){ 
      *what = 1500;
    }else
    if(*what <= 1500 -val){*what += val;
    }else
    if(*what >= 1500 +val){*what -= val ;
    }
    *what = constrain(*what,1000,2000);
}
