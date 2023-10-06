#pragma once

#include "stdafx.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 100.0f;
const float SCREEN_NEAR = 1.0f;

class D3DClass;
class CameraClass;
class ModelClass;
class TextureClass;
class ModelShaderClass;
class LightClass;

class GraphicsClass
{
	friend class ModelClass;
public:
	GraphicsClass() = default;
	GraphicsClass(const GraphicsClass& other);
	~GraphicsClass();

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void ShutDown();
	bool Frame(float rotationX, float rotationY, float translationZ, float translationX);

private:
	bool Render(float rotationX, float rotationY);

private:
	D3DClass* m_Direct3D = nullptr;
	CameraClass* m_Camera = nullptr;
	ModelClass* m_Model = nullptr;
	LightClass* m_Light = nullptr;
	ModelShaderClass* m_ModelShader = nullptr;
};