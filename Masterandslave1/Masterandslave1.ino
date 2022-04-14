#include <Wire.h>

#include <SoftwareSerial.h>
#define master 0x99 //153
#define slave1 0x01 //0
//#define modepin 13
//#define readmode LOW
//#define sendmode HIGH
SoftwareSerial rs485(2, 3); // RX, TX


byte slave2_call[10];
byte slave2_data[10];

byte slave3_call[10];
byte slave3_data[10];

byte slave4_call[10];
byte slave4_data[10];

//
//void SetupSQ500() {
//  Wire.beginTransmission(0x68);
//  Wire.write(1 << 4 | 1 << 7 | 1 << 3);
//  Wire.endTransmission(); 
//}
//
//float ReadSQ500() {
//  int16_t result = 0;
//
//
//  Wire.requestFrom(0x68, 3);
//  
//  while(!Wire.available()) {}
//  uint8_t msb = Wire.read();
////  Serial.print(msb, HEX);
// 
//  while(!Wire.available()) {}
//  uint8_t lsb = Wire.read();
////  Serial.print(lsb, HEX);
//
//  result = msb << 8 | lsb;
//  if (result < 0)
//    result = 0;
//
//  float ret = 0;
//
//  ret = (result / (float)0xFFFF) *  2.048;
//  ret *= 2000;
//  
//  if (Wire.available()) {
//    uint8_t config = Wire.read();
////    Serial.println();
//  }
//  return ret;
//}

  
void setup() {
//  Wire.begin();
//  SetupSQ500();
  Serial.begin(9600); //PC-아두이노간 TTL통신
  rs485.begin(9600); //아두이노-rs485간 TTL통신
//  pinMode(modepin,OUTPUT); //송수신제어핀
//  digitalWrite(modepin,readmode); //수신모드
}
void loop() {
  Serial.println("시작");
//  float quantum;
//
//  quantum = ReadSQ500();
//  int quantum_ = quantum*100;
//  String quantum__ = String(quantum_);
//  while(quantum__.length() < 6){
//    quantum__ = "0"+quantum__;
//    }
//  
  if(rs485.available()){
    //485모듈로 들어오는 값이 존재한다면
    byte recv[10];
    rs485.readBytes(recv,10);
    if(recv[0] != slave1) return; //쌩~
    Serial.print("받은거 = ");
    for(int i =0;i<10;i++){
      Serial.print(recv[i],HEX);
      Serial.print(",");
    }
    Serial.println(); 
//
    byte slave2_call[10];
    slave2_call[0] = 0x02;
    slave2_call[1] = 0x00;
    for(int i =2; i<10; i++){
      slave2_call[i] = 0x00;
    }
//    digitalWrite(modepin,sendmode);
    rs485.write(slave2_call,10);
//    digitalWrite(modepin,readmode);
    Serial.print("Slave2 보낸거 = ");
    for(int i =0;i<10;i++){
      Serial.print(slave2_call[i],HEX);
      Serial.print(",");
    }
    Serial.println(); 

    byte slave2_data[10];
    
    while(1){
      rs485.write(slave2_call,10);
//      if(rs485.available()){
      rs485.readBytes(slave2_data,10);
      if(slave2_data[0] == 0x02){
        break;
        }
      
      else{
        Serial.println("받는중..");
      }
    }
    Serial.print("Slave2 받은거 = ");
    for(int i =0;i<10;i++){
      Serial.print(slave2_data[i],HEX);
      Serial.print(",");
    }
    Serial.println(); 
    
    slave3_call[0] = 0x03;
    slave3_call[1] = 0x00;
    for(int i =2; i<10; i++){
      slave3_call[i] = 0x00;
    }
    Serial.print("Slave3 보낸거 = ");
    for(int i =0;i<10;i++){
      Serial.print(slave3_call[i],HEX);
      Serial.print(",");
    }
    Serial.println(); 
    
//    digitalWrite(modepin,sendmode);
    rs485.write(slave3_call,10);
//    digitalWrite(modepin,readmode); 
    
    while(1){
      if(rs485.available()){
        rs485.readBytes(slave3_data,10);
        if(slave3_data[0] == 0x03){
          break;
        }
      }
      else{
        Serial.println("받는중..");
      }
    }  
    Serial.print("Slave3 받은거 = ");
    for(int i =0;i<10;i++){
      Serial.print(slave3_data[i],HEX);
      Serial.print(",");
    }
    Serial.println(); 

    slave4_call[0] = 0x04;
    slave4_call[1] = 0x00;
    for(int i =2; i<10; i++){
      slave4_call[i] = 0x00;
    }
    Serial.print("Slave4 보낸거 = ");
    for(int i =0;i<10;i++){
      Serial.print(slave4_call[i],HEX);
      Serial.print(",");
    }
    Serial.println(); 
    
//    digitalWrite(modepin,sendmode);
    rs485.write(slave4_call,10);
//    digitalWrite(modepin,readmode); 
    
    while(1){
      if(rs485.available()){
        rs485.readBytes(slave4_data,10);
        if(slave4_data[0] == 0x04){
          break;
        }
      }
      else{
        Serial.println("받는중..");
      }
    }  
    Serial.print("Slave4 받은거 = ");
    for(int i =0;i<10;i++){
      Serial.print(slave4_data[i],HEX);
      Serial.print(",");
    }
    Serial.println(); 
    
    byte data[20];
    data[0] = recv[0];
    data[1] = recv[1];
    //응답데이터
    data[2] = slave4_data[2];
    data[3] = slave4_data[3];
    data[4] = slave4_data[4];
    data[5] = slave4_data[5];
    data[6] = slave4_data[6];
    data[7] = slave4_data[7];
    data[8] = slave2_data[2];
    data[9] = slave2_data[3];
    data[10] = slave2_data[4];
    data[11] = slave2_data[5];
    data[12] = slave3_data[2];
    data[13] = slave3_data[3];
    data[14] = slave3_data[4];
    data[15] = slave3_data[5];
    data[16] = slave3_data[6];
    data[17] = slave3_data[7];
    data[18] = slave3_data[8];
    data[19] = slave3_data[9];
    
//    for(int i =8;i<10;i++){
//      data[i] = 0x00;
//    }
    Serial.print("최종 보낸거 = ");
    for(int i =0;i<20;i++){
      Serial.print(data[i],HEX);
      Serial.print(",");
    }
    Serial.println(); 
//    digitalWrite(modepin,sendmode);
    rs485.write(data,20);
//    digitalWrite(modepin,readmode);
  }

}
