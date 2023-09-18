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

ID3D11ShaderResourceView* ModelClass::GetTexture1()
{
	return m_texture1->GetTexture();
}

ID3D11ShaderResourceView* ModelClass::GetTexture2()
{
	return m_texture2->GetTexture();
}

ID3D11ShaderResourceView* ModelClass::GetTexture3()
{
	return m_texture3->GetTexture();
}

int ModelClass::GetIndexCount(int nBufferNum)
{
	return m_indexCount[nBufferNum];
}

int ModelClass::GetNumMeshes()
{
	return m_NumBuffers;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	m_vertexBuffer = new ID3D11Buffer* [m_NumBuffers];
	m_indexBuffer = new ID3D11Buffer* [m_NumBuffers];

	for (int i = 0; i < m_NumBuffers; i++)
	{
		VertexType* vertices = new VertexType[m_vertexCount[i]];
		unsigned long* indices = new unsigned long[m_indexCount[i]];

		for (int j = 0; j < m_vertexCount[i]; j++)
		{
			vertices[j].position = XMFLOAT3(m_model[i][j].x, m_model[i][j].y, m_model[i][j].z);
			vertices[j].texture = XMFLOAT2(m_model[i][j].tu, m_model[i][j].tv);
			vertices[j].normal = XMFLOAT3(m_model[i][j].nx, m_model[i][j].ny, m_model[i][j].nz);
		}

		D3D11_BUFFER_DESC vertexBufferDesc;
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount[i];
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vertexData;
		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer[i]);

		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount[i];
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = m_indices[i];
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer[i]);

		delete[] vertices;
		vertices = nullptr;

	}

	return true;
}

void ModelClass::ShutDownBuffers()
{
	if (m_indexBuffer)
	{
		for (int i = 0; i < m_NumBuffers; i++)
		{
			m_indexBuffer[i]->Release();
			m_indexBuffer[i] = nullptr;
		}
	}

	if (m_vertexBuffer)
	{
		for (int i = 0; i < m_NumBuffers; i++)
		{
			m_vertexBuffer[i]->Release();
			m_vertexBuffer[i] = nullptr;
		}
	}
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	for (int i = 0; i < m_NumBuffers; i++)
	{
		deviceContext->IASetVertexBuffers(0, m_NumBuffers, &m_vertexBuffer[i], &stride, &offset);
		deviceContext->IASetIndexBuffer(m_indexBuffer[i], DXGI_FORMAT_R32_UINT, 0);
	}
	
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

	const int childNodeNum = scene->mRootNode->mNumChildren;
	int count = 0;

	m_NumBuffers = scene->mNumMeshes;
	
	m_model = new ModelType* [m_NumBuffers];
	m_indexCount = new unsigned int[m_NumBuffers];
	m_vertexCount = new unsigned int[m_NumBuffers];
	m_indices = new unsigned int* [m_NumBuffers];

	for (int i = 0; i < childNodeNum; i++) //child node 4개
	{
		int numMeshes = scene->mRootNode->mChildren[i]->mNumMeshes;
		for (int j = 0; j < numMeshes; j++) //child node의 mesh개수만큼 반복
		{
			aiMesh* mesh = scene->mMeshes[count];
			unsigned int numVertices = mesh->mNumVertices;
			m_vertexCount[count] = numVertices;
			m_model[count] = new ModelType[numVertices];
			
			for (int k = 0; k < numVertices; k++)
			{
				if (mesh->HasPositions())
				{
					m_model[count][k].x = mesh->mVertices[k].x;
					m_model[count][k].y = mesh->mVertices[k].y;
					m_model[count][k].z = mesh->mVertices[k].z;
				}
				if (mesh->HasTextureCoords(0))
				{
					m_model[count][k].tu = mesh->mTextureCoords[0][k].x;
					m_model[count][k].tv = mesh->mTextureCoords[0][k].y;
				}
				if (mesh->HasNormals())
				{
					m_model[count][k].nx = mesh->mNormals[k].x;
					m_model[count][k].ny = mesh->mNormals[k].y;
					m_model[count][k].nz = mesh->mNormals[k].z;
				}
			}

			m_indexCount[count] = mesh->mNumFaces * 3;
			m_indices[count] = new unsigned int[m_indexCount[count]];
			for (int k = 0; k < mesh->mNumFaces; k++)
			{
				aiFace& face = mesh->mFaces[k];
				//indices
				m_indices[count][3 * k] = face.mIndices[0];
				m_indices[count][3 * k + 1] = face.mIndices[1];
				m_indices[count][3 * k + 2] = face.mIndices[2];
			}
			count++;
		}
	}

	return true;
}

void ModelClass::ReleaseModel()
{
	if (m_indices)
	{
		for (int i = 0; i < m_NumBuffers; i++)
		{
			delete[] m_indices[i];
		}
		delete[] m_indices;
		m_indices = nullptr;
	}
	if (m_model)
	{
		for (int i = 0; i < m_NumBuffers; i++)
		{
			delete[] m_model[i];
		}
		delete[] m_model;
		m_model = nullptr;
	}
	if (m_vertexCount)
	{
		delete[] m_vertexCount;
	}
	if (m_indexCount)
	{
		delete[] m_indexCount;
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

