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
	// 텍스처를 파일로부터 읽어온다
	if (FAILED(CreateWICTextureFromFile(device, deviceContext, filename,nullptr, &m_texture)))
	{
		return false;
	}

	return true;
}

void TextureClass::ShutDown()
{
	//텍스처 뷰 리소스를 해제한다.
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