/** ZERO DELAY BLINK
 *
 *  Implements a simples project to show how to use Zero Delay Lib
 *  in place of Arduino's delay function.
 *  You can use it if you need your program still running while waits for any event.
 *
 *
 */

#include <avr/io.h>
#include "zerodelay.h"
int main(void)
{
    DDRB |= (1<<5);  // Sets PORTB5 (Arduino pin 13) as output, same as pinMode(13, HIGH);
    //timer1_init(10); // Enable timer1 with an overflow interrupt at each 10msec
    int64_t targetTimeAcc = wait(1000); // A 1000ms delay

    while(1) {
        if(isTime(targetTimeAcc)) {
            PORTB ^= (1<<5); // A flip (or toogle) at PORTB5 (Arduino Pin 13) there is no "one line" equivalent in arduino's standard libraries
            int64_t targetTimeAcc = wait(1000); // Update for the next flip
        }
    }
    return 0;
}

ISR () {
    baseTimeAccUpdade();
}
