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

	// 프레임 설정
	if (m_bFrame)
		iFlag |= ImGuiTreeNodeFlags_Framed;

	if (m_bSelected)
		iFlag |= ImGuiTreeNodeFlags_Selected;

	// 파일 이름 설정
	if (m_Owner->m_bShowFileName)
	{
		char buffer[256] = {};
		_splitpath_s(name.c_str(), 0, 0, 0, 0, buffer, 256, 0, 0);
		name = buffer;
	}

	// 화살표 설정
	if (m_vecChildNode.empty())
	{
		iFlag |= ImGuiTreeNodeFlags_Leaf;
		if (m_bFrame)
			name = "   " + name;
	}

	if (ImGui::TreeNodeEx(name.c_str(), iFlag))
	{
		// 해당 노드위에서 마우스 해제가 발생하면 해당 노드를 선택된 상태로 만든다.
		if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
		{	
			// 프레임 노드는 선택개념이 없다.
			if (!m_bFrame)
			{
				m_Owner->SetSelectedNode(this);
			}			
		}

		// 자식 노드 render
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
TreeUI::TreeUI(const string& _Name)
	: EditorUI(_Name, "##Tree")
	, m_RootNode(nullptr)
	, m_bShowRoot(true)
	, m_bShowFileName(false)
	, m_SelectedNode(nullptr)
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

	// 노드의 소유자가 트리임을 세팅함
	pNewNode->m_Owner = this;

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
	// 트리에 노드가 하나도 없는 경우
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


void TreeUI::SetSelectedNode(TreeNode* _Node)
{
	// 이전에 선택된 노드가 있으면 선택상태를 해제
	if (m_SelectedNode)
		m_SelectedNode->m_bSelected = false;

	m_SelectedNode = _Node;

	if (m_SelectedNode)
	{
		m_SelectedNode->m_bSelected = true;

		// 등록되어있는 CallBack, Delegate 가 있으면 호출시켜준다.
		if (m_SelectedCallBack)
		{
			m_SelectedCallBack();
		}

		if (m_SelectedInst && m_SelectedDelegate)
		{
			(m_SelectedInst->*m_SelectedDelegate)((DWORD_PTR)m_SelectedNode);
		}
	}	
}