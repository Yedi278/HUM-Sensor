#define DEBUG_LIGHT_PIN 7

#include "Blinker.h"
#include "RTC_Timer.h"
#include "SD_writer.h"
#include "DTH_Sensor.h"
#include <String.h>


// 08.07.2024.16.36.00

DS3231 rtc;
File dataFile;

float humidity, temp_DHT;
char input_buff = -1;
bool h12Flag, pmFlag, centuryFlag;
unsigned int seconds, minutes, hours, day, month, year, temp_RTC;
String input_str = "";

void setup(){
  
  Wire.begin();
  Serial.begin(9600);

  DHT sensor(DHTPIN, DHTTYPE);

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

  humidity = sensor.readHumidity();
  temp_DHT = sensor.readTemperature();

  //get time variables data from rtc module
  get_Time(seconds, minutes, hours, day, month, year, rtc, h12Flag, pmFlag, centuryFlag);
  
  //if(Serial) Serial.println(String(day) +"/"+ String(month) +"/"+ String(year)+ '-' + String(hours,DEC) +":"+ String(minutes, DEC) +":"+ String(seconds, DEC) +" - "+String(temp,DEC)+"°C");

  //read input from serial port
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
  
  Serial.print(String(day) +"/"+ String(month) +"/"+ String(year)+ '-' + String(hours,DEC) +":"+ String(minutes, DEC) +":"+ String(seconds, DEC) +" - "+String(temp_RTC,DEC)+"°C ");
  Serial.println(String(humidity) + "% " + String(temp_DHT) + "°C");
  
  delay(1000);
}
