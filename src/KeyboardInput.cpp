
#include "KeyboardInput.hpp"

KeyboardInput::KeyboardInput() {}

void KeyboardInput::start() {
	this->running = true;
	this->backgroundThread = thread(&KeyboardInput::loop, this);
}

void KeyboardInput::mainthread() {
	backgroundThread.join();
}

void KeyboardInput::background() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void KeyboardInput::stop() {
	this->running = false;
}

void KeyboardInput::onKeyPressed(char key, function<void()> callback) {
	this->keyEvents[key] = callback;
}

void KeyboardInput::onKeyboardPressed(function<void(int)> callback) {
	this->keyboardEvent = callback;
}

void KeyboardInput::keyboardlistener() {

	int key;

	for (int KEY = 8; KEY <= 190; KEY++)
	{
		if (GetAsyncKeyState(KEY) == -32767) {
			key = char(KEY);

			if (keyboardEvent != nullptr) {
				keyboardEvent(key);
			}

			if (this->keyEvents[key] != nullptr) {
				this->keyEvents[key]();
			}
		}
	}
}

void KeyboardInput::loop() {

	while (this->running) {
		Sleep(10);
		this->keyboardlistener();
	}
}
