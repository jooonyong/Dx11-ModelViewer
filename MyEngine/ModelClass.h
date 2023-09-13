#pragma once

class TextureClass;

class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	ModelClass() = default;
	~ModelClass();
	ModelClass(const ModelClass& other);

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* modelFileName, const WCHAR* textureFilename1, const WCHAR* textureFilename2, const WCHAR* textureFilename3);
	void ShutDown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();
private:
	bool InitializeBuffers(ID3D11Device* device);
	void ShutDownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

	bool LoadModel(const WCHAR* modelFileName);
	void ReleaseModel();

	bool LoadTextures(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* textureFilename1, const WCHAR* textureFilename2, const WCHAR* textureFilename3);
	void ReleaseTextures();
private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	unsigned int* m_indices = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;
	TextureClass* m_texture1 = nullptr;
	TextureClass* m_texture2 = nullptr;
	TextureClass* m_texture3 = nullptr;
	ModelType* m_model = nullptr;
};