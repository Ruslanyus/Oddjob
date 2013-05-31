void clean_mode()
{
     myGLCD.clrScr(); //clear the screen
     myGLCD.print("Clean Mode: "  ,10,10);
     myGLCD.print("Open Ext1 and Ext2 during few second "  ,10,10);
     myGLCD.print("Mode used to clean solenoid "  ,10,20);
     myGLCD.setFont(BigFont);

   // Turn solenoid on during few second
     ext1_turnOn();
     ext2_turnOn();
     
     for(unsigned int delayCounter = 0;  delayCounter <= 5;delayCounter++) {
     myGLCD.print("Wait "+ String(5-delayCounter)+ "s    "  ,10,50);
     delaySeconds(1,0); 
     }

     //turn off solenoid
     ext1_turnOff();
     ext2_turnOff();
}
