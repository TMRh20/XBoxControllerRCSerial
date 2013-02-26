
#if defined(RCSERIAL)

boolean doOnce = 0;
boolean lastFS = 0;
static char res =1;


//For associated processing sketch for monitoring errors and GPS info
//needs proper crc checking
void tryNSendGPS(){
 if(millis() - datTimer > 1000){// && f.GPS_FIX == 1){
   datTimer = millis();
    serialize8('*'); //best to send junk data first to ensure proper reception 
    serialize8('$');
    serialize8('M');
    serialize8('>');
   serialize16(i2c_errors_count);
   serialize32(GPS_coord[LAT]);
   serialize32(GPS_coord[LON]);
   serialize8(GPS_numSat);
   serialize16(heading);
   serialize8(32);
   UartSendData();
 }
}

 
void tmr(){
 
  //can't remember what this was for...
  if(!doOnce){
    doOnce = 1;
    pinMode(48,OUTPUT); 
  }
  //keep the failsafe from engaging if getting serial data
  if(millis() - rcTimer < 500){
    failsafeCnt = 0;
  }  
}


//test code for a music player that interprets the buzzer output
//and plays warning sounds etc. Not sure if worth doing
void tmrTunes(byte what){
  
  switch(what){
    case 1: patternDecode(res,20,30,0,50,0); //pause
    case 2: patternDecode(res,20,40,0,50,0); //imperial march
    case 3: patternDecode(res,30,10,0,50,0); //superfly
    case 4: patternDecode(res,10,40,0,50,0); //engage
  }  
}


#endif



