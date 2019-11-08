#include "MouseInput.hpp"

MouseInput::MouseInput() {
	this->mousePosition.x = 0;
	this->mousePosition.y = 0;
	this->mouseLeftPressed = false;
	this->mouseRightPressed = false;
}

MousePosition MouseInput::getMousePosition() {
	return this->mousePosition;
}

void MouseInput::start() {
	this->running = true;
	this->backgroundThread = thread(&MouseInput::loop, this);
}

void MouseInput::stop() {
	this->running = false;
}

void MouseInput::mainthread() {
	backgroundThread.join();
}

void MouseInput::background() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void MouseInput::onMouseMoved(function<void(MousePosition)> callback) {
	this->onMouseMovedEvent = callback;
}

void MouseInput::onMouseLeftButtonPressed(function<void(MousePosition)> callback) {
	this->onMouseLeftButtonPressedEvent = callback;
}

void MouseInput::onMouseLeftButtonReleased(function<void(MousePosition)> callback) {
	this->onMouseLeftButtonReleasedEvent = callback;
}

void MouseInput::onMouseRightButtonPressed(function<void(MousePosition)> callback) {
	this->onMouseRightButtonPressedEvent = callback;
}

void MouseInput::onMouseRightButtonReleased(function<void(MousePosition)> callback) {
	this->onMouseRightButtonReleasedEvent = callback;
}

void MouseInput::mousebuttonslistener() {

	if (this->isMouseLeftButtonPressed()) {
		this->mouseLeftPressed = true;

		if (this->onMouseLeftButtonPressedEvent != nullptr) {
			this->onMouseLeftButtonPressedEvent(this->mousePosition);
		}
	}
	else if (this->mouseLeftPressed && this->onMouseLeftButtonReleasedEvent != nullptr) {
		this->mouseLeftPressed = false;
		this->onMouseLeftButtonReleasedEvent(this->mousePosition);
	}

	if (this->isMouseRightButtonPressed()) {
		this->mouseRightPressed = true;

		if (this->onMouseRightButtonPressedEvent != nullptr) {
			this->onMouseRightButtonPressedEvent(this->mousePosition);
		}
	}
	else if (this->mouseRightPressed && this->onMouseRightButtonReleasedEvent != nullptr) {
		this->mouseRightPressed = false;
		this->onMouseRightButtonReleasedEvent(this->mousePosition);
	}
}

bool MouseInput::isMouseLeftButtonPressed() {
	return ((GetKeyState(VK_LBUTTON) & 0x100) != 0);
}

bool MouseInput::isMouseRightButtonPressed() {
	return ((GetKeyState(VK_RBUTTON) & 0x100) != 0);
}

bool MouseInput::hasMouseMoved() {
	return (this->referencePosition.x != this->mousePosition.x ||
		this->referencePosition.y != this->mousePosition.y);
}

void MouseInput::mousemotionlistener() {
	GetCursorPos(&this->referencePosition);

	if (this->hasMouseMoved()) {
		this->mousePosition.x = this->referencePosition.x;
		this->mousePosition.y = this->referencePosition.y;

		if (this->onMouseMovedEvent != nullptr) {
			this->onMouseMovedEvent(this->mousePosition);
		}
	}
}

void MouseInput::loop() {

	while (this->running) {
		Sleep(10);
		this->mousemotionlistener();
		this->mousebuttonslistener();
	}
}

