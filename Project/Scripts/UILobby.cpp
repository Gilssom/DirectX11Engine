#include "pch.h"
#include "UILobby.h"

#include <Engine\CKeyManager.h>
#include <Engine\CLevelManager.h>
#include <Engine\CLevel.h>

UILobby::UILobby(const string& name)
    : UIElement(name, L"texture\\UI\\Lobby.png")
    , m_IsShow(true)
{

}

UILobby::~UILobby()
{

}

void UILobby::Render()
{
    if (!m_IsShow)
        return;

    if (KEY_TAP(KEY::SPACE))
    {
        m_IsShow = false;

        CLevelManager::GetInst()->GetCurrentLevel()->GetBGM()->Stop();

        Ptr<CSound> pBgm = CAssetManager::GetInst()->FindAsset<CSound>(L"Sound\\elven_guard_old.wav");
        CLevelManager::GetInst()->ChangeBgm(pBgm);
        CLevelManager::GetInst()->GetCurrentLevel()->SetBGM(pBgm.Get());
    }

    ImGui::SetNextWindowBgAlpha(0.f); // ��� �����ϰ� ����
    ImGui::SetNextWindowPos(GetPosition(), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(/*GetWidth(), GetHeight()*/1285, 773), ImGuiCond_Always); // â ũ�� ����
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // â �е��� ����

    ImGui::Begin("Lobby UI", nullptr
        , ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::Image(GetTexID(), ImVec2(/*GetWidth(), GetHeight()*/1285, 773));
    ImGui::End();
    ImGui::PopStyleVar(); // ��Ÿ�� ������ ���� ���·� ����
}