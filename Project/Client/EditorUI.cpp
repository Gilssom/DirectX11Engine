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
	// �ڽ� UI delete
	Safe_Del_Vector(m_vecChildUI);
}

void EditorUI::Tick()
{
	// �ش� UI �� ��Ȱ��ȭ ���¸� return
	if (!m_Active)
		return;

	string fullname = m_Name + m_ID; // Inspector##Inspector

	// �ڽ��� "�������� UI" Ȥ�� "�θ� UI" ��� (�ֻ��� UI ��ü)
	if (IsRootUI())
	{
		ImGui::Begin(fullname.c_str());

		Render_Tick();

		// �ڽ� UI �� Tick �� �����ش�.
		for (size_t i = 0; i < m_vecChildUI.size(); i++)
		{
			m_vecChildUI[i]->Tick();
		}

		ImGui::End();
	}
	// �ڽ��� �θ� �ִ� "�ڽ� UI" ���
	else
	{
		ImGui::BeginChild(fullname.c_str(), m_vChildSize);

		Render_Tick();

		// �ڽ��� �ڽ� UI �� Tick �� �����ش�.
		for (size_t i = 0; i < m_vecChildUI.size(); i++)
		{
			m_vecChildUI[i]->Tick();
		}

		ImGui::EndChild();
	}
}