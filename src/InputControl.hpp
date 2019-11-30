#ifndef INPUTCONTROL_H
#define INPUTCONTROL_H

#include <thread>
#include <string>
#include <iostream>
#include <string>
#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

using namespace std;

class InputControl {

public:

	void background();
	void click();
	void moveTo(int x, int y);
	void sendKeystroke(string s);
	void changeBackground(string path);

	void clickRightButton();
	void clickLeftButton();
	void clickWheelButton();

	void pressRightButton();
	void pressLeftButton();
	void pressWheelButton();

	void releaseRightButton();
	void releaseLeftButton();
	void releaseWheelButton();

	void trigger(DWORD mouseInput);

	void volumeMute();
	int volumeLevel();
	void volumeSet(int value);
};

#endif