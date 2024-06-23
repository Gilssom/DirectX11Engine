#include "pch.h"
#include "UIElement.h"

UIElement::UIElement(const string& name, const wstring& texPath)
    : m_Name(name)
    , m_Position{}
    , m_Dragging(false)
{
    ChangeTexture(texPath);
}

void UIElement::ChangeTexture(const wstring& texPath)
{
    Ptr<CTexture> pTex = CAssetManager::GetInst()->FindAsset<CTexture>(texPath);

    if (pTex == m_Tex)
        return;

    m_Tex = pTex;
    m_TexID = m_Tex->GetSRV().Get();
    m_Width = m_Tex->GetWidth() * 1.2f;
    m_Height = m_Tex->GetHeight() * 1.2f;
}

void UIElement::Draw()
{
    ImGui::SetNextWindowBgAlpha(0.f); // ��� �����ϰ� ����
    ImGui::SetNextWindowPos(GetPosition(), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(m_Width, m_Height), ImGuiCond_Always);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // â �е��� ����

    ImGui::Begin(GetName().c_str(), nullptr
        , ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
        | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove);

    // Invisible button�� ����� �巡�� ���� ���� ����
    //ImGui::Button("##DragZone", ImVec2(m_Width, m_Height)); // ��ư ũ�⸦ �̹����� �����ϰ� ����

    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    {
        ImVec2 dragDelta = ImGui::GetMouseDragDelta();
        ImVec2 newPos = ImVec2(GetPosition().x + dragDelta.x, GetPosition().y + dragDelta.y);
        SetPosition(newPos);
        ImGui::ResetMouseDragDelta();
    }

    // �̹����� �׸��� ���� Ŀ���� ���������ϴ�.
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::Image(m_TexID, ImVec2(m_Width, m_Height));
    ImGui::End();
    ImGui::PopStyleVar(); // ��Ÿ�� ������ ���� ���·� ����
}