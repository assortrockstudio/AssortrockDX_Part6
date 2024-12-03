#include "pch.h"
#include "CMaterial.h"

#include "CDevice.h"
#include "CConstBuffer.h"

#include "CGraphicShader.h"


CMaterial::CMaterial()
	: CAsset(ASSET_TYPE::MATERIAL)
	, m_bDynamic(false)
{
	
}

CMaterial::~CMaterial()
{

}

void CMaterial::SetTexParam(TEX_PARAM _Param, Ptr<CTexture> _Tex)
{
	m_arrTex[_Param] = _Tex;
}

Ptr<CMaterial> CMaterial::GetDynamicMaterial()
{
	Ptr<CMaterial> pDynamicMtrl = Clone();
	pDynamicMtrl->m_bDynamic = true;
	return pDynamicMtrl;
}

void CMaterial::Binding()
{
	// �ؽ��� ���ε�
	for (UINT i = 0; i < TEX_PARAM::END; ++i)
	{
		if (nullptr == m_arrTex[i])
		{
			CTexture::Clear(i);
			m_Const.btex[i] = false;
			continue;
		}			

		m_arrTex[i]->Binding(i);
		m_Const.btex[i] = true;
	}


	// ��� ������ ���ε�
	if (nullptr != m_Shader.Get())
		m_Shader->Binding();

	CConstBuffer* pMtrlCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pMtrlCB->SetData(&m_Const);
	pMtrlCB->Binding();
}