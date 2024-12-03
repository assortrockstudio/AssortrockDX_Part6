#include "pch.h"
#include "ContentUI.h"

#include <Engine/CAssetMgr.h>
#include "TreeUI.h"


ContentUI::ContentUI()
	: EditorUI("Content", "##Content")
{
	// 자식 UI 로 TreeUI 생성
	m_Tree = new TreeUI("ContentTree");	
	AddChildUI(m_Tree);

	// TreeUI 의 루트노드를 보이지않게 설정
	m_Tree->ShowRoot(false);

	// 노드 항목의 파일 이름만 보이게 한다.
	m_Tree->ShowFileNameOnly(true);

	// 현재 Asset 의 상태를 트리에 반영
	RenewContent();
}

ContentUI::~ContentUI()
{
}

void ContentUI::RenewContent()
{
	// Tree 의 내용을 삭제
	m_Tree->Clear();

	// Dummy 용 루트노드 추가	
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "DummyRoot");	

	// AssetMgr 로부터 Asset 정보를 받아와서 트리에 반영시킨다.
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