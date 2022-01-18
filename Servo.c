/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License. 
 *           View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	/* set LED pin as an output */
	DDRA = 0xFF;
	DDRC = 0x00;
	/* forever loop (embedded programs never normally terminate) */
	for (;;) 
	{ 
		if (PINC & _BV(6))
		{
		/* Set pin B7 high */
		PORTA |= _BV(PINA2);
		_delay_ms(1);
		/* Set pin B7 low */
		PORTA &= ~_BV(PINA2);
		_delay_ms(20);
		}
	}
}
