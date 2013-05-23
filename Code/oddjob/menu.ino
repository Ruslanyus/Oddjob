//graphical menu library 

void popup_msg(String text)
{
  myGLCD.print(text, CENTER, 160);
}
//draw icon with error management
int draw_icon (int x,int y,int picsize_x,int picsize_y,String Filename)
{
// draw icon
  int res;

 
 char filename[13];
 Filename.toCharArray(filename,13);  
  res=myGLCD.loadBitmap(x,y, picsize_x, picsize_y, filename);
      if (res!=0)
      {
        if (res==0x10)
        {
          myGLCD.print("File not found....", 0, 0);
          myGLCD.print(filename, 0, 14);
        }
        else
        {
          myGLCD.print("ERROR: ", 0, 0);
          myGLCD.printNumI(res, 56, 0);
        }
     }         
     return(res);
    
}

void printCenter(String text,int x,int y,int size_x,int size_y)
{
  int size_max_x=size_x-x;
  int size_max_y=size_y-y;
  int fontx;
  int fonty;
  int textlength;
  fontx=myGLCD.getFontXsize();
  fonty=myGLCD.getFontYsize();
  textlength=text.length()*fontx;
  
   myGLCD.print(text, x+(size_max_x-textlength)/2, y+(size_max_y-fonty)/2);
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// draw icon list and return the selected icon
//icon are automatically arranged by line
// warning the first icon number is 0
int icon_menu(int nbmenu, String icon_file[], int picsize_x, int picsize_y) {
  
int value = nbmenu+1;
int nb_icon_x,nb_icon_y,screensize_x,screensize_y;
screensize_x=myGLCD.getDisplayXSize();
screensize_y=myGLCD.getDisplayYSize();
nb_icon_x=screensize_x/picsize_x;
nb_icon_y=screensize_y/picsize_y;
for (int i=0; i<nbmenu; i++)
  {
    if (icon_file[i]!="") //file not null
    {
      // draw icon
      res=draw_icon((i%nb_icon_x)*picsize_x, (i/nb_icon_x)*picsize_x, picsize_x, picsize_y, icon_file[i]);   
    }
  }
  while(value>nbmenu)
  {
    long x, y;
    while (myTouch.dataAvailable() == true)
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x!=-1) and (y!=-1))
      {
        for (int i=0; i<nbmenu; i++)
         {
           myGLCD.setColor(0, 0, 255);
           myGLCD.drawRoundRect ((i%nb_icon_x)*picsize_y, (i/nb_icon_x)*picsize_y, (i%nb_icon_x)*picsize_y+picsize_y, (i/nb_icon_x)*picsize_y+picsize_y);
         }
        res=(x/picsize_x)+(320/picsize_x)*(y/picsize_y);
        
        if (res<nbmenu) 
        {
          myGLCD.setColor(255, 0, 0);
          myGLCD.drawRoundRect ((res%nb_icon_x)*picsize_y, (res/nb_icon_x)*picsize_y, (res%nb_icon_x)*picsize_y+picsize_y, (res/nb_icon_x)*picsize_y+picsize_y);
          return(res);
        }

      }
    }
  }  
  return value;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// draw icon at specific position and return the selected icon
