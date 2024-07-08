#ifndef BLINKER_H
#define BLINKER_H

void blink_f(int pin, int num=1, int delay_time=500){
    for(int i=0; i<num; i++){
        
        digitalWrite(pin,HIGH);
        delay(200);
        digitalWrite(pin,LOW);
        delay(200);
    }
    delay(delay_time);
}

#endif
