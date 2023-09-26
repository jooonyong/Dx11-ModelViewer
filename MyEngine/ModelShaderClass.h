#pragma once
class ModelClass;

class ModelShaderClass : public AlignedAllocationPolicy<16>
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 specular;
		XMFLOAT3 lightDirection;
		float specularPower;
	};

public:
	ModelShaderClass() = default;
	~ModelShaderClass();
	ModelShaderClass(const ModelShaderClass& other);

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void ShutDown();
	bool Render(ID3D11DeviceContext* deviceContext, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView* texture,
		XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular, XMFLOAT3 lightDirection, XMFLOAT3 cameraPosition, float specularPower);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, const WCHAR* vsfilename, const WCHAR* psfilename);
	void ShutDownShader();
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const WCHAR*);
	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView* texture,
		XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular, XMFLOAT3 lightDirection, XMFLOAT3 cameraPosition, float specularPower);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_cameraBuffer;
	ID3D11Buffer* m_lightBuffer;
	ID3D11SamplerState* m_sampleState;
};