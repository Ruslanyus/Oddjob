/**
 *
 * - Oddjob
 *
 * This file is part of Oddjob based on the project Photoduino.
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
 
 // Load the default interval mode config to ram
void config_loadDefaults_intervalMode() {

  intervalMode_autofocusTime =   DEFAULT_intervalMode_autofocusTime;
  intervalMode_shutterLagTime =  DEFAULT_intervalMode_shutterLagTime;
  intervalMode_useFlash1 =       DEFAULT_intervalMode_useFlash1;
  intervalMode_preFlash1Time =   DEFAULT_intervalMode_preFlash1Time;
  intervalMode_useFlash2 =       DEFAULT_intervalMode_useFlash2;
  intervalMode_preFlash2Time =   DEFAULT_intervalMode_preFlash2Time;
  intervalMode_preCloseTime =    DEFAULT_intervalMode_preCloseTime;
  intervalMode_intervalUnits =   DEFAULT_intervalMode_intervalUnits;
  intervalMode_intervalValue =   DEFAULT_intervalMode_intervalValue;
  intervalMode_numCicles =       DEFAULT_intervalMode_numCicles;
  
}

// Save the inverval mode config to eeprom
void config_saveBackup_intervalMode(){

  eeprom_writeInt(EE_ADDR_intervalMode_autofocusTime, intervalMode_autofocusTime);
  eeprom_writeInt(EE_ADDR_intervalMode_shutterLagTime, intervalMode_shutterLagTime);
  EEPROM.write(EE_ADDR_intervalMode_useFlash1, intervalMode_useFlash1);
  eeprom_writeInt(EE_ADDR_intervalMode_preFlash1Time, intervalMode_preFlash1Time);
  EEPROM.write(EE_ADDR_intervalMode_useFlash2, intervalMode_useFlash2);
  eeprom_writeInt(EE_ADDR_intervalMode_preFlash2Time, intervalMode_preFlash2Time);
  eeprom_writeInt(EE_ADDR_intervalMode_preCloseTime, intervalMode_preCloseTime);
  EEPROM.write(EE_ADDR_intervalMode_intervalUnits, intervalMode_intervalUnits);
  eeprom_writeInt(EE_ADDR_intervalMode_intervalValue, intervalMode_intervalValue);
  eeprom_writeInt(EE_ADDR_intervalMode_numCicles, intervalMode_numCicles);  
  
}

// Load the interval mode config from eeprom to ram
void config_loadBackup_intervalMode(){  
  
  intervalMode_autofocusTime = eeprom_readInt(EE_ADDR_intervalMode_autofocusTime);
  intervalMode_shutterLagTime = eeprom_readInt(EE_ADDR_intervalMode_shutterLagTime);
  intervalMode_useFlash1 = EEPROM.read(EE_ADDR_intervalMode_useFlash1);
  intervalMode_preFlash1Time = eeprom_readInt(EE_ADDR_intervalMode_preFlash1Time);
  intervalMode_useFlash2 = EEPROM.read(EE_ADDR_intervalMode_useFlash2);
  intervalMode_preFlash2Time = eeprom_readInt(EE_ADDR_intervalMode_preFlash2Time);
  intervalMode_preCloseTime = eeprom_readInt(EE_ADDR_intervalMode_preCloseTime);
  intervalMode_intervalUnits = EEPROM.read(EE_ADDR_intervalMode_intervalUnits);
  intervalMode_intervalValue = eeprom_readInt(EE_ADDR_intervalMode_intervalValue);
  intervalMode_numCicles = eeprom_readInt(EE_ADDR_intervalMode_numCicles);
}

 
 
 
 int menu_interval()
{
   int res,res2;

  while (true)
  {
  
  res=mode_menu("Mode Interval");
   switch(res)
  {
    case 0: //run
    //res2=menu_conf_interval();
    runAs_interval();
    break;
    
    case 1: //config
     res2=menu_conf_interval();
     config_saveBackup_intervalMode();
     
    break;
    
    case 2: //home
    return(0);
    break;
  }
  }
}

int menu_conf_interval()
{
  struct list_data list[8];
  
  list[0].description="Use Flash1";
  list[0].unit=" ";
  list[0].value=intervalMode_useFlash1;
  list[0].mini=0;
  list[0].maxi=1;
  list[0].list[0]="Actif";
  list[0].list[1]="Inactif";
  list[0].list[3]="";
  list[0].list[4]="";

  list[1].description="PreFlash1Time";
  list[1].unit="ms";
  list[1].value=intervalMode_preFlash1Time;
  list[1].mini=0;
  list[1].maxi=1000;
  list[1].list[0]="";
  list[1].list[1]="";
  list[1].list[2]="";
  list[1].list[3]="";
  list[1].list[4]="";

  list[2].description="Use Flash2";
  list[2].unit=" ";
  list[2].value=intervalMode_useFlash2;
  list[2].mini=0;
  list[2].maxi=1;
  list[2].list[0]="Actif";
  list[2].list[1]="Inactif";
  list[2].list[2]="";
  list[2].list[3]="";
  list[2].list[4]="";

  list[3].description="PreFlash2 Time";
  list[3].unit="ms";
  list[3].value=intervalMode_preFlash2Time;
  list[3].mini=0;
  list[3].maxi=1000;
  list[3].list[0]="";
  list[3].list[1]="";
  list[3].list[2]="";
  list[3].list[3]="";
  list[3].list[4]="";

  list[4].description="PreClose Time";
  list[4].unit="ms";
  list[4].value=intervalMode_preCloseTime;
  list[4].mini=0;
  list[4].maxi=1000;
  list[4].list[0]="";
  list[4].list[1]="";
  list[4].list[2]="";
  list[4].list[3]="";
  list[4].list[4]="";

  list[5].description="Interval Unit";
  list[5].unit="ms";
  list[5].value=intervalMode_intervalUnits;
  list[5].mini=0;
  list[5].maxi=3;
  
  list[5].list[0]="ms";
  list[5].list[1]="s ";
  list[5].list[2]="min";
  list[5].list[3]="hour";
  list[5].list[4]="days";

  list[6].description="Interval Time";
  list[6].unit=" ";
  list[6].value=intervalMode_intervalValue;
  list[6].mini=0;
  list[6].maxi=1000;
  list[6].list[0]="";
  list[6].list[1]="";
  list[6].list[2]="";
  list[6].list[3]="";
  list[6].list[4]="";
  
  list[7].description="numberOfCycle";
  list[7].unit="s";
  list[7].value=intervalMode_numCicles;
  list[7].mini=0;
  list[7].maxi=1000;
  list[7].list[0]="";
  list[7].list[1]="";
  list[7].list[2]="";
  list[7].list[3]="";
  list[7].list[4]="";
  
  
  myGLCD.clrScr();
  res=menu_list(8,list);
  
  intervalMode_useFlash1=list[0].value;
  intervalMode_preFlash1Time=list[1].value;
  intervalMode_useFlash2=list[2].value;
  intervalMode_preFlash2Time=list[3].value;
  intervalMode_preCloseTime=list[4].value;
  intervalMode_intervalUnits=list[5].value;
  intervalMode_intervalValue=list[6].value;
  intervalMode_numCicles=list[7].value;
  
  return(0);
}

 
 
 // Run interval mode
void runAs_interval() { 
   
    int dec=20;
    int y=20;
    myGLCD.clrScr(); //clear the screen
    myGLCD.setFont(BigFont);
    myGLCD.setColor(200, 200, 200);
    myGLCD.print(MSG_RUN_INTERVAL,10,y);
    y=y+dec;
   
   
   cancelFlag=false;
   for(unsigned int ciclesCounter = 0; (cancelFlag==false && !(intervalMode_numCicles>0 && ciclesCounter >= intervalMode_numCicles));ciclesCounter++) { 
     myGLCD.print("photo "+ String(ciclesCounter+1)+ "/" + String(intervalMode_numCicles),10,y);
     camera_autofocusBegin(intervalMode_autofocusTime); 
     camera_shutterBegin(intervalMode_shutterLagTime); 
  
     if (intervalMode_useFlash1==0) flash_shoot(intervalMode_preFlash1Time, PINS_FLASH1);
     if (intervalMode_useFlash2==0) flash_shoot(intervalMode_preFlash2Time, PINS_FLASH2); 
     
     camera_shutterEnd(intervalMode_preCloseTime); 
     camera_autofocusEnd(); 
     
     waitInterval();
     myGLCD.print("                             ",10,50);
     cancelFlag=myTouch.dataAvailable();
     
   }
   

   myGLCD.setColor(255, 0, 255);
   myGLCD.setFont(SmallFont);
}

// Wait interval time
void waitInterval(){
  
       if(intervalMode_intervalUnits == UNITS_MS)     delay(intervalMode_intervalValue); 
  else if(intervalMode_intervalUnits == UNITS_SECS)   delaySeconds(intervalMode_intervalValue,1);  
  else if(intervalMode_intervalUnits == UNITS_MINS)   delayMinutes(intervalMode_intervalValue,1);  
  else if(intervalMode_intervalUnits == UNITS_HOURS)  delayHours(intervalMode_intervalValue,1);  
  else if(intervalMode_intervalUnits == UNITS_DAYS)   delayDays(intervalMode_intervalValue,1);  
}

// Wait a time in seconds
void delaySeconds(unsigned int value, int visible) {
  for (unsigned int i = 0; i<value && !myTouch.dataAvailable(); i++) 
    {
       if (visible==1) myGLCD.print( String(value-i)+ "s restantes",10,60);
      delay(1000); 
    }
}

// Wait a time in minutes
void delayMinutes(unsigned int value, int visible) {
  for (unsigned int i = 0; i<value && !myTouch.dataAvailable(); i++) 
  {
    if (visible==1) myGLCD.print( String(value-i)+ "m restantes",10,60);
    delaySeconds(60,0); 
  }
}

// Wait a time in hours
void delayHours(unsigned int value, int visible){
  for (unsigned int i = 0; i<value && !myTouch.dataAvailable(); i++) 
  {
    if (visible==1) myGLCD.print( String(value-i)+ "h restantes",10,60);
    delayMinutes(60,0); 
  }
}

// Wait a time in days
void delayDays(unsigned int value, int visible){
  for (unsigned int i = 0; i<value && !myTouch.dataAvailable(); i++) 
  {
    if (visible==1) myGLCD.print( String(value-i)+ "d restantes",10,60);
    delayHours(24,0); 
  }
}




