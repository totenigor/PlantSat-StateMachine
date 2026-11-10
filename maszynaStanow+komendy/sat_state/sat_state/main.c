#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "state_handle.h"
#include "usart_ini.h"

uint16_t ctrlSum;
uint8_t recording;			//SO THAT THE GPS WONT CANCEL OUT FRAMES SENT FROM THE USER
ISR(USART0_RXC_vect)
{
	char rcvdByte = USART0.RXDATAL;
	processByte(rcvdByte);
}

int main(void)
{
	USART0_ini(4800);			//COMMAND FRAMES
	USART1_ini(4800);			//GPS
	
	PORTD.DIRSET = 0xF0;		
	
	PORTD.OUTSET = 0xF0;
	_delay_ms(1000);
	PORTD.OUTCLR = 0xF0;	//check if every diode indicating a state works fine before program
	
	sei();
    while (1) 
    {
		checkState(currentState);
    }
}

