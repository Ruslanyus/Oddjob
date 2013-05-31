/* ------------------------------------------------------------------------------------------- *
 *                                                                                             *
 *                                      CONFIGURATION VALUES:                                  *
 *                             You can set the next configuration values                       *
 *                              before compile and upload this sketch                          * 
 *                                                                                             *
 * ------------------------------------------------------------------------------------------- */

                

//
// Default Shutterlag:
// - The default value for shutterlag to load when you reset configs
// 
// Valid values:
// - Number between 0 and 59999 in miliseconds
// - Check your camera model at: http://code.google.com/p/photoduino/wiki/CameraReference
//
#define DEFAULT_SHUTTERLAG               100 

// 
// Default intercicle time:
// - The default value in miliseconds camera needs to process photo and be ready for the next
// 
// Valid values:
// - Number between 0 and 59999 in miliseconds
//
#define DEFAULT_INTERCICLE_TIME          200  

// 
// Pulse width for shooting flashes:
// - Time in microseconds of the pulse to shoot the flashes.
// - Increase this value if you have problems with your flash model (very rare).
// 
// Valid values:
// - Number between 0 and 59999 in microseconds
// 
#define DEVICES_FLASHES_SHOOTING_PULSE     1 

// 
// Camera mirror lock-up time limit:
// - When use the mirror lock-up shooting mode, all cameras has a limit time (about 30 seconds) to 
//   make the photo while the mirror is locked up. After that time, the mirror is automaticaly unlocked
//   by the camera without taking photo. The next value is this time in miliseconds to say to photoduino 
//   when to re-lock-up the mirror if no photo has taken.
// 
// Valid values:
// - Number between 0 and 59999 in miliseconds
//
#define DEVICES_CAMERA_MIRROR_LOCKUP_TIMELIMIT         31000



//
// Arduino board type:
// - Make the firmware compatible with different boards
// 
// Valid values: 
// - BOARD_ARDUINO_DUEMILANOVE (With Atmega328)
// - BOARD_ARDUINO_MEGA
//



// Import libraries 
#include <avr/pgmspace.h>  // For messages in flash memory
#include <EEPROM.h>

// Signature and version codes 
#define SIGNATURE_CODE1             0x10 // day 
#define SIGNATURE_CODE2             0x03 // month
#define SIGNATURE_CODE3             0x20 // century
#define SIGNATURE_CODE4             0x13 // year of century
#define CODE_MAYOR_VERSION          0x1 // mayor version
#define CODE_MINOR_VERSION          0x13 // minor version

// Default system config
#define DEFAULT_system_useSpeaker                     true
#define DEFAULT_system_flashPulsing                   DEVICES_FLASHES_SHOOTING_PULSE

// Default interval mode config
#define DEFAULT_intervalMode_autofocusTime            0
#define DEFAULT_intervalMode_shutterLagTime           DEFAULT_SHUTTERLAG
#define DEFAULT_intervalMode_useFlash1                false
#define DEFAULT_intervalMode_preFlash1Time            0
#define DEFAULT_intervalMode_useFlash2                false
#define DEFAULT_intervalMode_preFlash2Time            0
#define DEFAULT_intervalMode_preCloseTime             0
#define DEFAULT_intervalMode_intervalUnits            UNITS_SECS
#define DEFAULT_intervalMode_intervalValue            1
#define DEFAULT_intervalMode_numCicles                0

// Audio trigger mode default config
#define DEFAULT_audioTriggerMode_sensorLimit          51
#define DEFAULT_audioTriggerMode_shootingMode         SHOOTINGMODE_NORMAL
#define DEFAULT_audioTriggerMode_autofocusTime        0
#define DEFAULT_audioTriggerMode_shutterLagTime       DEFAULT_SHUTTERLAG
#define DEFAULT_audioTriggerMode_preCloseTime         0
#define DEFAULT_audioTriggerMode_useFlash1            false
#define DEFAULT_audioTriggerMode_preFlash1Time        0
#define DEFAULT_audioTriggerMode_useFlash2            false
#define DEFAULT_audioTriggerMode_preFlash2Time        0
#define DEFAULT_audioTriggerMode_numCicles            0
#define DEFAULT_audioTriggerMode_interCicleTime       DEFAULT_INTERCICLE_TIME

