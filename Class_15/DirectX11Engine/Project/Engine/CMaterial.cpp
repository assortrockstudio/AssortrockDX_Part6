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

void* CMaterial::GetScalarParam(SCALAR_PARAM _Param)
{
	switch (_Param)
	{
	case INT_0:
	case INT_1:
	case INT_2:
	case INT_3:
		return &m_Const.iArr[_Param];
		break;
	case FLOAT_0:
	case FLOAT_1:
	case FLOAT_2:
	case FLOAT_3:
		return &m_Const.fArr[_Param - FLOAT_0];
		break;
	case VEC2_0:
	case VEC2_1:
	case VEC2_2:
	case VEC2_3:
		return &m_Const.v2Arr[_Param - VEC2_0];
		break;
	case VEC4_0:
	case VEC4_1:
	case VEC4_2:
	case VEC4_3:
		return &m_Const.v4Arr[_Param - VEC4_0];
		break;
	case MAT_0:
	case MAT_1:
	case MAT_2:
	case MAT_3:
		return &m_Const.matArr[_Param - MAT_0];
		break;	
	}

	return nullptr;
}

Ptr<CMaterial> CMaterial::GetDynamicMaterial()
{
	Ptr<CMaterial> pDynamicMtrl = Clone();
	pDynamicMtrl->m_bDynamic = true;
	return pDynamicMtrl;
}

void CMaterial::Binding()
{
	// 텍스쳐 바인딩
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


	// 상수 데이터 바인딩
	if (nullptr != m_Shader.Get())
		m_Shader->Binding();

	CConstBuffer* pMtrlCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pMtrlCB->SetData(&m_Const);
	pMtrlCB->Binding();
}