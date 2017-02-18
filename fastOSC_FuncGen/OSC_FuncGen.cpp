//
//  OSC_FuncGen.cpp
//  tempC++
//
//  Created by Jin on 2/15/17.
//  Copyright © 2017 Jin. All rights reserved.
//

#include "OSC_FuncGen.hpp"
#include "/Users/jin/OneDrive/C++/Arduino/utility/fastSwitch.h"
#include "/Users/jin/OneDrive/C++/Arduino/utility/Array.cpp"

OSC_FuncGen::OSC_FuncGen():SoftArduino(){
    setOSC_mode();
}

void OSC_FuncGen::setOSC_mode(){
    clear();
    Pin temp = {A0,INPUT,0};
    pins.pushBack(temp);
    setADCPreScale(64);
}
void OSC_FuncGen::setFunc_Gen_mode(){
    clear();
    Pin temp = {2,OUTPUT,0};
    pins.pushBack(temp);
    _delay = 20;
}

void OSC_FuncGen::run(){
    Pin temp;
    unsigned short a;
    for (int i = 0; i<pins.size(); i++) {
        temp = pins.get(i);
        switch (temp.mode) {
            case INPUT:
                a = analogRead(temp.pin);
                Serial.write((char*)&a,2);
                break;
            case OUTPUT:
                switch (temp.pin) {
                    case 0:
                    case 1:
                        break;
                    case 2:
                        temp.value? PIN2OFF:PIN2ON;
                        break;
                    case 3:
                        temp.value? PIN3OFF:PIN3ON;
                        break;
                    case 4:
                        temp.value? PIN4OFF:PIN4ON;
                        break;
                    case 5:
                        temp.value? PIN5OFF:PIN5ON;
                        break;
                    case 6:
                        temp.value? PIN6OFF:PIN6ON;
                        break;
                    case 7:
                        temp.value? PIN7OFF:PIN7ON;
                        break;
                    case 8:
                        temp.value? PIN8OFF:PIN8ON;
                        break;
                    case 9:
                        temp.value? PIN9OFF:PIN9ON;
                        break;
                    case 10:
                        temp.value? PIN10OFF:PIN10ON;
                        break;
                    case 11:
                        temp.value? PIN11OFF:PIN11ON;
                        break;
                    case 12:
                        temp.value? PIN12OFF:PIN12ON;
                        break;
                    case 13:
                        temp.value? PIN13OFF:PIN13ON;
                        break;
                    default:
                        break;
                }
                delayMicroseconds(_delay);
                pins.get(i).value = !temp.value;
            default:
                break;
        }
    }
}

void OSC_FuncGen::setDelay(String command){
    Array<String> parser = split(command, ':');
    int d = getPinNumber(parser.get(1));
    _delay = d? d:_delay;
}

unsigned char OSC_FuncGen::readCommand(String command){
    if (SoftArduino::readCommand(command) == 0)return 0;
    if (command == "osc") {
        setOSC_mode();
    }
    else if (command == "func"){
        setFunc_Gen_mode();
    }
    else if (command.startsWith("sd")){
        setDelay(command);
    }
    else{
        return 1;
    }
    return 0;
}
