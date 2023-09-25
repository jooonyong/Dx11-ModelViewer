#include "stdafx.h"
#include "InputClass.h"

InputClass::InputClass(const InputClass& other)
{
}

InputClass::~InputClass()
{
}

bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	HRESULT result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void InputClass::ShutDown()
{
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = nullptr;
	}

	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = nullptr;
	}
	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = nullptr;
	}
}

bool InputClass::Frame()
{
	if (!ReadKeyboard())
	{
		return false;
	}
	if (!ReadMouse())
	{
		return false;
	}
	ProcessMouseInput();
	InitializeMember();
	ProcessKeyboardInput();

	return true;
}

bool InputClass::IsEscapePressed()
{
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}
	return false;
}

bool InputClass::IsMouseClicked()
{
	if (m_mouseState.rgbButtons[0] & 0x80)
	{
		return true;
	}
	return false;
}

bool InputClass::CheckW()
{
	if (m_forward)
	{
		return true;
	}
	return false;
}

bool InputClass::CheckS()
{
	if (m_backward)
	{
		return true;
	}
	return false;
}

bool InputClass::CheckA()
{
	if (m_left)
	{
		return true;
	}
	return false;
}

bool InputClass::CheckD()
{
	if (m_right)
	{
		return true;
	}
	return false;
}


void InputClass::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
}

float InputClass::GetRotationX()
{
	return m_rotationX;
}

float InputClass::GetRotationY()
{
	return m_rotationY;
}

DIMOUSESTATE* InputClass::GetMouseState()
{
	return &m_mouseState;
}

bool InputClass::ReadKeyboard()
{
	HRESULT result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else {
			return false;
		}
	}
	return true;
}

bool InputClass::ReadMouse()
{
	HRESULT result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else {
			return false;
		}
	}
	return true;
}

void InputClass::InitializeMember()
{
	m_forward = false;
	m_backward = false;
	m_left = false;
	m_right = false;
}

void InputClass::ProcessMouseInput()
{
	//마우스 위치 업데이트
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	if (m_mouseX < 0)
		m_mouseX = 0;
	if (m_mouseY < 0)
		m_mouseY = 0;

	if (m_mouseX > m_screenWidth)
		m_mouseX = m_screenWidth;
	if (m_mouseY > m_screenHeight)
		m_mouseY = m_screenHeight;
}

void InputClass::ProcessKeyboardInput()
{
	if (m_keyboardState[DIK_W] & 0x80)
	{
		m_forward = true;
	}
	if (m_keyboardState[DIK_S] & 0x80)
	{
		m_backward = true;
	}
	if (m_keyboardState[DIK_A] & 0x80)
	{
		m_left = true;
	}
	if (m_keyboardState[DIK_D] & 0x80)
	{
		m_right = true;
	}
}


