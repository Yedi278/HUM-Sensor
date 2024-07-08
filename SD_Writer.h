#ifndef SD_WRITER_H
#define SD_WRITER_H

#include <SPI.h>
#include <SD.h>
#include <String.h>

#define FILE_NAME "data.csv"
#define CHIPSELECT 8

void init_SD(File& dataFile){
  if(SD.exists(FILE_NAME)){
    
    Serial.println("File found!, writing data...");
    
  }else{
    
    dataFile = SD.open(FILE_NAME, FILE_WRITE);
    if(dataFile){
      Serial.println("Writing Headers...");
      dataFile.write("DD,MM,YYYY,hh,mm,ss,humidity,tempDHT,tempRTC\n");
      dataFile.close();
    }else{
      Serial.println("Err creating data.csv file!");
      blink_f(DEBUG_LIGHT_PIN,2);
    }
  }
}

void clear_buff(char* buff, int size_buff){
  for(int i=0; i<size_buff; i++){
    buff[i] = -1;
  }
}

void print_File(File& dataFile){

  Serial.println("File Content:");
  dataFile = SD.open(FILE_NAME);
  char buff[16];
  int a = dataFile.available();
  
  while(a){
    
    clear_buff(buff,16);
    
    if(a < 16){
    
      dataFile.read(buff,16);
      Serial.print(buff);
    
    }else{
      
      dataFile.read(buff, a);
      for(int i=0; i<a; i++){
        Serial.print(buff[i]);
      }
    }
    a = dataFile.available();  
  }
  Serial.println();
  dataFile.close();
}

void write_File(File& dataFile, unsigned int& day, unsigned int& month, unsigned int& year, unsigned int& seconds, unsigned int& minutes, unsigned int& hours, float hum, float temp_DHT, unsigned int& temp_RTC){
  dataFile = SD.open(FILE_NAME, FILE_WRITE);
  //dataFile.write(day);
  dataFile.print(String(day) + "," + String(month) + "," + String(year) + "," + String(hours) + "," + String(minutes) + "," + String(seconds) + "," + String(hum) + "," + String(temp_DHT) + "," + String(temp_RTC) + "\n");
  dataFile.close();
}

#endif
