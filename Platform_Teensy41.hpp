/** \file Platform_Teensy41.hpp
*   \brief <a href="https://www.inmechasol.org/" target="_blank">IMS</a>:
		<a href="https://github.com/InMechaSol/ccNOos" target="_blank">ccNOos</a>,
		Platform Specification, Teensy Arduino 

    Copyright 2021 <a href="https://www.inmechasol.org/" target="_blank">InMechaSol, Inc</a>    

    Licensed under the Apache License, Version 2.0(the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

Notes:
	(.c includes .h) - for straight C or
	(.cpp includes .c which includes .h) - for C++ wrapped straight C
	*Always compiled to a single compilation unit, either C or CPP, not both

*/




#include <Arduino.h>
#include "execution_system.h"    
#include "console_menu.h" 
#define LIGHT_OFF (0u)                          // 1-PSoC4, 0-most others
#define uSEC_PER_CLOCK (1000u)

#if PLATFORM_NAME!=Arduino
error PLATFORM_NAME must be Arduino
#endif


#ifdef REDEFINE_NULLPTR
#error Must not compile with -DREDEFINE_NULLPTR on Arduino Teensy (maybe others, need to test)
#endif // !REDEFINE_NULLPTR
#ifndef __NOEXCEPTIONS
#error Must compile with -D__NOEXCEPTIONS on Arduino Teensy (maybe others, need to test)
#endif // !__NOEXCEPTIONS


int consoleCharInt = -1;


// 0) (Optional) Platform Config and Log Files/Devices
// 1) Platform Setup Function
void platformSetup()
{
    
#ifdef __USINGCONSOLEMENU
#ifdef __USINGFLOATPRINTF
    asm(".global _printf_float");
#endif
#endif
   
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
}
// 2) Platform Start Function
void platformStart()
{
    
}
// 3) Platform Loop Delay Function
void platformLoopDelay()
{
    consoleCharInt = Serial.read();
}

#ifdef __USINGCONSOLEMENU

// 8) Platform API Functions (From Template?)
PlatformAPIFuncsTemplate(size + 1);

#endif
// 9) Global Execution System Instance
//executionSystemClass PLATFORM_EXESYS_NAME(PLATFORM_NAME)(uSEC_PER_CLOCK);
// 10) ExeSys API Functions (From Template?)
ExeSysAPIFuncsTemplate