#include <Arduino.h>
#include "ToggleButtons.h"

// definition of the static values have to be done outside of the class
bool CToggleButtons::m_value0 = false;
bool CToggleButtons::m_value1 = false;

CToggleButtons::CToggleButtons(int interruptID, bool initValue) : m_interruptID(interruptID)
	{
		if(m_interruptID == 0){
			m_value0 = initValue;
			pinMode(2, INPUT);
			attachInterrupt(0, CToggleButtons::interruptFunction0, FALLING);
		}else{
			m_value1 = initValue;
			pinMode(3, INPUT);
			attachInterrupt(1, CToggleButtons::interruptFunction1, FALLING);
		}
	}

	void CToggleButtons::interruptFunction0()
	{
		// toggle value
		m_value0 = !m_value0;
	}

	void CToggleButtons::interruptFunction1()
	{
		// toggle value
		m_value1 = !m_value1;
	}

	CToggleButtons &CToggleButtons::instance0(bool initValue)
	{
		static CToggleButtons instance(0, initValue);
		return instance;
	}

	CToggleButtons &CToggleButtons::instance1(bool initValue)
	{
		static CToggleButtons instance(1, initValue);
		return instance;
	}

	bool CToggleButtons::getValue()
	{
		if(m_interruptID ==0)
			return m_value0;
		else
			return m_value1;
	}
