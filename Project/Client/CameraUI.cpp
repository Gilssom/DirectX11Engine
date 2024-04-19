#include "pch.h"
#include "CameraUI.h"

#include <Engine\\CCamera.h>

CameraUI::CameraUI()
	: ComponentUI("Camera", "##CameraUI", COMPONENT_TYPE::CAMERA)
{
	SetSize(ImVec2(0, 200));
}

CameraUI::~CameraUI()
{
}

void CameraUI::Render_Tick()
{
	Render_Title();

    CCamera* pCam = GetTarget()->Camera();

	// 투영 방식 Projection Type
    PROJ_TYPE ProjType = pCam->GetProjType();

    const char* items[2] = {};

    items[0] = "Orthographic";
    items[1] = "Perspective";

    if (ImGui::BeginCombo("##CameraProjType", items[(UINT)ProjType], 0))
    {
        for (int i = 0; i < 2; i++)
        {
            const bool is_selected = ((UINT)ProjType == i);
            if (ImGui::Selectable(items[i], is_selected))
            {
                pCam->SetProjType((PROJ_TYPE)i);
            }
        }

        ImGui::EndCombo();
    }

	// Camera Priority (우선순위)

	// Camera FOV

	// Camera Far

	// Camera Width
	// Camera AspectRatio

	// Camera Scale(Orthographic - 투영 범위)

	// Camera Layer Check

}