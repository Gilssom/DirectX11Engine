#include "pch.h"
#include "UIDamage.h"

UIDamage::UIDamage(int damage, const ImVec2& position, float startTime)
	: UIElement("Damage", L"")
    , m_StartTime(startTime)
    , m_Position(position)
    , m_Alpha(1.f)
    , m_LifeTime(3.f)
{
    string damageStr = to_string(damage);
    for (char digit : damageStr) 
    {
        int digitIndex = digit - '0';
        Ptr<CTexture> pTex = CAssetManager::GetInst()->FindAsset<CTexture>(L"texture\\UI\\Damage_" + std::to_wstring(digitIndex) + L".png");
        m_UseImage.push_back(pTex->GetSRV().Get());
    }
}

UIDamage::~UIDamage()
{

}

void UIDamage::Render()
{
    float elapsedTime = ImGui::GetTime() - m_StartTime;

    if (elapsedTime >= m_LifeTime)
    {
        return;
    }

    m_Alpha = 1.0f - (elapsedTime / m_LifeTime);

    // 고유한 윈도우 이름을 사용하여 충돌 방지
    string windowName = "Damage UI##" + to_string(reinterpret_cast<uintptr_t>(this));

    ImGui::SetNextWindowBgAlpha(0.f); // 배경 투명하게 설정
    ImGui::SetNextWindowPos(m_Position, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(100, 30), ImGuiCond_Always); // 창 크기 설정
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // 창 패딩을 제거

    ImGui::Begin(windowName.c_str(), nullptr
        , ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

    ImGui::SetCursorPos(ImVec2(0, 0));
    LoadNumberImage();

    ImGui::End();
    ImGui::PopStyleVar(); // 스타일 변수를 원래 상태로 복원
}

void UIDamage::LoadNumberImage()
{
    ImVec2 pos = m_Position;

    for (auto& number : m_UseImage)
    {
        ImGui::SetCursorPos(ImVec2(0, 0));
        ImGui::Image(number, ImVec2(20, 20), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, m_Alpha));
        pos.x += 5;
    }
}