/*****************************************************
Chip type               : ATmega32
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega32.h>
#include <delay.h>
#include <stdio.h>  //for call sprintf.
#include <alcd.h>   //for lcd functions and definitions.


unsigned int row,column;

void col_condition(int count)
{
  if((PINC & 0x70)==0x60)
  { 
    column=count+1;
    row=1;
  }
  if((PINC & 0x70)==0x50)
  { 
    column=count+1;
    row=2;
  }
  if((PINC & 0x70)==0x30)
  {
    column=count+1;
    row=3;
  }
}//end of col_condition.

void main(void)
{

int i=0;
char lcd_result[10];
unsigned char port_st[4]={0x0E,0x0D,0x0B,0x07};
// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=out Func2=Out Func1=Out Func0=Out 
// State7=T State6=P State5=P State4=P State3=1 State2=1 State1=1 State0=1 
PORTC=0x7F;
DDRC=0x0F;     //pins(0,1,2) defined as output with 1 value and pins(3,4,5,6) defined in with pull up.

lcd_init(16);   //initiate lcd.

lcd_clear();
lcd_gotoxy(0,0);
lcd_putsf("Press Any Key:");

while (1)
      {
       row=0;
       column=0;
       
       for(i=0;i<4;i++)      //3 is column in 4*3 matrix key.(3 is less)
       {
         PORTC=((PORTC & 0xF0)| port_st[i]);         
         col_condition(i);
         delay_ms(20);
       }//end of for.
       
       if(row!=0)
       {
          lcd_clear();
          lcd_gotoxy(0,0);
          lcd_putsf("Last COL & ROW:");
          
          lcd_gotoxy(0,1);
          sprintf(lcd_result,"%1d AND %1d",column,row);
          lcd_puts(lcd_result);
          delay_ms(50);
       }
       
      }//while(1)
}
