/**
 *
 * - Oddjob
 *
 * This file is part of Oddjob based on the Photoduino project.
 *
 * Oddjob is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Oddjob is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Oddjob.  If not, see <http://www.gnu.org/licenses/>.
 */ 
 
 
// Load the barrierMode from eeprom to ram
void config_loadBackup_barrierMode(){   
  
  barrierMode_shootingMode = EEPROM.read(EE_ADDR_barrierMode_shootingMode);
  barrierMode_sensorLimit = eeprom_readInt(EE_ADDR_barrierMode_sensorLimit);
  barrierMode_autofocusTime = eeprom_readInt(EE_ADDR_barrierMode_autofocusTime);
  barrierMode_shutterLagTime = eeprom_readInt(EE_ADDR_barrierMode_shutterLagTime);
  barrierMode_preCloseTime = eeprom_readInt(EE_ADDR_barrierMode_preCloseTime);
  barrierMode_useFlash1 = EEPROM.read(EE_ADDR_barrierMode_useFlash1);
  barrierMode_preFlash1Time = eeprom_readInt(EE_ADDR_barrierMode_preFlash1Time);
  barrierMode_useFlash2 = EEPROM.read(EE_ADDR_barrierMode_useFlash2);
  barrierMode_preFlash2Time = eeprom_readInt(EE_ADDR_barrierMode_preFlash2Time);
  barrierMode_numCicles =  eeprom_readInt(EE_ADDR_barrierMode_numCicles);
  barrierMode_interCicleTime =  eeprom_readInt(EE_ADDR_barrierMode_interCicleTime);
}

// Load the default barrierMode config to ram
void config_loadDefaults_barrierMode() {
  
  barrierMode_shootingMode =     DEFAULT_barrierMode_shootingMode;
  barrierMode_sensorLimit =      DEFAULT_barrierMode_sensorLimit;
  barrierMode_autofocusTime =    DEFAULT_barrierMode_autofocusTime;
  barrierMode_shutterLagTime =   DEFAULT_barrierMode_shutterLagTime;
  barrierMode_preCloseTime =     DEFAULT_barrierMode_preCloseTime;
  barrierMode_useFlash1 =        DEFAULT_barrierMode_useFlash1;
  barrierMode_preFlash1Time =    DEFAULT_barrierMode_preFlash1Time;
  barrierMode_useFlash2 =        DEFAULT_barrierMode_useFlash2;
  barrierMode_preFlash2Time =    DEFAULT_barrierMode_preFlash2Time;
  barrierMode_numCicles =        DEFAULT_barrierMode_numCicles;
  barrierMode_interCicleTime =   DEFAULT_barrierMode_interCicleTime;
}

// Save the barrierModee config from ram to eeprom
void config_saveBackup_barrierMode(){ 
  
  EEPROM.write(EE_ADDR_barrierMode_shootingMode, barrierMode_shootingMode);
  eeprom_writeInt(EE_ADDR_barrierMode_sensorLimit, barrierMode_sensorLimit);
  eeprom_writeInt(EE_ADDR_barrierMode_autofocusTime, barrierMode_autofocusTime);
  eeprom_writeInt(EE_ADDR_barrierMode_shutterLagTime, barrierMode_shutterLagTime);
  eeprom_writeInt(EE_ADDR_barrierMode_preCloseTime, barrierMode_preCloseTime);
  EEPROM.write(EE_ADDR_barrierMode_useFlash1, barrierMode_useFlash1);
  eeprom_writeInt(EE_ADDR_barrierMode_preFlash1Time, barrierMode_preFlash1Time);
  EEPROM.write(EE_ADDR_barrierMode_useFlash2, barrierMode_useFlash2);
  eeprom_writeInt(EE_ADDR_barrierMode_preFlash2Time, barrierMode_preFlash2Time);
  eeprom_writeInt(EE_ADDR_barrierMode_numCicles, barrierMode_numCicles);
  eeprom_writeInt(EE_ADDR_barrierMode_interCicleTime, barrierMode_interCicleTime); 
}


 
 
int menu_barrier()
{
   int res,res2;

  while (true)
  {
  
  res=mode_menu("Mode Barriere");
   switch(res)
  {
    case 0: //run
    runAs_barrierMode();
    break;
    
    case 1: //config
     res2=menu_conf_barrier();
     config_saveBackup_barrierMode();
     
    break;
    
    case 2: //home
    return(0);
    break;
  }
  }
}

