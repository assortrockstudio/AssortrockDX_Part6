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
	string name = m_Name;

	UINT iFlag = 0;

	// ������ ����
	if (m_bFrame)
		iFlag |= ImGuiTreeNodeFlags_Framed;

	// ���� �̸� ����
	if (m_Owner->m_bShowFileName)
	{
		char buffer[256] = {};
		_splitpath_s(name.c_str(), 0, 0, 0, 0, buffer, 256, 0, 0);
		name = buffer;
	}

	// ȭ��ǥ ����
	if (m_vecChildNode.empty())
	{
		iFlag |= ImGuiTreeNodeFlags_Leaf;
		name = "   " + name;
	}

	if (ImGui::TreeNodeEx(name.c_str(), iFlag))
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

	// ����� �����ڰ� Ʈ������ ������
	pNewNode->m_Owner = this;

	// �θ��带 �������� ������, ��Ʈ���� �߰��ϰڴٴ� �ǹ�	
	if (nullptr == _Parent)
	{
		// �̹� ��Ʈ�� TreeUI �� �����ϸ� assert
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
	// Ʈ���� ��尡 �ϳ��� ���� ���
	if (nullptr == m_RootNode)
		return;

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

