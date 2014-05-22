// a singleton button class
class CToggleButtons{
private:
	const int m_interruptID;
	static bool m_value0;
	static bool m_value1;

	// no direct construction
	CToggleButtons();
	// no copy construction
	CToggleButtons(const CToggleButtons &);
	// no direct construction with parameter
	CToggleButtons(int interruptID, bool initValue);

	// interrupt function toggles value of button 0
	static void interruptFunction0();

	// interrupt function toggles value of button 1
	static void interruptFunction1();

public:
	// get instance for button with interrupt-ID 0 (PIN 2)
	static CToggleButtons &instance0(bool initValue = false);

	// get instance for button with interrupt-ID 1 (PIN 3)
	static CToggleButtons &instance1(bool initValue = false);

	// get the value of button 0
	bool getValue();
};

