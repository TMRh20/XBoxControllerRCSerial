



void lcdMenu(){
  
  if(micros() - lcdTimer < 3000000){ return; } //If Start button has been held for 3 seconds
  digitalWrite(13,HIGH); //LED ON
  
  boolean lcdSaved = 0;
  delay(250);
  
  //Enter the LCD menu by sending RC commands
  //Set the yaw to the right and pitch forward:
  for(int i=0; i<10;i++){
    buffer8(4);
    buffer8(MSP_MYRC);
    buffer8(125); //Roll,Pitch,Yaw,Throttle
    buffer8(250);
    buffer8(250);
    buffer8(0);
    sendBuffer();
    delay(100);
  }
 
char cmds[5] = {'d','n','u','p'}; //Serial Cmds for navigating LCD menu

  while(!_digitalRead(A4)){ //While the Start button is being held
    
    if(!digitalRead(10)){ mySerial.print("s"); lcdSaved =1; break; } //If black button pressed, send Save and exit
    
    for(int i=2; i<6; i++){ //Read through ABYX buttons. If pressed, send associated navigation command
      if(!digitalRead(i)){
        mySerial.print(cmds[i-2]);
        digitalWrite(13,HIGH);
        delay(250);
        digitalWrite(13,LOW);
      }
    }
    
    
    delay(10);
  }
  if(lcdSaved == 0){//If not saved, Abort and Exit
    mySerial.print("x");    
  }
  
  digitalWrite(13,HIGH); //Turn LED back on
  delay(100);
  lcdTimer = micros(); //Reset Timer
}
