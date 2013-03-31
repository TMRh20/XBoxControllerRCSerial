

unsigned long bTimers[13];
boolean lcdToggle = 0;

void buttonLogic(){
 
  //Check the Select, Start and Black buttons
  //Used to toggle mode of A,B,X,Y,U,D,L,R buttons
  
  //Start: A4, Back: A5 
  boolean mode[3] = {_digitalRead(A4),_digitalRead(10),_digitalRead(A5)}; //start,black,back buttons
  
  int sel = 0;  
  for(int i=1; i<4; i++){
    if(!mode[i-1]){
       ledBlink(100);
       slpTimer = micros(); 
       sel = i;         
     }
  }
  if(sel==1){
      lcdMenu(); 
  }else{lcdTimer = micros(); }

//now read through ABXY,UDLR and black buttons    
for(int i=2; i<10; i++){
    if(_digitalRead(i) == LOW && micros() - bTimers[i] > 250000){ //if a button is toggled, and hasn't been toggled for 250ms, do the following
      ledBlink(175);
      bTimers[i] = micros();      
      slpTimer = micros();
      if(sel == 3){            //apply different actions depending on the mode specified by Back and Start buttons
                buttonSend = 1; //bTimer=millis;
                switch(i){
                  case 2: *aux1 = 2000; break; //A 
                  case 3: *aux1 = 1000; break; //B
                  case 4: *aux2 = 1000; break; //Y
                  case 5: *aux2 = 2000; break; //X
                  case 6: *aux3 = 1000; altHold=0; break;
                  case 7: *aux4 = 2000; break;
                  case 8: *aux3 = 2000; altHold = 1; altThrottle=*throttle; break;
                  case 9: *aux4 = 1000; break;
                }
      }else
      if(sel == 0){
                buttonSend = 1; //bTimer=millis;       
                switch(i){
                  case 2: *aux3 = 1000; altHold=0; break;
                  case 3: *aux4 = 2000; break;
                  case 4: *aux3 = 2000; altHold = 1; altThrottle=*throttle;break;
                  case 5: *aux4 = 1000; break;  
                  case 6: *aux1 = 2000; break;
                  case 7: *aux1 = 1000; break;
                  case 8: *aux2 = 1000; break;
                  case 9: *aux2 = 2000; break;
                }       
      }
    } 
  }

}



int _digitalRead(uint8_t pin)
{
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	if (*portInputRegister(port) & bit) return HIGH;
	return LOW;
}

