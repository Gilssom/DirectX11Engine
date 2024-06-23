#include "pch.h"
#include "UIHpBar.h"

#include "CUIManager.h"
#include "CPlayerScript.h"

UIHpBar::UIHpBar(const string& name)
	: UIElement(name, L"texture\\UI\\Player_HPUI.png")
{
    
}

UIHpBar::~UIHpBar()
{
}

void UIHpBar::Render()
{
    ImGui::SetNextWindowBgAlpha(0.f); // 배경 투명하게 설정
    ImGui::SetNextWindowPos(GetPosition(), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetWidth(), GetHeight()), ImGuiCond_Always); // 창 크기 설정
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // 창 패딩을 제거

    ImGui::Begin("HpBar UI", nullptr
        , ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

    ImGui::SetCursorPos(ImVec2(0, 0));
    RenderHealthBar();
    ImGui::End();
    ImGui::PopStyleVar(); // 스타일 변수를 원래 상태로 복원
}

void UIHpBar::RenderHealthBar()
{
    CPlayerScript* pPlayer =  CUIManager::GetInst()->GetPlayer();

    if (pPlayer == nullptr)
        return;

    // 플레이어의 체력
    int currentHealth = pPlayer->GetCurHp();
    int maxHealth = pPlayer->GetMaxHp();    

    // 체력 비율 계산
    float healthPercentage = (float)currentHealth / (float)maxHealth;

    // 체력 비율에 따라 조정된 UV 좌표
    ImVec2 uv0 = ImVec2(0.0f, 1.0f - healthPercentage);
    ImVec2 uv1 = ImVec2(1.0f, 1.0f);

    ImVec2 imageSize = ImVec2(GetWidth(), GetHeight() * healthPercentage);

    // 렌더링 위치 설정
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + GetHeight() * (1.0f - healthPercentage)));

    // 체력 바 렌더링
    ImGui::Image(GetTexID(), imageSize, uv0, uv1);
}