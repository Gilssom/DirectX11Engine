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
    ImGui::SetNextWindowBgAlpha(0.f); // 배경 투명하게 설정
    ImGui::SetNextWindowPos(GetPosition(), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(m_Width, m_Height), ImGuiCond_Always);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // 창 패딩을 제거

    ImGui::Begin(GetName().c_str(), nullptr
        , ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
        | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove);

    // Invisible button을 사용해 드래그 가능 영역 생성
    //ImGui::Button("##DragZone", ImVec2(m_Width, m_Height)); // 버튼 크기를 이미지와 동일하게 설정

    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    {
        ImVec2 dragDelta = ImGui::GetMouseDragDelta();
        ImVec2 newPos = ImVec2(GetPosition().x + dragDelta.x, GetPosition().y + dragDelta.y);
        SetPosition(newPos);
        ImGui::ResetMouseDragDelta();
    }

    // 이미지를 그리기 전에 커서를 돌려놓습니다.
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::Image(m_TexID, ImVec2(m_Width, m_Height));
    ImGui::End();
    ImGui::PopStyleVar(); // 스타일 변수를 원래 상태로 복원
}