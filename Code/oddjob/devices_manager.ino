/**
 *
 * - Oddjob
 *
 * This file is part of Photoduino.
 *
 * Photoduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Photoduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Photoduino.  If not, see <http://www.gnu.org/licenses/>.
 */

// Shoots the flash 
void flash_shoot_up( byte pin) {
    digitalWrite(pin,HIGH); 
 }
void flash_shoot_down( byte pin) {
    digitalWrite(pin,LOW); 
 }

// Shoots the flash after wait a delay
void flash_shoot(unsigned int previousDelay, byte pin) {
    delay(previousDelay);
    digitalWrite(pin,HIGH); 
    delayMicroseconds(DEVICES_FLASHES_SHOOTING_PULSE);
    digitalWrite(pin,LOW);
 }

// Begins the shutter 
void camera_shutterBegin(unsigned int shutterLag){
    digitalWrite(PINS_SHUTTER,HIGH); 
    delay(shutterLag);
}
 
// Ends the shutter
void camera_shutterEnd(unsigned int preCloseTime){
    delay(preCloseTime);
    digitalWrite(PINS_SHUTTER,LOW); 
}

// Begins the autofocus
void camera_autofocusBegin(unsigned int autofocusTime){
    digitalWrite(PINS_AUTOFOCUS,HIGH); 
    delay(autofocusTime);
}

// Ends the autofocus
void camera_autofocusEnd(){
    digitalWrite(PINS_AUTOFOCUS,LOW);
}

// Look-up the mirror 
void camera_mirrorLockUp(unsigned int autofocusTime, unsigned int shutterLag){
    
    digitalWrite(PINS_AUTOFOCUS,HIGH); 
    delay(autofocusTime);  
    digitalWrite(PINS_SHUTTER,HIGH); 
    delay(shutterLag);
    digitalWrite(PINS_SHUTTER,LOW); 
    digitalWrite(PINS_AUTOFOCUS,LOW);
}

// Turns the laser ON
void laser_turnOn(){
   digitalWrite(PINS_LASER1,HIGH);
   digitalWrite(PINS_LASER2,HIGH);
   delay(1); // waits for laser to anything
}

// Turns the laser OFF
void laser_turnOff(){
   digitalWrite(PINS_LASER1,LOW); 
   digitalWrite(PINS_LASER2,LOW);
}

// Reads the value of a sensor
unsigned int sensor_read(byte sensorPin) {
  
  unsigned int value = analogRead(sensorPin);
  if (value>999) value = 999;
 
  if (sensorPin == PINS_SENSOR_MIC) {
    if (value > 500) value = (value-500)*2;
    else value = (500-value)*2;
  } 
  
  return value;
}

// Waits for sensor cross the limit
boolean sensor_waitFor(byte pin, byte mode, unsigned int limitValue, unsigned int limitTime){
  
  unsigned long time = millis();
  unsigned int sensorValue = sensor_read(pin)>>4;
  boolean result = false;

  for(; !result && !cancelFlag && (millis()<time+limitTime || limitTime==0); sensorValue = sensor_read(pin)>>4) {
    if (mode==SENSOR_MODE_HIGHER && sensorValue>=limitValue) result = true;
    if (mode==SENSOR_MODE_LOWER && sensorValue<=limitValue) result = true;
  }
  if(cancelFlag) result = true;
  return result;
}





// Beeps buzzer a time in ms
void buzzer_beep(int time){
  
  if (system_useSpeaker==0){
     analogWrite(PINS_BUZZER,64); 
     delay(time);
     analogWrite(PINS_BUZZER,0); 
  }
}


