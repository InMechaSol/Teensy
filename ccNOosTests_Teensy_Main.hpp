//////////////////////////////////
// Include Application and cNOos
#include "Application_Serialization.h"

////////////////////////////////
// Compile Error if Examples/Tests not defining 
#ifndef Mn
#error Mn must be defined - see examples
#endif
#ifndef MODdeclareCREATEINS
#error MODdeclareCREATEINS must be defined - see examples
#endif
#ifndef MODcallCREATEINS
#error MODcallCREATEINS must be defined - see examples
#endif
#ifdef __cplusplus
#ifndef PLATFORM_APP_CLASS
#error PLATFORM_APP_CLASS macro must be defined in application code
#endif
#else
#ifndef MODdeclareDATA
#error MODdeclareDATA macro must be defined in application code
#endif
#endif

////////////////////////////////
// Compile Error if Examples/Tests not defining
#if PLATFORM_NAME==Arduino
#include "Platform_Teensy41.hpp"
#else
#error "No Platform Selected for Compile!"
#endif

///////////////////////////////////////////////////////////////////////
// Module Data Structure or Module Data Class 
//   -Declared from Macro Template
//   -Macro Template is Defined in the Application Solution Header
///////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
PLATFORM_APP_CLASS(Mn);
#else
MODdeclareDATA(Mn);
#endif

struct devicedatastruct PacketsInterfactDevDataStruct = createDeviceStruct();
struct devicedatastruct ConsoleMenuDevDataStruct = createDeviceStruct();

///////////////////////////////////////////////////////////////////////
// Platform and Application Specific IO Device Functions
void linkAPIioDevices(struct ccNOosTestsStruct* ccNOosTestsStructPtrIn)
{
    ConsoleMenuDevDataStruct.numbytes2Read = 1;
    ConsoleMenuDevDataStruct.triggerWriteOperation = ui8TRUE;
    ccNOosTestsStructPtrIn->ConsoleMenu.devptr = &ConsoleMenuDevDataStruct;
    ccNOosTestsStructPtrIn->PacketsAPI.devptr = &PacketsInterfactDevDataStruct;
    ccNOosTestsStructPtrIn->ConsoleMenu.showHelp = ui8TRUE;
}
UI_32 getMillis() {
    return millis();
}

// 4) Basic ability for user console input via any io device
void GetMenuChars(struct uiStruct* uiStructPtrin)
{
    // if Consolue Menu
    if (uiStructPtrin->devptr == &ConsoleMenuDevDataStruct)
    {
        if (consoleCharInt > -1)
        {
            if (uiStructPtrin->readIndex > 0 || (char)consoleCharInt != '\n')
            {
                uiStructPtrin->devptr->inbuff.charbuff[uiStructPtrin->readIndex] = (char)consoleCharInt;
                if (uiStructPtrin->devptr->inbuff.charbuff[uiStructPtrin->readIndex] == ';')
                {
                    uiStructPtrin->devptr->inbuff.charbuff[uiStructPtrin->readIndex + 1] = 0x00;
                    uiStructPtrin->devptr->newDataReadIn = ui8TRUE;
                    uiStructPtrin->parseIndex = 0;
                    uiStructPtrin->readIndex = 0;
                    return;
                }
                if (++uiStructPtrin->readIndex >= charBuffMax)
                    uiStructPtrin->readIndex = 0;
            }

        }
    }
}
// 5) Basic ability for user console output
void WriteMenuLine(struct uiStruct* uiStructPtrin)
{
    // if Consolue Menu
    if (uiStructPtrin->devptr == &ConsoleMenuDevDataStruct)
    {
        if (uiStructPtrin->clearScreen) {
            Serial.print(terminalClearString());
            uiStructPtrin->clearScreen = ui8FALSE;
        }
        Serial.print(&uiStructPtrin->devptr->outbuff.charbuff[0]);
        if (uiStructPtrin->showPrompt) {
            Serial.print(terminalPromptString(uiStructPtrin->currentUserLevel));
            uiStructPtrin->showPrompt = ui8FALSE;
        }
    }

}
// 6) (Optional) Logging Output
void WriteLogLine(struct logStruct* logStructPtrin)
{
    ;
}
// 7) (Optional) Config Input
void ReadConfigLine(struct configStruct* configStructPtrin)
{
    ;
}



///////////////////////////////////////////////////////////////////////
// Application Data Instances are Created here (Platform Specific)
ccNOosTestsVersionsTemplate
#ifdef __cplusplus
theApplicationClass theApplicationExample;
#else
PLATFORM_APP_CTEMPLATE(Mn)
#endif

////////////////////////////////////////////////////////////////////////////////
// Platform Main Entry Points call ExeSys Area Functions
#ifdef MAIN_C_NOos_Wsystick
C_NOos_MAINnSYSTICK_TEMPLATE
#endif
#ifdef MAIN_C_NOos_NOsystick
C_OS_MAIN_TEMPLATE
#endif
