#include "pch.h"
#include "EditorUI.h"

EditorUI::EditorUI(const string& name, const  string& id)
	: m_Name(name)
	, m_ID(id)
{
}

EditorUI::~EditorUI()
{
}

void EditorUI::Tick()
{
	string fullname = m_Name + m_ID; // Inspector##Inspector

	ImGui::Begin(fullname.c_str());

	Render_Tick();

	ImGui::End();
}