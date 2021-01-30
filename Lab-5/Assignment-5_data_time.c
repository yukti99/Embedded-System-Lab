/*******************RTC************************/
/****************connections ******************/
/*********	LCD control --- PORT 0	**********/
/*********	LCD DATA ----- PORT 2   **********/
/*********	RTC SEC ---- PORT 1	    **********/


// Need this header file for harware specific code when we want to use hardware peripherals like ports, timers and uart
// including sfr registers for ports of the controller
#include<reg51.h>
#include<intrins.h>  // to include operations like -> __nop__

// unsigned -> The variable will be stored in internal data memory of controller
typedef unsigned char uchar; // user-defined data types -> char, long int and int
typedef unsigned long ulong;
typedef unsigned int  uint;

// defining macros for constants used in the code 
#define		TIMER_RELOAD (-921)
#define		port_delay() _nop_(), _nop_(), _nop_(), _nop_() // defines port delay as 4 "no-operation func"
#define		AVG	10

// sbit -> is used to define a special bit from SFR (special function register) memory
sbit  LRS		=   P0 ^ 0;  // P0 -> lcd control, this is for lcd register select (LED connected to port-0, 0th pin)
sbit  LEN		=   P0 ^ 1;  // this is for enabling lcd  (port 0, 1st pin)
sbit ICLK		=   P1 ^ 0;  // Interface clock  (port 1, 0th pin)
sbit IDAT		=   P1 ^ 1;  // Interface Data  (port 1, 1st pin) ; here a signal is set and then data is sent 

// global variables - time counters
uint count;
uchar rdata,edata;
uint time;
uchar second,minute,hour,day,date,month,year;

/*
The timer keeps ticking
It generates interrupt by reloading it with value of -921 -> TIMER_RELOAD
We can calculate the delay as follows
RegValue = TimerMax-((Delay/1.085) * 10^6)
The 16-bit register of Timer 0 is accessed as low- and high-byte, The low-byte register is called TL0 (Timer 0 low byte) 
and the high-byte register is called TH0 (Timer 0 high byte)
*/
void timer0(void)
interrupt 1 using 1
{
	count++;
	// loading initial values to timer
	TH0 = (uchar)(TIMER_RELOAD>>8); // TIMER_RELOAD is divided by 2^8
	TL0 = (uchar)TIMER_RELOAD; // TL0 assigned its previous val
}


void delay(uint n){
	n = count + n;
   	while (n != count); // delay loop n times or halt the program for sometime
} 

// to display in string format
// lcd is divided into bit addressable display buffer

/*
NOTE : 
LEN=1
lEN=0
acts as a falling edge-> enables triggers LCD to accept value in P2 (LCD data port)
*/
void dispstr(uchar *str, uchar stcol, uchar encol){
    uint q;
	if(stcol <= 15)
		P2 = 0x80 + stcol; // lcd data port, start for 0x80 for day, month and year
	else
		P2 = 0xB0 + stcol; // start from 0xB0 for hours, minutes and seconds
		
	LRS = 0;  // LCD is set in command mode
	LEN = 1;  // this will trigger the lcd to accept P2 value (Falling edge 1 to 0)
    LEN = 0;
    delay(1);  
	LRS = 1; // this enables LCD in data mode from command mode before
	q=0;
	for(; stcol <= encol; stcol++)
	{
		if(stcol == 16)
		{
			P2 = 0xB0 + stcol;// starting from 0xB0 address on the lcd screen 
			LRS = 0; // command mode 
			LEN = 1; // falling edge for lcd to  accept P2 value as P2 is lcd data port
		    LEN = 0;
			delay(1);
			LRS = 1; // again data mode enabled 
		}
		P2 = str[q]; // the data portof lcd to assigned value of str[q], which will be displayed on the lcd
		q++; // q as index incremented 
		LEN = 1;  // again a falling edge-> accept data from P2, whose value we just assigned
	    LEN = 0;
		delay(1); // provides a small delay
	}
}
// this function is for  displaying int, similar to dispstr function above 
void dispnum(uint no, uchar stcol, uchar encol){
	uchar temp[5]; // temp array of size 5 declared 
	uchar i; // char i declared 
	for (i = 0; i < 2; i++)	{
		temp[i] = no % 10;  // temp array is digits of int->n from right to left
		// E.g if no = 12, temp[0] = 2 and temp[1] = 1
		no /= 10;
	}
	if(stcol <= 15)
		P2 = 0x80 + stcol; // lcd data port, start for 0x80 for day, month and year
	else
		P2 = 0xB0 + stcol; // start from 0xB0 for hours, minutes and seconds
		
	LRS = 0; // LCD is in command mode now 
	// edge trigger provided to lcd 
	LEN = 1;
    LEN = 0;
    delay(1); // small delay 
	LRS = 1;  // this enables LCD in data mode from command mode before
	i = 1;
	for(; stcol <= encol; stcol++){
		P2 = temp[i] + 0x30; // P2 is assigned values present in temp from index 1 backwards 
		i--;
		LEN = 1; // triggers the display of P2 value on LCD screen as LCD is in data mode 
	    LEN = 0;
		delay(1); // small delay
	}
}

