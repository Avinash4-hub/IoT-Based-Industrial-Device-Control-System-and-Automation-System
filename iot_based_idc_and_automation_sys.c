#include<lpc21xx.h>
#include<string.h>
#include"delay.h"
#define LCD 0XFF<<4
#define RS  1<<12
#define E 1<<13
#define LED1 1<<14
#define LED2 1<<15
#define LED3 1<<16
#define LED4 1<<17
void uart0_config(void);
void uart0_tx(unsigned char);
unsigned char uart0_rx(void);
void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char *);
int main()
{
unsigned char rxbyte;
PINSEL0|=0;
PINSEL1|=0;
IODIR0|=LED1|LED2|LED3|LED4;
IOSET0=LED1|LED2|LED3|LED4;
//unsigned char c[2];
uart0_config();
LCD_INIT();
LCD_COMMAND(0X01);
LCD_COMMAND(0X80);
LCD_STR("IOT BASED INDUSTRIAL");
LCD_COMMAND(0XC0);
LCD_STR("DEVICE CONTROL AND");
//LCD_COMMAND(0X01);
LCD_COMMAND(0X94);
LCD_STR("AUTOMATION SYSTEM");
delay_ms(3000);
LCD_COMMAND(0X01);
LCD_COMMAND(0X80);
LCD_STR("BULB1:"); 
LCD_COMMAND(0XC0);
LCD_STR("BULB2:");
 LCD_COMMAND(0X94);
LCD_STR("BULB3:");
  LCD_COMMAND(0XD4);
LCD_STR("BULB4:");
while(1)
{				  
rxbyte=uart0_rx();
//c[0]=rxbyte;
//c[1]='\0';
//uart0_tx(rxbyte);
if(rxbyte=='A')
{
IOCLR0=LED1;
LCD_COMMAND(0X89);
LCD_STR("ON  ");
}
else if(rxbyte=='a')
{
IOSET0=LED1;
LCD_COMMAND(0X89);
LCD_STR("OFF");
}
else if(rxbyte=='B')
{
IOCLR0=LED2;
LCD_COMMAND(0XC9);
LCD_STR("ON  ");
}
else if(rxbyte=='b')
{
IOSET0=LED2;
LCD_COMMAND(0XC9);
LCD_STR("OFF");
}
else if(rxbyte=='C')
{
IOCLR0=LED3;
  , nb LCD_COMMAND(0X9D);
LCD_STR("ON  ");
}
else if(rxbyte=='c')
{
IOSET0=LED3;
LCD_COMMAND(0X9D);
LCD_STR("OFF");
}
else if(rxbyte=='D')
{
IOCLR0=LED4;
LCD_COMMAND(0XDD);
LCD_STR("ON  ");
}
else if(rxbyte=='d')
{
IOSET0=LED4;
LCD_COMMAND(0XDD);
LCD_STR("OFF");
}
else
{
IOSET0=LED1|LED2|LED3|LED4;
}
}
}
void  uart0_config(void)
{
PINSEL0=0X05;
U0LCR=0X83;
U0DLL=97;
U0DLM=0;
U0LCR=0X03;
}
void uart0_tx(unsigned char txbyte)
{
while(((U0LSR>>5)&1)==0);
U0THR=txbyte;
}
unsigned char uart0_rx(void)
{
while((U0LSR&1)==0);
return U0RBR;
}
void LCD_INIT(void)

{

IODIR0|=LCD|RS|E;

LCD_COMMAND(0X01);	

LCD_COMMAND(0X02);

LCD_COMMAND(0X0C);

LCD_COMMAND(0X38);

}

void LCD_COMMAND(unsigned char cmd)

{

IOCLR0=LCD;

IOSET0=(cmd<<4);
 
IOCLR0=RS;

IOSET0=E;

delay_ms(2);

IOCLR0=E;

}

void LCD_DATA(unsigned char d)

{

IOCLR0=LCD;

IOSET0=(d<<4);

IOSET0=RS;

IOSET0=E;

delay_ms(2);

IOCLR0=E;

}
void LCD_STR(unsigned char*p)
{
while(*p)
{
LCD_DATA(*p++);
}
}


