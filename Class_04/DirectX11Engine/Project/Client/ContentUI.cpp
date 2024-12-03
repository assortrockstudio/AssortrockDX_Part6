#include "pch.h"
#include "ContentUI.h"

#include "TreeUI.h"

ContentUI::ContentUI()
	: EditorUI("Content", "##Content")
{
	m_Tree = new TreeUI;
	m_Tree->SetName("ContentTree");
	AddChildUI(m_Tree);

	m_Tree->ShowRoot(false);

	// ��Ʈ��� �߰�
	TreeNode* pNode = m_Tree->AddTreeNode(nullptr, "RootNode");

	// ��Ʈ ��� �ؿ� �ڽĳ�� 3�� �߰�
	TreeNode* pChild1Node = m_Tree->AddTreeNode(pNode, "ChildNode 1");
	TreeNode* pChild2Node = m_Tree->AddTreeNode(pNode, "ChildNode 2");
	TreeNode* pChild3Node = m_Tree->AddTreeNode(pNode, "ChildNode 3");

	pChild1Node->SetFrame(true);
	pChild2Node->SetFrame(true);
	pChild3Node->SetFrame(true);

	// ChildNode 1 �ؿ� �ڽ� �߰�
	m_Tree->AddTreeNode(pChild1Node, "ChildNode 1-1");
	m_Tree->AddTreeNode(pChild1Node, "ChildNode 1-2");
	m_Tree->AddTreeNode(pChild1Node, "ChildNode 1-3");
}

ContentUI::~ContentUI()
{
}

void ContentUI::render_tick()
{
	
}