// slave3 는 온습도센서


// 온습도센서 정의
#include <SHT1x.h>
#define dataPin  10
#define clockPin 11
SHT1x sht1x(dataPin, clockPin);
// 온습도센서 정의 끝

#include <SoftwareSerial.h>
#define master 0x99 //153
#define slave3 0x03 //0
//#define modepin 13
//#define readmode LOW
//#define sendmode HIGH
SoftwareSerial rs485(2, 3); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //PC-아두이노간 TTL통신
  rs485.begin(9600); //아두이노-rs485간 TTL통신
//  pinMode(modepin,OUTPUT); //송수신제어핀
//  digitalWrite(modepin,readmode); //수신모드
}
void loop() {
// 온습도 루프
  float temp;
  float humid;

  
  // Read values from the sensor
  temp = sht1x.readTemperatureC();
  humid = sht1x.readHumidity();

  int temp2 = temp*100;
  int humid2 = humid*100;
  
  String temp3 = String(temp2);
  String humid3 = String(humid2);

  while(temp3.length() < 4){
    temp3 = "0"+temp3;
    }
  while(humid3.length() < 4){
    humid3 = "0"+humid3;
    }

// 온습도 루프 끝
  Serial.println("ASD");
  if(rs485.available()){
    //485모듈로 들어오는 값이 존재한다면
    Serial.println("값들어옴");
    byte recv[10];
    rs485.readBytes(recv,10);
    Serial.println(recv[0]);
    if(recv[0] != 0x03) return; //쌩~
    Serial.print("받은거 = ");
    for(int i =0;i<10;i++){
      Serial.print(recv[i],DEC);
      Serial.print(",");
    }
    Serial.println(); 


    
    byte data[10];
    data[0] = recv[0];
    data[1] = recv[1];
    //응답데이터
    data[2] = temp3[0];
    data[3] = temp3[1];
    data[4] = temp3[2];
    data[5] = temp3[3];
    data[6] = humid3[0];
    data[7] = humid3[1];
    data[8] = humid3[2];
    data[9] = humid3[3];
    
//    Serial.print("보낸거 = ");
//    for(int i =0;i<10;i++){
//      Serial.print(data[i],DEC);
//      Serial.print(",");
//    }
//    Serial.println(); 
//    
//    digitalWrite(modepin,sendmode);
    rs485.write(data,10);
//    digitalWrite(modepin,readmode);
//    
  }
  
}
