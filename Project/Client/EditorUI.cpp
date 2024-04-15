#include "pch.h"
#include "EditorUI.h"

EditorUI::EditorUI(const string& name, const  string& id)
	: m_Name(name)
	, m_ID(id)
	, m_ParentUI(nullptr)
	, m_Active(true)
{

}

EditorUI::~EditorUI()
{
	// 자식 UI delete
	Safe_Del_Vector(m_vecChildUI);
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
		ImGui::Begin(fullname.c_str());

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
		ImGui::BeginChild(fullname.c_str(), m_vChildSize);

		Render_Tick();

		// 자식의 자식 UI 의 Tick 을 돌려준다.
		for (size_t i = 0; i < m_vecChildUI.size(); i++)
		{
			m_vecChildUI[i]->Tick();
		}

		ImGui::EndChild();
	}
}