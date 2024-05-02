#include "pch.h"
#include "MaterialUI.h"

#include <Engine\CMaterial.h>
#include <Engine\CGraphicShader.h>

#include "ParamUI.h"

MaterialUI::MaterialUI()
	: AssetUI("MaterialUI", "##MaterialUI", ASSET_TYPE::MATERIAL)
	, m_ParamDescMaxWidth(0)
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

	// Shader �� ���� ��ġ���� ���� �����ϰ� ������ ����

	// Material �� �����ϴ� Shader �� �ִٸ�
	if (pMaterial->GetShader() == nullptr)
		return;

	// Shader �� ��û�� Parameter ��� Ȯ��
	Ptr<CGraphicShader> pShader = pMaterial->GetShader();
	vector<tShaderScalarParam> ScalarParam = pShader->GetScalarParam();

	if(!ScalarParam.empty())
		ImGui::SeparatorText("Shader Parmeter");

	ParamUI::SetDescWidth(m_ParamDescMaxWidth);

	for (size_t i = 0; i < ScalarParam.size(); i++)
	{
		// Parameter �� Desc �� �ִ� ���� ���̸� ����Ѵ�.
		ImVec2 vDescWidth = ImGui::CalcTextSize(ScalarParam[i].strDesc.c_str());
		if (m_ParamDescMaxWidth < vDescWidth.x)
		{
			m_ParamDescMaxWidth = vDescWidth.x;
		}

		switch (ScalarParam[i].Param)
		{
		case INT_0:
		case INT_1:
		case INT_2:
		case INT_3:
			ParamUI::Param_DragInt(ScalarParam[i].strDesc, (int*)pMaterial->GetScalarParam(ScalarParam[i].Param));
			break;
		case FLOAT_0:
		case FLOAT_1:
		case FLOAT_2:
		case FLOAT_3:
			ParamUI::Param_DragFloat(ScalarParam[i].strDesc, (float*)pMaterial->GetScalarParam(ScalarParam[i].Param), 0.01f);
			break;
		case VEC2_0:
		case VEC2_1:
		case VEC2_2:
		case VEC2_3:
			ParamUI::Param_DragVec2(ScalarParam[i].strDesc, (Vec2*)pMaterial->GetScalarParam(ScalarParam[i].Param), 0.01f);
			break;
		case VEC4_0:
		case VEC4_1:
		case VEC4_2:
		case VEC4_3:
			ParamUI::Param_DragVec4(ScalarParam[i].strDesc, (Vec4*)pMaterial->GetScalarParam(ScalarParam[i].Param), 0.01f);
			break;
		case MAT_0:
		case MAT_1:
		case MAT_2:
		case MAT_3:
			ParamUI::Param_DragMat(ScalarParam[i].strDesc, (Matrix*)pMaterial->GetScalarParam(ScalarParam[i].Param), 0.01f);
			break;
		}
	}


	// Shader �� ��û�� Texture Parameter ��� Ȯ��
	vector<tShaderTexParam> TexParam = pShader->GetTexParam();

	if (!TexParam.empty())
		ImGui::SeparatorText("Texture Parmeter");
	for (size_t i = 0; i < TexParam.size(); i++)
	{
		// Parameter �� Desc �� �ִ� ���� ���̸� ����Ѵ�.
		ImVec2 vDescWidth = ImGui::CalcTextSize(TexParam[i].strDesc.c_str());
		if (m_ParamDescMaxWidth < vDescWidth.x)
		{
			m_ParamDescMaxWidth = vDescWidth.x;
		}

		ParamUI::Param_Texture(TexParam[i].strDesc, pMaterial->GetTexParam(TexParam[i].Param));
	}
}

void MaterialUI::TargetChanged()
{
	m_ParamDescMaxWidth = 0;
}