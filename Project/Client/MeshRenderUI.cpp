#include "pch.h"
#include "MeshRenderUI.h"

MeshRenderUI::MeshRenderUI()
	: ComponentUI("MeshRenderUI", "##MeshRenderUI", COMPONENT_TYPE::MESHRENDER)
{
}

MeshRenderUI::~MeshRenderUI()
{
}

void MeshRenderUI::Render_Tick()
{
	ImGui::Text("MeshRenderUI");
}
