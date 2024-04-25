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

	// Frame ����
	if (m_bFrame)
		iFlag |= ImGuiTreeNodeFlags_Framed;

	// Selected ����
	if (m_bSelected)
		iFlag |= ImGuiTreeNodeFlags_Selected;

	// File Name ����
	if (m_Owner->m_bShowFileName)
	{
		char buffer[256] = {};
		_splitpath_s(name.c_str(), 0, 0, 0, 0, buffer, 256, 0, 0);
		name = buffer;
	}

	// Arrow ����
	if (m_vecChildNode.empty())
	{
		iFlag |= ImGuiTreeNodeFlags_Leaf;

		if(m_bFrame)
			name = "   " + name;
	}

	if (ImGui::TreeNodeEx(name.c_str(), iFlag))
	{
		// �ش� Node ������ ���콺 Ŭ�� ������ �߻��ϸ� �ش� ��带 ���õ� ���·� �����.
		if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
		{
			// Frame Node �� ����
			if(!m_bFrame)
				m_Owner->SetSelectedNode(this);
		}

		// �ڽ� Node Render
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

	// Node �� Owner �� Tree ���� ����
	pNewNode->m_Owner = this;

	// Parent Node �� �������� ������, Root Node �� �߰��ϰڴٴ� �ǹ�
	if (parent == nullptr)
	{
		// ������ �̹� Root Node �� �����Ѵٸ� assert
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
	// Tree �� Node �� �ϳ��� ���� ���
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
	// ������ ���õ� Node �� ������ �ش� Node �� ����
	if (m_SelectedNode)
		m_SelectedNode->m_bSelected = false;

	m_SelectedNode = node;

	// ���� ���õ� Node �� Selected �缳��
	if (m_SelectedNode)
	{
		m_SelectedNode->m_bSelected = true;

		// ��ϵǾ��ִ� Call Back �̳�,
		if (m_SelectedCallBack)
		{
			m_SelectedCallBack();
		}

		// Delegate �� ������ ȣ��
		if (m_SelectedInst && m_SelectedDelegate)
		{
			(m_SelectedInst->*m_SelectedDelegate)((DWORD_PTR)m_SelectedNode);
		}
	}
}