// to clear the LCD 
void clrlcd(){
	LRS = 0;  // LCD in command mode 
	P2 = 0x01; // least significant bit set so value = 1 -> clear screen command 
	LEN = 1; // enables the lcd, falling edge as trigger for LCD to accept the command 
	LEN = 0; // disables the lcd
	delay(6);
}

void str1307(void){
   IDAT = 1 ; // Interface Data control signal is turned on 
   _nop_() , _nop_() , _nop_() ; // no operation 
   ICLK = 1 ; // Interface clock is switched on 
   _nop_() , _nop_() , _nop_() ;
   IDAT = 0 ; // Interface Data control signal is turned off
   _nop_() , _nop_() , _nop_() ;
   ICLK = 0 ; // Interface clock is switched on 
   _nop_() , _nop_() , _nop_() ;
}

// works opposite of str1307
void stp1307(void){
   IDAT = 0 ; // Interface Data control signal is turned off
   _nop_() , _nop_() , _nop_() ; // no operation to provide delay
   ICLK = 1 ; // Interface clock is switched on 
   _nop_() , _nop_() , _nop_() ;
   IDAT = 1 ; // Interface Data control signal is turned on 
   _nop_() , _nop_() , _nop_() ;
   ICLK = 0 ; // Interface clock is switched on 
   _nop_() , _nop_() , _nop_() ;
}
// clock -> used for data synchronisation
void clock(void){

   _nop_() ; _nop_() ; _nop_() ;
   ICLK = 1 ; 
   _nop_() ; _nop_() ; _nop_() ;
   ICLK = 0 ;
   _nop_() ; _nop_() ; _nop_() ;
}
// Interface clock is switched on 
// acknowledgement of data sent to microcontroller
void ack1307(void){
    IDAT = 0 ;
    clock() ;
}

// Interface data is switched on 
// no/negative acknowledgement
void nack1307(void){
    IDAT = 1 ;
    clock() ;
}


 
void opdat(char rtcdata){
    char i ;
	for ( i = 0 ; i < 8 ; i++ ) {
		// if the least significant bit of rtcdata*2^7/6/5/4/3/2/1/0 is set, then IDAT=1 otherwise IDAT=0 
    	if (( rtcdata >> ( 7 - i ) ) & 0x01 )  
			IDAT = 1 ; 
    	else      
			IDAT = 0 ;
        clock() ;
   }
}
// this function waits for the acknoledgment signal
// if IDAT turn 0 means there has been a change..acknoledgment has come
void waitack(void){
//   watch() ;
   IDAT = 1 ; //  switching on interface data and interface clock 
   _nop_() , _nop_() , _nop_() ;
   while ( IDAT ) ; // waiting while IDAT=1 i.e no acknowledgement is there yet
   ICLK = 1 ; 
   _nop_() , _nop_() , _nop_() ;
   ICLK = 0 ; 
}

// this function waits for the acknoledgment signal
// if IDAT turn 0 means there has been a change..acknoledgment has come
void waitack(void){
//   watch() ;
   IDAT = 1 ; // clock is enabled-> no operation and a wait loop introduced to check of acknowledgement
   _nop_() , _nop_() , _nop_() ;
   while ( IDAT ) ; // waiting while IDAT=1 i.e no acknowledgement is there yet
   ICLK = 1 ; // once the acknowledgement arrives, enable->no operation->disabled
   _nop_() , _nop_() , _nop_() ;
   ICLK = 0 ;// setting interface clock to 0
}

