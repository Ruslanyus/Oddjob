//main menu
int main_menu()
{
  int res;
  String files320[10]={"conf-64.RAW", "astro-64.RAW", "barri-64.RAW",  "slave-64.RAW", "inter-64.RAW", "marte-64.RAW", "sound-64.RAW","speed-64.RAW","water-64.RAW","help-64.RAW"}; // 320x240
  res=icon_menu(10, files320, 64,64);
  return(res);
}


//display Help menu
// one Home Icon to go to the home menu.
void help_menuP1()
{
  struct icon help_icon_tab[1];

  help_icon_tab[0].pos_x=319-64;
  help_icon_tab[0].pos_y=239-64;
  help_icon_tab[0].picsize_x=64;
  help_icon_tab[0].picsize_y=64;
  help_icon_tab[0].icon_file="home-64.RAW";  

  myGLCD.clrScr(); //clear the screen
  read_file("helpp1.txt",10,10,10); //display text
  flotting_icon_menu(1, help_icon_tab);
  myGLCD.clrScr(); //clear the screen after selection
  
}


//display mode menu
// run icon , return code 0
// config icon, return code 1
// Home Icon , return code 2.
//
int mode_menu(char* mode)
{
 
  struct icon mode_icon_tab[4];
  int res;

  mode_icon_tab[0].pos_x=80-32;
  mode_icon_tab[0].pos_y=120-32;
  mode_icon_tab[0].picsize_x=64;
  mode_icon_tab[0].picsize_y=64;
  mode_icon_tab[0].icon_file="run-64.RAW";  

  mode_icon_tab[1].pos_x=160-32;
  mode_icon_tab[1].pos_y=120-32;
  mode_icon_tab[1].picsize_x=64;
  mode_icon_tab[1].picsize_y=64;
  mode_icon_tab[1].icon_file="conf-64.RAW";  

  mode_icon_tab[2].pos_x=239-32;
  mode_icon_tab[2].pos_y=120-32;
  mode_icon_tab[2].picsize_x=64;
  mode_icon_tab[2].picsize_y=64;
  mode_icon_tab[2].icon_file="home-64.RAW";  
  
  myGLCD.clrScr(); //clear the screen
  myGLCD.setFont(BigFont);
  myGLCD.print(mode,CENTER,30);
  myGLCD.setFont(SmallFont);
  
  res=flotting_icon_menu(3, mode_icon_tab);
  myGLCD.clrScr(); //clear the screen
  return (res);
}



int menu_conf_system()
{
struct list_data list[4];
list[0].description="Buzzer";
list[0].value=system_useSpeaker;
list[0].mini=0;
list[0].maxi=1;
list[0].list[0]="Actif";
list[0].list[1]="Inactif";
list[0].list[2]="";
list[0].list[3]="";
list[0].list[4]="";

list[1].description="Flash Pulsing";
list[1].unit="ms";
list[1].value=system_flashPulsing;
list[1].mini=0;
list[1].maxi=100;
list[1].list[0]="";
list[1].list[1]="";
list[1].list[2]="";
list[1].list[3]="";
list[1].list[4]="";
  
list[2].description="AutoFocusTime";
list[2].unit="ms";
list[2].value=system_autofocusTime;
list[2].mini=0;
list[2].maxi=1000;
list[2].list[0]="";
list[2].list[1]="";
list[2].list[1]="";
list[2].list[2]="";
list[2].list[3]="";
list[2].list[4]="";

list[3].description="ShutterLagTime";
list[3].unit="ms";
list[3].value=system_shutterLagTime;
list[3].mini=0;
list[3].maxi=1000;
list[3].list[0]="";
list[3].list[1]="";


myGLCD.clrScr();
menu_list(4,list);

system_useSpeaker=list[0].value;
system_flashPulsing=list[1].value;
system_autofocusTime=list[2].value;
system_shutterLagTime=list[3].value;
}
