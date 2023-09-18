#pragma once

class ModelShaderClass : public AlignedAllocationPolicy<16>
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	ModelShaderClass() = default;
	~ModelShaderClass();
	ModelShaderClass(const ModelShaderClass& other);

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void ShutDown();
	bool Render(ID3D11DeviceContext* deviceContext, int, XMMATRIX, XMMATRIX, XMMATRIX,
		ID3D11ShaderResourceView* bodyTexture, ID3D11ShaderResourceView* faceTexture, ID3D11ShaderResourceView* hairTexture);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, const WCHAR* vsfilename, const WCHAR* psfilename);
	void ShutDownShader();
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const WCHAR*);
	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX, XMMATRIX, XMMATRIX,
		ID3D11ShaderResourceView* bodyTexture, ID3D11ShaderResourceView* faceTexture, ID3D11ShaderResourceView* hairTexture);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
};