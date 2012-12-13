char buffCount = 0;


//Construct MSP_SET_RAW_RC packet
//format $M>[length][code][data][checksum]
void sendRawRC(){
  
  //Fill array with data to send for RC Control
  buffer8(16); //length
  buffer8(200); //code
  for(int i=0; i<8;i++){       
    buffer16(channels[i]); //data (length = 8*2 bytes)
  }
  
  sendBuffer(); //add checksum value and send the data
}

//Construct custom MSP_PLAY packet
//Added to MultiWii to control a music player
void play(byte whichCmd){
  
 buffer8(1);
 buffer8(150);
 buffer8(whichCmd); 
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
