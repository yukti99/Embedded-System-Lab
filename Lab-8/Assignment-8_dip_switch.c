/*
YUKTI KHURANA
2017UCP1234
DIP - Dual-In-Line Package Switch: is actually set of small manual electronic 
switches that are designed to be packaged with other circuits.
This type of switch is designed to be used on a printed circuit board along with other electronic components 
and is commonly used to customize the behavior of an electronic device for specific situations. 
*/
#include<reg51.h>

// sbit -> is used to define a special bit from SFR (special function register) memory
// Port P0 is used to turn on LED
//  special bit a to h is assigned 8 different pins of LED Port-0
sbit a=P0^0;
sbit b=P0^1;
sbit c=P0^2;
sbit d=P0^3;
sbit e=P0^4;
sbit f=P0^5;
sbit g=P0^6;
sbit h=P0^7;

// Port P2 is used for dip switch
// DIP switches are also known as toggle switches, 
// which mean they have two possible positions - on or off.
// DIP switches usually have 8 switches.
// The following 8 switches are  defined as special registers from a1 to h1
sbit a1=P2^0; // a1 represents Pin 0 of Port P2 or switch-1 of dip
sbit b1=P2^1; 
sbit c1=P2^2;
sbit d1=P2^3;
sbit e1=P2^4;
sbit f1=P2^5;
sbit g1=P2^6;
sbit h1=P2^7;


void main(){
	// output configuration
	P0=0x00;// 0 means no light,  8 bit zero so no i/p goes to LED
	P2=0x00;
	while(1){ 
		// in the following way dip switch is providing manual control over LED
		// if dip switch-0 is enabled 
		if(a1==1)
		{ 
			a=1; // it will turn on LED-0	
		}
		// switch 1 of DIP is on meand Led-1 needs to be turned on 
		if(b1==1)
		{
			b=1; // it will turn on LED-1	
		}
		if(c1==1)
		{
			c=1; // it will turn on LED-2	 
		}
		if(d1==1)
		{
			d=1; // it will turn on LED-3
		}

		if(e1==1)
		{
			e=1 ; // it will turn on LED-4	
		}
		if(f1==1)
		{
			f=1;  // it will turn on LED-5 
		}
		if(g1==1)
		{
			g=1; // it will turn on LED-6	
		} 
		if(h1==1)
		{
			h=1; // it will turn on LED-7	
		}
		// if multiple switches of dip are turned on at a time, corresponding leds
		// will light up too

////////////////////////////////////////
		// if dip switch is turned off, the corresponding led must be turned off too to reflect the change
		if(a1==0)
		{ 
			a=0; // it will turn off LED-0
		}
		if(b1==0)
		{
			b=0; // it will turn off LED-1
		}
		if(c1==0)
		{
			c=0;   // it will turn off LED-2
		}
		if(d1==0)
		{
			d=0;// it will turn off LED-3
		}
		if(e1==0)
		{		
			e=0 ; // it will turn off LED-4
		}
		if(f1==0)
		{
			f=0;   // it will turn off LED-5
		}
		if(g1==0)
		{
			g=0;// it will turn off LED-6
		} 
		if(h1==0)
		{
			h=0; // it will turn off LED-7
		}
	}

} 
	
 

/*
OUTPUT:
This program is providing a manual control of turning LED's on and off by
using a dip switch to enable or disable led's by switching dip switches on or off.
whenever the dip switch is turned on, corresponding led lits up.

*/