//  get data 
char getdat(void){
   char i , dat ;
//   watch() ;
//Interface data control signal turned on
   IDAT = 1 ;
   _nop_() , _nop_() , _nop_() ;
   for ( i = 0 ; i < 8 ; i++ ){
      ICLK = 1 ;
      dat = ( ( ( dat << 1 ) & 0sxxfe ) | IDAT ) ;
	   _nop_() , _nop_() , _nop_() ;
      ICLK = 0 ;
 	   _nop_() , _nop_() , _nop_() ;
   }
   return dat ;
}

// get real time clock 
void getrtc(void){
   char rdata ;
//   watch() ;
   str1307() ;  // switches IDAT and ICLK
   opdat(0xd0) ;
   waitack() ;
   opdat(0x00) ;
   waitack() ; // waiting for acknowledgement 
   stp1307() ;
   _nop_() , _nop_() , _nop_() ;
   str1307() ;
   opdat(0xd1) ;
   waitack() ;
   rdata = getdat() ; // to get the date 
   ack1307() ; // acknowledgement of that data
   // second updated after acknowledgment 
   second = ( rdata & 0x7f) ;
   rdata = getdat() ;
   ack1307() ;
    // minute updated after acknowledgment 
	minute = ( rdata & 0x7f) ;
   rdata = getdat() ;
   ack1307() ;
    // hr updated after acknowledgment 
	hour = ( rdata & 0x3f) ;
   rdata = getdat() ;
   ack1307() ;
//   watch() ;
 // day updated after acknowledgment 
	day = ( rdata & 0x07) ;
   rdata = getdat() ;
   ack1307() ;
    // date updated after acknowledgment 
	date = ( rdata & 0x3f) ;
   rdata = getdat() ;
   ack1307() ;
    // month updated after acknowledgment 
	month = ( rdata & 0x1f) ;
   rdata = getdat() ;
   nack1307() ;
    // yr updated after acknowledgment 
	year = rdata ;
   stp1307() ;
}
// setting real time clock
void setrtc(void){
   char rdata ;
//   watch() ;
   str1307() ;
   opdat(0xd0) ;
   waitack() ;
   opdat(0x00) ;
   waitack() ;//wait for the acknowledgement after interface data is switched on
   rdata = ( second & 0x7f) ;
   opdat(rdata) ;
   waitack() ;
   rdata = ( minute & 0x7f) ;
   opdat(rdata) ;
   waitack() ;
   rdata = ( hour & 0x3f) ;
   opdat(rdata) ;
   waitack() ;
   rdata = ( day & 0x07) ;
   opdat(rdata);
   waitack();
   rdata = ( date & 0x3f);
   opdat(rdata) ;
   waitack() ;
   rdata = ( month & 0x1f);
   opdat(rdata);
   waitack() ;
   rdata = year ;
   opdat(rdata) ;
   waitack() ;
   stp1307() ;
}
// function that returns the BCD representation of unsigned char x
unsigned char bcdtime(unsigned char x){
    return ( ( ( x / 10 ) << 4 ) + ( x % 10 ) ) ;
}
// function that returns the binary representation of unsigned char x
unsigned char binarytime(unsigned char x){
    return ( ( ( x >> 4 ) * 10 ) + ( x & 0xf ) ) ;
}

void getrtc1(void){
    getrtc() ;
//    watch() ;
// convertin all time variables to binary representation after getrtc() function
    year = binarytime( year );
    month = binarytime( month );
    date  = binarytime( date );
    hour = binarytime( hour );
    minute = binarytime( minute );
    second = binarytime( second );
}

void setrtc1(void){
 //   watch() ;
 
   // converting all time variables to BCD representation and then calling setrtc() function  
    year   = bcdtime( year ) ;
    month  = bcdtime( month ) ;
    date   = bcdtime( date ) ;
    hour   = bcdtime( hour ) ;
    minute = bcdtime( minute ) ;
    second = bcdtime( second ) ;
    
    // setting real time clock 
    setrtc() ;
}

