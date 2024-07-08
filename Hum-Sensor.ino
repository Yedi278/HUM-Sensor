#define DEBUG_LIGHT_PIN 7

#include "RTC_Timer.h"
#include "Blinker.h"
#include "SD_writer.h"
#include <String.h>


// 08.07.2024.16.36.00

DS3231 rtc;
File dataFile;

char input_buff = -1;
bool h12Flag, pmFlag, centuryFlag;
unsigned int seconds, minutes, hours, day, month, year, temp;
String input_str = "";

void setup(){
  
  Wire.begin();
  Serial.begin(9600);

  pinMode(DEBUG_LIGHT_PIN, OUTPUT);
  pinMode(CHIPSELECT, OUTPUT);

  if(SD.begin(CHIPSELECT)){
    Serial.println("SD Card Correctly initialised!");
  }else{
    Serial.println("Error Reading SD Card");
    while(1) blink_f(DEBUG_LIGHT_PIN, 1);
  }

  init_SD(dataFile);

  print_File(dataFile);
}

void loop(){

  //get time variables data from rtc module
  get_Time(seconds, minutes, hours, day, month, year, rtc, h12Flag, pmFlag, centuryFlag);
  
  //if(Serial) Serial.println(String(day) +"/"+ String(month) +"/"+ String(year)+ '-' + String(hours,DEC) +":"+ String(minutes, DEC) +":"+ String(seconds, DEC) +" - "+String(temp,DEC)+"°C");

  //read written data in serial port if
  while(Serial.available()){
    input_buff = Serial.read();
    input_str += input_buff;
  }
  if(input_str.length()){
    
    if(input_str.length() != 19){
      Serial.println("Error input time, enter as DD:MM:YYYY.hh:mm:ss");
      Serial.println("Entered string -> " + input_str);
      input_str = "";
      
    }else{
      
      day = input_str.substring(0,2).toInt();
      month = input_str.substring(3,5).toInt();
      year = input_str.substring(6,10).toInt();
      hours = input_str.substring(11,13).toInt();
      minutes = input_str.substring(14,16).toInt();
      seconds = input_str.substring(17,19).toInt();

      //set rtc module time to input
      set_Time(seconds, minutes, hours, day, month, year, rtc);
      
    }
    input_str = "";
  }
  
  delay(1000);
}
