
#include <Wire.h>
#include <SoftwareSerial.h>
#include <time.h>
#include <stdlib.h>


// #define master 0x99 //153
#define S1 0x01 //0
#define S2 0x02
#define S3 0x03
#define S4 0x04
#define S5 0x05

#define LEN_slave 10
#define LEN_master 20


SoftwareSerial rs485(2, 3); // RX, TX

//RPi <-> Master
byte recv[LEN_slave];  
//Master <-> slave2
byte slave2_call[LEN_slave] = {0x02,0x00,};
byte slave2_data[LEN_slave];
//Master <-> slave3
byte slave3_call[LEN_slave] = {0x03,0x00,};
byte slave3_data[LEN_slave];
//Master <-> slave4
byte slave4_call[LEN_slave] = {0x04,0x00,};
byte slave4_data[LEN_slave];
//Master <-> slave5
byte slave5_call[LEN_slave] = {0x05,0x00,};
byte slave5_data[LEN_slave];
//Master<-slaves
byte data[LEN_master];

// 루프 예외 처리
extern volatile unsigned long timer0_millis;  //타이머변수
unsigned long time_sec_now;  //현재시간값 저장변수


void setup() {

  Serial.begin(9600); //RPI-아두이노간 TTL통신
  rs485.begin(9600); //아두이노-rs485간 TTL통신
}

void Slave_Call(byte *slave_call, int len){  //slave 호출 함수

    Serial.println("slave call...");

    for(int i =0; i<len; i++){
      Serial.print(slave_call[i], HEX);
      Serial.print(",");
    }

    Serial.println(); 
    rs485.write(slave_call, len);
}

void Slave_Received(byte *slave_data, int len){   //slave 데이터 받는 함수 선언
    
    Serial.println("slave data...");
    
    for(int i =0;i<len;i++){
      Serial.print(slave2_data[i],HEX);
      Serial.print(",");
    }

    Serial.println(); 
}

void Merge_Data(){  //데이터 수합 함수 선언

    data[0] = recv[0];
    data[1] = recv[1];

    //응답데이터 -> 20바이트 데이터로 송신
    data[2] = slave2_data[2];
    data[3] = slave2_data[3];
    data[4] = slave2_data[4];
    data[5] = slave2_data[5];

    data[6] = slave3_data[2];
    data[7] = slave3_data[3];
    data[8] = slave3_data[4];
    data[9] = slave3_data[5];
    data[10] = slave3_data[6];
    data[11] = slave3_data[7];
    data[12] = slave3_data[8];
    data[13] = slave3_data[9];

    data[14] = slave4_data[2];
    data[15] = slave4_data[3];
    data[16] = slave4_data[4];
    data[17] = slave4_data[5];
    data[18] = slave4_data[6];
    data[19] = slave4_data[7];

    //data[20] = slave5_data[2];  //1->highg, 0->low
    
    Slave_Call(data, LEN_master);  //Master->RPi
}

