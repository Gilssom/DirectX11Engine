#include "pch.h"
#include "Light2DUI.h"

#include <Engine\\CLight2D.h>

Light2DUI::Light2DUI()
	: ComponentUI("Light2D", "##Light2DUI", COMPONENT_TYPE::LIGHT2D)
{
	SetSize(ImVec2(0, 200));
}

Light2DUI::~Light2DUI()
{
}

void Light2DUI::Render_Tick()
{
	Render_Title();

	CLight2D* pLight2D = GetTarget()->Light2D();
	const tLightInfo& Info = pLight2D->GetLightInfo();

	// Light Type : Directional , Point , Spot
	ImGui::Text("Light Type"); ImGui::SameLine(150);
	const char* arrLightType[] = { "Directional", "Point", "Spot" };

	if (ImGui::BeginCombo("##Light2DType", arrLightType[Info.LightType], 0))
	{
		for (int i = 0; i < 3; i++)
		{
			const bool is_selected = Info.LightType == i;
			if (ImGui::Selectable(arrLightType[i], is_selected))
			{
				pLight2D->SetLightType((LIGHT_TYPE)i);
			}
		}

		ImGui::EndCombo();
	}

	// Light Color
	ImGui::Text("Light Color"); ImGui::SameLine(150);
	ImGui::ColorEdit3("##Light2D Color", (float*)&Info.Light.vDiffuse, 0);

	// Light Ambient
	ImGui::Text("Light Ambient"); ImGui::SameLine(150);
	ImGui::ColorEdit3("##Light2D Ambient", (float*)&Info.Light.vAmbient, 0);

	// Range : Point or Spot Light
	bool IsDirLight = Info.LightType == (UINT)LIGHT_TYPE::DIRECTIONAL;
	float fRange = Info.Range;
	ImGui::BeginDisabled(IsDirLight);

	ImGui::Text("Light Range"); ImGui::SameLine(150);
	if (ImGui::DragFloat("##Light Range", &fRange))
	{
		pLight2D->SetRange(fRange);
	}

	ImGui::EndDisabled();

	// Angle : Only Spot Light
	bool IsSpotLight = Info.LightType == (UINT)LIGHT_TYPE::SPOT;
	float fAngle = Info.Angle;
	ImGui::BeginDisabled(!IsSpotLight);

	ImGui::Text("Spot Light Angle"); ImGui::SameLine(150);
	if (ImGui::DragFloat("##Spot Light Angle", &fAngle))
	{
		pLight2D->SetRange(fAngle);
	}

	ImGui::EndDisabled();
}