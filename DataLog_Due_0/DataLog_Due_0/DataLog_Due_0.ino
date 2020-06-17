#include <SPI.h>
#include <SD.h>
#include <Wire.h>
//#include "RTClib.h"

//#define SERIAL_BUFFER_SIZE 1024
#define STATE_ERROR_LED 37
#define ld1 43
#define ld2 39
#define ld3 41

//RTC_PCF8523 rtc;

//struct datastore {
// char message;
//};

File SerLog1, SerLog2, SerLog3;

//struct datastore myData;

Sd2Card card;
SdVolume volume;
SdFile root;

char c;
int a=0;
const int chipSelect = 10;
String data1,data2,data3;
//char data1[128],data2[128],date3[128];

//  void Init_RTC(){
//   while (!rtc.begin()){
//    Serial.println("Couldn't find RTC");
//    digitalWrite(STATE_ERROR_LED, HIGH);
//    delay(1000); 
//    digitalWrite(STATE_ERROR_LED, LOW);  
//   }
//   if (! rtc.initialized()) { // To Set Time And Date On RTC
//      Serial.println("RTC is NOT running!"); 
//      // following line sets the RTC to the date & time this sketch was compiled
//      // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//      // This line sets the RTC with an explicit date & time, for example to set
//      // January 21, 2014 at 3am you would call:
//      // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
//    }
//   Serial.println("RTC_OK!");
//   digitalWrite(STATE_ERROR_LED, LOW);
//  }
  
void Init_Card(){
  SD.begin();
  Serial.println(F("Inizializza SD"));
  while (!card.init(SPI_HALF_SPEED, chipSelect)){
    digitalWrite(STATE_ERROR_LED, HIGH);
    Serial.println(F("SD init failed"));
  }
 digitalWrite(STATE_ERROR_LED, LOW);
 Serial.println(F("SDcard Ok!"));
 Serial.println(F(SERIAL_BUFFER_SIZE));
}

void Serial1Process(){
// char c;
 if(Serial1.available()){
  digitalWrite(ld1,HIGH);
  SerLog1 = SD.open("datalog1.txt",FILE_WRITE);
  data1="";
  do {
   if(Serial1.available()){
    c = Serial1.read();
    data1 += c;
   }
  } while(c != '\n');
 SerLog1.print(data1);
 Serial.print(F("1: "));
 Serial.print(data1);
 Serial1.flush();
 } 
digitalWrite(ld1,LOW);
SerLog1.close(); 
}

void Serial2Process(){
// char h;
 if(Serial2.available()){
  digitalWrite(ld2,HIGH);
  SerLog2 = SD.open("datalog2.txt",FILE_WRITE);
  data2="";
  do {
   if(Serial2.available()) {
      digitalWrite(ld2,HIGH);
    c = Serial2.read();
    data2 += c;
    }
  } while(c != '\n');
 SerLog2.print(data2);
 Serial.print(F("2:"));
 Serial.print(data2);
 Serial2.flush();
 } 
 digitalWrite(ld2,LOW);
 SerLog2.close(); 

}

void Serial3Process(){
// char k;
 if(Serial3.available()){
  digitalWrite(ld3,HIGH);
  SerLog3 = SD.open("datalog3.txt",FILE_WRITE);
  data3="";
  do {
   if(Serial3.available()) {
    c = Serial3.read();
    data3 += c;
   }
  } while(c != '\n');
 SerLog3.print(data3);
 Serial.print(F("3:"));
 Serial.print(data3);
 Serial3.flush();
 } 
 digitalWrite(ld3,LOW);
 SerLog3.close(); 
}

void setup(){
 pinMode(STATE_ERROR_LED, OUTPUT);
 pinMode(ld1, OUTPUT);
 pinMode(ld2, OUTPUT);
 pinMode(ld3, OUTPUT);
 pinMode(15, INPUT);
 pinMode(17, INPUT);
 pinMode(19, INPUT);
 digitalWrite(ld1,LOW);
 digitalWrite(ld2,LOW);
 digitalWrite(ld3,LOW);
 digitalWrite(STATE_ERROR_LED, LOW); 
 Serial.begin(115200);
 Serial1.begin(115200);
 Serial2.begin(115200);
 Serial3.begin(115200);
// Init_RTC();
 Init_Card(); 
// CLOCK.begin();
delay(10000);
}

void loop(){
  
 Serial1Process();
 Serial2Process();
// Serial3Process();
 Serial.flush();
}
