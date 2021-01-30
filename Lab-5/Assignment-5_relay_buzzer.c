/*  relay buzzer------Port P1 */
#include<reg51.h>

// delay loop till 20000
void delay(){
	int j;
	for(j=0;j<20000;j++); 
}

void main(){ 
	char k;
	//  infinite loop 
	while(1){
		P1=0x01;  // binary value 01 -> Relay switch on 
		delay(); // provides some delay in the program
		for(k=0;k<3;k++){
			//left shift here is used to amplify the buzzer intensity after each loop because
			// "<<" = P1's value being multiplied by 2 each time the loop runs 
			P1=P1<<1; 
			delay();  // provides delay for visible changes 
		}
	}
}