// Shock trigger mode default config
#define DEFAULT_shockTriggerMode_sensorLimit          51
#define DEFAULT_shockTriggerMode_shootingMode         SHOOTINGMODE_NORMAL
#define DEFAULT_shockTriggerMode_autofocusTime        0
#define DEFAULT_shockTriggerMode_shutterLagTime       DEFAULT_SHUTTERLAG
#define DEFAULT_shockTriggerMode_preCloseTime         0
#define DEFAULT_shockTriggerMode_useFlash1            false
#define DEFAULT_shockTriggerMode_preFlash1Time        0
#define DEFAULT_shockTriggerMode_useFlash2            false
#define DEFAULT_shockTriggerMode_preFlash2Time        0
#define DEFAULT_shockTriggerMode_numCicles            0
#define DEFAULT_shockTriggerMode_interCicleTime       DEFAULT_INTERCICLE_TIME

// Barrier mode default config
#define DEFAULT_barrierMode_sensorLimit               51
#define DEFAULT_barrierMode_shootingMode              SHOOTINGMODE_NORMAL
#define DEFAULT_barrierMode_autofocusTime             0
#define DEFAULT_barrierMode_shutterLagTime            DEFAULT_SHUTTERLAG
#define DEFAULT_barrierMode_preCloseTime              0
#define DEFAULT_barrierMode_useFlash1                 false
#define DEFAULT_barrierMode_preFlash1Time             0
#define DEFAULT_barrierMode_useFlash2                 false
#define DEFAULT_barrierMode_preFlash2Time             0
#define DEFAULT_barrierMode_numCicles                 0
#define DEFAULT_barrierMode_interCicleTime            DEFAULT_INTERCICLE_TIME

// Flash slave default config
#define DEFAULT_flashSlave_sensorLimit                51
#define DEFAULT_flashSlave_useFlash1                  true
#define DEFAULT_flashSlave_preFlash1Time              0
#define DEFAULT_flashSlave_useFlash2                  true
#define DEFAULT_flashSlave_preFlash2Time              0

// Default astro mode config
#define DEFAULT_astroMode_preCloseTime             0
#define DEFAULT_astroMode_intervalUnits            UNITS_SECS
#define DEFAULT_astroMode_intervalValue            1
#define DEFAULT_astroMode_pauseValue               1
#define DEFAULT_astroMode_numCicles                0


// Barrier2 mode default config
#define DEFAULT_barrier2Mode_sensor1Limit          51
#define DEFAULT_barrier2Mode_sensor2Limit          51
#define DEFAULT_barrier2Mode_distance              10

// Drop mode default config
#define DEFAULT_dropMode_dropCount                 0
#define DEFAULT_dropMode_dropDuration              100
#define DEFAULT_dropMode_dropInterval              500
#define DEFAULT_dropMode_drop2Duration             0
#define DEFAULT_dropMode_dropShooting              100
#define DEFAULT_dropMode_dropPause                 500

// Pinout settings
#define PINS_BUZZER          13  //(pwm6 pin)
#define PINS_SHUTTER         11  //(digital pin)
#define PINS_AUTOFOCUS       12  //(digital pin)
#define PINS_LASER1          8  //(digital pin)
#define PINS_LASER2          7  //(digital pin)

#define PINS_FLASH1          10 //10 56 = Mega 16 = Duemilanova //(digital pin)
#define PINS_FLASH2          9  //9 55 = Mega 15 = Duemilanova //(digital pin)
//#define PINS_RESERVED        54 // 54 = Mega 14 = Duemilanova //(digital pin)


#define PINS_LASER           PINS_RESERVED  // alias(digital pin)
#define PINS_SENSOR_SHOCK    61  //(analog pin)
#define PINS_SENSOR_BARRIER1 60  //(analog pin)
#define PINS_SENSOR_BARRIER2 59  //(analog pin)
#define PINS_SENSOR_MIC      58  //(analog pin)

