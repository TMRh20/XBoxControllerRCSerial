

unsigned long bTimers[13];
int sel = 0;

void buttonLogic(){
 
  //Check the Select, Start and Black buttons
  //Used to toggle mode of A,B,X,Y,U,D,L,R buttons
  
  boolean mode[3] = {digitalRead(A4),digitalRead(10),digitalRead(A5)}; //back,start,black buttons

  for(int i=0; i<3; i++){
    if(!mode[i]){
       ledBlink(1,1);
       slpTimer = millis(); 
       sel = i;         
     }    
  }
  

boolean buttonSend = 0;

//now read through ABXY,UDLR and black buttons    
for(int i=2; i<10; i++){
    if(digitalRead(i) == LOW && millis() - bTimers[i] > 250){ //if a button is toggled, and hasn't been toggled for 250ms, do the following
      ledBlink(1,3);
      bTimers[i] = millis();
      slpTimer = millis();
      if(sel == 0){            //apply different actions depending on the mode specified by Back and Start buttons
                switch(i){
                  case 2: break;               //A
                  case 3: trimYaw++; break;    //B
                  case 4: break;               //Y
                  case 5: trimYaw--; break;    //X
                  case 6: trimPitch++; break;  //Up
                  case 7: trimPitch--; break;  //Dn
                  case 8: trimRoll--; break;   //R
                  case 9: trimRoll++; break;   //L
                }
      }else
      if(sel == 2){
                buttonSend = 1;        
                switch(i){
                  case 2: break;
                  case 3: break;
                  case 4: *aux1 = 1500; break;
                  case 5: *aux2 = 1500; break;  
                  case 6: *aux1 = 2000; break;
                  case 7: *aux1 = 1000; break;
                  case 8: *aux2 = 1000; break;
                  case 9: *aux2 = 2000; break;
                }       
      }else{
                buttonSend = 1;
                switch(i){
                  case 2: break;
                  case 3: break;
                  case 4: *aux3 = 1500; break;
                  case 5: *aux4 = 1500; break;
                  case 6: *aux3 = 2000; break;
                  case 7: *aux3 = 1000; break;
                  case 8: *aux4 = 2000; break;
                  case 9: *aux4 = 1000; break;
                }
      }
    } 
  }
  if(buttonSend){ sendMyAux(); }
}


