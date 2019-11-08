#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

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

class KeyboardInput
{
public:
	KeyboardInput();

	void start();
	void stop();
	void mainthread();
	void background();

	/* EVENTS */
	void onKeyPressed(char key, function<void()> callback);
	void onKeyboardPressed(function<void(int)> callback);
	

private:
	bool running;
	thread backgroundThread;

	/* EVENTS */
	map<int, function<void()>> keyEvents;
	function<void(int)> keyboardEvent;

	void loop(); 
	void keyboardlistener();

};
#endif