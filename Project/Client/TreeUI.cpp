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

	// 화살표를 누르거나, 더블클릭한 경우에만 자식 노드를 펼친다.
	UINT iFlag = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;

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
		// Node 의 소유자(Tree UI) 가 Drag 기능을 사용하기로 했다면 아래 구문 체크
		if (m_Owner->m_bUseDrag)
		{
			if (ImGui::BeginDragDropSource())
			{
				// 첫번째 인자 ID 는 Node 의 소유자(Tree UI) (ex Outliner, Content)
				// 그 다음 전달하고자 하는 Data 의 시작 주소와 크기를 인자로
				ImGui::SetDragDropPayload(m_Owner->GetParentUI()->GetName().c_str(), &m_Data, sizeof(DWORD_PTR));

				// PayLoad 후, EndDragDrop 전에 사용된 Text 는 ToolTip 으로 적용된다.
				ImGui::Text(m_Name.c_str());

				ImGui::EndDragDropSource();
			}
		}

		// 해당 Node 위에서 마우스 클릭 해제가 발생하면 해당 노드를 선택된 상태로 만든다.
		if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
		{
			// 닫혀있는 부모 Tree 클릭 시 아래 함수 호출이 안됨
			if (ImGui::IsItemHovered())
			{
				// Frame Node 는 제외
				if (!m_bFrame)
					m_Owner->SetSelectedNode(this);
			}
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
	, m_bUseDrag(false)
	, m_bUseDrop(false)
	, m_SelectedCallBack(nullptr)
	, m_SelectedInst(nullptr)
	, m_SelectedDelegate(nullptr)
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