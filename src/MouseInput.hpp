#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <thread>         
#include <map>
#include <functional>

using namespace std;

typedef struct {
	int x;
	int y;
} MousePosition;


class MouseInput {

public:

	MousePosition getMousePosition();

	MouseInput();
	void start();
	void stop();
	void mainthread();
	void background();

	void onMouseMoved(function<void(MousePosition)> callback);
	void onMouseLeftButtonPressed(function<void(MousePosition)> callback);
	void onMouseLeftButtonReleased(function<void(MousePosition)> callback);
	void onMouseRightButtonPressed(function<void(MousePosition)> callback);
	void onMouseRightButtonReleased(function<void(MousePosition)> callback);

private:
	MousePosition mousePosition;
	POINT referencePosition;
	bool running;
	thread backgroundThread;
	bool mouseLeftPressed;
	bool mouseRightPressed;

	function<void(MousePosition)> onMouseMovedEvent;
	function<void(MousePosition)> onMouseLeftButtonPressedEvent;
	function<void(MousePosition)> onMouseLeftButtonReleasedEvent;
	function<void(MousePosition)> onMouseRightButtonPressedEvent;
	function<void(MousePosition)> onMouseRightButtonReleasedEvent;

	void loop();

	bool isMouseLeftButtonPressed();
	bool isMouseRightButtonPressed();
	bool hasMouseMoved();
	void mousebuttonslistener();
	void mousemotionlistener();
};

#endif