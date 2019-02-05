/*----------------------------------------------------------------------------
    File name   : main.c
    Purpose     : Demonstrate the use of The alphanumeric LCD driver functions
    Procesor    : ARM7TDMI-S on LPC2103 MCU
    Platform    : soft-kit  

    $$ ECEg-4501 - Microcomputers and interfacing, lab exercise $$
 ----------------------------------------------------------------------------*/

#include <LPC214x.h>
#include "system.h"
#include "lcd.h"

//a simple demonstration of a 2 row X 20 characters alphanumeric LCD

int main(void)            
{
   //SCS = 2;            //Enable Fast GPIO (FIO) --- to use the GPIO ports on the AHB instead of APB
                       //makes the port access ~3.5 times faster --- see chapter-8(GPIO) on manual
   
   clock_init();       //initialize and supply clock to the cpu 
   				   
   lcd_init();         //initialize LCD... see function definition in "lcd.c"     
   
   lcd_backlight(ON);  //turn on the backlight
      
   lcd_write("This is a test",1,1);   //print a string starting at row 1 column 1 on the LCD
   lcd_write("Line2",2,8);            //print a string starting at row 2 column 8 on the LCD
      
   lcd_put(':',2,14);         //print a character at row 2 column 14 on the LCD
   lcd_put(')',2,15);         //print a character at row 2 column 15 on the LCD
   
   //PCON = 2;           //sleep:   (untill interrupt or reset) 
}