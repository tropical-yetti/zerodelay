#include "zerodelay.h"

void timer1_init(int8_t baseTimeMSec)
{
  TCCR1A = 0;
	TCCR1B |= (1 << WGM12)|TIMER1_PRESCALER_MSK;	// set up timer with prescaler = 64 and CTC mode
	TIMSK1 |= (1 << OCIE1A);		// enable compare interrupt
	OCR1A = (F_CPU/TIMER1_PRESCALER_FACTOR)*(baseTimeMSec/1000)-1; //2499;	// initialize compare value: [(16MHZ/64)*10Millisec-1]
	TCNT1 = 0;	// initialize counter
	sei();
	baseTimeAcc = 0;
}

 void baseTimeAccUpdade()
{
  cli();
  baseTimeAcc++;
  sei();
}

int64_t wait(int64_t waitTimeMSec)
{
  return (baseTimeAcc+(waitTimeMSec/baseTimeMSec));
}

bool isTime(int64_t targetBaseTime)
{
  return (baseTimeACC>=targetBaseTime)?true:false;
}

ISR(TIMER1_COMPA_vect)
{
  baseTimeAccUpdate();
}
