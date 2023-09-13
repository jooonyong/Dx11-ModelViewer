#include "stdafx.h"
#include "TextureClass.h"
#include "Include/DDSTextureLoader.h"
#include "Include/WICTextureLoader.h"

TextureClass::TextureClass()
{
}

TextureClass::TextureClass(const TextureClass& other)
{
}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* filename)
{
	// �ؽ�ó�� ���Ϸκ��� �о�´�
	if (FAILED(CreateWICTextureFromFile(device, deviceContext, filename,nullptr, &m_texture)))
	{
		return false;
	}

	return true;
}

void TextureClass::ShutDown()
{
	//�ؽ�ó �� ���ҽ��� �����Ѵ�.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}