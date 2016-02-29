//
//  Buttons.cpp
//  tempC++
//
//  Created by Jin on 8/15/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include "Buttons.h"

Buttons::Buttons(){
    numberOfButtons = 0;
}

Buttons::~Buttons(){
    Button* temp;
    for (unsigned long i = 0,len = buttons.size();i<len ; i++) {
        temp = buttons.removeLast();
        delete temp;
    }
}


void Buttons::addButton(unsigned char button, void (*bAction)(unsigned char,state)){
    Button* temp = new Button;
    temp->button = button;
    temp->buttonState = low;
    temp->buttonSwitch = true;
    temp->buttonValue = 0;
    temp->buttonAction = bAction;

    pinMode(button,INPUT);
    buttons.insert(temp);
}

void Buttons::deleteButton(unsigned char button){
    Button* temp;
    for (unsigned long i,len = buttons.size(); i<len; i++) {
        temp = buttons.get(i);
        if (temp->button == button) {
            temp = buttons.remove(i);
            delete temp;
        }
    }
}

#define switchAllButton(s){ Button* temp; \
for (unsigned long i,len = buttons.size(); i<len; i++) { \
    temp = buttons.get(i); \
    temp->buttonSwitch = s; \
}}

void Buttons::switchAllButtonsOn(){
    switchAllButton(true);
}

void Buttons::switchAllButtonsOff(){
    switchAllButton(false);
}

#define switchButton(s) { Button* temp; \
for (unsigned long i,len = buttons.size(); i<len; i++){ \
    temp = buttons.get(i); \
    if (temp->button == button) { \
        temp->buttonSwitch = s; \
    } \
}}

void Buttons::switchButtonOn(unsigned char button){
    switchButton(true);
}

void Buttons::switchButtonOff(unsigned char button){
    switchButton(false);
}

void Buttons::begin(){
    Button* temp;
    unsigned char value;
    state s;
    for (unsigned long i = 0,len = buttons.size(); i<len; i++) {
        temp = buttons.get(i);
        if (temp->buttonSwitch) {
            value = digitalRead(temp->button);
            if (value!=temp->buttonValue) {
                s = value? rising:falling;
            }
            else{
                s = value? high:low;
            }
            temp->buttonValue = value;
            temp->buttonState = s;
            temp->buttonAction(temp->button,s);
        }
    }
}
