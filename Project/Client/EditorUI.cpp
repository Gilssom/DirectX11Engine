#include "pch.h"
#include "EditorUI.h"

EditorUI::EditorUI(const string& name, const  string& id)
	: m_Name(name)
	, m_ID(id)
	, m_ParentUI(nullptr)
	, m_Active(true)
	, m_Seperate(false)
{

}

EditorUI::~EditorUI()
{
	// 자식 UI delete
	Safe_Del_Vector(m_vecChildUI);
}

bool EditorUI::SetActive(bool active)
{
	if (m_Active == active)
		return false;

	m_Active = active;

	if (m_Active)
		Activate();
	else
		Deactivate();

	return true;
}

void EditorUI::SetFocus()
{
	string fullname = m_Name + m_ID;

	ImGui::SetWindowFocus(fullname.c_str());
}

void EditorUI::Tick()
{
	// 해당 UI 가 비활성화 상태면 return
	if (!m_Active)
		return;

	string fullname = m_Name + m_ID; // Inspector##Inspector

	// 자신이 "독립적인 UI" 혹은 "부모 UI" 라면 (최상위 UI 객체)
	if (IsRootUI())
	{
		if (m_Seperate)
		{
			// 구분선 생성
			ImGui::Separator();
		}

		// 새로 생긴 x 버튼을 누르면 *bool 을 false 로 변경해줌.
		bool bActive = m_Active;
		ImGui::Begin(fullname.c_str(), &bActive);
		SetActive(bActive);

		Render_Tick();

		// 자식 UI 의 Tick 을 돌려준다.
		for (size_t i = 0; i < m_vecChildUI.size(); i++)
		{
			m_vecChildUI[i]->Tick();
		}

		ImGui::End();
	}
	// 자신이 부모가 있는 "자식 UI" 라면
	else
	{
		if (m_Seperate)
		{
			// 구분선 생성
			//ImGui::Separator();
		}

		//ImGui::BeginChild(fullname.c_str(), m_vChildSize);

		if (ImGui::TreeNode(fullname.c_str()))
		{
			Render_Tick();

			ImGui::Separator();

			// 자식의 자식 UI 의 Tick 을 돌려준다.
			for (size_t i = 0; i < m_vecChildUI.size(); i++)
			{
				m_vecChildUI[i]->Tick();
			}

			ImGui::TreePop();
		}
				
		//ImGui::EndChild();
	}
}