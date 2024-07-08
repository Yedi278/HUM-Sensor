#ifndef RTC_TIMER_H
#define RTC_TIMER_H

#include <DS3231.h>
#include <Wire.h>

void get_Time(unsigned int& seconds,unsigned int& minutes,unsigned int& hours,unsigned int& day,unsigned int& month,unsigned int& year, unsigned int& temp, DS3231 rtc_obj, bool& h12Flag, bool& pmFlag, bool& centuryFlag){
  
    seconds = rtc_obj.getSecond();
    minutes = rtc_obj.getMinute();
    hours    = rtc_obj.getHour(h12Flag,pmFlag);
    day     = rtc_obj.getDate();
    month   = rtc_obj.getMonth(centuryFlag);
    year    = rtc_obj.getYear();
    temp    = rtc_obj.getTemperature();
}

void set_Time(unsigned int seconds,unsigned int minutes,unsigned int hours,unsigned int day,unsigned int month,unsigned int year, DS3231 rtc){

      rtc.setSecond(seconds);
      rtc.setMinute(minutes);
      rtc.setHour(hours);
      rtc.setDate(day);
      rtc.setMonth(month);
      rtc.setYear(year);

      if(Serial) Serial.println("Time set to : " + String(day) +"/"+ String(month) +"/"+ String(year)+ '-' + String(hours) +":"+ String(minutes) +":"+ String(seconds));
}

#endif
