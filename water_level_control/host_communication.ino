
void send_data(){
  Serial.print('$');
  Serial.print(level_1);
  Serial.print(',');
  Serial.print(level_2);
  Serial.print(',');
  Serial.print(level_3);
  Serial.print(',');
  Serial.print(manual_on);
  Serial.print(',');
  Serial.print(S_THRESHOLD);
  Serial.print(',');
  Serial.print(level);
  Serial.print(',');
  Serial.print(motor_on);
  Serial.print(',');
  Serial.print(sensor_error);
  Serial.println('#');
  
}

void command_read(){
 if(Serial.available()){
  char Ch=Serial.read();
  if(Ch=='M'){
    char value=Serial.read();
    if(value=='1'){
      manual_on=TRUE;
      Serial.println("MON");
    }
    else if(value=='0'){
      manual_on=FALSE;
      motor_on=FALSE;
      Serial.println("MOFF");
    }
  } 
  else if(Ch=='T'){
    char a[5];
    int i;
    Ch=Serial.read();
    for(i=0;i<4 && Ch!='\0' && Ch!='\r' && Ch!='\n';i++){
      a[i]=Ch;
      Ch=Serial.read();
    }
    a[i]='\0';
    int value=String(a).toInt();
    //Serial.print("value=");
    //Serial.println(value);
    if(value>=0 && value<=1023){
      S_THRESHOLD=value;
      Serial.print("T=");
      Serial.println(value);
    }
  }
  else if(Ch=='D'){
    Ch=Serial.read();
    char a[3];
    int i;
    for(i=0;i<2 && Ch!='\0' && Ch!='\r' && Ch!='\n';i++){
      a[i]=Ch;
      Ch=Serial.read();
    }
    a[i]='\0';
    int value=String (a).toInt();
    if(value>=0 && value<=1023){
      _MTR_OFF_DELAY=value;
      Serial.print("D=");
      Serial.println(value);
    }
  }
 }
}
