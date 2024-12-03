#include "pch.h"
#include "ContentUI.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CPathMgr.h>

#include "Inspector.h"
#include "TreeUI.h"


ContentUI::ContentUI()
	: EditorUI("Content", "##Content")
{
	// �ڽ� UI �� TreeUI ����
	m_Tree = new TreeUI("ContentTree");	
	AddChildUI(m_Tree);

	// TreeUI �� ��Ʈ��带 �������ʰ� ����
	m_Tree->ShowRoot(false);

	// TreeUI �� Drag ����� �Ҵ�.
	m_Tree->UseDrag(true);

	// ��� �׸��� ���� �̸��� ���̰� �Ѵ�.
	m_Tree->ShowFileNameOnly(true);

	// �׸� ���ý� ������ CallBack OR Delegate ���	
	m_Tree->RegisterSelectDelegate(this, (UI_DELEGATE1)&ContentUI::SelectAsset);

	// Content ������ �ִ� ��� ������ �޸𸮿� �ε�
	ReloadContent();

	// ���� Asset �� ���¸� Ʈ���� �ݿ�
	RenewContent();
}

ContentUI::~ContentUI()
{
}

void ContentUI::render_tick()
{
	if (CAssetMgr::GetInst()->IsAssetChanged())
	{
		RenewContent();
	}
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

void ContentUI::ReloadContent()
{
	// Content ���� ������ �����ϴ� ��� ���ϸ��� �˾Ƴ���.
	FindFileName(CPathMgr::GetInst()->GetContentPath());

}

void ContentUI::FindFileName(const wstring& _strFolderPath)
{
	wstring strFindPath = _strFolderPath + L"*.*";

	WIN32_FIND_DATA FindData = {};

	// ������ ���� �� ���͸��� �ش��ϴ� ������ Ž���ϴ� Ž����ü ����, �ڵ鰪 �ޱ�
	HANDLE hFind = FindFirstFile(strFindPath.c_str(), &FindData);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		MessageBox(nullptr, strFindPath.c_str(), L"���� Ž�� ����", MB_OK);
	}

	// �ش� ������ ���̻� ���� �� ������ �������� ������ ���� Ž�� ����
	while (FindNextFile(hFind, &FindData))
	{
		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!wcscmp(FindData.cFileName, L".."))
				continue;

			FindFileName(_strFolderPath + FindData.cFileName + L"\\");
		}
		
		else
		{
			m_vecContentName.push_back(FindData.cFileName);
		}
	}

	FindClose(hFind);	
}

UINT ContentUI::SelectAsset(DWORD_PTR _Data)
{
	TreeNode* pSelectedNode = (TreeNode*)_Data;

	pSelectedNode->GetName();
	Ptr<CAsset> pAsset = (CAsset*)pSelectedNode->GetData();

	Inspector* pInspector = CImGuiMgr::GetInst()->FindEditorUI<Inspector>("Inspector");

	pInspector->SetTargetAsset(pAsset);

	return 0;
}
