#pragma once

class LightShaderClass
{
private:
	struct LightType
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 specular;
		XMFLOAT3 lightDirection;
		float specularPower;
	};
	class CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass& other);
	~LightShaderClass();

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void ShutDown();
	bool Render(ID3D11DeviceContext* deviceContext, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4, XMFLOAT4,
		XMFLOAT4, XMFLOAT3, XMFLOAT3, float);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, const WCHAR* vsFilename, const WCHAR* psFilename);
	void ShutDownShader();
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const WCHAR* shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4, XMFLOAT4,
		XMFLOAT4, XMFLOAT3, XMFLOAT3, float);
	void RenderShader(ID3D11DeviceContext* deviceContext, int);

private:
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_layout = nullptr;
	ID3D11SamplerState* m_sampleState = nullptr;
	ID3D11Buffer* m_matrixBuffer = nullptr;
	ID3D11Buffer* m_lightBuffer = nullptr;
	ID3D11Buffer* m_cameraBuffer = nullptr;

};