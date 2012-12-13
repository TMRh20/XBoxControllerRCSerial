


void buttonLogic(){
   if(millis()- bTimer < 250){ return;}
   
  //Check the Select and Start buttons
  //Used to toggle mode of A,B,X,Y buttons
  int sel = 0;
    if(digitalRead(A5)==LOW){ //Back button
      slpTimer = millis();
      bTimer = millis();
      sel = 1;
    }
    if(digitalRead(A4)==LOW){ //Start button
        slpTimer = millis();
        bTimer = millis();
        sel = 2;
    }
    
//now read through ABXY,UDLR and black buttons    
for(int i=2; i<11; i++){
    if(digitalRead(i) == LOW){ //if a button is toggled, do the following
      bTimer = millis();
      slpTimer = millis();
      if(sel == 1){            //apply different actions depending on the mode specified by Back and Start buttons
                switch(i){
                  case 2: play(9);break;
                  case 3: play(7); break;
                  case 4: play(8); break; //aux2
                  case 5: break;  
                  case 6: play(8); break;
                  case 7: play(9); break;
                  case 8: break;
                  case 9: break;
                  //default: Serial.println(butArr[i]); break;
                }
      }else
      if(sel == 2){         
                switch(i){
                  case 2: sleepNow(); break;
                  case 3: break;
                  case 4: *aux1 = 1500; break; //aux2
                  case 5: *aux2 = 1500; break;  
                  case 6: *aux1 = 2000; break;
                  case 7: *aux1 = 1000; break;
                  case 8: *aux2 = 1000; break;
                  case 9: *aux2 = 2000; break;
                  //default: Serial.println(butArr[i]); break;
                }       
      }else{
        
                switch(i){
                  case 2: play(1); break; //play tune 1
                  case 3: play(2); break; //play tune 2
                  case 4: play(3); break; //play tune 3
                  case 5: play(4); break; //play tune 4
                  case 6: play(5); break; //tune 5
                  case 7: play(6); break; //tune 6
                  case 8: play(8); break; //volUp
                  case 9: play(9); break; //volDn
                  //default: Serial.println(butArr[i]); break;
                }
      }
    }
}
}
