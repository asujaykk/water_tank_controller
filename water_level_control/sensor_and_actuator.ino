void sens_read(){
  level_1=analogRead(S_LOW);
  level_2=analogRead(S_MED);
  level_3=analogRead(S_FUL);
  if(digitalRead(MANUAL_SWITCH)){
    if(manual_on==TRUE){
       manual_on=FALSE;
    }
    else{
      manual_on=TRUE;
    }
  }
}


void  update_indicator(){
  if (sensor_error==TRUE){
      //update_motor_control();
      if(blink_on==TRUE){
        digitalWrite(LED_FUL,HIGH);
        digitalWrite(LED_MED,HIGH);
        digitalWrite(LED_LOW,HIGH);
        digitalWrite(LED_EMPTY,HIGH);
      }
      else{
        digitalWrite(LED_FUL,LOW);
        digitalWrite(LED_MED,LOW);
        digitalWrite(LED_LOW,LOW);
        digitalWrite(LED_EMPTY,LOW);
      }
  } 
  else if (level==_FUL){
      digitalWrite(LED_FUL,HIGH);
      digitalWrite(LED_MED,HIGH);
      digitalWrite(LED_LOW,HIGH);
      digitalWrite(LED_EMPTY,HIGH);
  } 
  else if (level==_MED){
      digitalWrite(LED_FUL,LOW);
      digitalWrite(LED_MED,HIGH);
      digitalWrite(LED_LOW,HIGH);
      digitalWrite(LED_EMPTY,HIGH);
  }
  else if (level==_LOW){
      digitalWrite(LED_FUL,LOW);
      digitalWrite(LED_MED,LOW);
      digitalWrite(LED_LOW,HIGH);
      digitalWrite(LED_EMPTY,HIGH);
  }
    else if (level==_EMPTY){
      digitalWrite(LED_FUL,LOW);
      digitalWrite(LED_MED,LOW);
      digitalWrite(LED_LOW,LOW);
      digitalWrite(LED_EMPTY,HIGH);
  }
  
}

void drive_motor(){
  if(motor_on==TRUE){
    digitalWrite(MOTOR_PIN,HIGH);
  } else{
    digitalWrite(MOTOR_PIN,LOW);
  }
}
