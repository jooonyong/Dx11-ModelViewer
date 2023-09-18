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
	
	ID3D11ShaderResourceView* GetTexture1();
	ID3D11ShaderResourceView* GetTexture2();
	ID3D11ShaderResourceView* GetTexture3();

	int GetIndexCount(int nBufferNum);
	int GetNumMeshes();

private:
	bool InitializeBuffers(ID3D11Device* device);
	void ShutDownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

	bool LoadModel(const WCHAR* modelFileName);
	void ReleaseModel();

	bool LoadTextures(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* textureFilename1, const WCHAR* textureFilename2, const WCHAR* textureFilename3);
	void ReleaseTextures();

private:
	ID3D11Buffer** m_vertexBuffer = nullptr;
	ID3D11Buffer** m_indexBuffer = nullptr;
	unsigned int** m_indices = nullptr;
	unsigned int* m_vertexCount = nullptr;
	unsigned int* m_indexCount = nullptr;
	int m_NumBuffers = 0;
	TextureClass* m_texture1 = nullptr;
	TextureClass* m_texture2 = nullptr;
	TextureClass* m_texture3 = nullptr;
	ModelType** m_model = nullptr;
};