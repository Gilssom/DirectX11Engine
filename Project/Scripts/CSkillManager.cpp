#include "pch.h"
#include "CSkillManager.h"
#include "CPlayerSkillScript.h"

#include <Engine\\func.h>

#define MIN_FLOAT std::numeric_limits<float>::lowest()

CSkillManager::CSkillManager()
    : m_UsedPlayer(nullptr)
{

}

CSkillManager::~CSkillManager()
{
    if (m_UsedPlayer)
        m_UsedPlayer = nullptr;

    m_SkillInfoMap.clear();
}

void CSkillManager::Init()
{
    CSkillManager& manager = CSkillManager::Instance();
    manager.RegisterSkill(eSkillType::Attack_0, { Vec3(340.f, 148.5f, 30.f), false, L"Animation\\Attack_0_eff.anim", L"Attack_0_eff" });
    manager.RegisterSkill(eSkillType::Attack_1, { Vec3(261.f, 90.f, 29.f),   false, L"Animation\\Attack_1_eff.anim", L"Attack_1_eff" });
    manager.RegisterSkill(eSkillType::Attack_2, { Vec3(223.f, 40.f, 28.f),   false, L"Animation\\Attack_2_eff.anim", L"Attack_2_eff" });

    // 다른 스킬들도 동일한 방식으로 등록
    manager.RegisterSkill(eSkillType::SaintWall,            { Vec3(361.f, 0.f, 27.f),       false, L"Animation\\SaintWall_0_eff.anim",              L"SaintWall_0_eff", 10.f, MIN_FLOAT, 50 });
    manager.RegisterSkill(eSkillType::GrandCrossCrash,      { Vec3(100.f, 0.f, 30.f),       false, L"Animation\\GrandCrossCrash_0_eff.anim",        L"GrandCrossCrash_0_eff", 15.f, MIN_FLOAT, 60 });
    manager.RegisterSkill(eSkillType::GrandCrossCrash_1,    { Vec3(337.f, -60.f, 29.f),     false, L"Animation\\GrandCrossCrash_1_eff.anim",        L"GrandCrossCrash_1_eff" });
    manager.RegisterSkill(eSkillType::GrandCrossCrash_Aura, { Vec3(431.f, 210.f, 28.f),     false, L"Animation\\GrandCrossCrash_Ground_eff.anim",   L"GrandCrossCrash_Ground_eff" });
    manager.RegisterSkill(eSkillType::RefentenceSmash,      { Vec3(146.6f, -28.f, 29.f),    false, L"Animation\\Repentence_0_eff.anim",             L"Repentence_0_eff", 15.f, MIN_FLOAT, 70 });
    manager.RegisterSkill(eSkillType::HolyFlash,            { Vec3(274.f, 100.f, 30.f),     false, L"Animation\\HolyFlash_Cast_eff.anim",           L"HolyFlash_Cast_eff", 4.f, MIN_FLOAT, 20 });
    manager.RegisterSkill(eSkillType::HolyFlash_Ball,       { Vec3(274.f, 30.f, 29.f),      false, L"Animation\\HolyFlash_Ball_eff.anim",           L"HolyFlash_Ball_eff" });
    manager.RegisterSkill(eSkillType::CrusaderBuff,         { Vec3(0.f, 0.f, 0.f),          false, L"Animation\\Crusader_Buff_eff.anim",            L"Crusader_Buff_eff", 15.f, MIN_FLOAT, 150, true });
}

void CSkillManager::Tick()
{
    m_CurTime += DT;
}

CGameObject* CSkillManager::CreateSkill(eSkillType skillType, Vec3 spawnPos, bool isLeft)
{
    m_SkillPrefab = CAssetManager::GetInst()->FindAsset<CPrefab>(L"Prefab\\Attack_0_Prefab.pref");

    if (m_SkillInfoMap.find(skillType) == m_SkillInfoMap.end())
        return nullptr;

    CGameObject* skillEffect = Instantiate(m_SkillPrefab, 4, Vec3(spawnPos.x, spawnPos.y, 1.f));
    skillEffect->AddComponent(new CPlayerSkillScript);
    CPlayerSkillScript* skillScript = skillEffect->GetScript<CPlayerSkillScript>();

    const sSkill_Info& info = m_SkillInfoMap[skillType];

    skillScript->SetSkillType(skillType);

    Vec3 vPos = skillEffect->Transform()->GetRelativePos();
    sSkill_Info skillInfo = {};

    // Center
    if (info.isAbsolute)
    {
        skillInfo.pos = Vec3(vPos.x - 100.f, vPos.y + 150.f, info.pos.z);
        skillInfo.isLeft = false;
    }
    else
    {
        if (!isLeft)
        {
            skillInfo.pos = Vec3(vPos.x + info.pos.x, vPos.y - info.pos.y, info.pos.z);
            skillInfo.isLeft = false;
        }
        else
        {
            skillInfo.pos = Vec3(vPos.x - info.pos.x, vPos.y - info.pos.y, info.pos.z);
            skillInfo.isLeft = true;
        }
    }

    skillInfo.animPath = info.animPath;
    skillInfo.animName = info.animName;

    skillScript->SetSkillInfo(skillInfo);

    m_SkillInfoMap[skillType].lastUsedTime = m_CurTime;

    return skillEffect;
}

void CSkillManager::UseSkill(eSkillType skillType, Vec3 spawnPos, bool isLeft)
{
    CGameObject* skillEffect = CSkillManager::Instance().CreateSkill(skillType, spawnPos, isLeft);
}

bool CSkillManager::SkillCoolTime(eSkillType skillType)
{
    if (m_SkillInfoMap.find(skillType) == m_SkillInfoMap.end())
        return false;

    const sSkill_Info& info = m_SkillInfoMap[skillType];

    if (info.lastUsedTime == MIN_FLOAT || m_CurTime - info.lastUsedTime >= info.coolDownTime)
        return true;

    return false;
}

bool CSkillManager::SkillUseMana(eSkillType skillType, int& curMp)
{
    if (m_SkillInfoMap.find(skillType) == m_SkillInfoMap.end())
        return false;

    const sSkill_Info& info = m_SkillInfoMap[skillType];

    if (info.useMana > curMp)
        return false;
    else
    {
        curMp -= info.useMana;
        return true;
    }
}

float CSkillManager::GetSkillCoolTime(eSkillType skillType) const
{
    auto iter = m_SkillInfoMap.find(skillType);

    if (iter == m_SkillInfoMap.end())
        return 0.0f;

    const sSkill_Info& info = iter->second;

    if (info.lastUsedTime == MIN_FLOAT)
        return 0.0f;

    float elapsedTime = m_CurTime - info.lastUsedTime;
    float remainingCooltime = info.coolDownTime - elapsedTime;

    return remainingCooltime > 0 ? remainingCooltime : 0.0f;
}

CGameObject* CSkillManager::Instantiate(Ptr<CPrefab> prefab, int layerIdx, const Vec3& worldPos)
{
    CGameObject* pInst = prefab->Instantiate();
    pInst->Transform()->SetRelativePos(worldPos);
    SpawnObject(layerIdx, pInst);

    return pInst;
}