#pragma once

class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
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

	bool Initialize(ID3D11Device* device, const WCHAR* modelFileName );
	void ShutDown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();
private:
	bool InitializeBuffers(ID3D11Device* device);
	void ShutDownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

	bool LoadModel(const WCHAR* modelFileName);
	void ReleaseModel();
private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	unsigned int* m_indices = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;
	ModelType* m_model = nullptr;
};