// warning the first icon number is 0
int flotting_icon_menu(int nbmenu, struct icon  icon_tab[]) {
  
int value = nbmenu+1;

//myGLCD.clrScr(); //clear the screen
// draw icon
for (int i=0; i<nbmenu; i++)
  {
    if (icon_tab[i].text!="")
      {
///////////////////////
        myGLCD.setFont(BigFont);
        myGLCD.setColor(0, 0, 255);
        myGLCD.drawRoundRect(icon_tab[i].pos_x,icon_tab[i].pos_y,icon_tab[i].pos_x+icon_tab[i].picsize_x,icon_tab[i].pos_y+icon_tab[i].picsize_y);
        printCenter(icon_tab[i].text,icon_tab[i].pos_x,icon_tab[i].pos_y,icon_tab[i].pos_x+icon_tab[i].picsize_x,icon_tab[i].pos_y+icon_tab[i].picsize_y);
        myGLCD.setColor(255, 0, 255);
        myGLCD.setFont(SmallFont);
      }
      else
      {
        String Filename;
        char filename[13];
        Filename=icon_tab[i].icon_file;
        Filename.toCharArray(filename,13);
        res=draw_icon(icon_tab[i].pos_x, icon_tab[i].pos_y, icon_tab[i].picsize_x, icon_tab[i].picsize_y, filename);
      }
  }
  while(value>nbmenu)
  {
    long x, y;
    
    while (myTouch.dataAvailable() == true)
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x!=-1) and (y!=-1))
      {
        for (int i=0; i<nbmenu; i++)
           if (((x>=icon_tab[i].pos_x) and (x<=(icon_tab[i].pos_x+icon_tab[i].picsize_x))) and ((y>=icon_tab[i].pos_y) and (y<=(icon_tab[i].pos_y+icon_tab[i].picsize_y))) ) value=i;          
        if (value<nbmenu)  return(value);
      }
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//read and display file on specific position
void read_file(char* filename, int pos_x, int pos_y, int dec)
{
  word result;
  char textBuffer[81];
  int x,y;
  x=pos_x;
  y=pos_y;
  if (file.exists(filename))
  {  
    res=file.openFile(filename, FILEMODE_TEXT_READ);
    if (res==NO_ERROR)
    {
      result=0;
      while ((result!=EOF) and (result!=FILE_IS_EMPTY))
      {
        result=file.readLn(textBuffer, 80);
        if (result!=FILE_IS_EMPTY)
        {
          if (result==BUFFER_OVERFLOW)
            Serial.print(textBuffer);
          else
            //Serial.println(textBuffer);
            myGLCD.print(textBuffer,x,y);
            y=y+dec;
        }
        else
          Serial.println("** ERROR: File is empty...");
      }
      file.closeFile();
    }
    else
    {
      switch(res)
      {
        case ERROR_ANOTHER_FILE_OPEN:
          Serial.println("** ERROR: Another file is already open...");
          break;
        default:
          Serial.print("** ERROR: ");
          Serial.println(res, HEX);
          break;
      }
    }
  }
  else
    Serial.println("** ERROR:  does not exist...");
  Serial.println("***** All done... *****");

}


