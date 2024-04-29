#include "pch.h"
#include "MaterialUI.h"

#include <Engine\CMaterial.h>
#include <Engine\CShader.h>

MaterialUI::MaterialUI()
	: AssetUI("MaterialUI", "##MaterialUI", ASSET_TYPE::MATERIAL)
{

}

MaterialUI::~MaterialUI()
{

}

void MaterialUI::Render_Tick()
{
	Render_Title();

	string strName = ToString(GetTarget()->GetKey());

	Ptr<CMaterial> pMaterial = dynamic_cast<CMaterial*>(GetTarget().Get());
	assert(pMaterial.Get());

	// Mesh Name
	ImGui::Text("Material Name"); SAME_SET(110);
	ImGui::InputText("##MaterialNameMaterialUI", (char*)strName.c_str(), strName.capacity(), ImGuiInputTextFlags_ReadOnly);

	// Shader Info
	string strShaderName = nullptr == pMaterial->GetShader() ? "null" : ToString(pMaterial->GetShader()->GetKey());

	ImGui::Text("Shader Name"); SAME_SET(110);
	ImGui::InputText("##ShaderNameMaterialUI", (char*)strShaderName.c_str(), strShaderName.capacity(), ImGuiInputTextFlags_ReadOnly);

	// Shader 의 내부 수치까지 조절 가능하게 구현할 예정
}