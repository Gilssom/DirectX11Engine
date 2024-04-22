#include "pch.h"
#include "CameraUI.h"

#include <Engine\\CRenderManager.h>
#include <Engine\\CCamera.h>

CameraUI::CameraUI()
	: ComponentUI("Camera", "##CameraUI", COMPONENT_TYPE::CAMERA)
{
	//SetSize(ImVec2(0, 200));
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
    bool IsPerspective = ProjType == PROJ_TYPE::PERSPECTIVE;
    bool IsOrthographic = ProjType == PROJ_TYPE::ORTHOGRAPHIC;

    const char* items[2] = {};

    items[0] = "Orthographic";
    items[1] = "Perspective";

    ImGui::Text("Projection Type"); ImGui::SameLine(150);
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
    // Render Manager 로 부터 카메라 등록 최대 Capacity 를 알아낸다.
    vector<CCamera*>& vecCam = CRenderManager::GetInst()->GetRegisteredCamera();
    
    ImGui::Text("Priority"); ImGui::SameLine(150);
    int iPriority = pCam->GetCameraPriority();
    if (ImGui::InputInt("##CameraPriority", &iPriority))
    {
        // 카메라 우선순위 값을 변경했다면
        int CurPriority = pCam->GetCameraPriority();
        vecCam[CurPriority] = nullptr;
        pCam->SetCameraPriority(iPriority);
    }

    vector<string> vecCamName;

    for (size_t i = 0; i < vecCam.size(); i++)
    {
        char buffer[256] = {};
        sprintf_s(buffer, 256, "Priority %d : ", i);
        string Name = buffer;

        if (vecCam[i] == nullptr)
            vecCamName.push_back(Name + "null");
        else
            vecCamName.push_back(Name + ToString(vecCam[i]->GetOwner()->GetName()));
    }

    string strCurCamName;
    char buffer[256] = {};
    sprintf_s(buffer, 256, "Priority %d : ", iPriority);
    strCurCamName = buffer;
    strCurCamName += ToString(pCam->GetOwner()->GetName());

    ImGui::Text(""); ImGui::SameLine(150);
    if (ImGui::BeginCombo("##RegisteredCamera", strCurCamName.c_str(), 0))
    {
        for (size_t i = 0; i < vecCamName.size(); i++)
        {
            const bool is_selected = strCurCamName == vecCamName[i];
            if (ImGui::Selectable(vecCamName[i].c_str(), is_selected))
            {
                int a = 0;
            }
        }

        ImGui::EndCombo();
    }


	// Camera FOV (시야각도_원근 투영에서만)
    float FOV = pCam->GetFOV();
    FOV = (FOV * 180.f) / XM_PI;
    ImGui::Text("FOV"); ImGui::SameLine(150);

    ImGui::BeginDisabled(IsOrthographic);

    if (ImGui::DragFloat("##CameraFOV", &FOV, 0.1f, 0.f, 0.f, "%.3f"))
    {
        FOV = (FOV * XM_PI) / 180.f;
        pCam->SetFOV(FOV);
    }

    ImGui::EndDisabled();


	// Camera Far
    float Far = pCam->GetFar();
    ImGui::Text("Far"); ImGui::SameLine(150);

    if (ImGui::DragFloat("##CameraFar", &Far, 1.f))
    {
        if (Far < 2.f)
            Far = 2.f;

        pCam->SetFar(Far);
    }

	// Camera Width
    ImGui::Text("Width"); ImGui::SameLine(150);
    float Width = pCam->GetWidth();
    if (ImGui::DragFloat("##CameraWidth", &Width, 1.f))
    {
        if (Width < 1.f)
            Width = 1.f;

        pCam->SetWidth(Width);
    }
    
	// Camera AspectRatio
    ImGui::Text("AspectRatio"); ImGui::SameLine(150);
    float AspectRatio = pCam->GetAspectRatio();
    if (ImGui::DragFloat("##CameraAspectRatio", &AspectRatio, 0.1f))
    {
        if (AspectRatio < 0.f)
            AspectRatio = 0.f;

        pCam->SetAspectRatio(AspectRatio);
    }

	// Camera Scale(Orthographic - 투영 범위_직교 투영에서만)
    ImGui::Text("Projection Scale"); ImGui::SameLine(150);
    float Scale = pCam->GetScale();
    
    ImGui::BeginDisabled(IsPerspective);

    if (ImGui::DragFloat("##CameraScale", &Scale, 0.01f))
    {
        if (Scale < 0.1f)
            Scale = 0.1f;

        pCam->SetScale(Scale);
    }

    ImGui::EndDisabled();

	// Camera Layer Check
    //ImGui::Text("Layer Check"); ImGui::SameLine(120);
}