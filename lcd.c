/* ===================================================================================================
   This software is a driver for all character LCD (alpahnumeric LCD) modules based on
     the Hitachi HD487x chip on glass (COG) LCD controller IC. (get datasheet in the folder containing this file)
	 
	 Compatibility:  LM016: 2 rows x 16 characters alphanumeric LCD module
	                 LM017: 2 rows x 32 characters alphanumeric LCD module
                         LM018: 2 rows x 40 characters alphanumeric LCD module
                         LM020: 1 row  x 16 characters alphanumeric LCD module
                         LM032: 2 rows x 20 characters alphanumeric LCD module
                         LM041: 4 rows x 16 characters alphanumeric LCD module
	                 LM044: 4 rows x 20 characters alphanumeric LCD module
	
	This specific example uses the LM016 LCD module (which is the one on the Edu Board) 
         (In this example the 8-bit parallel interface is used)
	
	Note: See the shematic in folder "simulation" and the datasheet... to understand the HW connection
                  (The connections are in accordance with the Edu board)
              
             ARM P1[16..23] ------------ LCD Data[0..7]
             ARM P1_25 ----------------- LCD E  (Enable clock pulse)
             ARM P1_24 ----------------- LCD RS (Register Select: RS = 0 -> command mode; RS = 1 -> data mode)
             ARM P0_22 ----------------- LCD RW (RW = 0 -> write to LCD; RW = 1 -> read from LCD)
             ARM P0_30 ----------------- LCD Backlight control (LCD_BKL)
              
    $$ ECEG-4501 Microcomputers & Interfacing, Lab exercise.  Prepared by: Daniel D. @ ECED of AAiT $$
======================================================================================================= */
	
#include <LPC214x.h>
#include "lcd.h"

void delay(unsigned long a);

/*-------------------------------------------------------------------------
   Function Name: lcd_command

   Parameters: Command to be sent to LCD
 
   Return:  None
 
   Description: Sends a command byte to the LCD COG controller (Hitachi HD4878)

   Note: See the LCD datasheet 
 ---------------------------------------------------------------------------*/
void lcd_command(char cmd)
{
   // IOCLR_bit.P1_24 = 1;    //command mode (RS = 0)
   IOCLR1 = (1<<24);
	
   IO1PIN = cmd<<16;        //send command
   
   // IO1SET_bit.P1_25 = 1;    //Set the enable input (E)
   IOSET1 = (1<<25);
	 delay(10);
   
   // IO1CLR_bit.P1_25 = 1;  //toggle the E input to latch the command to the LCD controller (falling edge)
   IOCLR1 = (1<<25);
		delay(100);            //delay a little for the LCD to settle
}

/*-------------------------------------------------------------------------
   Function Name: lcd_data

   Parameters: data to be sent to LCD
 
   Return:  None
 
   Description: Sends a command byte to the LCD COG controller (Hitachi HD4878)

   Note: See the LCD datasheet 
 ---------------------------------------------------------------------------*/
void lcd_data(char data)
{
   // IO1SET_bit.P1_24 = 1;  //data mode (RS = 1)
		IOSET1 = (1<<24);
	
   ///FIO1MASK = 0xFF00FFFF;   //mask the unused bits of the PIO (to keep them unaffected)
   IO1PIN =  ((data<<16)|0x01000000);        //send data
   ///FIO1MASK = 0xF0FFFFFF;   //unmask RS and E
   
   // IO1SET_bit.P1_25 = 1;   //Set the enable input (E)
		IOSET1 = (1<<25);
	
		delay(10);
   // IO1CLR_bit.P1_25 = 1;   //toggle the E input to latch the command to the LCD controller (falling edge)
		IOCLR1 = (1<<25);
	 delay(100);              //delay a little for the LCD to settle
}

/*-------------------------------------------------------------------------
   Function Name: lcd_gotoXY

   Parameters: row and column address of LCD character
 
   Return:  None
 
   Description: put the cursor to address (row,col)
 ---------------------------------------------------------------------------*/
void lcd_gotoXY(char row, char col)
{
  char address;
  
  if((row > 2)||(col>16)) return;     //address out of range, just return
  
  if(row == 1) address = 0x80;        //first line
  else address = 0xC0;                //second line
  
  lcd_command(address + col);         //set address (row and column) 
}

/*-------------------------------------------------------------------------
   Function Name: lcd_put

   Parameters: the character to be put on LCD and the position on the screen
 
   Return:  None
 
   Description: put a character on LCD at address specified by (row,col)
 ---------------------------------------------------------------------------*/
void lcd_put(char character, char row, char col)
{
   lcd_gotoXY(row,col);
   lcd_data(character);
}

/*-------------------------------------------------------------------------
   Function Name: lcd_write

   Parameters: the string to be printed on LCD and the starting position on the screen
 
   Return:  None
 
   Description: prints a character string on LCD starting at address specified by (row,col)
 ---------------------------------------------------------------------------*/
void lcd_write(char *buffer,char row,char col)
{
   lcd_gotoXY(row,col);
   
   while(*buffer != 0)
   {
      lcd_data(*buffer++);
   }
}

/*-------------------------------------------------------------------------
   Function Name: lcd_init

   Parameters: None
 
   Return:  None
 
   Description: initializes the LCD module (see initialization process on datasheet)
 ---------------------------------------------------------------------------*/
void lcd_init(void)
{
   IO1DIR |= 0xFFFFFFFF;  //set direction to output
   IO0DIR |= 0x40400000;  //set P0_22 and P0_30 as output (LCD_RW and LCD_BKL resp)
      
   delay(160000);         //around 20ms
   
   // IO0CLR_bit.P0_22 = 1;  //LCD write mode
   IO0CLR = (1<<22);
   lcd_command(0x01);     //clear display
   delay(8000);           //around 1ms
   
   lcd_command(0x38);     //LCD function set, 8-bit mode, 5x7 font, 2 lines display
   delay(40000);          //around 5ms
   
   lcd_command(0x38);     //LCD function set, 8-bit mode, 5x7 font, 2 lines display
   delay(40000);          //around 5ms
   
   lcd_command(0x08);     //turn off LCD
   delay(40000);          //around 5ms
   
   lcd_command(0x0E);     //turn on LCD, cursor on, blink off
   delay(160000);         //around 20ms
      
   lcd_command(0x06);     //Entry mode set, auto-increment address when writing
   delay(40000);          //around 5ms
}

/*-------------------------------------------------------------------------
   Function Name: lcd_backlight

   Parameters: option, either ON or OFF
 
   Return:  None
 
   Description: Turns the LCD backlight ON or OFF (only on the EduBoard)

   Note: See the EduBoard schematic (page 5)
 ---------------------------------------------------------------------------*/
void lcd_backlight(char option)
{
   // IO0DIR_bit.P0_30 = 1;
   IO0DIR = (1<<30);
   if(option == ON)
	 {  //IO0SET_bit.P0_30 = 1;    //backlight ON
			IO0SET = (1<<30);
	 }
   else
      IO0CLR = (1<<30); //IO0CLR_bit.P0_30 = 1;    //backlight OFF
}

//private function for a simple delay
void delay(unsigned long a)
{
   while(--a != 0);
}