// slave4 는 퀀텀

#include <Wire.h>

#include <SoftwareSerial.h>
#define master 0x99 //153
#define slave4 0x04 //0
//#define modepin 13
//#define readmode LOW
//#define sendmode HIGH
SoftwareSerial rs485(2, 3); // RX, TX

void SetupSQ500() {
  Wire.beginTransmission(0x68);
  Wire.write(1 << 4 | 1 << 7 | 1 << 3);
  Wire.endTransmission(); 
}

float ReadSQ500() {
  int16_t result = 0;


  Wire.requestFrom(0x68, 3);
  
  while(!Wire.available()) {}
  uint8_t msb = Wire.read();
//  Serial.print(msb, HEX);
 
  while(!Wire.available()) {}
  uint8_t lsb = Wire.read();
//  Serial.print(lsb, HEX);

  result = msb << 8 | lsb;
  if (result < 0)
    result = 0;

  float ret = 0;

  ret = (result / (float)0xFFFF) *  2.048;
  ret *= 2000;
  
  if (Wire.available()) {
    uint8_t config = Wire.read();
//    Serial.println();
  }
  return ret;
}

  
void setup() {
  Wire.begin();
  SetupSQ500();
  Serial.begin(9600); //PC-아두이노간 TTL통신
  rs485.begin(9600); //아두이노-rs485간 TTL통신
//  pinMode(modepin,OUTPUT); //송수신제어핀
//  digitalWrite(modepin,readmode); //수신모드
}
void loop() {
  float quantum;

  quantum = ReadSQ500();
  int quantum_ = quantum*100;
  String quantum__ = String(quantum_);
  while(quantum__.length() < 6){
    quantum__ = "0"+quantum__;
    }
  Serial.println("시작");
  if(rs485.available()){
    Serial.println("avail");
    //485모듈로 들어오는 값이 존재한다면
    byte recv[10];
    rs485.readBytes(recv,10);
    Serial.println("sent");
    if(recv[0] != slave4) return; //쌩~
    Serial.print("받은거 = ");
    for(int i =0;i<10;i++){
      Serial.print(recv[i],HEX);
      Serial.print(",");
    }
    Serial.println(); 
    
    
    byte data[10];
    data[0] = recv[0];
    data[1] = recv[1];
    //응답데이터
    data[2] = quantum__[0];
    data[3] = quantum__[1];
    data[4] = quantum__[2];
    data[5] = quantum__[3]; 
    data[6] = quantum__[4]; 
    data[7] = quantum__[5];
    for(int i =8;i<10;i++){
      data[i] = 0x00;
    }
//    Serial.print("보낸거 = ");
//    for(int i =0;i<10;i++){
//      Serial.print(data[i],HEX);
//      Serial.print(",");
//    }
    Serial.println(); 
//    digitalWrite(modepin,sendmode);
    rs485.write(data,10);
//    digitalWrite(modepin,readmode);
  }

}
