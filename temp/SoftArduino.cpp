//
//  SoftArduino.cpp
//  tempC++
//
//  Created by Jin on 2/15/17.
//  Copyright © 2017 Jin. All rights reserved.
//

#include "SoftArduino.hpp"

SoftArduino::SoftArduino(){
    setDefaultMode();
}

SoftArduino::~SoftArduino(){}

void SoftArduino::setDefaultMode(){
    pins.clear();
    Pin out_temp;
    for (unsigned char i = 2;i<14 ; i++) {
        pinMode(i, OUTPUT);
        out_temp = {i,OUTPUT,0};
        pins.pushBack(out_temp);
    }
    Pin temp[] = {
        {A0,INPUT,0},
        {A1,INPUT,0},
        {A2,INPUT,0},
        {A3,INPUT,0},
        {A4,INPUT,0},
        {A5,INPUT,0}
    };
    pins.pushBack(temp[0]);
    pins.pushBack(temp[1]);
    pins.pushBack(temp[2]);
    pins.pushBack(temp[3]);
    pins.pushBack(temp[4]);
    pins.pushBack(temp[5]);
    for (int i = 0,len = sizeof(temp)/sizeof(Pin); i<len;i++) {
        pinMode(temp[i].pin,temp[i].mode);
    }
}

void SoftArduino::setPinMode(unsigned char pin, unsigned char mode){
    for (int i = 0; i<pins.size(); i++)
        if (pin == pins.get(i).pin) pins.get(i).setPinMode(mode);
}

void SoftArduino::setADCPreScale(unsigned char scale){
    ADCSRA &= ~PS_128;
    switch (scale) {
        case 2:
            ADCSRA |= PS_2;
            break;
        case 4:
            ADCSRA |= PS_4;
            break;
        case 8:
            ADCSRA |= PS_8;
            break;
        case 16:
            ADCSRA |= PS_16;
            break;
        case 32:
            ADCSRA |= PS_32;
            break;
        case 64:
            ADCSRA |= PS_64;
            break;
        case 128:
            ADCSRA |= PS_128;
            break;
        default:
            break;
    }
}

void SoftArduino::printPinInfo(){
    for (int i = 0; i<pins.size(); i++) {
        switch (pins.get(i).mode) {
            case INPUT:
                Serial.print("input: ");
                Serial.println(pins.get(i).pin);
                break;
            case OUTPUT:
                Serial.print("output: ");
                Serial.println(pins.get(i).pin);
            default:
                break;
        }
    }
}

Array<String> SoftArduino::split(String str, char chr){
    int len = str.length();
    String temp;
    Array<String> res;
    for (int i = 0; i<len; i++) {
        if (str[i]!=chr){
            temp += str[i];
        }
        else{
            res.pushBack(temp);
            temp = "";
        }
    }
    res.pushBack(temp);
    return res;
}

unsigned char SoftArduino::getPinNumber(String str){
    if (str.startsWith("A"))
    {
        return A0+str[1]-'0';
    }
    unsigned temp = (unsigned char)str.toInt();
    return temp == 0 ? 13:temp;
}

void SoftArduino::_setPinMode(String command){
    Array<String> parser = split(command, ':');
    unsigned char pin = getPinNumber(parser.get(1));
    unsigned char mode = (unsigned char)parser.get(2).toInt();
    for (int i = 0; i<pins.size(); i++) {
        if (pin == pins.get(i).pin){
            pins.get(i).setPinMode(mode);
            return;
        }
    }
}

void SoftArduino::addPinMode(String command){
    Array<String> parser = split(command, ':');
    unsigned char pin = getPinNumber(parser.get(1));
    unsigned char mode = (unsigned char)parser.get(2).toInt();
    for (int i = 0; i<pins.size(); i++) {
        if (pin == pins.get(i).pin){
            setPinMode(pin, mode);
            return;
        }
    }
    Pin temp = {pin,mode,0};
    pins.pushBack(temp);
}

void SoftArduino::delPin(String command){
    Array<String> parser = split(command, ':');
    unsigned char pin = getPinNumber(parser.get(1));
    for (int i = 0; i<pins.size(); i++) {
        if (pin == pins.get(i).pin){
            pins.remove(i);
            return;
        }
    }
}

void SoftArduino::_analogRead(String command){
    Array<String> parser = split(command, ':');
    unsigned char pin = getPinNumber(parser.get(1));
    for (int i = 0; i<pins.size(); i++) {
        if (pin == pins.get(i).pin){
            pins.get(i).value = analogRead(pin);
            return;
        }
    }
}

void SoftArduino::_analogWrite(String command){
    Array<String> parser = split(command, ':');
    unsigned char pin = getPinNumber(parser.get(1));
    unsigned char value = (unsigned char)parser.get(2).toInt();
    for (int i = 0; i<pins.size(); i++) {
        if (pin == pins.get(i).pin){
            analogWrite(pin,value);
            return;
        }
    }
}

void SoftArduino::_digitalRead(String command){
    Array<String> parser = split(command, ':');
    unsigned char pin = getPinNumber(parser.get(1));
    for (int i = 0; i<pins.size(); i++) {
        if (pin == pins.get(i).pin){
            pins.get(i).value = digitalRead(pin);
            return;
        }
    }
}
void SoftArduino::_digitalWrite(String command){
    Array<String> parser = split(command, ':');
    unsigned char pin = getPinNumber(parser.get(1));
    unsigned char value = (unsigned char)parser.get(2).toInt();
    for (int i = 0; i<pins.size(); i++) {
        if (pin == pins.get(i).pin){
            digitalWrite(pin,value);
            return;
        }
    }
}

void SoftArduino::clear(){
    pins.clear();
}

unsigned char SoftArduino::readCommand(String command){
    if (command.startsWith("sp")) {
        _setPinMode(command);
    }
    else if (command.startsWith("add")){
        addPinMode(command);
    }
    else if (command.startsWith("del")){
        delPin(command);
    }
    else if (command.startsWith("ar")){
        _analogRead(command);
    }
    else if (command.startsWith("aw")){
        _analogWrite(command);
    }
    else if (command.startsWith("dr")){
        _digitalRead(command);
    }
    else if (command.startsWith("dw")){
        _digitalWrite(command);
    }
    else if (command.startsWith("print")){
        printPinInfo();
    }
    else if (command.startsWith("clear")){
        clear();
    }
    else{
        return 1; //unknow command
    }
    return 0;
}
