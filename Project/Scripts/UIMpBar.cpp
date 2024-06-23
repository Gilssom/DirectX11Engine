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
    ImGui::SetNextWindowBgAlpha(0.f); // ��� �����ϰ� ����
    ImGui::SetNextWindowPos(GetPosition(), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetWidth(), GetHeight()), ImGuiCond_Always); // â ũ�� ����
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // â �е��� ����

    ImGui::Begin("MpBar UI", nullptr
        , ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

    ImGui::SetCursorPos(ImVec2(0, 0));
    RenderManaBar();
    ImGui::End();
    ImGui::PopStyleVar(); // ��Ÿ�� ������ ���� ���·� ����
}

void UIMpBar::RenderManaBar()
{
    CPlayerScript* pPlayer = CUIManager::GetInst()->GetPlayer();

    if (pPlayer == nullptr)
        return;

    // �÷��̾��� ����
    int currentMana = pPlayer->GetCurMp();
    int maxMana = pPlayer->GetMaxMp();

    // ���� ���� ���
    float manaPercentage = (float)currentMana / (float)maxMana;

    // ���� ������ ���� ������ UV ��ǥ
    ImVec2 uv0 = ImVec2(0.0f, 1.0f - manaPercentage);
    ImVec2 uv1 = ImVec2(1.0f, 1.0f);

    ImVec2 imageSize = ImVec2(GetWidth(), GetHeight() * manaPercentage);

    // ������ ��ġ ����
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + GetHeight() * (1.0f - manaPercentage)));

    // ���� �� ������
    ImGui::Image(GetTexID(), imageSize, uv0, uv1);
}