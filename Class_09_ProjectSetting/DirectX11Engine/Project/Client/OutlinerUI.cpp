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
	// �ڽ� UI �� TreeUI ����
	m_Tree = new TreeUI("OutlinerTree");	
	AddChildUI(m_Tree);

	// TreeUI �� ��Ʈ��带 �������ʰ� ����
	m_Tree->ShowRoot(false);

	// �׸� ���ý� ������ CallBack OR Delegate ���	
	m_Tree->RegisterSelectDelegate(this, (UI_DELEGATE1)&OutlinerUI::SelectGameObject);

	
	// ���� Asset �� ���¸� Ʈ���� �ݿ�
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
	// Tree �� Clear �Ѵ�.
	m_Tree->Clear();
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "DummyRoot");

	// ���� ������ �˾Ƴ���.
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
	
	// ���� �ش� ������Ʈ�� �ڽ� ������Ʈ�� �����ϰ� �ִٸ�
	const vector<CGameObject*>& vecChildren = _Object->GetChildren();

	// �ڽ� ������Ʋ �θ������Ʈ�� ������ ������� ��� ������ �ٽ� �߰��Ѵ�(���)
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
