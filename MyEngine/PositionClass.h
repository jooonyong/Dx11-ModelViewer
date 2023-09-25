#pragma once

class PositionClass
{
public:
	PositionClass() = default;
	PositionClass(const PositionClass& other);
	~PositionClass();

	void SetFrameTime(float time);
	void GetRotation(float& x, float& y);

	void TurnLeft();
	void TurnRight();
	void TurnUp();
	void TurnDown();

private:
	float m_frameTime;
	float m_rotationX;
	float m_rotationY;
	float m_turnSpeed;
};