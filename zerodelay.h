#ifndef F_CPU
#define F_CPU 16000000
/** PRESCALER MASK CONFIG TABLE:
 * CS12|CS11|CS10
 *      0|0|0 = 0x00    No Clock
 *      0|0|1 = 0x01    No Prescaler
 *      0|1|0 = 0x02    Prescaler factor = 8
 *      0|1|1 = 0x03    Prescaler factor = 64
 *      1|0|0 = 0x04    Prescaler factor = 256
 *      1|0|1 = 0x05    Prescaler factor = 1024
 *      1|1|0 = 0x06    Ext. src. T1, falling edge
 *      1|1|1 = 0x07    Ext. src. T1, rising edge
*/
#define  TIMER1_PRESCALER_MSK   0x03
#ifdef   TIMER1_PRESCALER_MSK==0x00
#define  TIMER1_PRESCALER_FACTOR 0
#elifdef TIMER1_PRESCALER_MSK==0x01
#define  TIMER1_PRESCALER_FACTOR 1
#elifdef TIMER1_PRESCALER_MSK==0x02
#define  TIMER1_PRESCALER_FACTOR 8
#elifdef TIMER1_PRESCALER_MSK==0x03
#define  TIMER1_PRESCALER_FACTOR 64
#elifdef TIMER1_PRESCALER_MSK==0x04
#define  TIMER1_PRESCALER_FACTOR 256
#elifdef TIMER1_PRESCALER_MSK==0x05
#define  TIMER1_PRESCALER_FACTOR 1024
#else
#define  TIMER1_PRESCALER_FACTOR 1
#endif // TIMER1_PRESCALER_MSK

volatile const int8_t baseTimeMSec = 10; 

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
