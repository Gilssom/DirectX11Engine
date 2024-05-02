#include "pch.h"
#include "ParamUI.h"

#include "ImGui\\imgui.h"
#include "CImGuiManager.h"

UINT ParamUI::g_ParamUI_ID = 0;
int ParamUI::g_DescWidth = 0;

int ParamUI::Param_DragInt(const string& strName, int* pInOut, int speed)
{
    // Parmeter Name
    ImGui::Text(strName.c_str()); ImGui::SameLine(g_DescWidth);

    char key[255] = {};
    sprintf_s(key, 255, "##DragInt_%d", g_ParamUI_ID++);

    if (ImGui::DragInt(key, pInOut, speed))
    {
        return true;
    }

    return false;
}

int ParamUI::Param_DragFloat(const string& strName, float* pInOut, float speed)
{
    // Parmeter Name
    ImGui::Text(strName.c_str()); ImGui::SameLine(g_DescWidth);

    char key[255] = {};
    sprintf_s(key, 255, "##DragFloat_%d", g_ParamUI_ID++);

    if (ImGui::DragFloat(key, pInOut, speed))
    {
        return true;
    }

    return false;
}

int ParamUI::Param_DragVec2(const string& strName, Vec2* pInOut, float speed)
{
    // Parmeter Name
    ImGui::Text(strName.c_str()); ImGui::SameLine(g_DescWidth);

    char key[255] = {};
    sprintf_s(key, 255, "##DragVec2_%d", g_ParamUI_ID++);

    float arr[2] = { pInOut->x, pInOut->y };
    if (ImGui::DragFloat2(key, arr, speed))
    {
        pInOut->x = arr[0];
        pInOut->y = arr[1];
        return true;
    }

    return false;
}

int ParamUI::Param_DragVec4(const string& strName, Vec4* pInOut, float speed)
{
    // Parmeter Name
    ImGui::Text(strName.c_str()); ImGui::SameLine(g_DescWidth);

    char key[255] = {};
    sprintf_s(key, 255, "##DragVec4_%d", g_ParamUI_ID++);

    if (ImGui::DragFloat4(key, *pInOut, speed))
    {
        return true;
    }

    return false;
}

int ParamUI::Param_DragMat(const string& strName, Matrix* pInOut, float speed)
{
    return false;
}

int ParamUI::Param_Texture(const string& strName, Ptr<CTexture> texture)
{
    // Parmeter Name
    ImGui::Text(strName.c_str()); ImGui::SameLine(g_DescWidth);

    char key[255] = {};
    sprintf_s(key, 255, "##DragTexture_%d", g_ParamUI_ID++);

    // Image Ãâ·Â
    ImGui::SeparatorText("Texture");

    ImTextureID TexID = (nullptr == texture) ? nullptr : texture->GetSRV().Get();
    
    ImGui::Image((ImTextureID)TexID
                , ImVec2(150.f, 150.f)
                , ImVec2(0.0f, 0.0f)
                , ImVec2(1.0f, 1.0f)
                , ImGui::GetStyleColorVec4(ImGuiCol_Text));

    return 0;
}
