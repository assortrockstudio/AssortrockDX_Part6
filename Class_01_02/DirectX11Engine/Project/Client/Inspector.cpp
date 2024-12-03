#include "pch.h"
#include "Inspector.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include "TransformUI.h"
#include "MeshRenderUI.h"
#include "CameraUI.h"
#include "Light2DUI.h"
#include "Animator2DUI.h"
#include "Collider2DUI.h"
#include "TileMapUI.h"
#include "ParticleSystemUI.h"


Inspector::Inspector()
	: EditorUI("Inspector", "##Inspector")
	, m_TargetObject(nullptr)
	, m_arrComUI{}
{
	// ComponentUI 생성
	CreateComponentUI();

}

Inspector::~Inspector()
{
	
}

void Inspector::render_tick()
{
	if (nullptr == m_TargetObject)
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		if (nullptr != pLevel)
		{
			CGameObject* pTarget = pLevel->FindObjectByName(L"MainCamera");			
			SetTargetObject(pTarget);
		}	
		return;
	}

	ImGui::Text("Inspector");
}

void Inspector::SetTargetObject(CGameObject* _Target)
{
	m_TargetObject = _Target;

	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{	
		// 해당 컴포넌트를 담당할 UI 가 생성되어있지 않기 때문에 nullptr 체크 해주어야 함
		if (nullptr == m_arrComUI[i])
			continue;

		m_arrComUI[i]->SetTarget(m_TargetObject);
	}	
}

void Inspector::CreateComponentUI()
{	
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM] = new TransformUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D] = new Collider2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::ANIMATOR2D] = new Animator2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA] = new CameraUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D] = new Light2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER] = new MeshRenderUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP] = new TileMapUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLESYSTEM] = new ParticleSystemUI;	

	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrComUI[i])
			continue;

		m_arrComUI[i]->SetActive(true);
		m_arrComUI[i]->SetSeperate(true);
		AddChildUI(m_arrComUI[i]);
	}
}