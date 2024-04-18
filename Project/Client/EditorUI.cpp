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
	// �ڽ� UI delete
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
	// �ش� UI �� ��Ȱ��ȭ ���¸� return
	if (!m_Active)
		return;

	string fullname = m_Name + m_ID; // Inspector##Inspector

	// �ڽ��� "�������� UI" Ȥ�� "�θ� UI" ��� (�ֻ��� UI ��ü)
	if (IsRootUI())
	{
		if (m_Seperate)
		{
			// ���м� ����
			ImGui::Separator();
		}

		// ���� ���� x ��ư�� ������ *bool �� false �� ��������.
		bool bActive = m_Active;
		ImGui::Begin(fullname.c_str(), &bActive);
		SetActive(bActive);

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
		if (m_Seperate)
		{
			// ���м� ����
			//ImGui::Separator();
		}

		//ImGui::BeginChild(fullname.c_str(), m_vChildSize);

		if (ImGui::TreeNode(fullname.c_str()))
		{
			Render_Tick();

			ImGui::Separator();

			// �ڽ��� �ڽ� UI �� Tick �� �����ش�.
			for (size_t i = 0; i < m_vecChildUI.size(); i++)
			{
				m_vecChildUI[i]->Tick();
			}

			ImGui::TreePop();
		}
				
		//ImGui::EndChild();
	}
}