// Measure units

#define UNITS_MS             0  // miliseconds
#define UNITS_SECS           1  // seconds
#define UNITS_MINS           2  // minutes
#define UNITS_HOURS          3  // hours
#define UNITS_DAYS           4  // days
#define UNITS_CICLES         10 // cicles
#define UNITS_US             11 // microseconds

// Sensor limit modes
#define SENSOR_MODE_LOWER    0 // for trigg by lower values
#define SENSOR_MODE_HIGHER   1 // for trigg by higher values


// Shooting modes
#define SHOOTINGMODE_NORMAL           0 // Normal mode 
#define SHOOTINGMODE_PREBULB          1 // Prebulb mode
#define SHOOTINGMODE_MIRRORLOCKUP     2 // Mirror lookup mode


// EEPROM size in bytes
#define EEPROM_SIZE         512

// EEPROM Addreses for signature code and version of firmware
#define EE_ADDR_SIGNATURE_CODE1                     0x00 // BYTE
#define EE_ADDR_SIGNATURE_CODE2                     0x01 // BYTE
#define EE_ADDR_SIGNATURE_CODE3                     0x02 // BYTE
#define EE_ADDR_SIGNATURE_CODE4                     0x03 // BYTE
#define EE_ADDR_CODE_MAYOR_VERSION                  0x04 // BYTE
#define EE_ADDR_CODE_MINOR_VERSION                  0x06 // BYTE

// EEPROM Addreses for system config
//#define EE_ADDR_system_useBacklight                 0x10 // BYTE
#define EE_ADDR_system_useSpeaker                   0x12 // BYTE
//#define EE_ADDR_system_interfaceSensorLimit         0x14 // BYTE
#define EE_ADDR_system_flashPulsing                 0x16 // BYTE

// EEPROM Addreses for interval mode config
#define EE_ADDR_intervalMode_autofocusTime          0x20 // WORD
#define EE_ADDR_intervalMode_shutterLagTime         0x22 // WORD
#define EE_ADDR_intervalMode_useFlash1              0x24 // BYTE
#define EE_ADDR_intervalMode_preFlash1Time          0x26 // WORD
#define EE_ADDR_intervalMode_useFlash2              0x28 // BYTE
#define EE_ADDR_intervalMode_preFlash2Time          0x2A // WORD
#define EE_ADDR_intervalMode_preCloseTime           0x2C // WORD
#define EE_ADDR_intervalMode_intervalUnits          0x2E // BYTE
#define EE_ADDR_intervalMode_intervalValue          0x30 // WORD
#define EE_ADDR_intervalMode_numCicles              0x32 // WORD

// EEPROM Addreses for audio trigger mode config
#define EE_ADDR_audioTriggerMode_sensorLimit        0x40 // WORD
#define EE_ADDR_audioTriggerMode_shootingMode       0x42 // BYTE
#define EE_ADDR_audioTriggerMode_autofocusTime      0x44 // WORD
#define EE_ADDR_audioTriggerMode_shutterLagTime     0x46 // WORD
#define EE_ADDR_audioTriggerMode_preCloseTime       0x48 // WORD
#define EE_ADDR_audioTriggerMode_useFlash1          0x4A // BYTE
#define EE_ADDR_audioTriggerMode_preFlash1Time      0x4C // WORD
#define EE_ADDR_audioTriggerMode_useFlash2          0x4E // BYTE
#define EE_ADDR_audioTriggerMode_preFlash2Time      0x50 // WORD
#define EE_ADDR_audioTriggerMode_numCicles          0x52 // WORD
#define EE_ADDR_audioTriggerMode_interCicleTime     0x54 // WORD

