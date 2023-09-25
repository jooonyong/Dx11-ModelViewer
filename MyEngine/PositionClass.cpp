#include "stdafx.h"
#include "PositionClass.h"

PositionClass::PositionClass(const PositionClass& other)
{
}

PositionClass::~PositionClass()
{
}

void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
}

void PositionClass::GetRotation(float& x, float& y)
{
	x = m_rotationX;
	y = m_rotationY;
}

void PositionClass::TurnLeft()
{
	m_turnSpeed += m_frameTime * 0.01f;

	if (m_turnSpeed > (m_frameTime * 0.15f))
	{
		m_turnSpeed = m_frameTime * 0.15f;
	}

	m_rotationY -= m_turnSpeed;
}

void PositionClass::TurnRight()
{
}

void PositionClass::TurnUp()
{
}

void PositionClass::TurnDown()
{
}
