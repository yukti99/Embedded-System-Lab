#include<reg51.h>
#define lcd P1

sbit rs=P2^0;
sbit e=P2^1;

void delay (int);
void cmd (char);
void display (char);
void custom (void);
void string (char *);
void init (void);

unsigned char custom_char[]= {0x00,0x04,0x0E,0x04,0x15,0x0E,0x04,0x00, 
	                      0x00,0x04,0x0E,0x0E,0x0E,0x1F,0x04,0x00, 
	                      0x00,0x0A,0x15,0x11,0x11,0x0A,0x04,0x00,
			      0x0E,0x11,0x11,0x1F,0x1B,0x1B,0x1B,0x1F,
	                      0x0E,0x11,0x10,0x1F,0x1B,0x1B,0x1B,0x1F,
			      0x00,0x0E,0x15,0x1B,0x0E,0x0E,0x00,0x00,
	                      };
	                          
 
void delay (int d)
{
	unsigned char i;
	for(;d>0;d--)
	{
		for(i=250;i>0;i--);
		for(i=248;i>0;i--);
	}
}
void cmd (char c)
{
	lcd=c;
	rs=0;
	e=1;
	delay(5);
	e=0;
}
void display (char c)
{
	lcd=c;
	rs=1;
	e=1;
	delay(5);
	e=0;
}
void custom (void)
{
	int k;
	cmd(0x40);
	for(k=0;k<48;k++)
	display(custom_char[k]);
	cmd(0x80);
}

void string (char *p)
{
	while(*p)
	{
		display(*p++);
	}
}
void init (void)
{
	cmd(0x38);
	cmd(0x0c);
	cmd(0x01);
	cmd(0x80);
}
void main()
{
	init();
	custom();
	string("WELCOME YUKTI");
	cmd(0xc0);
	string("    HEYYY GALLLLL    ");
	delay(2000);
	cmd(0x01);
	cmd(0x80);
	string("  Custom Chars  ");
	cmd(0xc0);
	string("  on 16x2 LCD   ");
	delay(2000);
	cmd(0x01);
	cmd(0x80);
	string("ABCDEFGHIJKLMNOP");
	cmd(0xc0);
	string("1234567890");
	cmd(0xca);
	display(0);
	display(1);
	display(2);
	display(3);
	display(4);
	display(5);
while(1);
}