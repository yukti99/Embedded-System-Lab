#include<reg51.h>
//////////// PIN DEFINED ///////////////
#define KEYPAD_PORT  P1
#define CONTROL  P2
#define DATA P3
//control port2
// sbit -> is used to define a special bit from SFR (special function register) memory
sbit RS = P2^0; // Register Select at control Port-P2, pin 0
sbit E = P2^1; // Enable at control Port-P2, pin 1
#include"delay.h"
#include"lcd.h"
#include"keypad.h"
#include"reg51.h"

//convert char into int
int get_num(char ch){
	switch(ch){
		case '0': return 0; break; // return integer value of given character 
		case '1': return 1; break;
		case '2': return 2; break;
		case '3': return 3; break;
		case '4': return 4; break;
		case '5': return 5; break;
		case '6': return 6; break;
		case '7': return 7; break;
		case '8': return 8; break;
		case '9': return 9; break;
		
	}
}
// to provide delay in the program 
void delay1(){
	int i;
	for(i=0;i<=30000;i++);
}
void print(int temp){
 	char arr[10]; // character array to store the char values of integer digits
	int i=0,j=0;
	if(temp==0){
		// if data to be printed is '0' on lcd screen 
	    data_lcd(48); // this function writes data to LCD port P1
		return;
	}
	while(temp!=0){
		int w;
		w = temp%10; // w is the remainder or last digit of temp integer
		// 48 stands for '0', to convert int to char 
		arr[i]=w+48;
		i++; // counter for the no of digits in temp variable 
		temp=temp/10; // to traverse other digits 
	}	 
	// i is a counter to keep track of length of the array->arr
	j=i-1; // j is assigned the last index of array to traverse array from right to left in reverse order
	while(j>=0){
		data_lcd(arr[j]); // write data in array-arr in reverse order to LCD port i.e in actual order from left digit to right of temp variable 
		j--; // counter decremented 
	}
}
/*
E.g. output of print(2345) -> 2 3 4 5 on lcd screen, to print the result of
calculation on the lcd screen 
*/

void main(void){
	
  unsigned char key1,key2,key3; // char input from keyboard
  
  init_lcd(); // to initialise the LCD at power on time
  cmd_lcd(0x80);  // set LCD cursor position                   
  string_lcd("Calculator:"); // will display the string "Calculator" on the LCD screen
  
  P0=0X00;  //0 means no light  8 bit zero so no i/p goes to led
  
  while(1){
  	int n1=0;
	int n2=0;
	// keyscan() function is used to get key pressed by the user	
	key1 = keyscan(); // operand 1
	key2 = keyscan(); // operation type-> A,B,C,D
	key3 = keyscan(); // operand 2
	
	// to calculate the result of an operation operands must be first converted to int form 	
    n1 = get_num(key1); // returns the integer value of character key input 
	n2 = get_num(key3);   
	cmd_lcd(0xc0); // set LCD cursor positions
	
	
    /* key 2 defines the Calculator operation that needs to be performed between operands key1 and key 2 using switch case
	   'A'-> Addition
	   'B'-> Subtraction
	   'C'-> Multiplication
	   'D'-> Division 			
	*/
	switch(key2){
    	case 'A':
			//data_lcd(n1+n2+48);
			data_lcd(key1); // display the 1st key i.e. operand 1 pressed on LCD
			string_lcd("+"); // then displays '+' sign for addition 
			data_lcd(key3); // displays 2nd key pressed or operand 2 
			string_lcd("="); // display = sign to form expression 
			print(n1+n2); // result of addition 
    		P0 = 0X01; // led is turned on to show that result has been displayed
			delay1();
			break;
		case 'B':
			//data_lcd(n1-n2+48);
			data_lcd(key1); // display the 1st key i.e. operand 1 pressed on LCD
			string_lcd("-"); //then displays '-' sign for subtraction
			data_lcd(key3); // displays 2nd key pressed or operand 2 
			string_lcd("=");
			// result of subtraction
			if(n1<n2){ // if operand-1 is smaller than operand-2 then result of subtraction will be negative and hence a '-' needs to be displayed on lcd
				string_lcd("-");  
				print(n2-n1); // result 
			}
			else{
				print(n1-n2); // else positive result 
			}
    		P0 = 0X02;  // led is turned on to show that result has been displayed
			delay1(); // provides delay in the program 
			
			break;
    	case 'C':
			//data_lcd(n1*n2+48);
			data_lcd(key1);  // display the 1st key i.e. operand 1 pressed on LCD
			string_lcd("*"); // then displays '*' sign for multiplication
			data_lcd(key3); // displays 2nd key pressed or operand 2 
			string_lcd("=");
			// result of multplication
			print(n1*n2);
    		P0 = 0X04;
			delay1(); // provides delay in the program 
			
			break;
    	case 'D':
			//data_lcd(n1/n2+48);
			data_lcd(key1); // display the 1st key i.e. operand 1 pressed on LCD
			string_lcd("/"); // then displays '/' sign for addition 
			data_lcd(key3); // displays 2nd key pressed or operand 2 
			string_lcd("=");
			// result of division
			if(n2!=0)
				print(n1/n2);
			else // if second operand is zero, division will be undefined, so provides a check for that 
				string_lcd("div by 0"); 
    		P0 = 0X08;  // led is turned on to show that result has been displayed
			delay1(); // provides delay in the program 
			
			break;
    		
    	default:
    		break; // end 
	}
    //data_lcd(key);    //Display pressed key on lcd
  }
}

/*
The above program works like a simple calculator in which user presses 3 keys 
operand1 -> key 1
operation-> key 2
operand2 -> key 3

Then the result of above input is displayed on LCD as:
a + b = result ,or
a - b = result ,or
a * b = result ,or
a / b = result

Example:
input keys: 
2 C 3
LCD -> 2 * 3 = 6
input keys: 
5 D 0
LCD -> 5 / 0 = div by 0
input keys: 
4 B 8
LCD -> 4 - 8 = -4
input keys: 
6 A 3
LCD -> 6 + 3 = 9

After result is displayed, operation-specific led is turned on

YUKTI KHURANA
2017UCP1234 

*/
