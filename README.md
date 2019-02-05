# Embedded
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
