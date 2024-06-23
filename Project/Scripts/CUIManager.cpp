#include "pch.h"
#include "CUIManager.h"
#include <fstream>

#include "..\\Client\\ImGui\\imgui.h"
#include "..\\Client\\ImGui\\imgui_impl_win32.h"
#include "..\\Client\\ImGui\\imgui_impl_dx11.h"

#include <Engine\CLevelManager.h>
#include <Engine\CLevel.h>

#include "UIStatus.h"
#include "UIMiniMap.h"
#include "UIHpBar.h"
#include "UIMpBar.h"
#include "UISkill.h"
#include "UIMonsterHp.h"
#include "UIResult.h"
#include "UILobby.h"

CUIManager::CUIManager()
    : m_PlayerScript(nullptr)
{

}

CUIManager::~CUIManager()
{
    UpdateUIPositions();
    SaveUIPositions("UI_Positions.txt");
}

void CUIManager::Init()
{
    std::shared_ptr<UIElement> pUI = std::make_shared<UILobby>("Lobby");
    AddUIElement(pUI);

    pUI = std::make_shared<UIResult>("Result");
    AddUIElement(pUI);

    pUI = std::make_shared<UIMiniMap>("MiniMap");
    AddUIElement(pUI);

    pUI = std::make_shared<UIStatus>("Status");
    AddUIElement(pUI);

    pUI = std::make_shared<UIHpBar>("HpBar");
    AddUIElement(pUI);

    pUI = std::make_shared<UIMpBar>("MpBar");
    AddUIElement(pUI);

    pUI = std::make_shared<UISkill>("SaintWall", L"texture\\UI\\SaintWall_Icon.png", eSkillType::SaintWall);
    AddUIElement(pUI);

    pUI = std::make_shared<UISkill>("GrandCrossCrash", L"texture\\UI\\GrandCrossCrash_Icon.png", eSkillType::GrandCrossCrash);
    AddUIElement(pUI);

    pUI = std::make_shared<UISkill>("RefentenceSmash", L"texture\\UI\\RefentenceSmash_Icon.png", eSkillType::RefentenceSmash);
    AddUIElement(pUI);

    pUI = std::make_shared<UISkill>("HolyFlash", L"texture\\UI\\HolyFlash_Icon.png", eSkillType::HolyFlash);
    AddUIElement(pUI);

    pUI = std::make_shared<UISkill>("Buff", L"texture\\UI\\Buff_Icon.png", eSkillType::CrusaderBuff);
    AddUIElement(pUI);

    pUI = std::make_shared<UIMonsterHp>("MonsterHp");
    AddUIElement(pUI);

    std::filesystem::path exePath = std::filesystem::current_path();
    std::string filename = (exePath / "UI_Positions.txt").string();

    LoadUIPositions(filename);
}

void CUIManager::Tick()
{
    for (const auto& element : m_UIElement)
    {
        if(CLevelManager::GetInst()->GetCurrentLevel()->GetState() == LEVEL_STATE::STOP)
            element->Draw();

        else if(CLevelManager::GetInst()->GetCurrentLevel()->GetState() == LEVEL_STATE::PLAY)
            element->Render();
    }

    for (auto it = m_UIDamage.begin(); it != m_UIDamage.end(); ) 
    {
        (*it)->Render();

        if ((*it)->IsExpired()) 
            it = m_UIDamage.erase(it);
        else 
            ++it;
    }
}

void CUIManager::ChangeLevel(const wstring& levelName)
{
    auto pMiniMap = FindUIElementByType<UIMiniMap>();

    pMiniMap->ChangeTexture(L"texture\\UI\\" + levelName + L".png");
}

void CUIManager::SaveUIPositions(const string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open()) 
        return;

    file << m_UIPositions.size() << "\n";

    for (const auto& pos : m_UIPositions)
        file << pos.name << " " << pos.x << " " << pos.y << "\n";

    file.close();
}

void CUIManager::LoadUIPositions(const string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) 
        return;

    m_UIPositions.clear();

    size_t uiCnt;
    string name;
    float x, y;

    file >> uiCnt;

    for (size_t i = 0; i < uiCnt; i++)
    {
        file >> name >> x >> y;
        m_UIPositions.push_back({ name, x, y });
    }

    file.close();

    for (const auto& element : m_UIElement)
    {
        for (const auto& pos : m_UIPositions) 
        {
            if (element->GetName() == pos.name)
            {
                element->SetPosition(ImVec2(pos.x, pos.y));
                break;
            }
        }
    }
}

void CUIManager::UpdateUIPositions()
{
    m_UIPositions.clear();

    for (const auto& element : m_UIElement)
    {
        ImVec2 pos = element->GetPosition();
        m_UIPositions.push_back({ element->GetName(), pos.x, pos.y });
    }
}