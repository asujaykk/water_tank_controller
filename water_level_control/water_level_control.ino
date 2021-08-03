/*OUTPUT PIN definitions*/
  #define MOTOR_PIN 7 
  #define LED_EMPTY 2
  #define LED_LOW 3
  #define LED_MED 4
  #define LED_FUL 5
  #define MANUAL_SWITCH 6

/*NPUT PIN definitions*/
  #define S_LOW A0
  #define S_MED A1
  #define S_FUL A2


/*WATER LEVEL DEFINES*/
  #define _SERROR 5
  #define _FUL 4
  #define _MED 3
  #define _LOW 2
  #define _EMPTY 1



/*BOOLEAN DEFINES*/
  #define TRUE 1
  #define FALSE 0




/*GLOBAL VARIABLES*/
  int level_1=0;
  int level_2=0;
  int level_3=0;

  int level=_FUL;
  int sensor_error=FALSE; 
  int motor_on=FALSE;
  int manual_on=FALSE;
  int motor_turn_off_delay=0;
  int blink_on=FALSE;


/*SENSOR THRESHOLD VALUE*/
  int S_THRESHOLD=800;
  int _MTR_OFF_DELAY=10;



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(MOTOR_PIN,OUTPUT);
  digitalWrite(MOTOR_PIN,LOW);
  pinMode(MANUAL_SWITCH,INPUT);
  for (int i=2;i<7;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
    delay(1000);
    digitalWrite(i,LOW);
    delay(1000);
  }
  /*Read the following parameter from EEPROM and update
  * This will help to restore the state if there was a power failure
  * S_THRESHOLD
  * manual_on
  * _MTR_OFF_DELAY
  */
  
  
  readParametersFromMemory();
}

void loop() {

  // put your main code here, to run repeatedly:
   sens_read();

   //command read
   command_read();
   
   //Serial.println("update_level");
   update_level();
   
   //Serial.println("indicator");
   update_indicator();
   

   //Serial.println("m_control");
   update_motor_control();

   //update memory
   writeParametersToMemory();
   
   //activate/deactivate motor
   drive_motor();

   //Serial.println("send_data");
   send_data();

   delay(1000);
}



void update_level(){
  if(level_3>S_THRESHOLD && level_2>S_THRESHOLD && level_1>S_THRESHOLD ){
    level=_FUL;
    sensor_error=FALSE;
  } 
  else if (level_3<S_THRESHOLD && level_2>S_THRESHOLD && level_1>S_THRESHOLD ){
    level=_MED;
     sensor_error=FALSE;
  }
  else if (level_3<S_THRESHOLD && level_2<S_THRESHOLD && level_1>S_THRESHOLD ) {
    level=_LOW;
     sensor_error=FALSE;
  }
  else if (level_3<S_THRESHOLD && level_2<S_THRESHOLD && level_1<S_THRESHOLD ) {
    level=_EMPTY;
     sensor_error=FALSE;
  }
  else{
    level=_SERROR;
    sensor_error=TRUE;
    if (blink_on){
      blink_on=FALSE;
    }
    else{
      blink_on=TRUE;
    }
  }
}

void update_motor_control(){
   if(sensor_error==FALSE && (level==_EMPTY || (manual_on==TRUE && level != _FUL) ) ){
     motor_on=TRUE;   
     
   } else if(sensor_error==TRUE) {
      motor_on=FALSE;
   
   } else if(level==_FUL) {

      if(motor_turn_off_delay==0){
        motor_turn_off_delay=_MTR_OFF_DELAY;
      }
      else if(motor_turn_off_delay==1){
         motor_on=FALSE;
         manual_on=FALSE;
      }
      else{
        motor_turn_off_delay--;
      }
   }
}