int draw_elt(int x,int y,String description, String value,String unit, int r,int g, int b)
{
  myGLCD.setFont(BigFont);
  myGLCD.setColor(r, g, b);
  myGLCD.print(String(description+":"+value+unit),x,y);
  myGLCD.setColor(255, 0, 255);
  myGLCD.setFont(SmallFont);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// char* label  //display
// unsigned int value  //
// min
// max
//list 0-Desactive 1-activé
// type  unsigned int
//      
int menu_list(int nbEntry,list_data list[])
{
  int nbEltMax;  //number of possible line in the menu
  int nbElt;  //number ofline in the menu
  int dec,x,y, shift, select;
  struct icon mode_icon_tab[4];
  int res;
  myGLCD.setColor(0,0,255);

  mode_icon_tab[0].pos_x=0;
  mode_icon_tab[0].pos_y=239-64;
  mode_icon_tab[0].picsize_x=64;
  mode_icon_tab[0].picsize_y=64;
  mode_icon_tab[0].icon_file="prev-64.RAW";  
  mode_icon_tab[0].text=""; 

  mode_icon_tab[1].pos_x=84;
  mode_icon_tab[1].pos_y=239-64;
  mode_icon_tab[1].picsize_x=64;
  mode_icon_tab[1].picsize_y=64;
  mode_icon_tab[1].icon_file="edit-64.RAW";  
  mode_icon_tab[1].text=""; 

  mode_icon_tab[2].pos_x=168;
  mode_icon_tab[2].pos_y=239-64;
  mode_icon_tab[2].picsize_x=64;
  mode_icon_tab[2].picsize_y=64;
  mode_icon_tab[2].icon_file="home-64.RAW";  
  mode_icon_tab[2].text=""; 

  mode_icon_tab[3].pos_x=319-64;
  mode_icon_tab[3].pos_y=239-64;
  mode_icon_tab[3].picsize_x=64;
  mode_icon_tab[3].picsize_y=64;
  mode_icon_tab[3].icon_file="next-64.RAW";  
  mode_icon_tab[3].text=""; 
  
  x=10;
  dec=20; // space between line
  shift=0; // scoll shift 
  select=0; //by default select the first line
  myGLCD.setFont(BigFont);
  nbEltMax=((myGLCD.getDisplayYSize()-74)/myGLCD.getFontYsize())-2;
  
  myGLCD.clrScr(); //clear the screen
  if (nbEntry<nbEltMax) 
    nbElt=nbEntry;
    else
    nbElt=nbEltMax;
    
  // wrote list

 while (true)
 {
   y=10; // start to write on the top of the screen
  for (int i=0;i<nbElt;i++)
  {
    if (i+shift==select) //wrote the selected line
    {
          if (list[i+shift].list[0]!="") // data is a list element  
          {
            if (list[i+shift].value>list[i+shift].maxi) list[i+shift].value=list[i+shift].maxi;
             draw_elt(x,y,list[i+shift].description,list[i+shift].list[(int) list[i+shift].value],"",255,0,0);
          }
          else
             draw_elt(x,y,list[i+shift].description,String(list[i+shift].value),list[i+shift].unit,255,0,0);
    }
   
    else
    { //wrote unselected line
    if (list[i+shift].list[0]!="") // data is  a list element  
           draw_elt(x,y,list[i+shift].description,list[i+shift].list[(int) list[i+shift].value],"",0,0,255);
      else
      draw_elt(x,y,list[i+shift].description,String(list[i+shift].value),list[i+shift].unit,0,0,255);
    }
    y=y+dec;
  }
  
  res=flotting_icon_menu(4, mode_icon_tab);
  switch (res)
  {
   case 0: //prev
   if (select>0) select--;
   if (select<shift)
     if (shift>0) {
         shift--;
         myGLCD.setColor(0,0,0);
         myGLCD.fillRect(1,1,319,173); //clear text part
         myGLCD.setColor(0,255,0);
     }

  break;
   case 1: //edit
     myGLCD.clrScr(); //clear screan
     //if (list[select].list[4]=="Sensor")
     if (list[select].maxi==list[select].mini)
     {
       list[select].value=menu_edit_sensor_uint(list[select].maxi,list[select].description, list[select].value);
     }
     
     else
     {
       if (list[select].list[0]!="")
       {
           list[select]=menu_edit_list(list[select]);
       }
       else
       {     
          list[select]=menu_edit_unsigned_int(list[select]);
       }
     }
     myGLCD.clrScr();
  break;
   case 2: //home
   myGLCD.clrScr(); //clear screan
   return (0);
  break;
   case 3: //next
   select++;
   if (select>=nbEntry) select=nbEntry-1;
   if (select>(nbElt+shift-1)) 
     {
        shift++; //need scroll
        myGLCD.setColor(0,0,0);
        myGLCD.fillRect(1,1,319,173); //clear text part
        myGLCD.setColor(0,255,0);

     }
  break;
  
  }    
 }  
}
////////////////////////////////////////////////////////////////////////////////////////

list_data menu_edit_list(list_data data)
{
  struct list_data ret;
  struct icon mode_icon_tab[6];
  for (int i=0;i<5;i++)
  {
    mode_icon_tab[i].pos_x=20;
    mode_icon_tab[i].pos_y=20+i*((239-64-20)/5);
    mode_icon_tab[i].picsize_x=319-mode_icon_tab[i].pos_x;
    mode_icon_tab[i].picsize_y=((239-64-20)/5);
    mode_icon_tab[i].icon_file="";
    mode_icon_tab[i].text=data.list[i]+" ";
  } 
    
  // icon OK on bottom right
  mode_icon_tab[5].pos_x=319-64;
  mode_icon_tab[5].pos_y=239-64;
  mode_icon_tab[5].picsize_x=64;
  mode_icon_tab[5].picsize_y=64;
  mode_icon_tab[5].icon_file="valid-64.RAW";  
  mode_icon_tab[5].text=""; 
  //put select icon to the right line
  for (int i=0;i<5;i++)
  {
    if (data.value==i)  draw_icon(1, 20+i*((239-64-20)/5), 20, 20, "sel-20.RAW");
    else
    {
        myGLCD.setColor(0,0,0);
        myGLCD.fillRect(1,20+i*((239-64-20)/5),20,40+i*((239-64-20)/5)); //clear text part
        myGLCD.setColor(0,255,0);
    }
  }
  
   while (true)
 {
   res=flotting_icon_menu(6, mode_icon_tab);
   if (res<5)
   {
     if (res<=data.maxi) data.value=res;
      for (int i=0;i<5;i++)
    {
      if (data.value==i)  draw_icon(1, 20+i*((239-64-20)/5), 20, 20, "sel-20.RAW");
      else
      {
          myGLCD.setColor(0,0,0);
          myGLCD.fillRect(1,20+i*((239-64-20)/5),20,40+i*((239-64-20)/5)); //clear text part
          myGLCD.setColor(0,255,0);
      }
     }
   }
   
   if (res==5)
     {
     myGLCD.clrScr(); //clear the screen
     ret=data;
     return(ret);
     }
 }
}


list_data menu_edit_unsigned_int(list_data data)
{
  struct list_data ret;
  ret=data;
  struct icon mode_icon_tab[12];
  for (int i=0;i<10;i++)
  {
    mode_icon_tab[i].pos_x=(64*i)%320;
    mode_icon_tab[i].pos_y=45+(i/5)*64;
    mode_icon_tab[i].picsize_x=64;
    mode_icon_tab[i].picsize_y=64;
    mode_icon_tab[i].icon_file="";
    mode_icon_tab[i].text=String(i);
  }
 
    
  // icon OK on bottom right
  mode_icon_tab[10].pos_x=319-64;
  mode_icon_tab[10].pos_y=239-64;
  mode_icon_tab[10].picsize_x=64;
  mode_icon_tab[10].picsize_y=64;
  mode_icon_tab[10].icon_file="valid-64.RAW";  
  mode_icon_tab[10].text=""; 
  
  // back
  mode_icon_tab[11].pos_x=0;
  mode_icon_tab[11].pos_y=239-64;
  mode_icon_tab[11].picsize_x=64;
  mode_icon_tab[11].picsize_y=64;
  mode_icon_tab[11].icon_file="del-64.RAW";  
  mode_icon_tab[11].text=""; 
  
  myGLCD.setFont(BigFont);
  myGLCD.print("Edit "+ret.description, 0, 1);
  myGLCD.print("mini: "+String(ret.mini), 80, 239-64);
  myGLCD.print("maxi: "+String(ret.maxi), 80, 239-64+20);
   while (true)
 {
     myGLCD.setFont(BigFont);
     myGLCD.print("Valeur :"+String(ret.value)+ret.unit+"  ", 0, 20);
     myGLCD.setFont(SmallFont);
   res=flotting_icon_menu(12, mode_icon_tab);
   if (res<10)
   {
      ret.value=ret.value*10+res;
      if (ret.value>ret.maxi) ret.value=ret.maxi;
   }
   
   if (res==11) //delete
            ret.value=ret.value/10;
 
    if (res==10) //valide
              return (ret); 
   
 }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int flotting_icon_menu_sensor(int nbmenu, struct icon  icon_tab[],int level, int readPin) {
int maxi=1;  
int value = nbmenu+1;
unsigned int sensorValue;
unsigned int old_sensorValue;
unsigned int memory_sensor[10];

sensorValue=0;
for (int i=0;i<10;i++)
      memory_sensor[i]=1;

// draw icon
for (int i=0; i<nbmenu; i++)
  {
     String Filename;
     char filename[13];
     Filename=icon_tab[i].icon_file;
     Filename.toCharArray(filename,13);
     res=draw_icon(icon_tab[i].pos_x, icon_tab[i].pos_y, icon_tab[i].picsize_x, icon_tab[i].picsize_y, filename);  
  }
  while(value>nbmenu)
  {
    long x, y;
  
    // read sensor value
    sensorValue= sensor_read(readPin)>>4;
    if (sensorValue>60) sensorValue=60; // limitation
    for (int i=0;i<9;i++)
      memory_sensor[i]=memory_sensor[i+1];
    memory_sensor[9]=sensorValue;
    old_sensorValue=maxi;
    
    maxi=memory_sensor[0];
    for (int i=0;i<10;i++) 
      if (maxi<memory_sensor[i]) maxi=memory_sensor[i];
    // delete old sensor grath
    myGLCD.setColor(0, 0, 0);
    if (old_sensorValue<maxi)
        myGLCD.fillRect(10+old_sensorValue*5,100,10+maxi*5,140);
        else
         myGLCD.fillRect(10+maxi*5,100,10+old_sensorValue*5,140);
    
    //draw new sensor graph
    myGLCD.setColor(0, 255, 0);
    if (maxi<level)
      myGLCD.fillRect(10,100,10+maxi*5,140);
      else
      myGLCD.fillRect(10,100,10+level*5,140);
    //draw in green value over the level
    if (maxi>level)
    {
       myGLCD.setColor(255, 0, 0);
       myGLCD.fillRect(level*5,100,10+maxi*5,140);
       buzzer_beep(10); 
    }

    while (myTouch.dataAvailable() == true)
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x!=-1) and (y!=-1))
      {
        for (int i=0; i<nbmenu; i++)
           if (((x>=icon_tab[i].pos_x) and (x<=(icon_tab[i].pos_x+icon_tab[i].picsize_x))) and ((y>=icon_tab[i].pos_y) and (y<=(icon_tab[i].pos_y+icon_tab[i].picsize_y))) ) value=i;          
        if (value<nbmenu)  return(value);
      }
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int  menu_edit_sensor_uint(int readPin,String title, unsigned int init_level)
{
  unsigned int level;
  
  struct icon mode_icon_tab[3];
  level=init_level;    
  // icon OK on bottom right
  mode_icon_tab[0].pos_x=319-64;
  mode_icon_tab[0].pos_y=239-64;
  mode_icon_tab[0].picsize_x=64;
  mode_icon_tab[0].picsize_y=64;
  mode_icon_tab[0].icon_file="valid-64.RAW";  
  mode_icon_tab[0].text="";  
  
  // -
  mode_icon_tab[1].pos_x=24+64;
  mode_icon_tab[1].pos_y=239-64;
  mode_icon_tab[1].picsize_x=64;
  mode_icon_tab[1].picsize_y=64;
  mode_icon_tab[1].icon_file="down-64.RAW";  
  mode_icon_tab[1].text=""; 
  
  // +
  mode_icon_tab[2].pos_x=2*(24+64);
  mode_icon_tab[2].pos_y=239-64;
  mode_icon_tab[2].picsize_x=64;
  mode_icon_tab[2].picsize_y=64;
  mode_icon_tab[2].icon_file="up-64.RAW";  
  mode_icon_tab[2].text=""; 
    
  myGLCD.clrScr(); //clear the screen
  myGLCD.setFont(BigFont);
  myGLCD.print(title, 0, 1);
   while (true)
 {
   res=flotting_icon_menu_sensor(3, mode_icon_tab,level,readPin);
   if (res==2) //+
      level=level+2;
   
   if (res==1) //-
               level=level-2;
 
    if (res==0) //valide
              {
                 myGLCD.clrScr(); //clear the screen
                 return (level); 
              }
   
 }
}
