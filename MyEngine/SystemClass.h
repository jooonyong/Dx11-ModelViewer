#pragma once

class InputClass;
class GraphicsClass;
class FPSClass;

class SystemClass
{
public:
	SystemClass() = default;
	SystemClass(const SystemClass& other);
	~SystemClass();

	bool Initialize();
	void ShutDown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutDownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input = nullptr;
	GraphicsClass* m_Graphics = nullptr;
	FPSClass* m_FPS = nullptr;
	int m_prevMouseX = 0;
	int m_prevMouseY = 0;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* ApplicationHandle = 0;