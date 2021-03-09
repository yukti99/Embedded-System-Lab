unsigned char keyscan()
{
  char arr[10]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};
  char ch[6]={0x77,0x7f,0x39,0xbf,0x79,0x71};
  while(1)
  {
        KEYPAD_PORT = 0XeF;
        delay(1000);  /////must for response at port when key press
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return ch[2];}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return arr[8];}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return arr[4];}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return arr[0];}

        KEYPAD_PORT = 0XdF;
        delay(1000);
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return ch[3];}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return arr[9];}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return arr[5];}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return arr[1];}

        KEYPAD_PORT = 0XbF;
        delay(1000);
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return ch[4];}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return ch[0];}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return arr[6];}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return arr[2];}

        KEYPAD_PORT = 0X7F;
        delay(1000);
        if((KEYPAD_PORT&0X01)==0){while((KEYPAD_PORT&0X01)==0); return ch[5];}
        if((KEYPAD_PORT&0X02)==0){while((KEYPAD_PORT&0X02)==0); return ch[1];}
        if((KEYPAD_PORT&0X04)==0){while((KEYPAD_PORT&0X04)==0); return arr[7];}
        if((KEYPAD_PORT&0X08)==0){while((KEYPAD_PORT&0X08)==0); return arr[3];}
   }
}