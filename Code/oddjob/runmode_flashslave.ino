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
  
  
// Load the default flash slave config to ram
void config_loadDefaults_flashSlave() {

  flashSlave_sensorLimit =     DEFAULT_flashSlave_sensorLimit;
  flashSlave_useFlash1   =     DEFAULT_flashSlave_useFlash1;
  flashSlave_preFlash1Time =   DEFAULT_flashSlave_preFlash1Time;
  flashSlave_useFlash2 =       DEFAULT_flashSlave_useFlash2;
  flashSlave_preFlash2Time =   DEFAULT_flashSlave_preFlash2Time;
}

// Save the flash slave config to eeprom
void config_saveBackup_flashSlave(){
  
  eeprom_writeInt(EE_ADDR_flashSlave_sensorLimit, flashSlave_sensorLimit);
  EEPROM.write(EE_ADDR_flashSlave_useFlash1, flashSlave_useFlash1);
  eeprom_writeInt(EE_ADDR_flashSlave_preFlash1Time, flashSlave_preFlash1Time);
  EEPROM.write(EE_ADDR_flashSlave_useFlash2, flashSlave_useFlash2);
  eeprom_writeInt(EE_ADDR_flashSlave_preFlash2Time, flashSlave_preFlash2Time);
 
}

// Load the flash slave config from eeprom to ram
void config_loadBackup_flashSlave(){  
  
  flashSlave_sensorLimit = eeprom_readInt(EE_ADDR_flashSlave_sensorLimit);
  flashSlave_useFlash1 = EEPROM.read(EE_ADDR_flashSlave_useFlash1);
  flashSlave_preFlash1Time = eeprom_readInt(EE_ADDR_flashSlave_preFlash1Time);
  flashSlave_useFlash2 = EEPROM.read(EE_ADDR_flashSlave_useFlash2);
  flashSlave_preFlash2Time = eeprom_readInt(EE_ADDR_flashSlave_preFlash2Time);
  
}


  
  int menu_slave()
{
   int res;
   while (true)
  {
 
    res=mode_menu("Mode Flash Slave");
     switch(res)
    {
      case 0: //run
      runAs_flashSlave();
      break;
      
      case 1: //config
      menu_conf_slave();
      config_saveBackup_flashSlave();
      break;
      
      case 2: //home
      return(0);
      break;
    }
  }
}

int menu_conf_slave()
{
 struct list_data list[9];
  
  list[0].description="Sensor Limit";
  list[0].unit=" ";
  list[0].value=flashSlave_sensorLimit;
  list[0].mini=PINS_SENSOR_BARRIER1;
  list[0].maxi=PINS_SENSOR_BARRIER1;
  list[0].list[0]="";
  list[0].list[1]="";
  list[0].list[3]="";
  list[0].list[4]="Sensor";

  list[1].description="Shooting Mode";
  list[1].unit=" ";
  list[1].value=flashSlave_shootingMode;
  list[1].mini=0;
  list[1].maxi=1;
  list[1].list[0]="Normal";
  list[1].list[1]="Pre-Bulb";
  list[1].list[3]="Mirror Lock-ip";
  list[1].list[4]="Pre Focused";
  
  
  list[2].description="Use Flash1";
  list[2].unit=" ";
  list[2].value=flashSlave_useFlash1;
  list[2].mini=0;
  list[2].maxi=1;
  list[2].list[0]="Actif";
  list[2].list[1]="Inactif";
  list[2].list[3]="";
  list[2].list[4]="";

  list[3].description="PreFlash1Time";
  list[3].unit="ms";
  list[3].value=flashSlave_preFlash1Time;
  list[3].mini=0;
  list[3].maxi=1000;
  list[3].list[0]="";
  list[3].list[1]="";
  list[3].list[2]="";
  list[3].list[3]="";
  list[3].list[4]="";

  list[4].description="Use Flash2";
  list[4].unit=" ";
  list[4].value=flashSlave_useFlash2;
  list[4].mini=0;
  list[4].maxi=1;
  list[4].list[0]="Actif";
  list[4].list[1]="Inactif";
  list[4].list[2]="";
  list[4].list[3]="";
  list[4].list[4]="";

  list[5].description="PreFlash2 Time";
  list[5].unit="ms";
  list[5].value=flashSlave_preFlash2Time;
  list[5].mini=0;
  list[5].maxi=1000;
  list[5].list[0]="";
  list[5].list[1]="";
  list[5].list[2]="";
  list[5].list[3]="";
  list[5].list[4]="";

  list[6].description="PreClose Time";
  list[6].unit="ms";
  list[6].value=shockTriggerMode_preCloseTime;
  list[6].mini=0;
  list[6].maxi=1000;
  list[6].list[0]="";
  list[6].list[1]="";
  list[6].list[2]="";
  list[6].list[3]="";
  list[6].list[4]="";
  
  
  
  myGLCD.clrScr();
  res=menu_list(7,list);
  flashSlave_sensorLimit=list[0].value;
  flashSlave_shootingMode=list[1].value;
  flashSlave_useFlash1=list[2].value;
  flashSlave_preFlash1Time=list[3].value;
  flashSlave_useFlash2=list[4].value;
  flashSlave_preFlash2Time=list[5].value;
  flashSlave_preCloseTime=list[6].value;
  return(0);
}




 // Run flash slave trigger mode
void runAs_flashSlave() { 
       
    myGLCD.clrScr(); //clear the screen
    myGLCD.setFont(BigFont);
    myGLCD.setColor(200, 200, 200);
    myGLCD.print(MSG_RUN_FLASH_SLAVE,10,20);
    cancelFlag=false;
   
   for(;(cancelFlag==false);) { 
       sensor_waitFor(PINS_SENSOR_BARRIER1, SENSOR_MODE_HIGHER, flashSlave_sensorLimit, 0);
       if (flashSlave_useFlash1==0) flash_shoot(flashSlave_preFlash1Time, PINS_FLASH1);
       if (flashSlave_useFlash2==0) flash_shoot(flashSlave_preFlash2Time, PINS_FLASH2); 
       cancelFlag=myTouch.dataAvailable();
   } 
   

}

