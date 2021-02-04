
              ////led------Port P0 ////

# include<reg51.h>
void delay();
void main()	{
	 while(1){
			P0=0X01;
			delay();
			P0=0X03;
			delay();
			P0=0X07;
			delay();			
			P0=0X0F;
			delay();
		}
}
void delay(){
	int i;
	for(i=0;i<=30000;i++);
}
