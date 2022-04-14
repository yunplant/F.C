// slave5 는 led컨트롤


int relay1 = 4;
int relay2 = 5;
int relay3 = 6;
int relay4 = 7;
int relay5 = 8;
int relay6 = 9;
int relay7 = 10;
int relay8 = 12;

int pwm = 11;

#include <SoftwareSerial.h>
#define master 0x99 //153
#define slave9 0x09
#define modepin 13
#define readmode LOW
#define sendmode HIGH


SoftwareSerial rs485(2, 3); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200); //PC-아두이노간 TTL통신
  rs485.begin(19200); //아두이노-rs485간 TTL통신
  pinMode(modepin,OUTPUT); //송수신제어핀
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
  pinMode(pwm, OUTPUT);
  digitalWrite(modepin,readmode); //수신모드
}
void loop() {
  // put your main code here, to run repeatedly:
  if(rs485.available()){
    //485모듈로 들어오는 값이 존재한다면
    byte recv[10];
    rs485.readBytes(recv,10);
    if(recv[0] != slave9) return; //쌩~
//    Serial.print("받은거=");
//    for(int i =0;i<10;i++){
//      Serial.print(recv[i],HEX);
//      Serial.print(",");
//    }
//    Serial.println(); 

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
//    byte data[10];
//    data[0] = recv[0];
//    data[1] = recv[1];
//    //응답데이터
//    data[2] = 'O';
//    data[3] = 'K';
//    for(int i =4;i<10;i++){
//      data[i] = 0x00;
//    }
//    Serial.print("보낸거=");
//    for(int i =0;i<10;i++){
//      Serial.print(data[i],HEX);
//      Serial.print(",");
//    }
//    Serial.println(); 
//    digitalWrite(modepin,sendmode);
//    rs485.write(data,10);
  digitalWrite(modepin,readmode);
  }
}
