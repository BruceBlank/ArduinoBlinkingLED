// Do not remove the include below
#include "Arduino.h"

int led = 13;
unsigned long timeScale=0;

void initialization(void)
{
	init();
	pinMode(led, OUTPUT);
}

void dit(void)
{
// the short signal (dit) and the gap
	digitalWrite(led, HIGH);
	delay(timeScale * 1);
	digitalWrite(led, LOW);
	delay(timeScale * 1);
}

void dah(void)
{
// the long signal (dah) and the gap
	digitalWrite(led, HIGH);
	delay(timeScale * 3);
	digitalWrite(led, LOW);
	delay(timeScale * 1);
}

void letterGap(void)
{
// (additional) silence between two letters
	delay(timeScale * 2);
}

void wordGap(void)
{
	// (additional) silence between two words	  while(1);
	delay(timeScale * 4);
}

int main(void)
{
  initialization();

  while (1)
  {
	  // read and set timeScale from A2: [0,1023] -> [100,500]
	  int sensorValue = analogRead(A2);
	  timeScale = (unsigned long)(sensorValue * (400.0 / 1023) + 100);
	  //Serial.println(timeScale);

	  // send SOS
	  dit(); dit(); dit(); letterGap();
	  dah(); dah(); dah(); letterGap();
	  dit(); dit(); dit(); letterGap(); wordGap();
  }
  return 0; // never reached
}
