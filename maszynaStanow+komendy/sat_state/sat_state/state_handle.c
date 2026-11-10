#include "state_handle.h"

state_t currentState = IDLE;
static uint16_t localXor = 0; 

void processByte(char byte) {
	if (byte == 'S' && localXor == 0) {
		localXor = byte;
		return;
	}

	else if (byte == '(' || byte == 'c' || byte == ',') {
		if (localXor == (uint16_t)byte) {
			if (byte == '(') currentState = IDLE;
			else if (byte == 'c') currentState = RDY;
			else if (byte == ',') currentState = ACTV;
			} else {
			PORTD.OUTTGL = PIN4_bm; 
		}
		localXor = 0; 
	}
	else if (localXor != 0) {
		localXor ^= byte;
	}
}

void checkState(state_t state) {
	PORTD.OUTCLR = HANDLE_DIODES;
	if (state == IDLE)  PORTD.OUTSET = PIN5_bm; // RED
	if (state == RDY) PORTD.OUTSET = PIN6_bm; // YELLOW
	if (state == ACTV)  PORTD.OUTSET = PIN7_bm; // GREEN
}