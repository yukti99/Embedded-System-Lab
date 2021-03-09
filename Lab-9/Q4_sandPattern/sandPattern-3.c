
              ////led------Port P0 ////

# include<reg51.h>
void delay();
void main()
{	 while(1)
{
P0=0X11;
delay();
P0=0X22;
delay();
P0=0X44;
delay();			
P0=0X88;
delay();
}}
void delay()
{
int i;
for(i=0;i<=30000;i++);
}
