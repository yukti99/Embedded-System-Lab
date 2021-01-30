#include<reg51.h>
//////////// PIN DEFINED ///////////////
#define KEYPAD_PORT  P0
#define DATA P1
//control port2
sbit RS=P2^0;
sbit E=P2^1;
#include"delay.h"
#include"lcd.h"
#include"keypad.h"

void main(void)
{
  int counter=0;
  unsigned char key;
  init_lcd();                           //lcd init.
  cmd_lcd(0x80);                        //Set curser position
  string_lcd("Press key : ");        //Display string
  cmd_lcd(0xc0);
  while(1){        
        key = keyscan();                        //Scan keypad
		counter++;
		if (counter%15==0){
		 	counter = 0;
			 cmd_lcd(0xc0);
		}
        data_lcd(key);                                //Display pressed key on lcd
  }
}