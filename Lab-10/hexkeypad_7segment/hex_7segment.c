/***************Seven Segments***************/
/***************Connections******************/
/**********		SS data --- PORT 0	    ******/
/**********		SS control --- PORT 2	******/
#include<reg51.h>
//////////// PIN DEFINED ///////////////
#define KEYPAD_PORT  P1
#include"delay.h"
#include"keypad.h"

void main(void){

	while(1)
	{	
		P2=0x02;   //7 segment display on 
	  	P0=keyscan(); //send code for number to be displayed
	    delay(30000);
	}
}