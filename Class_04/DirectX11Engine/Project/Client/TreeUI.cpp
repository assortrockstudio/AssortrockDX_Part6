#include "pch.h"
#include "TreeUI.h"


// =========
// Tree Node
// =========
TreeNode::~TreeNode()
{
	Safe_Del_Vector(m_vecChildNode);
}

void TreeNode::render_tick()
{
	UINT iFlag = 0;

	if (m_bFrame)
		iFlag |= ImGuiTreeNodeFlags_Framed;

	if (m_vecChildNode.empty())
		iFlag |= ImGuiTreeNodeFlags_Leaf;


	if (ImGui::TreeNodeEx(m_Name.c_str(), iFlag))
	{
		for (size_t i = 0; i < m_vecChildNode.size(); ++i)
		{
			m_vecChildNode[i]->render_tick();
		}

		ImGui::TreePop();
	}
}













// ========
// TreeUI
// ========

TreeUI::TreeUI()
	: EditorUI("", "##Tree")
	, m_RootNode(nullptr)
	, m_bShowRoot(true)
{
}

TreeUI::~TreeUI()
{
	if (nullptr != m_RootNode)
	{
		delete m_RootNode;
	}
}

TreeNode* TreeUI::AddTreeNode(TreeNode* _Parent, const string& _NodeName, DWORD_PTR _dwData)
{
	TreeNode* pNewNode = new TreeNode(_NodeName, _dwData);

	// 부모노드를 지정하지 않으면, 루트노드로 추가하겠다는 의미	
	if (nullptr == _Parent)
	{
		// 이미 루트가 TreeUI 에 존재하면 assert
		assert(!m_RootNode);

		m_RootNode = pNewNode;		
	}

	else
	{
		_Parent->AddChildNode(pNewNode);
	}


	return pNewNode;
}

void TreeUI::render_tick()
{	
	if (m_bShowRoot)
	{
		m_RootNode->render_tick();
	}

	else
	{
		const vector<TreeNode*>& vecChildNode = m_RootNode->GetChildNode();

		for (size_t i = 0; i < vecChildNode.size(); ++i)
		{
			vecChildNode[i]->render_tick();
		}
	}
}