void io_open(void){
	LEN = 0;  // disable the lcd 
	
	// TMOD - timer mode control is an 8-bit register used for selecting timer or counter and mode of timers.
	// Lower 4-bits -> control operation of timer 0 or counter0
	// Higher 4-bits ->control operation of timer1 or counter1.
	TMOD = 0x21; //0010 0001 -> 33
	// TMOD = gate|c/t|m1|m0|gate|c1/t|m1|m0
	//			here m1 = 1 for timer1/c1 and m0 = 1 for timer0/c0
	// mode bits-> 10 for timer1/c1 -> 8-bit auto-reload mode 2^8=256 pulses
	// 01 for timer0/c0 -> 	16-bit 2^16= 65535 pulses	
	
	// INTERRUPT ENABLE REGISTER	
	IE = 0x92;   //1001 0010 -> 146
	// EA|-|-|ES|ET1|EX1|ET0|EX0
	// here EA=1->It disables all interrupts. When EA = 0 no interrupt will be acknowledged and EA = 1 enables the interrupt individually.
	//ES=1 -> Enables/disables serial port interrupt and ET0 = 1 -> Enables/disables timer0 overflow interrupt	
	
	// Serial port control register -> SM0|SM1|SM2|REN|TB8|RB8|TI|RI
	SCON = 0x50; //0101 0000 -> 80
	// SM1 = 1-> serial port mode 1 8 bit UAR + variable and  REN = 1 ->set/ clear by software to enable/disable reception
	
	REN = 1;     //Receiver Enable-> Set/clear to enable/disable receive operation
	TL0 = (uchar)TIMER_RELOAD; 	// loading initial values to timer
	TH0 = (uchar)TIMER_RELOAD >> 8; 	// multiply by 2^8
	TH1 = TL1 = 0xFA;
	TR0 = 1; //Timer0 Run Control Bit = 1 means, timer0 start 
	TR1 = 1;  //Timer1 Run Control Bit = 1 meand timer1 start 
}

void initlcd(void){
	LEN = 0; // disable lcd
	LRS = 0; // command mode
	delay(20); // provides delay 20  ms

    P2 = 0x30; // port2 assigned command value 
    LEN = 1;   // enable lcd
    delay(1); // small delay
    LEN = 0;   // disable lcd (falling trigger,  remains high for 1 microsec -> basically enables lcd to perform the command given throught PORT-2
    delay(6); 
  
    P2 = 0x30;  //funtion set -> 8-bit, 1 Line, 5x7 Dots
    LEN = 1;
    delay(1);
    LEN = 0;
    delay(6);

    P2 = 0x30; 
    LEN = 1;
    delay(1);
    LEN = 0;
    delay(6);

    P2 = 0x38;  //funtion set -> 8-bit, 2 Line, 5x7 Dots
    LEN = 1;
    delay(1);
    LEN = 0;
    delay(6);
 
    P2 = 0x0c8; // to turn the display off
    LEN = 1;
    delay(1);
    LEN = 0;
    delay(6);

    P2 = 0x01;  //to clear display;
    LEN = 1;
    delay(1);
    LEN = 0;
    delay(6);

   P2 = 0x06; // entry mode set
   LEN = 1;
   delay(1);
   LEN = 0;
   delay(6);

   P2 = 0x0c; //display  ON
   LEN = 1;
	delay(1);
   LEN = 0;
   delay(6);

}

void main(void){		
	io_open(); // initialise and start timers
	initlcd(); // initialize the LCD 
	clrlcd (); // clear if something written in LCD
	//dispstr("     ADVANCE    ",0,15);
	delay(2000); // delay loop -> to add a delay of 2000 microseconds
	
	// Initialise the global values/ time variables 
	minute = 52; 
	hour = 3;
	second = 1;
	date = 4;
	month = 5;
	year = 4;

	// convert all time counters to bcd format and set real time clock 
	setrtc1();
	////	getrtc1();
	
	// display date, months and year
	// display on the screen the date, month and year as they change over time 
	// while hrs, mins  and second will keep changing on the course of run of application 
	dispnum(date,1,2);
	dispnum(month,4,5);
	dispnum(year,7,8);
	
	//displaying string 
	dispstr("/",3,3);  // second argument <15 to display day, month and year
	dispstr("/",6,6); // since stcol and encol are equal, loop runs once to display "/" on screen 
	dispstr(":",18,18);
	dispstr(":",21,21);
	
	// declarations done till now
	// infinite loop maintains application
	while(1){
		getrtc1(); // keep changing the time for a real time clock
		dispnum(hour,16,17);  // keeps changing the time 
		dispnum(minute,19,20); // since arguments > 15-> we display hrs, minutes and seconds 
		dispnum(second,22,23);
	}
}
