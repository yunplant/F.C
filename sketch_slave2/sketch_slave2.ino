#include <cm1106_i2c.h>
CM1106_I2C cm1106_i2c;


#include <SoftwareSerial.h>
#define master 0x99 //153
#define slave2 0x02 //0
//#define modepin 13
//#define readmode LOW
//#define sendmode HIGH
SoftwareSerial rs485(2, 3); // RX, TX

void setup() {
  cm1106_i2c.begin();
  // put your setup code here, to run once:
  Serial.begin(9600); //PC-아두이노간 TTL통신
  rs485.begin(9600); //아두이노-rs485간 TTL통신
//  pinMode(modepin,OUTPUT); //송수신제어핀
//  digitalWrite(modepin,readmode); //수신모드
}
void loop() {
  Serial.println("asd");
  uint8_t ret = cm1106_i2c.measure_result();
//  cm_result = cm1106_i2c.co2;
  String cm__result = String(cm1106_i2c.co2);

  while(cm__result.length() < 4){
    cm__result = "0"+cm__result;
  }
    
  if(rs485.available()){
    //485모듈로 들어오는 값이 존재한다면
    byte recv[10];
    rs485.readBytes(recv,10);
    if(recv[0] != slave2) return; //쌩~
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
    data[2] = cm__result[0];
    data[3] = cm__result[1];
    data[4] = cm__result[2];
    data[5] = cm__result[3];
    
    for(int i =6;i<10;i++){
      data[i] = 0x00;
    }
    Serial.print("보낸거 = ");
    for(int i =0;i<10;i++){
      Serial.print(data[i],HEX);
      Serial.print(",");
    }
    Serial.println(); 
//    digitalWrite(modepin,sendmode);
    rs485.write(data,10);
//    digitalWrite(modepin,readmode);
  }
}
