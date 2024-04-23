#include "pch.h"
#include "TreeUI.h"

// ===========
//  Tree Node
// ===========
TreeNode::~TreeNode()
{
	Safe_Del_Vector(m_vecChildNode);
}

void TreeNode::Render_Tick()
{
	UINT iFlag = 0;

	if (m_bFrame)
		iFlag |= ImGuiTreeNodeFlags_Framed;

	if (m_vecChildNode.empty())
		iFlag |= ImGuiTreeNodeFlags_Leaf;

	if (ImGui::TreeNodeEx(m_Name.c_str(), iFlag))
	{
		for (size_t i = 0; i < m_vecChildNode.size(); i++)
		{
			m_vecChildNode[i]->Render_Tick();
		}

		ImGui::TreePop();
	}
}




// ===========
//   Tree UI
// ===========
TreeUI::TreeUI()
	: EditorUI("", "##Tree")
	, m_RootNode(nullptr)
	, m_bShowRoot(false)
{

}

TreeUI::~TreeUI()
{
	if (m_RootNode != nullptr)
	{
		delete m_RootNode;
	}
}

TreeNode* TreeUI::AddTreeNode(TreeNode* parent, const string& nodeName, DWORD_PTR dwData)
{
	TreeNode* pNewNode = new TreeNode(nodeName, dwData);

	// Parent Node 를 지정하지 않으면, Root Node 로 추가하겠다는 의미
	if (parent == nullptr)
	{
		// 하지만 이미 Root Node 가 존재한다면 assert
		assert(!m_RootNode);

		m_RootNode = pNewNode;
	}
	else
	{
		parent->AddChildNode(pNewNode);
	}

	return pNewNode;
}

void TreeUI::Render_Tick()
{
	if (m_bShowRoot)
	{
		m_RootNode->Render_Tick();
	}
	else
	{
		const vector<TreeNode*>& vecChildNode = m_RootNode->GetChildNode();

		for (size_t i = 0; i < vecChildNode.size(); i++)
		{
			vecChildNode[i]->Render_Tick();
		}
	}
}