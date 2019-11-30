#include "InputControl.hpp"

void InputControl::background() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void InputControl::click() {
	this->clickLeftButton();
}

void InputControl::moveTo(int x, int y) {
	SetCursorPos(x, y);
}

void InputControl::sendKeystroke(string s) {

	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	HKL kbl = GetKeyboardLayout(0);

	for (unsigned int i = 0; i < s.length(); ++i)
	{
		char c = s[i];
		ip.ki.wVk = VkKeyScanExA(c, kbl); //<== don't mix ANSI with UNICODE
		ip.ki.dwFlags = 0; //<= Add this to indicate key-down
		SendInput(1, &ip, sizeof(ip));
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(ip));
	}
}

void InputControl::changeBackground(string path) {
	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID) path.c_str(), SPIF_UPDATEINIFILE);
}

void InputControl::clickLeftButton() {
	this->pressLeftButton();
	this->releaseLeftButton();
}

void InputControl::clickRightButton() {
	this->pressRightButton();
	this->releaseRightButton();
}

void InputControl::clickWheelButton() {
	this->pressWheelButton();
	this->releaseWheelButton();
}

void InputControl::pressLeftButton() {
	this->trigger(MOUSEEVENTF_LEFTDOWN);
}

void InputControl::pressRightButton() {
	this->trigger(MOUSEEVENTF_RIGHTDOWN);
}

void InputControl::pressWheelButton() {
	this->trigger(MOUSEEVENTF_MIDDLEDOWN);
}

void InputControl::releaseLeftButton() {
	this->trigger(MOUSEEVENTF_LEFTDOWN);
}

void InputControl::releaseRightButton() {
	this->trigger(MOUSEEVENTF_RIGHTUP);
}

void InputControl::releaseWheelButton() {
	this->trigger(MOUSEEVENTF_MIDDLEUP);
}

void InputControl::trigger(DWORD mouseInput) {
	INPUT Inputs[1] = { 0 };
	Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dwFlags = mouseInput;
	SendInput(1, Inputs, sizeof(INPUT));
}

void InputControl::volumeMute() {
	INPUT ip = { 0 };
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = VK_VOLUME_MUTE; //or VOLUME_DOWN or MUTE
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

int InputControl::volumeLevel() {
	HRESULT hr;

	CoInitialize(NULL);
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
	IMMDevice* defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume* endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID*)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	float currentVolume = 0;
	//Current volume in dB
	hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);

	endpointVolume->Release();
	CoUninitialize();

	return (int) (currentVolume * 100);
}

void InputControl::volumeSet(int value) {
	if (!(value >= 0 && value <= 100)) return;

	HRESULT hr;

	CoInitialize(NULL);
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
	IMMDevice* defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume* endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID*)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	float conversion = (( (float) value) / 100);
	hr = endpointVolume->SetMasterVolumeLevelScalar(conversion, NULL);
	endpointVolume->Release();
	CoUninitialize();
}