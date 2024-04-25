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
	string name = m_Name;

	UINT iFlag = 0;

	// Frame 설정
	if (m_bFrame)
		iFlag |= ImGuiTreeNodeFlags_Framed;

	// Selected 설정
	if (m_bSelected)
		iFlag |= ImGuiTreeNodeFlags_Selected;

	// File Name 설정
	if (m_Owner->m_bShowFileName)
	{
		char buffer[256] = {};
		_splitpath_s(name.c_str(), 0, 0, 0, 0, buffer, 256, 0, 0);
		name = buffer;
	}

	// Arrow 설정
	if (m_vecChildNode.empty())
	{
		iFlag |= ImGuiTreeNodeFlags_Leaf;

		if(m_bFrame)
			name = "   " + name;
	}

	if (ImGui::TreeNodeEx(name.c_str(), iFlag))
	{
		// 해당 Node 위에서 마우스 클릭 해제가 발생하면 해당 노드를 선택된 상태로 만든다.
		if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
		{
			// Frame Node 는 제외
			if(!m_bFrame)
				m_Owner->SetSelectedNode(this);
		}

		// 자식 Node Render
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
TreeUI::TreeUI(const string& name)
	: EditorUI(name, "##Tree")
	, m_RootNode(nullptr)
	, m_bShowRoot(false)
	, m_bShowFileName(false)
	, m_SelectedNode(nullptr)
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

	// Node 의 Owner 가 Tree 임을 설정
	pNewNode->m_Owner = this;

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
	// Tree 에 Node 가 하나도 없는 경우
	if (m_RootNode == nullptr)
		return;

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

void TreeUI::SetSelectedNode(TreeNode* node)
{
	// 이전에 선택된 Node 가 있으면 해당 Node 는 해제
	if (m_SelectedNode)
		m_SelectedNode->m_bSelected = false;

	m_SelectedNode = node;

	// 새로 선택된 Node 로 Selected 재설정
	if (m_SelectedNode)
	{
		m_SelectedNode->m_bSelected = true;

		// 등록되어있는 Call Back 이나,
		if (m_SelectedCallBack)
		{
			m_SelectedCallBack();
		}

		// Delegate 가 있으면 호출
		if (m_SelectedInst && m_SelectedDelegate)
		{
			(m_SelectedInst->*m_SelectedDelegate)((DWORD_PTR)m_SelectedNode);
		}
	}
}