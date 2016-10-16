#include <AT89X51.H>
sbit DQ_IO=P1^1;
sbit LED=P1^3;
sbit DS1821_Vcc=P1^0;
sbit DS1821_GND=P1^2;
unsigned char NUMBER[3];
char code TABLE[13]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x20,0x2d,0x2e};//  ªÅ¥Õ- .
char TEMP;
bit bdata work;
#include <DS1821.H>





main()
{
  IE=0x90;
  SCON=0x70;
  TMOD=0x20;
  TH1=0XFD;
  TR1=1;
	DS1821_Vcc=1;
	DS1821_GND=0;
   
  while(1)
  {
   if(work==1)
   {
    reset_DS();
    write_1byte(0xee);
    TEMP=read_temp();
    display(TEMP);
    TI=1;
    delay_ms(1000);
   }
  }
}

void serial_INT(void) interrupt 4
{
    unsigned char n;
      if(TI==1)
	    { 
	      TI=0;
		  for (n=0;n<3;n++)
		  {
	      SBUF=TABLE[NUMBER[n]];
		  while(TI==0);
		  TI=0;
		  }
          
         }
      if(RI==1)
	  {
	      RI=0;
		  switch(SBUF)
		   {
		     case 0x41:
			   work=1;
			   LED=0;
	           break;
		     case 0x42:
			   work=0;
			   LED=1;
	           break;              
			 default:
			   break;
		 }
      }
}

