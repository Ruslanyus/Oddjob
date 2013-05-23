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

void config_init(){
  
  // Check if the firmware version is the same of eeprom config
  if (
      EEPROM.read(EE_ADDR_SIGNATURE_CODE1) == SIGNATURE_CODE1 && 
      EEPROM.read(EE_ADDR_SIGNATURE_CODE2) == SIGNATURE_CODE2 && 
      EEPROM.read(EE_ADDR_SIGNATURE_CODE3) == SIGNATURE_CODE3 && 
      EEPROM.read(EE_ADDR_SIGNATURE_CODE4) == SIGNATURE_CODE4 &&
      EEPROM.read(EE_ADDR_CODE_MAYOR_VERSION) == CODE_MAYOR_VERSION &&
      EEPROM.read(EE_ADDR_CODE_MINOR_VERSION) == CODE_MINOR_VERSION
     ) {
       // loads in ram the eeprom config
       config_loadBackup_all();
     
   } else {
      // clear the eeprom
      for (int i = 0; i < EEPROM_SIZE; i++)  EEPROM.write(i, 0xFF);
      
      // writes sign codes
      EEPROM.write(EE_ADDR_SIGNATURE_CODE1,SIGNATURE_CODE1);
      EEPROM.write(EE_ADDR_SIGNATURE_CODE2,SIGNATURE_CODE2);
      EEPROM.write(EE_ADDR_SIGNATURE_CODE3,SIGNATURE_CODE3);
      EEPROM.write(EE_ADDR_SIGNATURE_CODE4,SIGNATURE_CODE4);
      EEPROM.write(EE_ADDR_CODE_MAYOR_VERSION,CODE_MAYOR_VERSION);
      EEPROM.write(EE_ADDR_CODE_MINOR_VERSION,CODE_MINOR_VERSION);
      
      // load defaults in ram and save it on eeprom
      config_loadDefaults_all();
      config_saveBackup_all();
      
      // inform of resetting action
      //display_printResetting();
  } 
}

void config_loadDefaults_all(){
  
    config_loadDefaults_system();
    config_loadDefaults_intervalMode();
    config_loadDefaults_audioTriggerMode();
    config_loadDefaults_shockTriggerMode();
    config_loadDefaults_barrierMode();  
    config_loadDefaults_flashSlave();  
    config_loadDefaults_astroMode();
    config_loadDefaults_barrier2Mode(); 
    config_loadDefaults_waterMode();
}

void config_saveBackup_all(){
  
    config_saveBackup_system();
    config_saveBackup_intervalMode();
    config_saveBackup_audioTriggerMode();
    config_saveBackup_shockTriggerMode();
    config_saveBackup_barrierMode();
    config_saveBackup_flashSlave();
    config_saveBackup_astroMode();
    config_saveBackup_barrier2Mode();
    config_saveBackup_waterMode();

}
 
void config_loadBackup_all(){
    config_loadBackup_system();
    config_loadBackup_intervalMode();
    config_loadBackup_audioTriggerMode();
    config_loadBackup_shockTriggerMode();
    config_loadBackup_barrierMode();
    config_loadBackup_flashSlave();
    config_loadBackup_astroMode();
    config_loadBackup_barrier2Mode();
    config_loadBackup_waterMode();
} 
 
// Load the system config from eeprom to ram
void config_loadBackup_system(){   
  
  system_useSpeaker = EEPROM.read(EE_ADDR_system_useSpeaker);
  system_interfaceSensorLimit = EEPROM.read(EE_ADDR_system_interfaceSensorLimit);
  system_flashPulsing = EEPROM.read(EE_ADDR_system_flashPulsing);
}

// Load the default system config to ram
void config_loadDefaults_system() {
  
  system_useSpeaker = DEFAULT_system_useSpeaker;
  system_interfaceSensorLimit = DEFAULT_system_interfaceSensorLimit;
  system_flashPulsing = DEFAULT_system_flashPulsing ;
}

// Save the system config from ram to eeprom
void config_saveBackup_system(){ 
  
  EEPROM.write(EE_ADDR_system_useSpeaker, system_useSpeaker);
  EEPROM.write(EE_ADDR_system_interfaceSensorLimit, system_interfaceSensorLimit);
  EEPROM.write(EE_ADDR_system_flashPulsing, system_flashPulsing);

}





