/***************Seven Segments***************/
/***************Connections******************/
/**********		SS data --- PORT 0	    ******/
/**********		SS control --- PORT 1/2	******/
#include<reg51.h>
char arr[10]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};

/*
	(dp)gfedcba decides which segment (from provided 8 segment) to be active according to the bits that are set
	(here dp means decimal point)

	0xbf = '0.'
	0x86 = '1.'
	0xdb = '2.'
	0xcf = '3.'
	0xe6 = '4.'
	0xed = '5.'
	0xfd = '6.'
	0x87 = '7.'
	0xff = '8.'
	0xef = '9.'
*/

// Counter from 0.0.0.0. to 9.9.9.9.


void delay(void);
void main(void)
{
	int i,j,k,l,m;	
	for(l=0;l<10;l++)
	{
		for(k=0;k<10;k++)
		{
			for(j=0;j<10;j++)
			{
				for(i=0;i<10;i++)
				{
					for(m=0;m<50;m++)
					{
					P2=0x01;   // chooses rightmost display
					P0=arr[i];	 // sending data
					
					delay();
					P2=0x02;   // chooses 2nd display from right
					P0=arr[j];	   // sending data
					delay();
					P2=0x04;   // chooses 3rd display from right
					P0=arr[k];	   // sending data
					
					delay();
					P2=0x08;   // chooses leftmost display
					P0=arr[l];	   //sending data
					delay();		   
					}
				}
			

			}
		
		}
	}
}
void delay(void)	  // Causes delay
{
	int f;
	for(f=0;f<50;f++);
}