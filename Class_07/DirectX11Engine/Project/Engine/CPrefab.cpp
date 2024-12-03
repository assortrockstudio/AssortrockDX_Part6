#include "pch.h"
#include "CPrefab.h"

#include "CGameObject.h"
#include "CTransform.h"

CPrefab::CPrefab()
	: CAsset(ASSET_TYPE::PREFAB)
	, m_ProtoObj(nullptr)
{
}

CPrefab::CPrefab(CGameObject* _Proto)
	: CAsset(ASSET_TYPE::PREFAB)
	, m_ProtoObj(_Proto)
{
	m_ProtoObj->Transform()->SetRelativePos(0.f, 0.f, 0.f);
}

CPrefab::CPrefab(const CPrefab& _Other)
	: CAsset(_Other)
	, m_ProtoObj(nullptr)
{
	m_ProtoObj = _Other.m_ProtoObj->Clone();
	m_ProtoObj->Transform()->SetRelativePos(0.f, 0.f, 0.f);
}

CPrefab::~CPrefab()
{
	if (nullptr != m_ProtoObj)
		delete m_ProtoObj;
}

CGameObject* CPrefab::Instantiate()
{
	return m_ProtoObj->Clone();
}