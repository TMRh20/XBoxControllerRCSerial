char buffCount = 0;


//Construct MSP_SET_RAW_RC packet
//format $M>[length][code][data][checksum]

void sendRawRC(){
  //Fill array with data to send for RC Control
  buffer8(16); //length
  buffer8(MSP_SET_RAW_RC); //code
  for(int i=0; i<8;i++){       
    buffer16(channels[i]); //data (length = 8*2 bytes)
  }  
  sendBuffer(); //add checksum value and send the data
}

//void sendMyRC(){  
//  buffer8(8);
//  buffer8(MSP_MYRC);
//  for(int i=0; i<4;i++){
//    buffer16(channels[i]);
//  }
//  sendBuffer();
//}

void sendMyRC(){  
  buffer8(4);
  buffer8(MSP_MYRC);
  
  byte chans[8];
    for(int i=0; i<4;i++){
      byte TMP = map(channels[i],1000,2000,0,250);
      buffer8(TMP);
    }

  sendBuffer();
}


//Functions for converting and loading data into a sending buffer
//based on multiwii RCSerial protocol

//load two 8-bit values (16 bits) into sending array
void buffer16(int a){
  //convert 16-bit to 8Bit
  buffer8((a) & 0xFF); //strip the 'most significant bit' (MSB) and buffer
  buffer8((a>>8) & 0xFF); //move the MSB to LSB, strip the MSB and buffer
}

//load an 8-bit value into sending array
void buffer8(byte a){  
    toSend[buffCount] = a;
    checksum ^= a;
    buffCount++;
    if(buffCount >= 42){ buffCount = 0; checksum=0; Serial.print("fail"); }
}


//Function to send the data once loaded
void sendBuffer(){
  toSend[buffCount] = checksum; //checksum
  mySerial.print("$M<"); 
  for(int u=0;u<buffCount+2;u++){
    mySerial.write(toSend[u]);    
  }
  checksum=0;
  buffCount = 0;
}
