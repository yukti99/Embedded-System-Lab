/*
 YUKTI KHURANA 
Question: a key(from 0 to 7) is pressed in hex keypad, and then that number is shown on LCD and a unique LED is also turned on for that corresponding number. 

 
This is an Embedded C-code (Atmel 898c51) to
display the pressed key of hex keypad on LCD and LED.

The program defines P1 as keypad_port, P2 as control port and P3 as data port
It then declared RS and E led pins

A delay1 function which has a for loop to provide sufficient delay in the program is defined
The program initiates the lcd at power on time
P0 is assigned to 0 - no light, no input goes to led initially
Then an infinite loop is written to scan keyboard character (0-7) using the keyscan
function which stores the entered key by user in variable 'key'
then cursor position is set at lcd using lcd_cmd function at 0xc0 ( the location where the character
is to be displayed)

Switch case to display different keys on lcd and turn on a unique led for that key
data_lcd function displayed the entered key on the lcd while P0 value is changed to switch on the
corresponding led. Then some delay is provided and loop breaks
Same is done for all cases for key from 0 to 7 to switch on different led's

*/

#include<reg51.h>
#define KEYPAD_PORT  P1
#define CONTROL  P2
#define DATA P3
// LED port P0

//control port2
// keypad connections 
sbit RS=P2^0;  // defining led pin
sbit E=P2^1;

#include"delay.h"
#include"lcd.h"
#include"keypad.h"
#include"reg51.h"

void delay1(){
	int i;
	for(i=0;i<=30000;i++); // delay loop 
}

void main(void){
  unsigned char key;
  init_lcd();                           //lcd init.
  cmd_lcd(0x80);                        //Set curser position
  string_lcd("Press Key : ");                 //Display string
  P0=0X00;                              //0 means no light  8 bit zero so no i/p goes to led
  while(1){
	// from keyscan function from keypad.h file 
    key = keyscan();   // scan keyboard, stores entered key by user in var 'key'
    cmd_lcd(0xc0); // set curser position, to write command at lcd port (location where the character is to be displayed)
	
    switch(key){
      case '0':
        data_lcd(key); //Display pressed key on lcd
        P0=0X01; 	   // binary value 01
		delay1(); // to provide some delay 
		break;
      case '1':
	  	data_lcd(key); //Display pressed key on lcd
        P0=0X02; 		   // binary value  10
		delay1(); // to provide some delay 
		break;
				        
      case '2':
	  	data_lcd(key); //Display pressed key on lcd
        P0=0X04; 		   // binary value 100
		delay1(); // to provide some delay 
		break;
				        
      case '3':
	  	data_lcd(key);//Display pressed key on lcd
        P0=0X08; 			  // binary value 1000
		delay1(); // to provide some delay 
		break;
				      
      case '4':
	  	data_lcd(key); //Display pressed key on lcd
        P0=0X10; 			// binary value 10000
		delay1(); // to provide some delay 
		break;
				       
 
	  case '5':
	  	data_lcd(key);//Display pressed key on lcd
        P0=0X20; 	   // binary value 100000
		delay1(); // to provide some delay 
		break;	                           
      
      case '6':
	  	data_lcd(key);//Display pressed key on lcd
        P0=0X40; 		// binary value 100000
		delay1(); // to provide some delay 
		break;
				        
      case '7':
	  	data_lcd(key); //Display pressed key on lcd
        P0=0X80; 		  // binary value 100000
		delay1(); // to provide some delay 
		break;
				        
      default:
        	break;
  }
  data_lcd(key); //Display pressed key on lcd
  }
}
