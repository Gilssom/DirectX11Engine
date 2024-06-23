#include "pch.h"
#include "UIMonsterHp.h"
#include "CUIManager.h"
#include "CPlayerScript.h"

#include "CGoblinScript.h"
#include "CTauScript.h"
#include "CBossScript.h"

UIMonsterHp::UIMonsterHp(const string& name)
	: UIElement(name, L"texture\\UI\\GoblinHpUI.png")
    , m_LineMaxHp(2500)
{
    Init();
}

UIMonsterHp::~UIMonsterHp()
{
    
}

void UIMonsterHp::Init()
{
    for (int i = 0; i < 5; ++i) 
    {
        HpBarImage hpBar;

        Ptr<CTexture> pTex = CAssetManager::GetInst()->FindAsset<CTexture>(L"texture\\UI\\MonsterHp_" + to_wstring(i) + L".png");
        hpBar.textureID = pTex->GetSRV().Get();
        hpBar.width = pTex->GetWidth() * 1.2f;
        hpBar.height = pTex->GetHeight() * 1.2f;
        hpBar.color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        m_HpBars.push_back(hpBar);
    }

    for (int i = 0; i < 5; ++i)
    {
        HpBarImage hpBar;

        Ptr<CTexture> pTex = CAssetManager::GetInst()->FindAsset<CTexture>(L"texture\\UI\\BossHp_" + to_wstring(i) + L".png");
        hpBar.textureID = pTex->GetSRV().Get();
        hpBar.width = pTex->GetWidth() * 1.2f;
        hpBar.height = pTex->GetHeight() * 1.2f;
        hpBar.color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        m_BossHpBars.push_back(hpBar);
    }

    for (int i = 0; i < 10; ++i)
    {
        NumberImage number;

        Ptr<CTexture> pTex = CAssetManager::GetInst()->FindAsset<CTexture>(L"texture\\UI\\HpUI_" + to_wstring(i) + L".png");
        number.textureID = pTex->GetSRV().Get();
        number.width = pTex->GetWidth();
        number.height = pTex->GetHeight();
        m_NumberImages.push_back(number);
    }

    Ptr<CTexture> pTex = CAssetManager::GetInst()->FindAsset<CTexture>(L"texture\\UI\\HpUI_X.png");
    m_MultiplyImage.textureID = pTex->GetSRV().Get();
    m_MultiplyImage.width = pTex->GetWidth();
    m_MultiplyImage.height = pTex->GetHeight();
}

void UIMonsterHp::Render()
{
    if (CUIManager::GetInst()->GetPlayer()->GetTarget())
        m_IsShow = true;
    else
        m_IsShow = false;

    if (!m_IsShow)
        return;

    ImGui::SetNextWindowBgAlpha(0.f); // 배경 투명하게 설정
    ImGui::SetNextWindowPos(GetPosition(), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetWidth(), GetHeight()), ImGuiCond_Always); // 창 크기 설정
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // 창 패딩을 제거

    ImGui::Begin("Monster HpBar UI", nullptr
        , ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);
    
    RenderHealthBar();
    ImGui::End();
    ImGui::PopStyleVar(); // 스타일 변수를 원래 상태로 복원
}

void UIMonsterHp::RenderHealthBar()
{
    // 현재 Player 타겟 Monster 정보 가져오기
    CMonsterScript* pMonster = CUIManager::GetInst()->GetPlayer()->GetTarget();

    if (pMonster == nullptr)
        return;

    vector<HpBarImage> vecImage;
    ImVec2 barPos;
    ImVec2 numPos;

    if (dynamic_cast<CGoblinScript*>(pMonster))
    {
        ChangeTexture(L"texture\\UI\\GoblinHpUI.png");
        vecImage = m_HpBars;
        barPos = ImVec2(35, 20);
        numPos = ImVec2(660, 2);
    }

    else if (dynamic_cast<CTauScript*>(pMonster))
    {
        ChangeTexture(L"texture\\UI\\TauHpUI.png");
        vecImage = m_HpBars;
        barPos = ImVec2(35, 20);
        numPos = ImVec2(660, 2);
    }

    else if (dynamic_cast<CBossScript*>(pMonster))
    {
        ChangeTexture(L"texture\\UI\\BossHpUI.png");
        vecImage = m_BossHpBars;
        barPos = ImVec2(5, 0);
        numPos = ImVec2(460, 2);
    }

    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::Image(GetTexID(), ImVec2(GetWidth(), GetHeight()));

    float hpRatio = static_cast<float>(pMonster->GetCurHealth()) / pMonster->GetMaxHealth();
    int totalBars = pMonster->GetMaxHealth() / m_LineMaxHp;
    int activeBars = static_cast<int>(totalBars * hpRatio);

    ImGui::SetCursorPos(barPos);

    float remainingHp = pMonster->GetCurHealth();

    for (int i = 0; i < totalBars; i++)
    {
        float barWidth;

        if (remainingHp > m_LineMaxHp)
        {
            barWidth = vecImage[i % 5].width;
            remainingHp -= m_LineMaxHp;
        }
        else
        {
            barWidth = (remainingHp / m_LineMaxHp) * vecImage[i % 5].width;
            remainingHp = 0;
        }

        ImGui::Image(vecImage[i % 5].textureID, ImVec2(barWidth, vecImage[i % 5].height), ImVec2(0, 0), ImVec2(barWidth / vecImage[i % 5].width, 1));

        if (i < totalBars - 1) 
        {
            ImGui::SetCursorPos(barPos);
        }
    }

    ImGui::SetCursorPos(numPos);

    ImGui::Image(m_MultiplyImage.textureID, ImVec2(m_MultiplyImage.width, m_MultiplyImage.height));

    float xOffset = numPos.x + m_MultiplyImage.width + 3;
    float initialGap = 3; 
    float numberGap = 1;

    string remainingBarsStr = std::to_string(activeBars);

    bool isFirstDigit = true;

    for (char digit : remainingBarsStr) 
    {
        int digitIndex = digit - '0';
        ImGui::SetCursorPos(ImVec2(xOffset, numPos.y));
        ImGui::Image(m_NumberImages[digitIndex].textureID, ImVec2(m_NumberImages[digitIndex].width, m_NumberImages[digitIndex].height));
       
        if (isFirstDigit) 
        {
            xOffset += m_NumberImages[digitIndex].width + initialGap;
            isFirstDigit = false;
        }
        else 
        {
            xOffset += m_NumberImages[digitIndex].width + numberGap;
        }
    }
}