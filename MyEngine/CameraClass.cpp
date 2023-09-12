#include "stdafx.h"
#include "CameraClass.h"

CameraClass::CameraClass(const CameraClass& other)
{
	m_position.x = 0;
	m_position.y = 0;
	m_position.z = -5.0f;
	m_rotation.x = 0;
	m_rotation.y = 0;
	m_rotation.z = 0;
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}

XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

void CameraClass::Render()
{
	XMFLOAT3 up, position, lookAt;
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	XMVECTOR upVector = XMLoadFloat3(&up);

	position = m_position;

	XMVECTOR positionVector = XMLoadFloat3(&position);

	float radians = m_rotation.y * 0.0174532925f;

	lookAt.x = sinf(radians) + m_position.x;
	lookAt.y = m_position.y;
	lookAt.z = cosf(radians) + m_position.z;

	XMVECTOR lookAtVector = XMLoadFloat3(&lookAt);
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
}

void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	m_viewMatrix = viewMatrix;
}

