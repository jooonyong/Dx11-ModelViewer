#include "stdafx.h"
#include "LightClass.h"

LightClass::LightClass(const LightClass& other)
{
}

LightClass::~LightClass()
{
}

void LightClass::SetAmbientColor(float r, float g, float b, float a)
{
	m_ambientColor.x = r;
	m_ambientColor.y = g;
	m_ambientColor.z = b;
	m_ambientColor.w = a;
}

void LightClass::SetDiffuseColor(float r, float g, float b, float a)
{
	m_diffuseColor.x = r;
	m_diffuseColor.y = g;
	m_diffuseColor.z = b;
	m_diffuseColor.w = a;
}

void LightClass::SetDirection(float x, float y, float z)
{
	m_direction.x = x;
	m_direction.y = y;
	m_direction.z = z;
}

void LightClass::SetSpecularColor(float r, float g, float b, float a)
{
	m_specularColor.x = r;
	m_specularColor.y = g;
	m_specularColor.z = b;
	m_specularColor.w = a;
}

void LightClass::SetSpecularPower(float value)
{
	m_specularPower = value;
}

XMFLOAT4 LightClass::GetAmbientColor()
{
	return m_ambientColor;
}

XMFLOAT4 LightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}

XMFLOAT3 LightClass::GetDirection()
{
	return m_direction;
}

XMFLOAT4 LightClass::GetSpecularColor()
{
	return m_specularColor;
}

float LightClass::GetSpecularPower()
{
	return m_specularPower;
}
