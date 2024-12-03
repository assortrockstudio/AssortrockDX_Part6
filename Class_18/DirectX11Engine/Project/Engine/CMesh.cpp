#include "pch.h"
#include "CMesh.h"

#include "CDevice.h"

CMesh::CMesh(bool _bEngine)
	: CAsset(ASSET_TYPE::MESH, _bEngine)
	, m_VBDesc{}
	, m_VtxCount(0)
	, m_VtxSysMem(nullptr)
	, m_IBDesc{}
	, m_IdxCount(0)
	, m_IdxSysMem(nullptr)
{
}

CMesh::~CMesh()
{
	if (nullptr != m_VtxSysMem)
		delete[] m_VtxSysMem;

	if (nullptr != m_IdxSysMem)
		delete[] m_IdxSysMem;
}

int CMesh::Create(Vtx* _VtxSysMem, size_t _VtxCount, UINT* _IdxSysMem, size_t _IdxCount)
{
	m_VtxCount = (UINT)_VtxCount;
	m_IdxCount = (UINT)_IdxCount;

	// Create Vertex Buffer
	m_VBDesc.ByteWidth = sizeof(Vtx) * m_VtxCount;
	m_VBDesc.MiscFlags = 0;

	// ������ �뵵 ����
	m_VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// ���۰� ������ ���Ŀ� CPU ���� �����ؼ� GPU �� �ִ� �����͸�
	// ����Ⱑ �����ϰ� ����
	m_VBDesc.CPUAccessFlags = 0;
	m_VBDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = _VtxSysMem;

	if (FAILED(DEVICE->CreateBuffer(&m_VBDesc, &SubDesc, m_VB.GetAddressOf())))
	{
		return E_FAIL;
	}
		

	
	m_IBDesc.ByteWidth = sizeof(UINT) * m_IdxCount;
	m_IBDesc.MiscFlags = 0;

	// ������ �뵵 ����
	m_IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// �ѹ� ������ ���Ŀ� �б�, ���� �Ұ���
	m_IBDesc.CPUAccessFlags = 0;
	m_IBDesc.Usage = D3D11_USAGE_DEFAULT;

	SubDesc = {};
	SubDesc.pSysMem = _IdxSysMem;

	if (FAILED(DEVICE->CreateBuffer(&m_IBDesc, &SubDesc, m_IB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// SysMem ����
	m_VtxSysMem = new Vtx[m_VtxCount];
	memcpy(m_VtxSysMem, _VtxSysMem, sizeof(Vtx) * m_VtxCount);

	m_IdxSysMem = new UINT[m_IdxCount];
	memcpy(m_IdxSysMem, _IdxSysMem, sizeof(UINT) * m_IdxCount);

	return S_OK;
}

void CMesh::Binding()
{
	UINT Stride = sizeof(Vtx);
	UINT Offset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &Stride, &Offset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CMesh::render()
{
	Binding();

	CONTEXT->DrawIndexed(m_IdxCount, 0, 0);
	
}

void CMesh::render_particle(UINT _instance)
{
	Binding();

	CONTEXT->DrawIndexedInstanced(m_IdxCount, _instance, 0, 0, 0);
}