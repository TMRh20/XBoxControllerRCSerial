
#if defined(TMRh20)

boolean doOnce = 0;
boolean lastFS = 0;
static char res =1;


//For associated processing sketch for monitoring errors and GPS info
//needs proper crc checking
void tryNSendInfo(unsigned long wait){
 if(millis() - datTimer > wait){
   datTimer = millis();
   byte mins = datTimer / 60 / 1000;
   byte mode = 0;
   
   //Use the 8 bits in a byte to capture the different flight mode options:
   if(f.ARMED){         bitWrite(mode,0,1);  }else{  bitWrite(mode,0,0);  }
   if(f.HORIZON_MODE){  bitWrite(mode,1,1);  }else{  bitWrite(mode,1,0);  }   
   if(f.ANGLE_MODE){    bitWrite(mode,2,1);  }else{  bitWrite(mode,2,0);  }   
   if(f.HEADFREE_MODE){ bitWrite(mode,3,1);  }else{  bitWrite(mode,3,0);  }
   if(f.MAG_MODE){      bitWrite(mode,4,1);  }else{  bitWrite(mode,4,0);  }   
   if(f.BARO_MODE){     bitWrite(mode,5,1);  }else{  bitWrite(mode,5,0);  }
   if(i2c_errors_count > 0){bitWrite(mode,6,1);  }else{  bitWrite(mode,6,0);  }

  
    //serialize8('*'); //send junk data first to ensure proper reception
    serialize8('$');
    serialize8('M');
    serialize8('<');
    checksum[CURRENTPORT] = 0; // start calculating a new checksum
    serialize8(4);
    serialize8(MSP_MY_INFO);
    serialize8(vbat); //Voltage
    //serialize16(i2c_errors_count); //I2C Errors
    //serialize16(rxCnt1); rxCnt1 = 0; //For testing: Shows how many serial cmds recvd
    serialize8(mins); //Flight Time
    serialize8(mode); //Flight Mode: Using the different bits to represent flight modes
    byte altitude = constrain(EstAlt/100,0,255);
    serialize8(altitude);
    tailSerialReply(); //Add CRC and send


 }
}

 
unsigned long lastCnt = 0;
boolean lastArm =0;
unsigned long armTimer = 0;

void tmr(){
  //can't remember what this was for...
  if(!doOnce){
    doOnce = 1;
    pinMode(48,OUTPUT); 
  }
  #if defined(RCSERIAL)
  //keep the failsafe from engaging if getting serial data
  if(millis() - rcTimer < 250){
    failsafeCnt = 0;
  }
  #endif
  //if(!f.ARMED){
    tryNSendInfo(483); //Send Info MSP packet every second
  //}
  
}


#endif



