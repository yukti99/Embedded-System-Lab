////relay buzzer------Port P1//////
#include<reg51.h>
void delay()
{
	int j;
	for(j=0;j<2000;j++);
}
void main()
{ 
	char k;
	while(1)
	{
		P1=0x01;
		delay();
		for(k=0;k<3;k++)
		{
			delay();delay();delay();
			P1=P1<<1;
			delay();
			delay();
			delay();
		}
	}
}
