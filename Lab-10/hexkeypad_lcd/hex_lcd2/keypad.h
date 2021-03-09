unsigned char keyscan()
{
  while(1)
  {
        KEYPAD_PORT = 0XeF;
        delay(1000);  /////must for response at port when key press
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return 'C\0';}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return '8\0';}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return '4\0';}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return '0\0';}

        KEYPAD_PORT = 0XdF;
        delay(1000);
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return "D\0";}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return "9\0";}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return "5\0";}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return "1\0"  ;}

        KEYPAD_PORT = 0XbF;
        delay(1000);
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return "E\0";}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return "A\0";}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return "6\0";}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return "2\0";}

        KEYPAD_PORT = 0X7F;
        delay(1000);
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return "F\0";}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return "B\0";}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return "7\0";}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return "3\0";}
   }
}