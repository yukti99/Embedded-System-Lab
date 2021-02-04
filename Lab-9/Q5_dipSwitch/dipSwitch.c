#include<reg51.h>

/*
	The 8051 Development board has eight numbers of point LEDs, 
	connected with I/O Port lines (P0.0 – P0.7) to make port pins high. 
	Eight switches, connected with I/O port lines (P2.0 – P2.7) are used to control eight LEDs.
*/

sbit a=P0^0;
sbit b=P0^1;
sbit c=P0^2;
sbit d=P0^3;
sbit e=P0^4;
sbit f=P0^5;
sbit g=P0^6;
sbit h=P0^7;
sbit a1=P2^0;
sbit b1=P2^1;
sbit c1=P2^2;
sbit d1=P2^3;
sbit e1=P2^4;
sbit f1=P2^5;
sbit g1=P2^6;
sbit h1=P2^7;

void main(){	
	
	P0=0x00;	  // all LED are off initially
	P2=0x00;	  // all switches are off initially
	while(1)
	{ 
/*
	When any of the switch(a1,b1,c1,d1,e1,f1,g1,h1) is on i.e equals to 1 
	corresponding LED(a,b,c,d,e,f,g,h) should also be on i,e 1
*/

		if(a1==1)	
		{ 
			a=1;	
		}
		if(b1==1)
		{
			b=1; 
		}
		if(c1==1)
		{
			c=1;   
		}
		if(d1==1)
		{
			d=1;
		}

		if(e1==1)
		{
			e=1 ; 
		}
		if(f1==1)
		{
			f=1;   
		}
		if(g1==1)
		{
			g=1;
		} 
		if(h1==1)
		{
			h=1; 
		}

////////////////////////////////////////

/*
	When any of the switch(a1,b1,c1,d1,e1,f1,g1,h1) is off i.e equals to 0 
	corresponding LED(a,b,c,d,e,f,g,h) should also be off i,e 0
*/

		if(a1==0)
		{ 
			a=0;	
		}
		if(b1==0)
		{
			b=0; 
		}
		if(c1==0)
		{
			c=0;   
		}
		if(d1==0)
		{
			d=0;
		}

		if(e1==0)
		{
			e=0 ; 
		}
		if(f1==0)
		{
			f=0;   
		}
		if(g1==0)
		{
			g=0;
		} 
		if(h1==0)
		{
			h=0; 
		}

	} 
	
} 
