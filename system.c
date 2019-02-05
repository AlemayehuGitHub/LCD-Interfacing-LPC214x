/*--------------------------------------------------------------
 File:      system.c
 Purpose:   To initialize and configure the ARM Clock source
 Compiler:  IAR EW 5.5
 System:    Philips LPC2148 MCU with ARM7TDMI-s core
 
 Notes:
     PLL = Phase Locked Loop - Is an electronic circuit consisting of
	                           Current controlled oscillator(CCO), phase detector
 							   and frequency multiplier.
		   The task of the PLL is to generate the required clock for the CPU from
		   the crystal oscillator base frequency.
		   
	 PLL feed code = The byte sequence (0xAA-0x55) is required to change the PLL config.
	                 to protect it from changing inadvertently by spurious system activity
					 or external processes.
----------------------------------------------------------------*/
#include <LPC214x.h>

void clock_init(void)
{
  /*crystal input is 12MHz (Fosc = 12MHz)
   We can set the multiplier(MSEL) to achive required CPU clock 
  PLLCFG_bit.MSEL = 0x3;  //M - multiplier=4  (CCLK = 4*Fosc = 48MHz) CCLK = CPU clock 
  
  // We can set the divider(PSEL) to keep the output of the CCO in the specified range (156-320MHz) 
  PLLCFG_bit.PSEL = 0x1;  //P - divider=2 (CCO frequency = CCLK*2P = 182MHz)
  
  //set changes (write PLL Feed code - 0xAA followed by 0x55 in to PLLFEED register)
  PLLFEED_bit.FEED = 0xAA;
  PLLFEED_bit.FEED = 0x55;

  //enable PLL to start the lock sequence(set PLLEN bit in PLLCON register)
  PLLCON_bit.PLLE = 1;
  
  //set changes (write PLL Feed code - 0xAA followed by 0x55 in to PLLFEED register)
  PLLFEED_bit.FEED = 0xAA;
  PLLFEED_bit.FEED = 0x55;

  //wait for PLL to lock on to the new frequency (the LOCK bit in PLLSTAT register becomes '1' on successful lock)
  while(PLL0STAT == 0);     //wait untill the LOCK bit becomes '1'

  //connect PLL to the clock tree (Now the PLL is the clock source for the ARM CPU complex)
  PLLCON_bit.PLLC = 1;
  
  //set changes (write PLL Feed code - 0xAA followed by 0x55 in to PLLFEED register)
  PLLFEED_bit.FEED = 0xAA;
  PLLFEED_bit.FEED = 0x55;
  
  VPBDIV_bit.VPBDIV = 1;        //PCLK = CCLK .... PCLK = peripheral clock*/
	
	PLL0CON = 0x01;
	PLL0CFG = 0x23;
	PLL0FEED = 0xaa;
	PLL0FEED = 0x55;
	while(!(PLL0STAT & 0x00000400));
	PLL0CON = 0x03;
	PLL0FEED = 0xaa;
	PLL0FEED = 0x55;
	VPBDIV = 0x01;
}

