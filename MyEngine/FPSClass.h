#pragma once

#pragma comment(lib,"winmm.lib")

class FPSClass
{
public:
	FPSClass() = default;
	FPSClass(const FPSClass& other);
	~FPSClass();

	void Initialize();
	void Frame();
	int GetFPS();

private:
	int m_FPS;
	int m_count;
	unsigned long m_startTime;
};