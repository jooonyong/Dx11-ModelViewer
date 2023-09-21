#include "stdafx.h"
#include "GraphicsClass.h"
#include "D3DClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "ModelShaderClass.h"

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	m_Direct3D = new D3DClass{};
	if (!m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
	{
		return false;
	}

	m_Camera = new CameraClass{};
	if (!m_Camera)
	{
		return false;
	}
	
	m_Model = new ModelClass{};
	if (!m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(),
		L"C:/Users/junyong/source/repos/MyEngine/MyEngine/Model/source/character.fbx",
		L"C:/Users/junyong/source/repos/MyEngine/MyEngine/Model/textures/bodyCol.png",
		L"C:/Users/junyong/source/repos/MyEngine/MyEngine/Model/textures/faceCol.png",
		L"C:/Users/junyong/source/repos/MyEngine/MyEngine/Model/textures/HairCol.png"))
	{
		return false;
	}

	m_ModelShader = new ModelShaderClass{};
	if (!m_ModelShader->Initialize(m_Direct3D->GetDevice(), hwnd))
	{
		return false;
	}

	return true;
}

void GraphicsClass::ShutDown()
{
	if (m_ModelShader)
	{
		m_ModelShader->ShutDown();
		delete m_ModelShader;
		m_ModelShader = nullptr;
	}
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = nullptr;
	}
	if (m_Model)
	{
		m_Model->ShutDown();
		delete m_Model;
		m_Model = nullptr;
	}
	if (m_Direct3D)
	{
		m_Direct3D->ShutDown();
		delete m_Direct3D;
		m_Direct3D = nullptr;
	}
}

bool GraphicsClass::Frame()
{
	return Render();
}

bool GraphicsClass::Render()
{
	m_Direct3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);
	
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	//m_Camera->SetRotation(90.0f, 0.0f, 0.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);

	XMMATRIX transform = XMMatrixRotationX(XMConvertToRadians(-90.0f)) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	
	worldMatrix =transform;

	//worldMatrix = XMMatrixTranslation(0.0f, 5.0f, 0.0f);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	for (int i = 0; i < m_Model->GetNumMeshes(); i++)
	{
		m_Model->Render(m_Direct3D->GetDeviceContext(), i); //���ؽ� ���� �ε������� ����
		if (i < 2)
		{
			m_ModelShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(i), worldMatrix, viewMatrix, projectionMatrix,
				m_Model->GetTexture3());
		}
		else if (i > 5)
		{
			m_ModelShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(i), worldMatrix, viewMatrix, projectionMatrix,
				m_Model->GetTexture1());
		}
		else
		{
			m_ModelShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(i), worldMatrix, viewMatrix, projectionMatrix,
				m_Model->GetTexture2());
		}
		
	}
	
	m_Direct3D->EndScene();

	return true;
}
