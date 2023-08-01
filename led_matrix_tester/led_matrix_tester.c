////////////////////
//
// HEADER FILES
//
#include <system.h>
#include <rand.h>

// PIC CONFIG BITS
// - RESET INPUT DISABLED
// - WATCHDOG TIMER OFF
// - INTERNAL OSC
#pragma DATA _CONFIG1, _FOSC_INTOSC & _WDTE_OFF & _MCLRE_OFF &_CLKOUTEN_OFF
#pragma DATA _CONFIG2, _WRT_OFF & _PLLEN_OFF & _STVREN_ON & _BORV_19 & _LVP_OFF
#pragma CLOCK_FREQ 16000000

//
// TYPE DEFS
//
typedef unsigned char byte;

//
// MACRO DEFS
//

/*
PIN ASSIGNMENTS
VDD		VSS
RA5		RA0
RA4		RA1
RA3		RA2

RA0 - row dat
RA1 - col dat
RA2 - row s/rclk
RA4 - col rclk 
RA5 - col srclk


*/
#define P_ROW_DAT		lata.2
#define P_ROW_CLK		lata.0
#define P_COL_DAT		lata.1
#define P_COL_STORE		lata.4
#define P_COL_SHIFT		lata.5




//                    76543210
#define P_TRISA		0b11000000

byte leds[8];
void update_display() {

	//P_ROW_CLK = 0;
	//P_ROW_DAT = 1;
	//P_ROW_CLK = 1;
	//P_ROW_DAT = 0;
	
	for(int row=0; row<8; ++row) {
		byte dat = leds[row];
		byte mask = 0x80;
		
		
		P_ROW_CLK = 0;
		P_COL_STORE = 0;
		while(mask) {
			
			P_COL_SHIFT = 0;
			P_COL_DAT = !!(dat & mask);
			P_COL_SHIFT = 1;
			
			mask>>=1;
		}

		P_ROW_DAT = !!(row==7);
		P_ROW_CLK = 1;
		P_COL_STORE = 1;
		//delay_ms(1);
	}
}

////////////////////////////////////////////////////////////
// MAIN
void main()
{ 
	// osc control / 16MHz / internal
	osccon = 0b01111010;

	// configure io
	trisa = P_TRISA;              	
	porta=0;
	
	ansela = 0b00000000;  
	
#if 0
	leds[0] = 0b00011000;
	leds[1] = 0b00100100;
	leds[2] = 0b01000010;
	leds[3] = 0b01111110;
	leds[4] = 0b01000010;
	leds[5] = 0b01000010;
	leds[6] = 0b01000010;
	leds[7] = 0b01000010;
#endif

#if 0
	leds[0] = 0b01010101;
	leds[1] = 0b00000000;
	leds[2] = 0b01010101;
	leds[3] = 0b00000000;
	leds[4] = 0b01010101;
	leds[5] = 0b00000000;
	leds[6] = 0b01010101;
	leds[7] = 0b00000000;
#endif
	
#if 0
	leds[0] = 0b00000000;
	leds[1] = 0b10101010;
	leds[2] = 0b00000000;
	leds[3] = 0b10101010;
	leds[4] = 0b00000000;
	leds[5] = 0b10101010;
	leds[6] = 0b00000000;
	leds[7] = 0b10101010;
#endif	
	
#if 1
	leds[0] = 0b10000000;
	leds[1] = 0b00010000;
	leds[2] = 0b00000010;
	leds[3] = 0b01000000;
	leds[4] = 0b00001000;
	leds[5] = 0b00000001;
	leds[6] = 0b00100000;
	leds[7] = 0b00000100;
#endif		
	
	// loop forever (until power off)
	for(;;) {	
	
		update_display();
	}	
}



   
  
