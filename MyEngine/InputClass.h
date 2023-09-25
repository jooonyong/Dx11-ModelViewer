#pragma once

class InputClass
{
public:
	InputClass() = default;
	InputClass(const InputClass& other);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void ShutDown();
	bool Frame();

	bool IsEscapePressed();
	bool IsMouseClicked();
	
	bool CheckW();
	bool CheckS();
	bool CheckA();
	bool CheckD();
	
	void GetMouseLocation(int&, int&);
	float GetRotationX();
	float GetRotationY();
	DIMOUSESTATE* GetMouseState();

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void InitializeMember();
	void ProcessMouseInput();
	void ProcessKeyboardInput();
	
private:
	IDirectInput8* m_directInput = nullptr;
	IDirectInputDevice8* m_keyboard = nullptr;
	IDirectInputDevice8* m_mouse = nullptr;

	unsigned char m_keyboardState[256] = { 0, };
	DIMOUSESTATE m_mouseState;

	int m_screenWidth = 0;
	int m_screenHeight = 0;
	int m_mouseX = 0;
	int m_mouseY = 0;

	float m_rotationX;
	float m_rotationY;

	bool m_forward = false;
	bool m_backward = false;
	bool m_right = false;
	bool m_left = false;
};