#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>


#define LED PORTB5 // LED is on Pin 13 or Pin 5 of Port B
#define timeScale 250

void initIO(void)
{
DDRB |= (1<<LED);
}

void dit(void)
{
// the short signal (dit) and the gap
	PORTB |= (1<<LED); // set
	_delay_ms(timeScale * 1);
	PORTB &= ~(1<<LED); // clear
	_delay_ms(timeScale * 1);
}

void dah(void)
{
// the long signal (dah) and the gap
	PORTB |= (1<<LED); // set
	_delay_ms(timeScale * 3);
	PORTB &= ~(1<<LED); // clear
	_delay_ms(timeScale * 1);
}

void letterGap(void)
{
// (additional) silence between two letters
	_delay_ms(timeScale * 2);
}

void wordGap(void)
{
// (additional) silence between two words
	_delay_ms(timeScale * 4);
}

int main(void)
{
  initIO();

  while (1)
  {
	  // send SOS
	  dit(); dit(); dit(); letterGap();
	  dah(); dah(); dah(); letterGap();
	  dit(); dit(); dit(); letterGap(); wordGap();
  }
  return 0; // never reached
}
