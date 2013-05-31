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
 

// Write a unsigned int (two bytes) value to eeprom
void eeprom_writeInt(int address, unsigned int value){
    
  EEPROM.write(address, value/256);
  EEPROM.write(address+1, value % 256);

}

// read a unsigned int (two bytes) value from eeprom
unsigned int eeprom_readInt(int address){
  
  return EEPROM.read(address)*256+EEPROM.read(address+1);
}


