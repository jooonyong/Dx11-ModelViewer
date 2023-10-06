#include "stdafx.h"
#include "FPSClass.h"

FPSClass::FPSClass(const FPSClass& other)
{
}

FPSClass::~FPSClass()
{
}

void FPSClass::Initialize()
{
	m_FPS = 0;
	m_count = 0;
	m_startTime = timeGetTime();
}

void FPSClass::Frame()
{
	m_count++;
	if (timeGetTime() >= (m_startTime + 1000))
	{
		m_FPS = m_count;
		m_count = 0;
		m_startTime = timeGetTime();
	}
}

int FPSClass::GetFPS()
{
	return m_FPS;
}
