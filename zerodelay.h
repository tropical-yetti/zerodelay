#ifndef ZERODELAY_H_INCLUDED
#define ZERODELAY_H_INCLUDED

#ifndef F_CPU
#define F_CPU 16000000
#endif // F_CPU
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

#define TIMER1_PRESCALER_MSK 3
#if   TIMER1_PRESCALER_MSK == 1
#define  TIMER1_PRESCALER_FACTOR 1
#elif TIMER1_PRESCALER_MSK == 2
#define  TIMER1_PRESCALER_FACTOR 8
#elif TIMER1_PRESCALER_MSK == 3
#define  TIMER1_PRESCALER_FACTOR 64
#elif TIMER1_PRESCALER_MSK == 4
#define  TIMER1_PRESCALER_FACTOR 256
#elif TIMER1_PRESCALER_MSK == 5
#define  TIMER1_PRESCALER_FACTOR 1024
#else
#define  TIMER1_PRESCALER_FACTOR 1
#endif // TIMER1_PRESCALER_MSK

volatile const int8_t baseTimeMSec = 10;

void timer1_init(int8_t baseTimeMSec);
void baseTimeAccUpdade();
int64_t wait(int64_t waitTimeMSec);
int8_t isTime(int64_t targetBaseTime);

#endif // ZERODELAY_H_INCLUDED
