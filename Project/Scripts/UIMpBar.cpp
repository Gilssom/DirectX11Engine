#include "pch.h"
#include "UIMpBar.h"

#include "CUIManager.h"
#include "CPlayerScript.h"

UIMpBar::UIMpBar(const string& name)
	: UIElement(name, L"texture\\UI\\Player_MPUI.png")
{
}

UIMpBar::~UIMpBar()
{
}

void UIMpBar::Render()
{
    ImGui::SetNextWindowBgAlpha(0.f); // 배경 투명하게 설정
    ImGui::SetNextWindowPos(GetPosition(), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetWidth(), GetHeight()), ImGuiCond_Always); // 창 크기 설정
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // 창 패딩을 제거

    ImGui::Begin("MpBar UI", nullptr
        , ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

    ImGui::SetCursorPos(ImVec2(0, 0));
    RenderManaBar();
    ImGui::End();
    ImGui::PopStyleVar(); // 스타일 변수를 원래 상태로 복원
}

void UIMpBar::RenderManaBar()
{
    CPlayerScript* pPlayer = CUIManager::GetInst()->GetPlayer();

    if (pPlayer == nullptr)
        return;

    // 플레이어의 마나
    int currentMana = pPlayer->GetCurMp();
    int maxMana = pPlayer->GetMaxMp();

    // 마나 비율 계산
    float manaPercentage = (float)currentMana / (float)maxMana;

    // 마나 비율에 따라 조정된 UV 좌표
    ImVec2 uv0 = ImVec2(0.0f, 1.0f - manaPercentage);
    ImVec2 uv1 = ImVec2(1.0f, 1.0f);

    ImVec2 imageSize = ImVec2(GetWidth(), GetHeight() * manaPercentage);

    // 렌더링 위치 설정
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + GetHeight() * (1.0f - manaPercentage)));

    // 마나 바 렌더링
    ImGui::Image(GetTexID(), imageSize, uv0, uv1);
}