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
    ImGui::SetNextWindowBgAlpha(0.f); // ��� �����ϰ� ����
    ImGui::SetNextWindowPos(GetPosition(), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetWidth(), GetHeight()), ImGuiCond_Always); // â ũ�� ����
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // â �е��� ����

    ImGui::Begin("HpBar UI", nullptr
        , ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

    ImGui::SetCursorPos(ImVec2(0, 0));
    RenderHealthBar();
    ImGui::End();
    ImGui::PopStyleVar(); // ��Ÿ�� ������ ���� ���·� ����
}

void UIHpBar::RenderHealthBar()
{
    CPlayerScript* pPlayer =  CUIManager::GetInst()->GetPlayer();

    if (pPlayer == nullptr)
        return;

    // �÷��̾��� ü��
    int currentHealth = pPlayer->GetCurHp();
    int maxHealth = pPlayer->GetMaxHp();    

    // ü�� ���� ���
    float healthPercentage = (float)currentHealth / (float)maxHealth;

    // ü�� ������ ���� ������ UV ��ǥ
    ImVec2 uv0 = ImVec2(0.0f, 1.0f - healthPercentage);
    ImVec2 uv1 = ImVec2(1.0f, 1.0f);

    ImVec2 imageSize = ImVec2(GetWidth(), GetHeight() * healthPercentage);

    // ������ ��ġ ����
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + GetHeight() * (1.0f - healthPercentage)));

    // ü�� �� ������
    ImGui::Image(GetTexID(), imageSize, uv0, uv1);
}