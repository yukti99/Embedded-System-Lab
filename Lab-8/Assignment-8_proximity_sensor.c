#include<reg51.h>
//using Relay Buzzer
 ////relay buzzer------Port P0//////
/*
YUKTI KHURANA
2017UCP1234
A relay is an electromechanical switch, which perform ON and OFF operations without any
human interaction.
A proximity sensor is a sensor in a position to detect the presence of nearby objects without any physical get in touch with. 
A proximity sensor often emits an electromagnetic field or a beam of electromagnetic radiation (infrared, for instance), 
and looks for changes in the field or return signal. The object becoming sensed is usually referred to as the proximity sensor’s target.
*/

sbit a = P2^0;  //for proximity sensor,a will be 1 when it sense metal
sbit a1 = P0^0; //for relay buzzer

// to provide delay in the program 
void delay(){
	int j;
	for(j=0;j<20000;j++);
}
void main(){
	char k;
	// both the ports are initialised
	P2 = 0X0; 
	P0 = 0X0;
	while(1){	
		// a=1 means the proximity sensor has sensed something	
		while(a==1){
			P0 = 0x01; // it turns on buzzer 1 followed by a delay 
			delay();
			// other 3 buzzers are then turned off with delays in between whenever
			// the proximity sensor senses something 
			for(k=0;k<3;k++){
				P0 = P0 << 1; // left shift to turn on other buzzers
				delay();// to provide delay in between buzzer sounds 
			}
		}
	}
}
/*
The program will act like a metal detector which produes buzzer sound,
whenever the proximity sensor detects metal through it Port-2, pin 0.
So whenever the proximity sensor senses an object nearby, the buzzer is enabled to
indicate this.

*/


//Using Led 
/*
#include<regx51.h>
sbit a = P2^0;
sbit a1 = P0^0;  // led
void main()
{
	P2=0X0;
	 P0=0X0;
	while(1)
	{
		if(a==1)
			a1=1;
		if(a==0)
			a1=0;
	}
}
*/