#include "pch.h"
#include "ContentUI.h"

#include "TreeUI.h"

ContentUI::ContentUI()
	: EditorUI("Content", "##Content")
{
	m_Tree = new TreeUI;
	m_Tree->SetName("Content Tree");
	AddChildUI(m_Tree);

	m_Tree->ShowRoot(false);

	// parent 가 nullptr 이면 Root Node 지정
	TreeNode* pNode = m_Tree->AddTreeNode(nullptr, "Root Node");

	// Root Node(=pNode) 밑에 Child Node 추가
	TreeNode* pChildNode1 = m_Tree->AddTreeNode(pNode, "Child Node 1");
	TreeNode* pChildNode2 = m_Tree->AddTreeNode(pNode, "Child Node 2");
	TreeNode* pChildNode3 = m_Tree->AddTreeNode(pNode, "Child Node 3");

	pChildNode1->SetFrame(true);
	pChildNode2->SetFrame(true);
	pChildNode3->SetFrame(true);

	m_Tree->AddTreeNode(pChildNode1, "Child Node 1-1");
	m_Tree->AddTreeNode(pChildNode1, "Child Node 1-2");
	m_Tree->AddTreeNode(pChildNode1, "Child Node 1-3");
}

ContentUI::~ContentUI()
{

}

void ContentUI::Render_Tick()
{
	//ImGui::Text("Content UI");
}