
              ////led------Port P0 ////

# include<reg51.h>
void delay();
void main(){	 
	char arr[8] = {0X11, 0X02, 0X04, 0X08, 0X80, 0X40, 0X20, 0X10};
	int i=0;
	while(1){
	    // for alternate led blinking, change step in for loop
		for(i=0;i<8;i+=1){
			P0 = arr[i];
			delay();
		}
	}
}
void delay(){
	int i;
	for(i=0;i<=30000;i++);
}

