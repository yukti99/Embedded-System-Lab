/***************Seven Segments***************/
/***************Connections******************/
/**********		SS data --- PORT 0	    ******/
/**********		SS control --- PORT 1/2	******/
#include<reg51.h>

// array of 10 hex values to represent 10 numbers from 0 to 9 in seven segment display
char arr[10]= {0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};
// declaration of delay function
void delay(void);

void main(void){
	int i,j,k,l,m;	
	for(l=0;l<10;l++){ // MSB value of number 
		for(k=0;k<10;k++){ // 2nd last LSB value of number 
			for(j=0;j<10;j++){ // 2nd LSB value of the number 
				for(i=0;i<10;i++){ // LSB digit value of the number 
					for(m=0;m<50;m++){
						// seven-segment control port 
						P2=0x01; // represent the postion of the LSB digit of the number 
						// seven-segment data port to display
						P0=arr[i]; // to display LSB on seven segment display 
												
						delay();// delay
						
						P2=0x02; // represents the position of second LSB digit of the number 
						P0=arr[j]; // to display tens digit on seven segment display
						delay();
						P2=0x04; // represents the position of the 2nd last LSB digit of the number 
						P0=arr[k]; // to display hundredth digit 
						
						delay();// delay
						P2=0x08; //represents the position of the MSB digit of the number 
						P0=arr[l]; // to display MSB on seven segment display 
						delay(); // delay after each digit display so that it can be seen properly 		   
					}
				}		

			}		
		}
	}
}
// to provide delay between display of digits for easy display 
void delay(void)
{
	int f;
	for(f=0;f<50;f++);
}
/*
OUTPUT: 

This program works like a counter from 0 to 9999 numbers 
It displays the digits on seven segment display using the 10 size array 
It displays the value of current count from least significant to most significant digit 

The outer loops represent digit places i.e
outermost loop->l represents the 4th MSB or thousandth place value
loop->k represents the 3rd MSB / digit or hundredth place value
loop->j represents the 2nd MSB / digit or tens place value
loop->i reprsents the LSB/ digit or ones place value

The innermost loop -> m  makes sure that all the digits of the current number is displaced on seven-segment one by one 
The loop runs 50 times so one number will persist for the time of 50 loop runs 
E.g

[similar to 
MSB = arr[l] & LSB = arr[i]
 printf("\ncount = %d%d%d%d\n",arr[l],arr[k],arr[j],arr[i]);  ]

(the digits from LSB to MSB are displayed on seven segment display )
LSB   MSB
0 0 0 0    ( in between there will be delays to represent all digits on seven segment display, persists for 50 runs )
1 0 0 0    ( the counter incremented to display number '1')
....
8 0 0 0
9 0 0 0

0 1 0 0  number -> 10
1 1 0 0  number -> 11
1 2 0 0
1 3 0 0
.....
1 9 0 0


0 2 0 0   number->0020 or 20
...

9 2 0 0  number->0029 or 29

..

4 5 8 0 number-> 0854 or 854

... and so on 

YUKTI KHURANA 
2017UCP1234

*/

