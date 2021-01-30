/*
#include<reg51.h>
//////////// PIN DEFINED ///////////////
#define KEYPAD_PORT  P1
#define DATA P1
//control port2
sbit RS=P2^0;
sbit E=P2^1;
#include"delay.h"
#include"lcd.h"
#include"keypad.h"
void main(void)
{
  unsigned char key;
  init_lcd();                           //lcd init.
  cmd_lcd(0x80);                        //Set curser position
  string_lcd("Press key : ");        //Display string
  while(1)
  {
        cmd_lcd(0xc0);
        key = keyscan();                        //Scan keypad
        data_lcd(key);                          //Display pressed key on lcd
  }
}
*/
//YUKTI KHURANA
// 2017UCP1234

#include<reg51.h>
#define KEYPAD_PORT  P1
#define CONTROL  P2
#define DATA P3

//control port2
sbit RS = P2^0; // Register select, port-2, pin 0
sbit E  = P2^1; // Enable, port-2, port-2, pin 1
#include <string.h>
#include "delay.h"
#include "lcd.h"
#include "keypad.h"
#include "reg51.h"
//////////// PIN DEFINED ///////////////

// to provide delay in the program 
void delay1(){
	int i;
	for(i=0;i<=30000;i++);
}

void main(void){
  unsigned char key;
  // in the below string st, the left blank spaces are from 0 to 15 -> 16
  // words from index 16 to 52 -> 37 
  // right blanks from 53 to 68 -> 16
  char st[] = "                Listen student of mnit !! HI From Us.                ";
  int len = strlen(st);
  int i;
  len-=32; // this is the length of just non-blank characters
  i = 0x0;
  // function to initialize the LCD at power on time
  init_lcd(); // initialisation of lcd     
  P0 = 0X00;  // 0 means no light,  8 bit zero, so no i/p goes to led
  // starting program/application

  while(1) {
    cmd_lcd(0x80); // function to write command at lcd port 
    // this command is used to Force cursor to the beginning of  1st line
   
	if(i>=16 && i<=32+len)
		// decreasing the left spaces one by one when i becomes greater than 16
      string_lcd(st+(i-16)); // display this string on lcd
    else{
    	// if i<16, st+i is a blank space char
    	string_lcd("                ");
	}      
    cmd_lcd(0xc0); // to force cursor to the beginning of 2nd line
    if (i>=0 && i<=16+len){
      // printing from ith index onwards whole string 
      string_lcd(st+i); // to print 
	}
    else{
    	//  blank string printed when i reaches right blank spaces index
      string_lcd("                ");
	}
    delay1(); // to provide delay in the program  
    i++;
    i = i%(len+32); // i should be set to 0 after it becomes greater than actual length of string st
  }
}
/*
OUTPUT:
this programs gives an impression of the whole string "Listen student of mnit !! HI From Us."
moving on the screen from right to left like an Advertisement board. It appears to disappear on the left and starts coming in again from right 
continuously on the lcd screen 
*/
