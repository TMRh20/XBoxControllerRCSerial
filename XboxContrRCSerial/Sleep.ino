

//Sleep mode stuff
void wakeUpNow(){
  slpTimer=millis();
}



//function for sleeping to save power
void sleepNow(){
  delay(250);
  ledBlink(3,100);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  attachInterrupt(0,wakeUpNow, FALLING);  
  sleep_mode();
  power_all_disable();
  sleep_disable();
  power_all_enable();
  detachInterrupt(0);
  slpTimer = millis();
  ledBlink(1,225);
}


void ledBlink(byte times, byte period){
  
  for(int i=0;i<times;i++){
    digitalWrite(13,HIGH);
    delay(period);
    digitalWrite(13,LOW);
    delay(period);
  }
}
