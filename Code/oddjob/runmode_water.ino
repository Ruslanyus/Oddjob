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
 
 
// Load the waterMode from eeprom to ram

void config_loadBackup_waterMode(){   
  dropMode_dropCount    = eeprom_readInt(EE_ADDR_dropMode_dropCount);
  dropMode_dropDuration = eeprom_readInt(EE_ADDR_dropMode_dropDuration);
  dropMode_dropInterval = eeprom_readInt(EE_ADDR_dropMode_dropInterval);
  dropMode_drop2Duration= eeprom_readInt(EE_ADDR_dropMode_drop2Duration);
  dropMode_dropShooting = eeprom_readInt(EE_ADDR_dropMode_dropShooting);
  dropMode_dropPause    = eeprom_readInt(EE_ADDR_dropMode_dropPause);
}

// Load the default barrierMode config to ram

void config_loadDefaults_waterMode() {
  dropMode_dropCount    =      DEFAULT_dropMode_dropCount;
  dropMode_dropDuration =   DEFAULT_dropMode_dropDuration;
  dropMode_dropInterval =   DEFAULT_dropMode_dropInterval;
  dropMode_drop2Duration=   DEFAULT_dropMode_drop2Duration;
  dropMode_dropShooting =   DEFAULT_dropMode_dropShooting;
  dropMode_dropPause    =   DEFAULT_dropMode_dropPause;
}

// Save the barrierModee config from ram to eeprom

void config_saveBackup_waterMode(){ 
  eeprom_writeInt(EE_ADDR_dropMode_dropCount, dropMode_dropCount);
  eeprom_writeInt(EE_ADDR_dropMode_dropDuration, dropMode_dropDuration);
  eeprom_writeInt(EE_ADDR_dropMode_dropInterval, dropMode_dropInterval);
  eeprom_writeInt(EE_ADDR_dropMode_drop2Duration, dropMode_drop2Duration);
  eeprom_writeInt(EE_ADDR_dropMode_dropShooting, dropMode_dropShooting);
  eeprom_writeInt(EE_ADDR_dropMode_dropPause, dropMode_dropPause);
}


 
 
int menu_water()
{
   int res,res2;

  while (true)
  {
  
  res=mode_menu("Mode Water drop");
   switch(res)
  {
    case 0: //run
    runAs_waterMode();
    break;
    
    case 1: //config
     
     res2=menu_conf_water();
     config_saveBackup_waterMode();
     
    break;
    
    case 2: //home
    return(0);
    break;
  }
  }
}

int menu_conf_water()
{
 struct list_data list[6];
  
  
  list[0].description="Drop count";
  list[0].unit="  ";
  list[0].value=dropMode_dropCount;
  list[0].mini=0;
  list[0].maxi=10000;
  list[0].list[0]="";
  list[0].list[1]="";
  list[0].list[2]="";
  list[0].list[3]="";
  list[0].list[4]="";

  list[1].description="DropDuration";
  list[1].unit="ms";
  list[1].value=dropMode_dropDuration;
  list[1].mini=0;
  list[1].maxi=64000;
  list[1].list[0]="";
  list[1].list[1]="";
  list[1].list[2]="";
  list[1].list[3]="";
  list[1].list[4]="";

  list[2].description="DropInterval";
  list[2].unit="ms";
  list[2].value=dropMode_dropInterval;
  list[2].mini=0;
  list[2].maxi=64000;
  list[2].list[0]="";
  list[2].list[1]="";
  list[2].list[2]="";
  list[2].list[3]="";
  list[2].list[4]="";
  
  list[3].description="Drop2Duration";
  list[3].unit="ms";
  list[3].value=dropMode_drop2Duration;
  list[3].mini=0;
  list[3].maxi=64000;
  list[3].list[0]="";
  list[3].list[1]="";
  list[3].list[2]="";
  list[3].list[3]="";
  list[3].list[4]="";
  
  list[4].description="TShooting";
  list[4].unit="ms";
  list[4].value=dropMode_dropShooting;
  list[4].mini=0;
  list[4].maxi=64000;
  list[4].list[0]="";
  list[4].list[1]="";
  list[4].list[2]="";
  list[4].list[3]="";
  list[4].list[4]="";

  list[5].description="TIntercycle";
  list[5].unit="ms ";
  list[5].value=dropMode_dropPause;
  list[5].mini=0;
  list[5].maxi=64000;
  list[5].list[0]="";
  list[5].list[1]="";
  list[5].list[2]="";
  list[5].list[3]="";
  list[5].list[4]="";
  
  myGLCD.clrScr();
  res=menu_list(6,list);
  dropMode_dropCount=list[0].value;
  dropMode_dropDuration=list[1].value;
  dropMode_dropInterval=list[2].value;
  dropMode_drop2Duration=list[3].value;
  dropMode_dropShooting=list[4].value;
  dropMode_dropPause=list[5].value;
  return(0);
}

// Turns the ext1 ON
void ext1_turnOn(){
   digitalWrite(PINS_LASER1,HIGH);
   //delay(1); // waits for laser to anything
}

// Turns the laser OFF
void ext1_turnOff(){
   digitalWrite(PINS_LASER1,LOW); 
}

// Turns the ext1 ON
void ext2_turnOn(){
   digitalWrite(PINS_LASER2,HIGH);
   //delay(1); // waits for laser to anything
}

// Turns the laser OFF
void ext2_turnOff(){
   digitalWrite(PINS_LASER2,LOW);
}


 
 // Run water mode
void runAs_waterMode() { 
       

    int dec=20;
    int y=20;
    unsigned int dropTime;
    myGLCD.clrScr(); //clear the screen
    myGLCD.setFont(BigFont);
    myGLCD.setColor(200, 200, 200);
    myGLCD.print("Water Drop Mode",10,y);
    y=y+dec;
    cancelFlag=false;
   dropTime=dropMode_dropShooting-dropMode_dropDuration-dropMode_drop2Duration-dropMode_dropInterval;
   if (dropTime<1) dropTime=1;
   for(unsigned int ciclesCounter = 0; (cancelFlag==false && !(dropMode_dropCount>0 && ciclesCounter >= dropMode_dropCount));ciclesCounter++) { 
     myGLCD.print("photo "+ String(ciclesCounter+1)+ "/" + String(dropMode_dropCount),10,y);
     
     // first droplet
     ext1_turnOn();
     delay(dropMode_dropDuration);
     ext1_turnOff();
     // waiting for the second
     delay(dropMode_dropInterval);
     //start focus
     camera_autofocusBegin(0);
     // start the second droplet
     ext1_turnOn();
     delay(dropMode_drop2Duration);
     ext1_turnOff();
     //waiting for the shooting
     delay(dropTime);
     //shoot
     
     camera_shutterBegin(1); 
     //flash_shoot(0, PINS_FLASH1);
     flash_shoot_up(PINS_FLASH1);
     //flash_shoot(0, PINS_FLASH2);
     flash_shoot_up(PINS_FLASH2);
     flash_shoot_down(PINS_FLASH1);
     flash_shoot_down(PINS_FLASH2);
     delay(40);
     camera_shutterEnd(0); 
     camera_autofocusEnd();
     // pause inter cycle
     delay(dropMode_dropPause);
     cancelFlag=myTouch.dataAvailable(); 
     }
     
     myGLCD.print("                             ",10,50);
     cancelFlag=myTouch.dataAvailable();
   
   
  
}
