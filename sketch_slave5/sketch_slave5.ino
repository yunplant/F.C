#include <SoftwareSerial.h>
#define master 0x99 //153
#define slave5 0x05 //0

int relay = 6;
SoftwareSerial rs485(2, 3); // RX, TX

void setup() {

  Serial.begin(9600); //PC-아두이노간 TTL통신
  rs485.begin(9600); //아두이노-rs485간 TTL통신
}

void loop() {
    if(rs485.available()){
      byte recv[10];
      rs485.readBytes(recv,10);
      if(recv[0] != slave5) return; //쌩~

      if(recv[2] == 1){
        digitalWrite(relay, HIGH);
      }else if(recv[2] == 0){
        digitalWrite(relay, LOW);
      }
    }
}
