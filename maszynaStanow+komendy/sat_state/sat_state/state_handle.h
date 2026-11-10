

#ifndef STATE_HANDLE_H_
#define STATE_HANDLE_H_

#include <avr/io.h>
#include <stdint.h>

#define HANDLE_DIODES (PIN5_bm | PIN6_bm | PIN7_bm)

typedef enum {IDLE, RDY, ACTV} state_t;
extern state_t currentState;

//STATE HANDLE FUNCTIONS
void processByte(char byte);

void checkState(state_t state);



#endif /* STATE_HANDLE_H_ */