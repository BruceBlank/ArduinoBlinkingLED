// Do not remove the include below
#include <Arduino.h>

//TODO: implement the button to switch between SOS- and regular blinking

class CBlinkingLED {
public:
	// the constructor
	CBlinkingLED(uint8_t ledpin, uint8_t potpin, uint8_t buttonpin);
	// does the work once
	void doit();
private:
	const uint8_t m_ledpin;
	const uint8_t m_potpin;
	const uint8_t m_buttonpin;
	unsigned long m_timeScale;

	// the short signal (dit) and the gap
	void dit();
	// the long signal (dah) and the gap
	void dah();
	// (additional) silence between two letters
	void letterGap();
	// (additional) silence between two words
	void wordGap();
	// a special internalDelay method set timeScale on every delay
	// time is a generalized time value
	void internalDelay(float time);
};

void CBlinkingLED::internalDelay(float time)
{
	// read and set timeScale from A2: [0,1023] -> [25,800]
	int sensorValue = analogRead(m_potpin);
	m_timeScale = (unsigned long)(sensorValue * (775.0 / 1023) + 25);

	//TODO: here, an event handler for the button should be implemented
	delay(m_timeScale * time);
}


CBlinkingLED::CBlinkingLED(uint8_t ledpin, uint8_t potpin, uint8_t buttonpin) :
				m_ledpin(ledpin) , m_potpin(potpin), m_buttonpin(buttonpin) , m_timeScale(0)
{
	pinMode(m_ledpin, OUTPUT);
	pinMode(m_buttonpin, INPUT);
	// no pinMode for analog input necessary
}

void CBlinkingLED::dit(void)
{
	digitalWrite(m_ledpin, HIGH);
	internalDelay(1);
	digitalWrite(m_ledpin, LOW);
	internalDelay(1);
}

void CBlinkingLED::dah(void)
{
	digitalWrite(m_ledpin, HIGH);
	internalDelay(3);
	digitalWrite(m_ledpin, LOW);
	internalDelay(1);
}

void CBlinkingLED::letterGap(void)
{
	internalDelay(2);
}

void CBlinkingLED::wordGap(void)
{
	internalDelay(4);
}

void CBlinkingLED::doit()
{
	// send SOS
	dit(); dit(); dit(); letterGap();
	dah(); dah(); dah(); letterGap();
	dit(); dit(); dit(); letterGap(); wordGap();
}

// a singleton button class
class CToggleButtons{
private:
	static bool m_value0;
	static bool m_value1;

	// no direct construction
	CToggleButtons();
	// no copy construction
	CToggleButtons(const CToggleButtons &);
	// no direct construction with parameter
	CToggleButtons(int interruptID, bool initValue)
	{
		if(interruptID == 0){
			m_value0 = initValue;
			attachInterrupt(0, CToggleButtons::interruptFunction0, FALLING);
		}else{
			m_value1 = initValue;
			attachInterrupt(1, CToggleButtons::interruptFunction1, FALLING);
		}
	}

	// interrupt function toggles value of button 0
	static void interruptFunction0()
	{
		// toggle value
		m_value0 = !m_value0;
	}

	// interrupt function toggles value of button 1
	static void interruptFunction1()
	{
		// toggle value
		m_value1 = !m_value1;
	}

public:
	// get instance for button with interrupt-ID 0 (PIN 2)
	static CToggleButtons &instance0(bool initValue = false)
	{
		static CToggleButtons instance(0, initValue);
		return instance;
	}

	// get instance for button with interrupt-ID 1 (PIN 3)
	static CToggleButtons &instance1(bool initValue = false)
	{
		static CToggleButtons instance(1, initValue);
		return instance;
	}

	// get the value of button 0
	static bool getValue0(bool v) {return m_value0;}
	// get the value of button 0
	static bool getValue1(bool v) {return m_value1;}
};

void interrupt_pin2()
{
	//FORTESTING:
	digitalWrite(13, HIGH);
}

//TODO: test new toggle button class
int main(void)
{
	// general initialization
	init();

	//FORTESTING: register button-interrupt
	pinMode(2, INPUT);
	attachInterrupt(0, interrupt_pin2, LOW);

	CBlinkingLED blinkLED(13, A0, 8);

	while (true)
	{
		blinkLED.doit();
	}
	return 0; // never reached
}
