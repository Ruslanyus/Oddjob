
void lux_mode() {

   int i;
   uint16_t val=0;
   uint16_t val_min=0;
   uint16_t val_max=0;
   struct icon home_icon_tab[1];

   home_icon_tab[0].pos_x=319-64;
   home_icon_tab[0].pos_y=239-64;
   home_icon_tab[0].picsize_x=64;
   home_icon_tab[0].picsize_y=64;
   home_icon_tab[0].icon_file="home-64.RAW";
   myGLCD.clrScr(); //clear the screen
   res=draw_icon(home_icon_tab[0].pos_x, home_icon_tab[0].pos_y, home_icon_tab[0].picsize_x,home_icon_tab[0].picsize_y, home_icon_tab[0].icon_file);
   myGLCD.print("LUX meter Mode: "  ,10,10);
   cancelFlag=false;
   myGLCD.setFont(BigFont);
   BH1750_Init(BH1750address);
    if(2==BH1750_Read(BH1750address))
     {
       val=((buff[0]<<8)|buff[1])/1.2;
       val_max=val;
       val_min=val;
     }
   while(cancelFlag==false) { 
     
 
    //delay(20);
    if(2==BH1750_Read(BH1750address))
     {
       val=((buff[0]<<8)|buff[1])/1.2;
       if (val>val_max) val_max=val;
       if (val<val_min) val_min=val;
       myGLCD.print("lum: "+ String(val)+ "lux    "  ,10,50);
       myGLCD.print("Min: "+ String(val_min)+ "lux    "  ,10,70);
       myGLCD.print("Max: "+ String(val_max)+ "lux    "  ,10,90);
  
    }
 delay(150);


     //myGLCD.print("                             ",10,50);
     cancelFlag=myTouch.dataAvailable();
     
   }
myGLCD.clrScr(); //clear the screen after selection
myGLCD.setFont(SmallFont);
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

