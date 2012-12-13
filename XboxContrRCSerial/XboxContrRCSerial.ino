#include <SoftwareSerial.h>

#define rxPin 10 //unused - pin10 connected to black button
#define txPin 11 

#include <avr/sleep.h>
#include <avr/power.h>

boolean digArr[14];
unsigned long slpTimer = 0;
int trigZero[3] = {1,1};

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);


//declare 8 channels and configure some pointers for ease of use
int channels[8];

int *roll = &channels[0], *pitch = &channels[1], *yaw = &channels[2], *throttle = &channels[3];
int *aux1= &channels[4],*aux2=&channels[5],*aux3=&channels[6],*aux4=&channels[7];

unsigned long bTimer = 0;
unsigned long jTimer = 0;

char toSend[42];
byte checksum = 0;

void setup(){
  
  *aux1=1500;*aux2=1500;*aux3=1500;*aux4=1500;

  pinMode(12,OUTPUT); digitalWrite(12,HIGH);
  
  Serial.begin(115200);
  Serial.println("st");
  pinMode(13,OUTPUT);

 for(int i=2; i<11; i++){
   pinMode(i,INPUT_PULLUP); 
 } 
 pinMode(A4,INPUT_PULLUP);
 pinMode(A5,INPUT_PULLUP);
 trigZero[0] = analogRead(A6);
 trigZero[1] = analogRead(A7);
  mySerial.begin(57600);
}



void loop(){

  //sleep if throttle not being applied for 5 seconds or more
  if(millis() - slpTimer > 5000){digitalWrite(13,LOW); sleepNow();}
  
  
  
  
  //check button status
    buttonLogic(); //function for reading button status and determining what to do
  
 unsigned long tmp = millis();
  //send dataCmds every 90ms  
  if(tmp - jTimer > 90){
    
    getRollPitchYawThrottle();

    //if throttle is being applied, reset sleep timer
    if(*throttle > 1005){ 
      slpTimer = millis();
    }
    jTimer = tmp;   
    
    sendRawRC();

  }
    
}

//Read Joysticks, mapt to values 1000-2000, and fix center values

void getRollPitchYawThrottle( ){
  
    int tmpRoll = constrain(analogRead(A1), 220,800);   
    int tmpPitch = constrain(analogRead(A0), 190,800);
    int tmpYaw = constrain(analogRead(A3),290,800);
    int tmpThrottle = constrain(analogRead(A6),50,trigZero[0]-15);
    
    //Values must be adjusted to provide a reading closest to 1000-2000
    *roll = map(tmpRoll,220,800,2000,1000);
    *pitch = map(tmpPitch,190,800,1000,2000);
    *yaw = map(tmpYaw,290,800,1000,2000);
    
    centerFix(yaw);
    centerFix(pitch);
    centerFix(roll);   
  
    *throttle = map(tmpThrottle,50,trigZero[0]-15,2000,1000); 
}
  

//Create a 'zero point' or 'center area' to allow for play in the joysticks
//Any small movements around center will not affect output
void centerFix(int *what){
  if(*what >= 1450 && *what <= 1550){ 
      *what = 1500;
    }else
    if(*what < 1450){*what += 50;
    }else
    if(*what > 1550){*what -= 50;}
}

void ledBlink(byte times, byte period){  
  
  for(int i=0;i<times;i++){
    digitalWrite(13,HIGH);
    delay(period);
    digitalWrite(13,LOW);
    delay(period);
  }
}  
