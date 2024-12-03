#include "pch.h"
#include "ContentUI.h"

#include <Engine/CAssetMgr.h>
#include "TreeUI.h"


ContentUI::ContentUI()
	: EditorUI("Content", "##Content")
{
	// �ڽ� UI �� TreeUI ����
	m_Tree = new TreeUI;
	m_Tree->SetName("ContentTree");
	AddChildUI(m_Tree);

	// TreeUI �� ��Ʈ��带 �������ʰ� ����
	m_Tree->ShowRoot(false);

	// ��� �׸��� ���� �̸��� ���̰� �Ѵ�.
	m_Tree->ShowFileNameOnly(true);

	// ���� Asset �� ���¸� Ʈ���� �ݿ�
	RenewContent();
}

ContentUI::~ContentUI()
{
}

void ContentUI::RenewContent()
{
	// Tree �� ������ ����
	m_Tree->Clear();

	// Dummy �� ��Ʈ��� �߰�	
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "DummyRoot");	

	// AssetMgr �κ��� Asset ������ �޾ƿͼ� Ʈ���� �ݿ���Ų��.
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		TreeNode* pCategoryNode = m_Tree->AddTreeNode(pRootNode, ASSET_TYPE_STRING[i]);
		pCategoryNode->SetFrame(true);
		
		const map<wstring, Ptr<CAsset>>& mapAsset = CAssetMgr::GetInst()->GetAssets((ASSET_TYPE)i);

		for (const auto& pair : mapAsset)
		{
			m_Tree->AddTreeNode(pCategoryNode, ToString(pair.first).c_str(), (DWORD_PTR)pair.second.Get());
		}
	}
}

void ContentUI::render_tick()
{
	
}