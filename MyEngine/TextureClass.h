#pragma once

class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass& other);
	~TextureClass();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR*);
	void ShutDown();

	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* m_texture = nullptr;
};