void cmd_lcd (unsigned char dat)    // function to write command at lcd port 
{
	DATA=dat;
	RS=0;			  //clear RS (ie. RS=0) to write command
	E=1;			  // send  H-L pulse	at E pin		
	delay(100);
	E=0;
	delay(100);
}

void data_lcd (unsigned char dat)	// function to write data at lcd port 
{
	DATA=dat;
	RS=1;				// set RS=1 to write DATA
	E=1;			  // send  H-L pulse	at E pin		
	delay(100);
	E=0;
	delay(100);					  
}

void init_lcd()		        	 // function to initialize the LCD at power on time
{
	cmd_lcd(0x38);			 // 2x16 display select
	delay(50000);
	cmd_lcd(0x0c);			 // display on cursor off command
	delay(1000);
	cmd_lcd(0x06);			 // automatic cursor movement to right
	delay(1000);
	cmd_lcd(0x01);			 // lcd clear command 
	delay(5000);
}

void string_lcd(unsigned char *str)	   // function to display string to lcd
{
	 while(*str!='\0')		  		// '\0' is null char as last char of pointer is null
	 {
		 data_lcd(*str);
		 str++;
	 }
 }