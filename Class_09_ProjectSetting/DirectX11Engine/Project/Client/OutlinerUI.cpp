#include "pch.h"
#include "OutlinerUI.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/CTaskMgr.h>


#include "Inspector.h"
#include "TreeUI.h"

OutlinerUI::OutlinerUI()
	: EditorUI("Outliner", "##Outliner")
{
	// 자식 UI 로 TreeUI 생성
	m_Tree = new TreeUI("OutlinerTree");	
	AddChildUI(m_Tree);

	// TreeUI 의 루트노드를 보이지않게 설정
	m_Tree->ShowRoot(false);

	// 항목 선택시 동작할 CallBack OR Delegate 등록	
	m_Tree->RegisterSelectDelegate(this, (UI_DELEGATE1)&OutlinerUI::SelectGameObject);

	
	// 현재 Asset 의 상태를 트리에 반영
	RenewGameObject();
}

OutlinerUI::~OutlinerUI()
{
}

void OutlinerUI::render_tick()
{
	if (CTaskMgr::GetInst()->IsObjectChanged())
	{
		RenewGameObject();
	}
}

void OutlinerUI::RenewGameObject()
{
	// Tree 를 Clear 한다.
	m_Tree->Clear();
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "DummyRoot");

	// 현재 레벨을 알아낸다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	if (nullptr == pCurLevel)
		return;

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);

		const vector<CGameObject*>& vecParent = pLayer->GetParentObjects();

		for (size_t i = 0; i < vecParent.size(); ++i)
		{
			AddGameObject(pRootNode, vecParent[i]);
		}
	}
}


void OutlinerUI::AddGameObject(TreeNode* _Node, CGameObject* _Object)
{
	TreeNode* pNewNode = m_Tree->AddTreeNode(_Node, ToString(_Object->GetName()), (DWORD_PTR)_Object);
	
	// 만약 해당 오브젝트가 자식 오브젝트를 보유하고 있다면
	const vector<CGameObject*>& vecChildren = _Object->GetChildren();

	// 자식 오브젝틀 부모오브젝트의 정보로 만들어진 노드 밑으로 다시 추가한다(재귀)
	for (size_t i = 0; i < vecChildren.size(); ++i)
	{
		AddGameObject(pNewNode, vecChildren[i]);
	}
}

UINT OutlinerUI::SelectGameObject(DWORD_PTR _Data)
{
	TreeNode* pSelectedNode = (TreeNode*)_Data;

	CGameObject* pSelectedObject = (CGameObject*)pSelectedNode->GetData();

	Inspector* pInspector = CImGuiMgr::GetInst()->FindEditorUI<Inspector>("Inspector");

	pInspector->SetTargetObject(pSelectedObject);

	return 0;
}
