//
//  SoftArduino.hpp
//  tempC++
//
//  Created by Jin on 2/15/17.
//  Copyright © 2017 Jin. All rights reserved.
//

#ifndef SoftArduino_hpp
#define SoftArduino_hpp

#include "/Users/jin/OneDrive/C++/Arduino/utility/fastSwitch.h"
#include "/Users/jin/OneDrive/C++/Arduino/utility/Array.cpp"
#include "Arduino.h"

class SoftArduino {
public:
    SoftArduino();
    ~SoftArduino();
    
    void setDefaultMode();
    void setPinMode(unsigned char pin, unsigned char mode);
    void setADCPreScale(unsigned char scale); //2,4,8,16,32,64,128
    virtual unsigned char readCommand(String command);
    void printPinInfo();
    //command type:
    //sp:p:m (set pin:pin_num:mode),
    //add:p:m (add:pin:mode)
    //del:p (delete:p)
    //ar:p (analog read:pin)
    //aw:p:v (analog write:pin:value)
    //dr:p (digiral read:pin)
    //dw:p:v (digital write:pin:value)
    //print (print all pin info)
    //clear (clear all pins)
    
protected:
    struct Pin{
        unsigned char pin;
        unsigned char mode; //0 input, 1 output
        int value;
        void setPinMode(unsigned char m){
            mode = m;
            pinMode(pin, m);
        }
    };
    const unsigned char PS_2 = (1 << ADPS0);
    const unsigned char PS_4 = (1 << ADPS1);
    const unsigned char PS_8 = (1 << ADPS1) | (1 << ADPS0);
    const unsigned char PS_16 = (1 << ADPS2);
    const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
    const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
    const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    Array<Pin> pins;
    void _setPinMode(String command);
    void addPinMode(String command);
    void delPin(String command);
    void _analogRead(String command);
    void _analogWrite(String command);
    void _digitalRead(String command);
    void _digitalWrite(String command);
    void clear();
    unsigned char getPinNumber(String str);
    Array<String> split(String str,char chr);
};

#endif /* SoftArduino_hpp */