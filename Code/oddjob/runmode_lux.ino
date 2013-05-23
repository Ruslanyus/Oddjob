
void lux_mode() {

   int i;
   uint16_t val=0;
   cancelFlag=false;
   while(cancelFlag==false) { 
     
 
    BH1750_Init(BH1750address);
    delay(200);
    if(2==BH1750_Read(BH1750address))
     {
       val=((buff[0]<<8)|buff[1])/1.2;
       myGLCD.print("lum: "+ String(val)+ "lx  "  ,10,20);
  
    }
 delay(150);


     myGLCD.print("                             ",10,50);
     cancelFlag=myTouch.dataAvailable();
     
   }

}

int BH1750_Read(int address) //
 {
 int i=0;
 Wire.beginTransmission(address);
 Wire.requestFrom(address, 2);
 while(Wire.available()) //
 {
 buff[i] = Wire.read(); // receive one byte
 i++;
 }
 Wire.endTransmission(); 
return i;
 }
 
void BH1750_Init(int address) 
{
 Wire.beginTransmission(address);
 Wire.write(0x10);//1lx reolution 120ms
 Wire.endTransmission();
 }