// EEPROM Addreses for shock trigger mode config
#define EE_ADDR_shockTriggerMode_sensorLimit        0x60 // WORD
#define EE_ADDR_shockTriggerMode_shootingMode       0x62 // BYTE
#define EE_ADDR_shockTriggerMode_autofocusTime      0x64 // WORD
#define EE_ADDR_shockTriggerMode_shutterLagTime     0x66 // WORD
#define EE_ADDR_shockTriggerMode_preCloseTime       0x68 // WORD
#define EE_ADDR_shockTriggerMode_useFlash1          0x6A // BYTE
#define EE_ADDR_shockTriggerMode_preFlash1Time      0x6C // WORD
#define EE_ADDR_shockTriggerMode_useFlash2          0x6E // BYTE
#define EE_ADDR_shockTriggerMode_preFlash2Time      0x70 // WORD
#define EE_ADDR_shockTriggerMode_numCicles          0x72 // WORD
#define EE_ADDR_shockTriggerMode_interCicleTime     0x74 // WORD

// EEPROM Addreses for barrier mode config
#define EE_ADDR_barrierMode_sensorLimit             0x80 // WORD
#define EE_ADDR_barrierMode_shootingMode            0x82 // BYTE
#define EE_ADDR_barrierMode_autofocusTime           0x84 // WORD
#define EE_ADDR_barrierMode_shutterLagTime          0x86 // WORD
#define EE_ADDR_barrierMode_preCloseTime            0x88 // WORD
#define EE_ADDR_barrierMode_useFlash1               0x8A // BYTE
#define EE_ADDR_barrierMode_preFlash1Time           0x8C // WORD
#define EE_ADDR_barrierMode_useFlash2               0x8E // BYTE
#define EE_ADDR_barrierMode_preFlash2Time           0x90 // WORD
#define EE_ADDR_barrierMode_numCicles               0x92 // WORD
#define EE_ADDR_barrierMode_interCicleTime          0x94 // WORD

// EEPROM Addreses for flash slave config
#define EE_ADDR_flashSlave_sensorLimit              0xA0 // WORD
#define EE_ADDR_flashSlave_useFlash1                0xA2 // BYTE
#define EE_ADDR_flashSlave_preFlash1Time            0xA4 // WORD
#define EE_ADDR_flashSlave_useFlash2                0xA6 // BYTE
#define EE_ADDR_flashSlave_preFlash2Time            0xA8 // WORD


// EEPROM Addreses for astro mode config
#define EE_ADDR_astroMode_preCloseTime              0xAA // WORD
#define EE_ADDR_astroMode_intervalUnits             0xAC // BYTE
#define EE_ADDR_astroMode_intervalValue             0xAE // WORD
#define EE_ADDR_astroMode_pauseValue                0xB0 // WORD
#define EE_ADDR_astroMode_numCicles                 0xB2 // WORD

// EEPROM Addreses for barrier2 mode config
#define EE_ADDR_barrier2Mode_sensor1Limit           0xB4 // WORD
#define EE_ADDR_barrier2Mode_sensor2Limit           0xB6 // WORD
#define EE_ADDR_barrier2Mode_distance               0xB8 // WORD
 
// EEPROM Addreses for water mode config
#define EE_ADDR_dropMode_dropCount                  0xBA // WORD
#define EE_ADDR_dropMode_dropDuration               0xBC // WORD
#define EE_ADDR_dropMode_dropInterval               0xBE // WORD
#define EE_ADDR_dropMode_drop2Duration              0xC0 // WORD
#define EE_ADDR_dropMode_dropPause                  0xC2 // WORD
#define EE_ADDR_dropMode_dropShooting               0xC4 // WORD

#define MSG_RUN_AUDIO                 "Run audio"
#define MSG_RUN_INTERVAL              "Run interval"
#define MSG_RUN_BARRIER               "Run barrier"
#define MSG_RUN_SHOCK                 "Run shock"
#define MSG_RUN_FLASH_SLAVE           "Run flashslave"
#define MSG_RUN_ASTRO                 "Run astro"

struct icon {
  String icon_file;  // icon file
  int pos_x;         // x pos of the icon (top left)
  int pos_y;         // y pos of the icon (top left)
  int picsize_x;     // x size of the icon
  int picsize_y;     // y size of the icon
  String text;       // If you want text intead of icon if text is set, icon is not used.
};

struct list_data {
  String description;
  unsigned int value;
  String unit;
  unsigned int mini;
  unsigned int maxi;
  String list[5];
};
