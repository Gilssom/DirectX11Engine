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
    ImGui::SetNextWindowBgAlpha(0.f); // 배경 투명하게 설정
    ImGui::SetNextWindowPos(GetPosition(), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetWidth(), GetHeight()), ImGuiCond_Always); // 창 크기 설정
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // 창 패딩을 제거

    ImGui::Begin("MiniMap UI", nullptr
        , ImGuiWindowFlags_NoTitleBar        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove            | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::Image(GetTexID(), ImVec2(GetWidth(), GetHeight()));
    ImGui::End();
    ImGui::PopStyleVar(); // 스타일 변수를 원래 상태로 복원
}