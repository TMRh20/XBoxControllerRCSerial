#include <MemoryFree.h>

#include <SoftwareSerial.h>
//#include <avr/sleep.h>
//#include <avr/power.h>

#define rxPin 10 //not actually used
#define txPin 11 
#define MSP_SET_RAW_RC 200
#define MSP_MYRC 199

SoftwareSerial mySerial(rxPin, txPin);

//declare 8 channels and configure some pointers for ease of use
int channels[8];
int *roll = &channels[0], *pitch = &channels[1], *yaw = &channels[2], *throttle = &channels[3];
int *aux1= &channels[4],*aux2=&channels[5],*aux3=&channels[6],*aux4=&channels[7];

int altThrottle = 1000, bttnCnt = 0;;
int trigZero[3] = {1,1};

unsigned long jTimer = 0, blinkLength = 0; //slpTimer = 0
char toSend[45];
byte checksum = 0;
boolean altHold = 0;
boolean buttonSend = 0;
unsigned long lcdTimer = 0;
unsigned long tmpTimer = 0;

void setup(){
  
  *aux1=1500;*aux2=1500;*aux3=1500;*aux4=1500;

  pinMode(12,OUTPUT); digitalWrite(12,HIGH); //APC220 SET pin, low activates
  pinMode(13,OUTPUT);
  
  Serial.begin(115200);
  Serial.println("st");
  mySerial.begin(57600);  

  for(int i=2; i<11; i++){ //turn pullups on for all the buttons
    pinMode(i,INPUT_PULLUP); 
  } 
  pinMode(A4,INPUT_PULLUP);
  pinMode(A5,INPUT_PULLUP);
  trigZero[0] = analogRead(A6); 
  trigZero[1] = analogRead(A7);
  
//  mySerial.end();
//  delay(220);
//  mySerial.begin(9600);
//  delay(100);
//  digitalWrite(12,LOW);
//  delay(220);
//  char* tesst = "WR 450000 4 9 6 0";
//  mySerial.println(tesst);
//  delay(250);
//  digitalWrite(12,HIGH);
//  mySerial.end();
//  delay(220);
//  mySerial.begin(57600);
}



void loop(){
  
  if(micros() > blinkLength ){
    digitalWrite(13,LOW); 
  }
  

  //sleep if throttle not being applied for 5 seconds or more
  //if(micros() - slpTimer > 5000000){digitalWrite(13,LOW); sleepNow();}
    
  //check button status
    buttonLogic(); //function for reading button status and determining what to do
  
  unsigned long DL = 25000; //Adjust delay depending on command to be sent
  if(buttonSend){DL = 65000;}
  
  if(micros() - jTimer > DL){ //start sending dataCmds every 75ms
    
    getRollPitchYawThrottle(); //function to get readings from joysticks
    
//    if(*throttle > 1010){ //1005//if throttle is being applied, reset sleep timer
//      slpTimer = micros();
//    }   
    
    if(buttonSend){
      bttnCnt++; if(bttnCnt >= 15){ bttnCnt=0; buttonSend = 0; }       
      sendRawRC();  //send the full data
    }else{
      
      sendMyRC(); 
    }
    jTimer = micros();
  }
//
//  if(millis() - tmpTimer > 500){
//    tmpTimer = millis();
//    //Serial.println("rp:");
//    //Serial.println(*roll);
//    //Serial.println(*pitch);
//    Serial.println(*yaw);
//  
//  }

}




