#include "pch.h"
#include "TransformUI.h"

#include <Engine\\CTransform.h>

TransformUI::TransformUI()
	: ComponentUI("Transform", "##TransformUI", COMPONENT_TYPE::TRANSFORM)
{
	SIZE;
}

TransformUI::~TransformUI()
{
}

void TransformUI::Render_Tick()
{
	// Title 출력
	Render_Title();

	// 해당 UI에 출력할 정보 입력
	// Vector3 에 Vector 의 포인터를 넘겨주는 operator 가 구현이 되어 있음
	Vec3 vPos = GetTarget()->Transform()->GetRelativePos();
	Vec3 vScale = GetTarget()->Transform()->GetRelativeScale();
	Vec3 vRotation = GetTarget()->Transform()->GetRelativeRotation();

	ImGui::Text("Position"); SAME;
	if (ImGui::DragFloat3("##Position", vPos, 0.1f))
		GetTarget()->Transform()->SetRelativePos(vPos);

	ImGui::Text("Scale"); SAME;
	if (ImGui::DragFloat3("##Scale", vScale, 0.1f))
		GetTarget()->Transform()->SetRelativeScale(vScale);

	ImGui::Text("Rotation"); SAME;
	vRotation = (vRotation / XM_PI) * 180.f;
	if (ImGui::DragFloat3("##Rotation", vRotation, 0.1f))
	{
		vRotation = (vRotation / 180.f) * XM_PI;
		GetTarget()->Transform()->SetRelativeRotation(vRotation);
	}

	bool Absolute = GetTarget()->Transform()->IsAbsolute();
	ImGui::Text("Is Absolute"); SAME;
	if (ImGui::Checkbox("##Absolute", &Absolute))
	{
		GetTarget()->Transform()->SetAbsolute(Absolute);
	}
}