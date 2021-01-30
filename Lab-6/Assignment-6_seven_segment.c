/***************Seven Segments***************/
/***************Connections******************/
/**********		SS data --- PORT 0	    ******/
/**********		SS control --- PORT 2	******/

// YUKTI KHURANA
// 2017UCP1234
#include<reg51.h>
// _gfedcba
char arr[10]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};
void delay(void); // delay function

void main(void){
	int a;
	// application starts
	while(1)	{	
		// loop runs 9 times for 9 digits to be displayed on 7-segment display
 		for(a=0;a<10;a++) 		{
 			P2=0x02;  // seven segment control port
		  	P0=arr[a]; // seven segment data port
			delay();  // to provide delay between display of digits
	  		delay();
		    delay();
		}
	}
}
//       DP G F E D C B A (for seven segment display), DP-> point 
// 0xbf = 1 0 1 1 1 1 1 1 -> digit 0.
// 0x86 = 1 0 0 0 0 1 1 0 -> digit 1.
// 0xdb = 1 1 0 1 1 0 1 1 -> digit 2.
// 0xcf = 1 1 0 0 1 1 1 1 -> digit 3.
// 0xe6 = 1 1 1 0 0 1 1 0 -> digit 4.
// 0xed = 1 1 1 0 1 1 0 1 -> digit 5.
// 0xfd = 1 1 1 1 1 1 0 1 -> digit 6.
// 0x87 = 1 0 0 0 0 1 1 1 -> digit 7.
// 0xff = 1 1 1 1 1 1 1 1 -> digit 8.
// 0xef = 1 1 1 0 1 1 1 1 -> digit 9.
// (for common cathode display, for common anode display the bits 
// we'll have to take the complement of each bit and replace the hexadecimal values in the code )

/*
   a
 _____
f|   |b
   g
 _____
e|   |c
 _____  . DP
   d

*/

// to provide delay in program
void delay(void){
 	int f;
 	for(f=0;f<30000;f++);//  wait loop 
}

/*
OUTPUT:
all digits from 0 to 9, as the data port of seven segment 
display is assigned above hex values, whose binary representation
corresponds to different bit values of 8 LED's a,b,c,d,e,f,g,dp of seven
segment displays and lights up the respected LEDS  to form 
the numbers from 0 to 9, with equal delay in the display of each number
so that changing digits on seven segment display is easily visible

OUTPUT:
0.
1.
2.
3.
4.
5.
6.
7.
8.
9.

*/
