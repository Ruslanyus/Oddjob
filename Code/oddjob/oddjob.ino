// oddjob (C)2013 Ludovic Godreau
// web: http://www.godreau.fr
//
// This program is a test for new photoduino interface
// This program requires UTFT_tinyFAT, UTFT v1.2 or higher, 
// as well as the tinyFAT v3.0 or higher.
//
// The image files must be present in the root folder 
// of a FAT16 formatted SDcard in the module cardslot.
//

#include <tinyFAT.h>
#include <UTFT.h>
#include <UTFT_tinyFAT.h>
#include <UTouch.h>
#include "oddjob.h"
#include <EEPROM.h>
#include <Wire.h> //IIC
#include <math.h> //IIC
 
// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];



// Global variables
int          BH1750address = 0x23;      //luxmeter
byte         buff[2];                   //lux

// System config in ram
boolean      system_useSpeaker;
unsigned int system_flashPulsing;


// Interval mode config in ram
unsigned int intervalMode_autofocusTime;
unsigned int intervalMode_shutterLagTime;
boolean      intervalMode_useFlash1;
unsigned int intervalMode_preFlash1Time;
boolean      intervalMode_useFlash2;
unsigned int intervalMode_preFlash2Time;
unsigned int intervalMode_preCloseTime;
byte         intervalMode_intervalUnits;
unsigned int intervalMode_intervalValue;
unsigned int intervalMode_numCicles;

// Audio trigger mode config in ram
unsigned int audioTriggerMode_sensorLimit;
byte         audioTriggerMode_shootingMode;
unsigned int audioTriggerMode_autofocusTime;
unsigned int audioTriggerMode_shutterLagTime;
unsigned int audioTriggerMode_preCloseTime;
boolean      audioTriggerMode_useFlash1;
unsigned int audioTriggerMode_preFlash1Time;
boolean      audioTriggerMode_useFlash2;
unsigned int audioTriggerMode_preFlash2Time;
unsigned int audioTriggerMode_numCicles;
unsigned int audioTriggerMode_interCicleTime;

// Shock trigger mode config in ram
unsigned int shockTriggerMode_sensorLimit;
byte         shockTriggerMode_shootingMode;
unsigned int shockTriggerMode_autofocusTime;
unsigned int shockTriggerMode_shutterLagTime;
unsigned int shockTriggerMode_preCloseTime;
boolean      shockTriggerMode_useFlash1;
unsigned int shockTriggerMode_preFlash1Time;
boolean      shockTriggerMode_useFlash2;
unsigned int shockTriggerMode_preFlash2Time;
unsigned int shockTriggerMode_numCicles;
unsigned int shockTriggerMode_interCicleTime;

// Barrier mode config in ram
unsigned int barrierMode_sensorLimit;
byte         barrierMode_shootingMode;
unsigned int barrierMode_autofocusTime;
unsigned int barrierMode_shutterLagTime;
unsigned int barrierMode_preCloseTime;
boolean      barrierMode_useFlash1;
unsigned int barrierMode_preFlash1Time;
boolean      barrierMode_useFlash2;
unsigned int barrierMode_preFlash2Time;
unsigned int barrierMode_numCicles;
unsigned int barrierMode_interCicleTime;

// Flash slave config in ram
unsigned int flashSlave_sensorLimit;
boolean      flashSlave_useFlash1;
unsigned int flashSlave_preFlash1Time;
boolean      flashSlave_useFlash2;
unsigned int flashSlave_preFlash2Time;

byte         flashSlave_shootingMode;
unsigned int flashSlave_autofocusTime;
unsigned int flashSlave_shutterLagTime;
unsigned int flashSlave_preCloseTime;

// astro  mode config in ram
unsigned int astroMode_preCloseTime;
byte         astroMode_intervalUnits;
unsigned int astroMode_intervalValue;
unsigned int astroMode_pauseValue;
unsigned int astroMode_numCicles;

// Barrier2 mode config in ram
unsigned int barrier2Mode_sensor1Limit;
unsigned int barrier2Mode_sensor2Limit;
unsigned int barrier2Mode_distance;

// water mode config in ram
unsigned int dropMode_dropCount;
unsigned int dropMode_dropDuration;
unsigned int dropMode_dropInterval;
unsigned int dropMode_drop2Duration;
unsigned int dropMode_dropShooting;
unsigned int dropMode_dropPause;

//unsigned int system_useSpeaker=0;
//unsigned int system_flashPulsing=10;
unsigned int system_autofocusTime=43;
unsigned int system_shutterLagTime=0;


// Variables used on interrupt mode
volatile boolean cancelFlag = false;    // Flag used to abort interrupt mode



UTFTtf   myGLCD(ITDB32S, 38, 39, 40, 41);   // Remember to change the model parameter to suit your display module!
UTouch   myTouch(6,5,4,3,2);

int picsize_x, picsize_y;

word res;



int debug=1;
void setup()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
  file.initFAT(SPISPEED_VERYHIGH);
  myGLCD.setColor(255,255,255);
  myGLCD.setFont(SmallFont);
  picsize_x=myGLCD.getDisplayXSize();
  picsize_y=myGLCD.getDisplayYSize();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

// Initialize serial communication 
  Serial.begin(115200);
  Serial.println();

  // Pinmode inputs
  pinMode(PINS_SENSOR_SHOCK, INPUT); 
  pinMode(PINS_SENSOR_BARRIER1, INPUT);
  pinMode(PINS_SENSOR_BARRIER2, INPUT);
  pinMode(PINS_SENSOR_MIC, INPUT);
  
  // Pinmode outputs
  pinMode(PINS_SHUTTER, OUTPUT);
  pinMode(PINS_AUTOFOCUS, OUTPUT);
  pinMode(PINS_FLASH1, OUTPUT);
  pinMode(PINS_FLASH2, OUTPUT);
  pinMode(PINS_LASER1, OUTPUT);
  pinMode(PINS_LASER2, OUTPUT);
  
  pinMode(PINS_BUZZER, OUTPUT);
  //pinMode(PINS_RESERVED, OUTPUT);
  
  Wire.begin();  //IIC

  
 // Initialize config
  config_init(); 
}

void loop()
{
  
  res=main_menu();
  switch (res)
  {
    case 0:
    menu_conf_system();
    config_saveBackup_system();
    break;
    case 1:
    menu_astro();
    break;
    case 2:
    menu_barrier();
    break;
    case 3: //flash slave
    menu_slave();
    break;
    case 4:
      menu_interval();
    break;
    case 5: //shock
     menu_shock();
    break;
    case 6: //audio
      menu_audio();
    break;
    case 7: //speed
      menu_2barrier();
    break;
     case 8: //water
      menu_water();
    break;
    case 9: //clean
    clean_mode();
    break;
    case 10: //lux meter
    lux_mode();
    break;

    case 11: //help
    help_menuP1();
    break;
  }
 
}

