//
//  OSC_FuncGen.hpp
//  tempC++
//
//  Created by Jin on 2/15/17.
//  Copyright © 2017 Jin. All rights reserved.
//

#ifndef OSC_FuncGen_hpp
#define OSC_FuncGen_hpp
#include "/Users/jin/OneDrive/C++/Arduino/utility/SoftArduino.hpp"
#include "Arduino.h"

class OSC_FuncGen:public SoftArduino {
public:
    OSC_FuncGen();
    ~OSC_FuncGen(){};
    
    void setOSC_mode();
    void setFunc_Gen_mode();
    
    virtual unsigned char readCommand(String command);
    //command:
    //osc (set osc mode)
    //func (set function generator mode)
    //sd:value (set delay:value)
    
    void run();
private:
    int _delay;
    void setDelay(String str);
};

#endif /* OSC_FuncGen_hpp */