void loop() {

  Serial.println("Loop start");

  /*** RPi -> Master ***/
  //Master 호출
  if(!rs485.available()){

    Serial.println("No data received to rs485..");
  }
  else{

    /*** Slave1(Master) - start ***/
    rs485.readBytes(recv, LEN_slave);

    if(recv[0] != S1){
      Serial.println("RPi->Master 호출 기다리는 중..");
      return;
    }
    Slave_Received(recv, LEN_slave);  //RPi->Master 
    /*** Slave1(Master) - end ***/


    /*** Slave2(CO2) - start ***/
    //Slave2 Tx 
    Slave_Call(slave2_call, LEN_slave);  //함수 호출  

    //Slave2 Rx 
    timer0_millis = 0;  //reset
    int cnt_recall = 0;  //재호출 카운트 변수 선언

    while(1){  //값 받을 때까지 대기..
      
      time_sec_now = millis()

      if(rs485.available()){ 
        rs485.readBytes(slave2_data,10);
        if(slave2_data[0] == S2){
          break;
        }
        else{ 
          Serial.println("waiting to receive slave..");

          if(time_sec_now > 30000 and cnt_recall==0){
            Serial.println("30초 이상 경과하여 모듈을 재호출합니다.");
            Slave_Call(slave2_call, LEN_slave);

            cnt_recall += 1;            
          }
          else if(time_sec_now > 60000){ //루프 예외처리
            Serial.println("1분 이상 경과하여 루프를 탈출합니다.");
            break;
          }
        }
      }
    }
    Slave_Received(slave2_data, LEN_slave);  //함수 호출
    /*** Slave2(CO2) - end ***/


    /*** Slave3(Temp & Humi) - start***/
    //Slave3 Tx 
    Slave_Call(slave3_call, LEN_slave);  //함수 호출  

    //Slave3 Rx 
    timer0_millis = 0;  //reset
    cnt_recall = 0;  //재호출 카운트 변수 선언

    while(1){  //값 받을 때까지 대기.. 
      
      time_sec_now = millis()

      if(rs485.available()){ 
        rs485.readBytes(slave3_data,10);
        if(slave3_data[0] == S3){
          break;
        }
        else{ 
          Serial.println("waiting to receive slave..");

          if(time_sec_now > 30000 and cnt_recall==0){
            Serial.println("30초 이상 경과하여 모듈을 재호출합니다.");
            Slave_Call(slave3_call, LEN_slave);

            cnt_recall += 1;            
          }
          else if(time_sec_now > 60000){ //루프 예외처리
            Serial.println("1분 이상 경과하여 루프를 탈출합니다.");
            break;
          }
        }
      }
    }    
    Slave_Received(slave3_data, LEN_slave);  //함수 호출    
    /*** Slave3(Temp & Humi) - end***/
    

    /*** Slave4(Quntum) - start ***/
    //Slave4 Tx 
    Slave_Call(slave4_call, LEN_slave);  //함수 호출  

    //Slave4 Rx 
    timer0_millis = 0;  //reset
    cnt_recall = 0; 
    
    while(1){  //값 받을 때까지 대기..
      
      time_sec_now = millis();
      
      if(rs485.available()){ 
        rs485.readBytes(slave4_data,10);
        if(slave4_data[0] == S4){
          break;
        }
        else{ 
          Serial.println("waiting to receive slave..");

          if(time_sec_now > 30000 and cnt_recall==0){
            Serial.println("30초 이상 경과하여 모듈을 재호출합니다.");
            Serial.print("time : ");
            Serial.println(time_sec_now);

            Slave_Call(slave4_call, LEN_slave);

            cnt_recall += 1;            
          }
          else if(time_sec_now > 60000){ //루프 예외처리
            Serial.println("1분 이상 경과하여 루프를 탈출합니다.");
            Serial.print("time : ");
            Serial.println(time_sec_now);

            break;
          }
        }
      }
    }    
    Slave_Received(slave4_data, LEN_slave);  //함수 호출    
    /*** Slave4(Quntum) - end ***/


    /*** Slave5(Irrigation) - start ***/
    /*
    //slave5 Tx 
    Slave_Call(slave5_call, LEN_slave);  //함수 호출  

    //slave5 Rx 
    while(1){  //값 받을 때까지 대기..
      time_sec_now = tm.tm_sec;
      time_sec_gap = abs(time_sec_now - time_sec_past);  
      
      if(rs485.available()){ 
        rs485.readBytes(slave5_data,10);
        if(slave5_data[0] == S5){

          break;
        }
        else{ 
          Serial.println("waiting to receive slave..");

          if(time_sec_gap > 30 and cnt_recall==0){
            Serial.println("30초 이상 경과하여 모듈을 재호출합니다.");
            Slave_Call(slave5_call, LEN_slave);

            cnt_recall += 1;            
          }
          else if(time_sec_gap > 60){ //루프 예외처리
            Serial.println("1분 이상 경과하여 루프를 탈출합니다.");
            break;
          }
        }
      }
    }    
    Slave_Received(slave5_data, LEN_slave);  //함수 호출   
    */
    /*** Slave5(Irrigation) - end ***/


    /*** 데이터 수합 - start ***/
    Merge_Data();
    /*** 데이터 수합 - end ***/

  }
}
