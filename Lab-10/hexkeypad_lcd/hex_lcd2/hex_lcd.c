#include<reg51.h>
//////////// PIN DEFINED ///////////////
#define KEYPAD_PORT  P0
#define DATA P1
//control port2
sbit RS=P2^0;
sbit E=P2^1;


 void delay(int num)
{
int a;
for(a=0;a<=num;a++);
}

 void delay1()
{
int a;
for(a=0;a<=1000;a++);
}



unsigned char keyscan()
{
  while(1)
  {
        KEYPAD_PORT = 0XeF;
        delay(1000);  /////must for response at port when key press
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return 'C';}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return '8';}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return '4';}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return '0';}

        KEYPAD_PORT = 0XdF;
        delay(1000);
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return 'D';}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return '9';}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return '5';}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return '1'  ;}

        KEYPAD_PORT = 0XbF;
        delay(1000);
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return 'E';}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return 'A';}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return '6';}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return '2';}

        KEYPAD_PORT = 0X7F;
        delay(1000);
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return 'F';}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return 'B';}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return '7';}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return '3';}
   }
}

void cmd_lcd (unsigned char dat)    // function to write command at lcd port
{
DATA=dat;
RS=0;  //clear RS (ie. RS=0) to write command
E=1;  // send  H-L pulse at E pin
delay(100);
E=0;
delay(100);
}

void data_lcd (unsigned char dat) // function to write data at lcd port
{
DATA=dat;
RS=1; // set RS=1 to write DATA
E=1;  // send  H-L pulse at E pin
delay(100);
E=0;
delay(100);  
}

void init_lcd()         // function to initialize the LCD at power on time
{
cmd_lcd(0x38); // 2x16 display select
delay(50000);
cmd_lcd(0x0c); // display on cursor off command
delay(1000);
cmd_lcd(0x06); // automatic cursor movement to right
delay(1000);
cmd_lcd(0x01); // lcd clear command
delay(5000);
}

void string_lcd(unsigned char *str)   // function to display string to lcd
{
while(*str!='\0')   // '\0' is null char as last char of pointer is null
{
data_lcd(*str);
str++;
}
 }

void main(void)
{
  unsigned char key;
  init_lcd();                           //lcd init.
  cmd_lcd(0x80);                        //Set curser position
  string_lcd("Press key : ");        //Display string
  while(1)
  {
        cmd_lcd(0xc0);
        key = keyscan();                        //Scan keypad
        switch(key){
          case '0':
data_lcd(key);                                //Display pressed key on lcd
            P0 = 0X01; // Turning on 1st led
            delay1();
            break;
          case '1':
data_lcd(key);                                //Display pressed key on lcd
            P0 = 0X02; // Turning on 2nd led
            delay1();
            break;
          case '2':
data_lcd(key);                                //Display pressed key on lcd
            P0 = 0X04; // Turning on 3rd led
            delay1();
            break;
          case '3':
data_lcd(key);                                //Display pressed key on lcd
            P0 = 0X08; // Turning on 4th led
            delay1();
            break;
          case '4':
data_lcd(key);                                //Display pressed key on lcd
            P0 = 0X10; // Turning on 5th led
            delay1();
            break;
          case '5':
data_lcd(key);                                //Display pressed key on lcd
            P0 = 0X20; // Turning on 6th led
            delay1();
            break;
          case '6':
data_lcd(key);                                //Display pressed key on lcd
            P0 = 0X40; // Turning on 7th led
            delay1();
            break;
          case '7':
data_lcd(key);                                //Display pressed key on lcd
            P0 = 0X80; // Turning on 8th led
            delay1();
            break;
    }
  }
}

