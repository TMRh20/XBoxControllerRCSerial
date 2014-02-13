//
//
////Sleep mode stuff
//void wakeUpNow(){
//  slpTimer=micros();
//}
//
//
//
////function for sleeping to save power
//void sleepNow(){
//  digitalWrite(13,HIGH);
//  delay(50);
//  digitalWrite(13,LOW);
//  delay(50);
//  digitalWrite(13,HIGH);
//  delay(50);
//  digitalWrite(13,LOW);
//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//  attachInterrupt(0,wakeUpNow, FALLING);  
//  sleep_mode();
//  power_all_disable();
//  sleep_disable();
//  power_all_enable();
//  detachInterrupt(0);
//  slpTimer = micros();
//  //ledBlink(1,225);
//}
//


void ledBlink(unsigned long period){
  
  digitalWrite(13,HIGH);
  blinkLength = micros() + (period * 1000);
}
