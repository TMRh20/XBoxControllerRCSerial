#include <SoftwareSerial.h>
#include <avr/sleep.h>
#include <avr/power.h>

#define rxPin 10
#define txPin 11
#define MSP_SET_RAW_RC 200
#define MYRC 199
#define MYAUX 198


SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

//declare 8 channels and configure some pointers for ease of use
int channels[8];
int *roll = &channels[0], *pitch = &channels[1], *yaw = &channels[2], *throttle = &channels[3];
int *aux1= &channels[4],*aux2=&channels[5],*aux3=&channels[6],*aux4=&channels[7];

int jCenter = 1500;
int trigZero[3] = {1,1};
int trimRoll = 0, trimPitch = 0, trimYaw = 0;

unsigned long jTimer = 0;
unsigned long slpTimer = 0;
char toSend[42];
byte checksum = 0;



void setup(){
  
  *aux1=1500;*aux2=1500;*aux3=1500;*aux4=1500;

  pinMode(12,OUTPUT); digitalWrite(12,HIGH);
  pinMode(13,OUTPUT);
  
  Serial.begin(115200);
  Serial.println("st");
  mySerial.begin(57600);  

  for(int i=2; i<11; i++){
    pinMode(i,INPUT_PULLUP); 
  } 
  pinMode(A4,INPUT_PULLUP);
  pinMode(A5,INPUT_PULLUP);
  trigZero[0] = analogRead(A6); 
  trigZero[1] = analogRead(A7);
  
}



void loop(){

  //sleep if throttle not being applied for 5 seconds or more
  if(millis() - slpTimer > 5000){digitalWrite(13,LOW); sleepNow();}
    
  //check button status
    buttonLogic(); //function for reading button status and determining what to do
      
  unsigned long tmp = millis();  
  if(tmp - jTimer > 90){ //start sending dataCmds every 90ms  
    getRollPitchYawThrottle(); //function to get readings from joysticks
    
    if(*throttle > 1005){ //if throttle is being applied, reset sleep timer
      slpTimer = millis();
    }
    jTimer = tmp;
    sendRawRC();  //send the data
  }
}




