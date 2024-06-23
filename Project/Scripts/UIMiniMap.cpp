#include "pch.h"
#include "UIMiniMap.h"

UIMiniMap::UIMiniMap(const string& name)
    : UIElement(name, L"texture\\UI\\Town_MiniMap.png")
{
    
}

UIMiniMap::~UIMiniMap()
{

}

void UIMiniMap::Render()
{
    ImGui::SetNextWindowBgAlpha(0.f); // ��� �����ϰ� ����
    ImGui::SetNextWindowPos(GetPosition(), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetWidth(), GetHeight()), ImGuiCond_Always); // â ũ�� ����
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // â �е��� ����

    ImGui::Begin("MiniMap UI", nullptr
        , ImGuiWindowFlags_NoTitleBar        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove            | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::Image(GetTexID(), ImVec2(GetWidth(), GetHeight()));
    ImGui::End();
    ImGui::PopStyleVar(); // ��Ÿ�� ������ ���� ���·� ����
}