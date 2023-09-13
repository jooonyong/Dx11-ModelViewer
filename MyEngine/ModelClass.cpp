#include "stdafx.h"
#include "TextureClass.h"
#include "ModelClass.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

ModelClass::~ModelClass()
{
}

ModelClass::ModelClass(const ModelClass& other)
{
}

bool ModelClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* modelFileName, const WCHAR* textureFilename1, const WCHAR* textureFilename2, const WCHAR* textureFilename3)
{
	if (!LoadModel(modelFileName))
	{
		return false;
	}
	if (!InitializeBuffers(device))
	{
		return false;
	}
	return LoadTextures(device, deviceContext, textureFilename1, textureFilename2, textureFilename3);
}

void ModelClass::ShutDown()
{
	ShutDownBuffers();
	ReleaseModel();
	ReleaseTextures();
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffers(deviceContext);
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices = new VertexType[m_vertexCount];

	unsigned long* indices = new unsigned long[m_indexCount];

	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = XMFLOAT2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
	}

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;


	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = m_indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);

	delete[] vertices;
	vertices = nullptr;

	return true;
}

void ModelClass::ShutDownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool ModelClass::LoadModel(const WCHAR* modelFileName)
{
	Assimp::Importer importer;

	std::wstring ws(modelFileName);
	std::string strFileName(ws.begin(), ws.end());
	const aiScene* scene = importer.ReadFile( strFileName,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	
	if (!scene)
	{
		return false;
	}

	const int numMeshes = scene->mNumMeshes;

	//for (int i = 0; i < numMeshes; i++) //8¹ø¹Ýº¹
	//{
	aiMesh* mesh = scene->mMeshes[0];

	m_vertexCount = mesh->mNumVertices;
	m_model = new ModelType[m_vertexCount];

	for (int j = 0; j < m_vertexCount; j++)
	{
		if (mesh->HasPositions())
		{
			m_model[j].x = mesh->mVertices[j].x;
			m_model[j].y = mesh->mVertices[j].y;
			m_model[j].z = mesh->mVertices[j].z;
		}
		if (mesh->HasTextureCoords(0))
		{
			m_model[j].tu = mesh->mTextureCoords[0][j].x;
			m_model[j].tv = mesh->mTextureCoords[0][j].y;
		}
		if (mesh->HasNormals())
		{
			m_model[j].nx = mesh->mNormals[j].x;
			m_model[j].ny = mesh->mNormals[j].y;
			m_model[j].nz = mesh->mNormals[j].z;
		}
		
	}

	m_indexCount = mesh->mNumFaces * 3;
	m_indices = new unsigned int[m_indexCount];
	for (int j = 0; j < mesh->mNumFaces; j++)
	{
		aiFace& face = mesh->mFaces[j];
		//indices
		m_indices[3 * j] = face.mIndices[0];
		m_indices[3 * j + 1] = face.mIndices[1];
		m_indices[3 * j + 2] = face.mIndices[2];
	}
	//}
	

	return true;
}

void ModelClass::ReleaseModel()
{
	if (m_indices)
	{
		delete[] m_indices;
		m_indices = nullptr;
	}
	if (m_model)
	{
		delete[] m_model;
		m_model = nullptr;
	}
}

bool ModelClass::LoadTextures(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* textureFilename1, const WCHAR* textureFilename2, const WCHAR* textureFilename3)
{
	m_texture1 = new TextureClass{};
	if (!m_texture1)
	{
		return false;
	}
	if (!m_texture1->Initialize(device, deviceContext, textureFilename1))
	{
		return false;
	}

	m_texture2 = new TextureClass{};
	if (!m_texture2)
	{
		return false;
	}
	if (!m_texture2->Initialize(device, deviceContext, textureFilename2))
	{
		return false;
	}

	m_texture3 = new TextureClass{};
	if (!m_texture3)
	{
		return false;
	}
	if (!m_texture3->Initialize(device, deviceContext, textureFilename3))
	{
		return false;
	}
	return true;
}

void ModelClass::ReleaseTextures()
{
	if (m_texture1)
	{
		m_texture1->ShutDown();
		delete m_texture1;
		m_texture1 = nullptr;
	}
	if (m_texture2)
	{
		m_texture2->ShutDown();
		delete m_texture2;
		m_texture2 = nullptr;
	}
	if (m_texture3)
	{
		m_texture3->ShutDown();
		delete m_texture3;
		m_texture3= nullptr;
	}
}