int menu_conf_barrier()
{
 struct list_data list[9];
  
  list[0].description="Sensor Limit";
  list[0].unit=" ";
  list[0].value=barrierMode_sensorLimit;
  list[0].mini=PINS_SENSOR_BARRIER1;
  list[0].maxi=PINS_SENSOR_BARRIER1;
  list[0].list[0]="";
  list[0].list[1]="";
  list[0].list[3]="";
  list[0].list[4]="Sensor";

  list[1].description="Shooting Mode";
  list[1].unit=" ";
  list[1].value=barrierMode_shootingMode;
  list[1].mini=0;
  list[1].maxi=4;
  list[1].list[0]="Normal";
  list[1].list[1]="Pre-Bulb";
  list[1].list[3]="Mirror Lock-up";
  list[1].list[4]="Pre Focused";
  
  
  list[2].description="Use Flash1";
  list[2].unit=" ";
  list[2].value=barrierMode_useFlash1;
  list[2].mini=0;
  list[2].maxi=1;
  list[2].list[0]="Actif";
  list[2].list[1]="Inactif";
  list[2].list[3]="";
  list[2].list[4]="";

  list[3].description="PreFlash1Time";
  list[3].unit="ms";
  list[3].value=barrierMode_preFlash1Time;
  list[3].mini=0;
  list[3].maxi=1000;
  list[3].list[0]="";
  list[3].list[1]="";
  list[3].list[2]="";
  list[3].list[3]="";
  list[3].list[4]="";

  list[4].description="Use Flash2";
  list[4].unit=" ";
  list[4].value=barrierMode_useFlash2;
  list[4].mini=0;
  list[4].maxi=1;
  list[4].list[0]="Actif";
  list[4].list[1]="Inactif";
  list[4].list[2]="";
  list[4].list[3]="";
  list[4].list[4]="";

  list[5].description="PreFlash2 Time";
  list[5].unit="ms";
  list[5].value=barrierMode_preFlash2Time;
  list[5].mini=0;
  list[5].maxi=1000;
  list[5].list[0]="";
  list[5].list[1]="";
  list[5].list[2]="";
  list[5].list[3]="";
  list[5].list[4]="";

  list[6].description="PreClose Time";
  list[6].unit="ms";
  list[6].value=barrierMode_preCloseTime;
  list[6].mini=0;
  list[6].maxi=1000;
  list[6].list[0]="";
  list[6].list[1]="";
  list[6].list[2]="";
  list[6].list[3]="";
  list[6].list[4]="";

  list[7].description="Nb Cicles";
  list[7].unit="  ";
  list[7].value=barrierMode_numCicles;
  list[7].mini=0;
  list[7].maxi=10000;
  list[7].list[0]="";
  list[7].list[1]="";
  list[7].list[2]="";
  list[7].list[3]="";
  list[7].list[4]="";

  list[8].description="Interval Time";
  list[8].unit="s ";
  list[8].value=barrierMode_interCicleTime;
  list[8].mini=0;
  list[8].maxi=1000;
  list[8].list[0]="";
  list[8].list[1]="";
  list[8].list[2]="";
  list[8].list[3]="";
  list[8].list[4]="";
  
  
  
  myGLCD.clrScr();
  res=menu_list(9,list);
  barrierMode_sensorLimit=list[0].value;
  barrierMode_shootingMode=list[1].value;
  barrierMode_useFlash1=list[2].value;
  barrierMode_preFlash1Time=list[3].value;
  barrierMode_useFlash2=list[4].value;
  barrierMode_preFlash2Time=list[5].value;
  barrierMode_preCloseTime=list[6].value;
  barrierMode_numCicles=list[7].value;
  barrierMode_interCicleTime=list[8].value;
  return(0);
}







 
 
 // Run barrier mode
void runAs_barrierMode() { 
       

    int dec=20;
    int y=20;
    myGLCD.clrScr(); //clear the screen
    myGLCD.setFont(BigFont);
    myGLCD.setColor(200, 200, 200);
    myGLCD.print(MSG_RUN_BARRIER,10,y);
    y=y+dec;
    cancelFlag=false;
   
   for(unsigned int ciclesCounter = 0; (cancelFlag==false && !(barrierMode_numCicles>0 && ciclesCounter >= barrierMode_numCicles));ciclesCounter++) { 
     myGLCD.print("photo "+ String(ciclesCounter+1)+ "/" + String(barrierMode_numCicles),10,y);
     // Normal shooting mode
     if (barrierMode_shootingMode == 0) {

       laser_turnOn();
       sensor_waitFor(PINS_SENSOR_BARRIER1, SENSOR_MODE_LOWER, barrierMode_sensorLimit, 0);
       laser_turnOff();
       
       if(!cancelFlag) {
         
         camera_autofocusBegin(barrierMode_autofocusTime); 
         camera_shutterBegin(barrierMode_shutterLagTime); 
          
         if (barrierMode_useFlash1==0) flash_shoot(barrierMode_preFlash1Time, PINS_FLASH1);
         if (barrierMode_useFlash2==0) flash_shoot(barrierMode_preFlash2Time, PINS_FLASH2); 
       }
     }
     
     // Prebulb shooting mode
     if (barrierMode_shootingMode == 1) {
      
       camera_autofocusBegin(barrierMode_autofocusTime);
       camera_shutterBegin(barrierMode_shutterLagTime); 
       laser_turnOn();
       sensor_waitFor(PINS_SENSOR_BARRIER1, SENSOR_MODE_LOWER, barrierMode_sensorLimit, 0);
       laser_turnOff();
       
       if(!cancelFlag) {
         if (barrierMode_useFlash1==0) flash_shoot(barrierMode_preFlash1Time, PINS_FLASH1);
         if (barrierMode_useFlash2==0) flash_shoot(barrierMode_preFlash2Time, PINS_FLASH2); 
       }
     }  
     
     // Mirror lock-up shooting mode
     if (barrierMode_shootingMode == 3) {
              
       for(boolean result = false; result == false;  ){      
         camera_mirrorLockUp(barrierMode_autofocusTime, barrierMode_shutterLagTime);
         result = sensor_waitFor(PINS_SENSOR_BARRIER1, SENSOR_MODE_LOWER, barrierMode_sensorLimit, DEVICES_CAMERA_MIRROR_LOCKUP_TIMELIMIT);
       }
       camera_shutterBegin(1); 
      
       if(!cancelFlag) {
         
         if (barrierMode_useFlash1==0) flash_shoot(barrierMode_preFlash1Time, PINS_FLASH1);
         if (barrierMode_useFlash2==0) flash_shoot(barrierMode_preFlash2Time, PINS_FLASH2); 
       }          
     }
    
     // Common for all shooting modes
     camera_shutterEnd(barrierMode_preCloseTime); 
     camera_autofocusEnd();
     if(!cancelFlag) delay(barrierMode_interCicleTime);
     myGLCD.print("                             ",10,50);
     cancelFlag=myTouch.dataAvailable();
   }
   
   laser_turnOn();
  
}
