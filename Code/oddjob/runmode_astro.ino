/**
 *
 * - Oddjob
 *
 * This file is part of Oddjob based on the Photoduino.
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
 
 

// Load the default astro mode config to ram
void config_loadDefaults_astroMode() {

  astroMode_preCloseTime =    DEFAULT_astroMode_preCloseTime;
  astroMode_intervalUnits =   DEFAULT_astroMode_intervalUnits;
  astroMode_intervalValue =   DEFAULT_astroMode_intervalValue;
  astroMode_pauseValue =      DEFAULT_astroMode_pauseValue;
  astroMode_numCicles =       DEFAULT_astroMode_numCicles;
  
}

// Save the inverval mode config to eeprom
void config_saveBackup_astroMode(){

  eeprom_writeInt(EE_ADDR_astroMode_preCloseTime, astroMode_preCloseTime);
  EEPROM.write(EE_ADDR_astroMode_intervalUnits, astroMode_intervalUnits);
  eeprom_writeInt(EE_ADDR_astroMode_intervalValue, astroMode_intervalValue);
  eeprom_writeInt(EE_ADDR_astroMode_pauseValue, astroMode_pauseValue);
  eeprom_writeInt(EE_ADDR_astroMode_numCicles, astroMode_numCicles);  
  
}

// Load the interval mode config from eeprom to ram
void config_loadBackup_astroMode(){  
  
  astroMode_preCloseTime = eeprom_readInt(EE_ADDR_astroMode_preCloseTime);
  astroMode_intervalUnits = EEPROM.read(EE_ADDR_astroMode_intervalUnits);
  astroMode_intervalValue = eeprom_readInt(EE_ADDR_astroMode_intervalValue);
  astroMode_pauseValue = eeprom_readInt(EE_ADDR_astroMode_pauseValue);
  astroMode_numCicles = eeprom_readInt(EE_ADDR_astroMode_numCicles);
}
 
 int menu_astro()
{
   int res,res2;

  while (true)
  {
  
  res=mode_menu("Mode Astro");
   switch(res)
  {
    case 0: //run
    //res2=menu_conf_interval();
    runAs_astro();
    break;
    
    case 1: //config
     res2=menu_conf_astro();
     config_saveBackup_astroMode();
     
    break;
    
    case 2: //home
    return(0);
    break;
  }
  }
}

int menu_conf_astro()
{
  struct list_data list[5];
  
  list[0].description="PauseBulbTime";
  list[0].unit="ms";
  list[0].value=astroMode_pauseValue;
  list[0].mini=0;
  list[0].maxi=1000;
  list[0].list[0]="";
  list[0].list[1]="";
  list[0].list[2]="";
  list[0].list[3]="";
  list[0].list[4]="";

  list[1].description="PreClose Time";
  list[1].unit="ms";
  list[1].value=astroMode_preCloseTime;
  list[1].mini=0;
  list[1].maxi=1000;
  list[1].list[0]="";
  list[1].list[1]="";
  list[1].list[2]="";
  list[1].list[3]="";
  list[1].list[4]="";

  
  list[2].description="Interval Unit";
  list[2].unit="";
  list[2].value=astroMode_intervalUnits;
  list[2].mini=0;
  list[2].maxi=4;
  list[2].list[0]="ms ";
  list[2].list[1]="s ";
  list[2].list[2]="m ";
  list[2].list[3]="h ";
  list[2].list[4]="";

  list[3].description="Interval Time";
  list[3].unit=" ";
  list[3].value=astroMode_intervalValue;
  list[3].mini=0;
  list[3].maxi=1000;
  list[3].list[0]="";
  list[3].list[1]="";
  list[3].list[2]="";
  list[3].list[3]="";
  list[3].list[4]="";
  
  list[4].description="numberOfCycle";
  list[4].unit="s";
  list[4].value=astroMode_numCicles;
  list[4].mini=0;
  list[4].maxi=1000;
  list[4].list[0]="";
  list[4].list[1]="";
  list[4].list[2]="";
  list[4].list[3]="";
  list[4].list[4]="";

  
  //myGLCD.clrScr();
  res=menu_list(5,list);
  
  astroMode_pauseValue=list[0].value;
  astroMode_preCloseTime=list[1].value;
  astroMode_intervalUnits=list[2].value;
  astroMode_intervalValue=list[3].value;
  astroMode_numCicles=list[4].value;
  
  return(0);
}

 
 
 
 
 
 
 
 
 // Run interval mode
void runAs_astro() { 

    int dec=20;
    int y=20;
    myGLCD.clrScr(); //clear the screen
    myGLCD.setFont(BigFont);
    myGLCD.setColor(200, 200, 200);
    myGLCD.print(MSG_RUN_ASTRO,10,y);
    y=y+dec;
   cancelFlag=false;
   
   for(unsigned int ciclesCounter = 0; (cancelFlag==false && !(astroMode_numCicles>0 && ciclesCounter >= astroMode_numCicles));ciclesCounter++) { 
     y=2+dec;
     myGLCD.print("photo "+ String(ciclesCounter+1)+ "/" + String(astroMode_numCicles),10,y);
     y=y+dec;
     myGLCD.print("pause mode   ",10,y);
     
     waitAstroInterval(astroMode_pauseValue);
     camera_autofocusBegin(0); 
     camera_shutterBegin(0); 
     myGLCD.print("Bulb  Mode   ",10,y);
     waitAstroInterval(astroMode_intervalValue);
     camera_shutterEnd(0); 
     camera_autofocusEnd(); 
     myGLCD.print("                             ",10,50);
     cancelFlag=myTouch.dataAvailable();
   }
 
 

}

// Wait interval time
void waitAstroInterval(unsigned int value){
  
       if(astroMode_intervalUnits == UNITS_MS)     delay(value); 
  else if(astroMode_intervalUnits == UNITS_SECS)   
  {
     for(unsigned int delayCounter = 0; (cancelFlag==false && !( delayCounter >= value));delayCounter++) {
    //delaySeconds(astroMode_intervalValue);  
      myGLCD.print("delay "+ String(delayCounter)+ "/" + String(value)+" s",10,60);
     delaySeconds(1,0); 
     } 
  }
  else if(astroMode_intervalUnits == UNITS_MINS)
  {
     for(unsigned int delayCounter = 0; (cancelFlag==false && !( delayCounter >= value));delayCounter++) {
     myGLCD.print("delay "+ String(delayCounter)+ "/" + String(value)+" m",10,60);
     delayMinutes(1,0); 
     }
  }
  else if(astroMode_intervalUnits == UNITS_HOURS) 
   {
     for(unsigned int delayCounter = 0; (cancelFlag==false && !( delayCounter >= value));delayCounter++) {
     myGLCD.print("delay "+ String(delayCounter)+ "/" + String(value)+" h",10,60);
     delayHours(1,0);   
     }
   }
  else if(astroMode_intervalUnits == UNITS_DAYS)
  {
     for(unsigned int delayCounter = 0; (cancelFlag==false && !( delayCounter >= value));delayCounter++) {
     myGLCD.print("delay "+ String(delayCounter)+ "/" + String(value)+" d",10,60);
     delayDays(1,0);  
     }
  }
}


