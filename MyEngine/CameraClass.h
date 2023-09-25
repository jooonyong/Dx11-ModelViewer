#pragma once

class CameraClass :public AlignedAllocationPolicy<16>
{
public:
	CameraClass();
	CameraClass(const CameraClass& other);
	~CameraClass();

	void SetTranslation(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render(float rotationX, float rotationY, float translationZ, float translationX);
	void GetViewMatrix(XMMATRIX&);

private:
	XMVECTOR m_up;
	XMVECTOR m_lookAt;
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMMATRIX m_viewMatrix;
};