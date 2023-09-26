#include "stdafx.h"
#include "CameraClass.h"

CameraClass::CameraClass()
{
	m_position.x = 0.0f;
	m_position.y = 3.0f;
	m_position.z = -6.0f; 
	m_rotation.x = 0;
	m_rotation.y = 0;
	m_rotation.z = 0;
	m_lookAt = XMVectorSet(0.0f, 3.0f, 4.0f, 0.0f);
	m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
}

CameraClass::CameraClass(const CameraClass& other)
{
	m_position = other.m_position;
	m_rotation.x = other.m_rotation.x;
	m_rotation.y = other.m_rotation.y;
	m_rotation.z = other.m_rotation.z;
	m_lookAt = other.m_lookAt;
	m_up = other.m_lookAt;
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetTranslation(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;

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

void CameraClass::Render(float rotationX, float rotationY, float translationZ, float translationX)
{
	XMMATRIX rotation = XMMatrixRotationX(rotationX) * XMMatrixRotationY(rotationY);
	m_up = XMVector3Transform(m_up, rotation);
	
	SetTranslation(translationX, 0.0f, translationZ);
	
	XMVECTOR positionVector;
	positionVector = XMLoadFloat3(&m_position);
	positionVector = XMVector3Transform(positionVector, rotation);

	m_rotation.x = rotationX;
	m_rotation.y = rotationY;

	float xRadians = m_rotation.x * 0.0174532925f; //0.0174532925f = pi / 180;
	float yRadians = m_rotation.y * 0.0174532925f;
	
	m_lookAt = XMVector3Transform(m_lookAt, rotation);

	m_viewMatrix = XMMatrixLookAtLH(positionVector, m_lookAt, m_up);
}

void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}



