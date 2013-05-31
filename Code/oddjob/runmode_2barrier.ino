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
 
 
 
 // Load the barrier2Mode from eeprom to ram
void config_loadBackup_barrier2Mode(){   
  

  barrier2Mode_sensor1Limit = eeprom_readInt(EE_ADDR_barrier2Mode_sensor1Limit);
  barrier2Mode_sensor2Limit = eeprom_readInt(EE_ADDR_barrier2Mode_sensor2Limit);
  barrier2Mode_distance     = eeprom_readInt(EE_ADDR_barrier2Mode_distance);
}


// Load the default barrier2Mode config to ram
void config_loadDefaults_barrier2Mode() {
  
  barrier2Mode_sensor1Limit =      DEFAULT_barrier2Mode_sensor1Limit;
  barrier2Mode_sensor2Limit =      DEFAULT_barrier2Mode_sensor2Limit;
  barrier2Mode_distance     =    DEFAULT_barrier2Mode_distance;
 
}

// Save the barrier2Modee config from ram to eeprom
void config_saveBackup_barrier2Mode(){ 
  
  eeprom_writeInt(EE_ADDR_barrier2Mode_sensor1Limit, barrier2Mode_sensor1Limit);
  eeprom_writeInt(EE_ADDR_barrier2Mode_sensor2Limit, barrier2Mode_sensor2Limit);
  eeprom_writeInt(EE_ADDR_barrier2Mode_distance, barrier2Mode_distance);

}

 
 
int menu_2barrier()
{
   int res;

  while (true)
  {
  
    res=mode_menu("Mode 2Barriere");
     switch(res)
    {
      case 0: //run
      runAs_2barrierMode();
      break;
      
      case 1: //config
      menu_conf_2barrier();
      config_saveBackup_barrier2Mode();
      break;
      
      case 2: //home
      return(0);
      break;
    }
  }
}

int menu_conf_2barrier()
{
 struct list_data list[3];
  
  list[0].description="Sensor1 Limit";
  list[0].unit=" ";
  list[0].value=barrier2Mode_sensor1Limit;
  list[0].mini=PINS_SENSOR_BARRIER1;
  list[0].maxi=PINS_SENSOR_BARRIER1;
  list[0].list[0]="";
  list[0].list[1]="";
  list[0].list[3]="";
  list[0].list[4]="Sensor";

  list[1].description="Sensor2 Limit";
  list[1].unit=" ";
  list[1].value=barrier2Mode_sensor2Limit;
  list[1].mini=PINS_SENSOR_BARRIER2;
  list[1].maxi=PINS_SENSOR_BARRIER2;
  list[1].list[0]="";
  list[1].list[1]="";
  list[1].list[3]="";
  list[1].list[4]="Sensor";

  
  list[2].description="Distance";
  list[2].unit="cm";
  list[2].value=barrier2Mode_distance;
  list[2].mini=0;
  list[2].maxi=100;
  list[2].list[0]="";
  list[2].list[1]="";
  list[2].list[3]="";
  list[2].list[4]="";

     
  
  myGLCD.clrScr();
  res=menu_list(3,list);
  barrier2Mode_sensor1Limit=list[0].value;
  barrier2Mode_sensor2Limit=list[1].value;
  return(0);
}







 
 
 // Run barrier mode
void runAs_2barrierMode() { 
       
    unsigned int barrier1;
    unsigned int barrier2;
    double speed;
    
    int dec=20;
    int y=20;
    myGLCD.clrScr(); //clear the screen
    myGLCD.setFont(BigFont);
    myGLCD.setColor(200, 200, 200);
    myGLCD.print(MSG_RUN_BARRIER,10,y);
    y=y+dec;
    myGLCD.print("waiting for barrier 1",10,y);
    y=y+dec;
    cancelFlag=false;
   
    laser_turnOn();
    sensor_waitFor(PINS_SENSOR_BARRIER1, SENSOR_MODE_LOWER, barrier2Mode_sensor1Limit, 0);
    barrier1=micros();
  
      
    //myGLCD.print("waiting for barrier 2",10,y);     
    sensor_waitFor(PINS_SENSOR_BARRIER2, SENSOR_MODE_LOWER, barrier2Mode_sensor2Limit, 0);
    barrier2=micros();
    y=y+dec;
    myGLCD.print("time:"+String(barrier2-barrier1)+" micro s",10,y);
    y=y+dec;
    speed=(barrier2Mode_distance*100000)/((barrier2-barrier1));
    myGLCD.print("speed:"+String(int(speed))+" m/s",10,y);
    delaySeconds(10,0); 
    laser_turnOff();
       
     
  
}
