//
//  Buttons.h
//  tempC++
//
//  Created by Jin on 8/15/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __tempC____Buttons__
#define __tempC____Buttons__
#include <Arduino.h>
#include "Array.cpp"

enum state{
    low=0,
    high,
    rising,
    falling
};

class Buttons {
public:
    Buttons();
    ~Buttons();
    void addButton(unsigned char button, void (*bAction)(unsigned char,state));
    void deleteButton(unsigned char button); //Warning: do not call deleteButton in the bAction function!!!!!!!
    void switchAllButtonsOn();
    void switchAllButtonsOff();
    void switchButtonOn(unsigned char button);
    void switchButtonOff(unsigned char button);
    void begin();
private:
    struct Button{
        unsigned char button;
        bool buttonSwitch;
        unsigned char buttonValue;
        state buttonState;
        void (*buttonAction)(unsigned char button,state s);
    };
    unsigned char numberOfButtons;
    Array<Button*> buttons;
};

#endif /* defined(__tempC____Buttons__) */
