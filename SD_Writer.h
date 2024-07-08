#ifndef SD_WRITER_H
#define SD_WRITER_H

#include <SPI.h>
#include <SD.h>

#define FILE_NAME "data.csv"
#define CHIPSELECT 8

void init_SD(File& dataFile){
  dataFile = SD.open(FILE_NAME, FILE_WRITE);
  if(dataFile){
    Serial.println("data.csv successfully found, writing headers");
    dataFile.write("DD,MM,YYYY,hh,mm,ss,temp,humidity\n");
    dataFile.close();
  }else{
    Serial.println("Err reading data.csv");
    blink_f(DEBUG_LIGHT_PIN,2);
  }
}

void print_File(File& dataFile){

  Serial.println("File Content:");
  dataFile = SD.open(FILE_NAME);
  char buff[64];
  while(dataFile.available()){
    dataFile.read(buff,64);
    Serial.print(buff);
  }
  Serial.println();
  dataFile.close();
}

void clear_File(File& dataFile){
  dataFile = SD.open(FILE_NAME, FILE_WRITE);
  
  dataFile.close();
}

#endif
