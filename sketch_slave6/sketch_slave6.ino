// slave6 는 led컨트롤
#include <SoftwareSerial.h>
#define master 0x99 //153
#define slave6 0x06

int relay1 = 4;
int relay2 = 5;
int relay3 = 6;
int relay4 = 7;
int relay5 = 8;
int relay6 = 9;
int relay7 = 10;
int pwm = 11;  //pwm 포트 번호
int relay8 = 12; 

SoftwareSerial rs485(2, 3); // RX, TX

void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600); //PC-아두이노간 TTL통신
  rs485.begin(9600); //아두이노-rs485간 TTL통신

//  pinMode(modepin,OUTPUT); //송수신제어핀
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
  pinMode(pwm, OUTPUT);
}


void loop() {

        
  // put your main code here, to run repeatedly:
  if(rs485.available()){

    //485모듈로 들어오는 값이 존재한다면
    byte recv[10];
    rs485.readBytes(recv,10);

    if(recv[0] != slave6) return; //쌩~

    /* default(전원 꺼졌을 때):NC(connected)->불 켜짐 <=> if recv[3]=0 HIGH */
    if(recv[2] == 1 and recv[3] == 0){
      digitalWrite(relay1,LOW);
    }else if(recv[2] == 1 and recv[3] == 1){
      digitalWrite(relay1,HIGH);
    }
    if(recv[2] == 2 and recv[3] == 0){
      digitalWrite(relay2,LOW);
    }else if(recv[2] == 2 and recv[3] == 1){
      digitalWrite(relay2,HIGH);
    }
    if(recv[2] == 3 and recv[3] == 0){
      digitalWrite(relay3,LOW);
    }else if(recv[2] == 3 and recv[3] == 1){
      digitalWrite(relay3,HIGH);
    }
    if(recv[2] == 4 and recv[3] == 0){
      digitalWrite(relay4,LOW);
    }else if(recv[2] == 4 and recv[3] == 1){
      digitalWrite(relay4,HIGH);
    }
    if(recv[2] == 5 and recv[3] == 0){
      digitalWrite(relay5,LOW);
    }else if(recv[2] == 5 and recv[3] == 1){
      digitalWrite(relay5,HIGH);
    }
    if(recv[2] == 6 and recv[3] == 0){
      digitalWrite(relay6,LOW);
    }else if(recv[2] == 6 and recv[3] == 1){
      digitalWrite(relay6,HIGH);
    }
    if(recv[2] == 7 and recv[3] == 0){
      digitalWrite(relay7,LOW);
    }else if(recv[2] == 7 and recv[3] == 1){
      digitalWrite(relay7,HIGH);
    }
    if(recv[2] == 8 and recv[3] == 0){
      digitalWrite(relay8,LOW);
    }else if(recv[2] == 8 and recv[3] == 1){
      digitalWrite(relay8,HIGH);
    }


    
    if(recv[2] == 9){

       analogWrite(pwm,recv[3]);
       Serial.println(recv[3]);
    }

    

  }
}