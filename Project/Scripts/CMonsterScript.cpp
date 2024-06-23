#include "pch.h"
#include "CMonsterScript.h"
#include "CCameraMoveScript.h"

#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>

#include <Engine\\CAnim2D.h>

#include "CUIManager.h"
#include "CPlayerScript.h"
#include "UIDamage.h"
#include "CDamageScript.h"

CMonsterScript::CMonsterScript(SCRIPT_TYPE type)
	: CScript(type)
	, m_OriginPosObject(nullptr)
	, m_Target(nullptr)
	, m_Speed(0.f)
	, m_Health(0)
	, m_Armor(0)
	, m_Damage(0)
	, m_AttackRange(0.f)
	, m_AttackCoolTime(0.f)
	, m_IsDeath(false)
	, m_IsAttack(false)
	, m_Animator(nullptr)
	, m_HitTimer(0.f)
	, m_TraceDistance(0.f)
{

}

CMonsterScript::CMonsterScript(SCRIPT_TYPE type, const CMonsterScript& other)
	: CScript(type)
	, m_OriginPosObject(other.m_OriginPosObject)
	, m_Target(other.m_Target)
	, m_Speed(other.m_Speed)
	, m_Health(other.m_Health)
	, m_Armor(other.m_Armor)
	, m_Damage(other.m_Damage)
	, m_AttackRange(other.m_AttackRange)
	, m_AttackCoolTime(other.m_AttackCoolTime)
	, m_IsDeath(other.m_IsDeath)
	, m_IsAttack(other.m_IsAttack)
	, m_Animator(other.m_Animator)
	, m_HitTimer(0.f)
{

}

CMonsterScript::~CMonsterScript()
{

}

void CMonsterScript::Begin()
{
	m_Animator = GetOwner()->Animator2D();
	AnimationInit();
}

void CMonsterScript::Tick()
{
	if (m_HitTimer > 0.f)
	{
		m_HitTimer -= DT;

		if (m_HitTimer <= 0.f)
		{
			GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 0);
			m_HitTimer = 0.f;
		}
	}
}

void CMonsterScript::Attack(const wstring& animName)
{
	/*if (m_CurrentAttackCoolTime <= 0.f)
	{
		m_CurrentAttackCoolTime = m_AttackCoolTime;
		PlayAnimation(animName, false);
	}*/
}

void CMonsterScript::TakeDamage(float minDamage, float maxDamage, const wstring& hitName)
{
	if (m_IsDeath)
		return;

	CPlayerScript* pPlayer = CUIManager::GetInst()->GetPlayer();

	if (pPlayer == nullptr)
		return;

	if (maxDamage >= 0.01f)
	{
		int finalDamage = GetRandomInt((int)(pPlayer->GetDamage() * minDamage), (int)(pPlayer->GetDamage() * maxDamage));
		int getCritical = GetRandomInt(0, 9);

		finalDamage -= m_Armor;

		m_Health -= finalDamage;

		if (pPlayer->GetTarget() == nullptr)
			pPlayer->SetTarget(this);

		bool critical = getCritical < 3 ? true : false;
		DamageFont(finalDamage, critical);
	}

	HitEvent();

	if(hitName != L"")
		HitEffect(hitName);

	// g_int_0 = 1 (Hit)
	GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 1);

	m_HitTimer = 0.1f;

	CCameraMoveScript* pCamScript = CLevelManager::GetInst()->GetCurrentLevel()->FindObjectByName(L"Main Camera")->GetScript<CCameraMoveScript>();
	pCamScript->StartShake(0.15f, 2.f);

	if (m_Health <= 0)
	{
		if(pPlayer->GetTarget() == this)
			pPlayer->ResetTarget();

		m_IsDeath = true;
	}
}

void CMonsterScript::PlayAnimation(const wstring& animName, bool repeat)
{
	if (m_Animator)
	{
		m_Animator->Play(animName, repeat);
	}
}

void CMonsterScript::HitEffect(const wstring& hitEventName = L"")
{
	CGameObject* pHitEffect = new CGameObject;
	pHitEffect->SetName(L"Hit Effect");
	pHitEffect->AddComponent(new CTransform);
	pHitEffect->AddComponent(new CMeshRender);
	pHitEffect->AddComponent(new CAnimator2D);

	Vec3 vPos = m_OriginPosObject->Transform()->GetRelativePos();
	pHitEffect->Transform()->SetRelativeScale(800.f, 600.f, 1.f);

	pHitEffect->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pHitEffect->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DAlphaMaterial"));

	if (hitEventName == L"Refentence")
	{
		int hitIndex = m_RefentenceHit % 2;

		if(hitIndex == 0)
			pHitEffect->Transform()->SetRelativePos(Vec3(vPos.x + 280.f, vPos.y - 100.f, 25.f));
		else
			pHitEffect->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y + 50.f, 24.f));

		wstring index = to_wstring(hitIndex);
		wstring animPath = L"Animation\\Repentence_Hit_" + index + L"_eff.anim";
		wstring animName = L"Repentence_Hit_" + index + L"_eff";

		pHitEffect->Animator2D()->LoadAnimation(animPath);
		pHitEffect->Animator2D()->Play(animName, false);

		m_RefentenceHit++;

		if (m_RefentenceHit % 2 == 0)
			m_RefentenceHit = 0;
	}

	if (hitEventName == L"HolyFlash")
	{
		pHitEffect->Transform()->SetRelativePos(Vec3(vPos.x + 200.f, vPos.y, 24.f));

		wstring animPath = L"Animation\\HolyFlash_Hit_eff.anim";
		wstring animName = L"HolyFlash_Hit_eff";

		pHitEffect->Animator2D()->LoadAnimation(animPath);
		pHitEffect->Animator2D()->Play(animName, false);

		PlaySoundEffect(L"Sound\\holyflash.ogg");
	}

	SpawnObject(6, pHitEffect);

	pHitEffect->Animator2D()->GetCurAnim()->SetEndCallBack([pHitEffect]()
		{
			pHitEffect->Destroy();
		});
}

void CMonsterScript::KnockBack(CGameObject* target, const wstring& hitEventName)
{
	float vTargetPosX = target->Transform()->GetRelativePos().x;
	Vec3 vPos = m_OriginPosObject->Transform()->GetRelativePos();

	if (hitEventName == L"SaintWall")
	{
		Vec3 updatePos = Vec3(vTargetPosX, vPos.y, vPos.z);
		m_OriginPosObject->Transform()->SetRelativePos(updatePos);
	}
}

void CMonsterScript::DamageFont(int damage, bool critical)
{
	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();

	Vec3 curPos = m_OriginPosObject->Transform()->GetRelativePos();

	int Xcnt = 0;
	int getDamage = damage;
	wstring isCriKey = critical ? L"texture\\UI\\Damage_" : L"texture\\UI\\n_Damage_";

	while (getDamage != 0)
	{
		int temp = getDamage % 10;
		wstring key = isCriKey + to_wstring(temp) + L".png";

		CGameObject* dmgFont = new CGameObject;
		dmgFont->SetName(L"DamageFont_" + to_wstring(temp));
		dmgFont->AddComponent(new CTransform);
		dmgFont->AddComponent(new CMeshRender);
		dmgFont->AddComponent(new CDamageScript);

		Ptr<CTexture> pTex = CAssetManager::GetInst()->FindAsset<CTexture>(key);

		dmgFont->Transform()->SetRelativePos(Vec3(curPos.x - (18 * Xcnt), curPos.y, 20.f - (Xcnt * 0.1f)));
		dmgFont->Transform()->SetRelativeScale(Vec3(30.f, 30.f, 1.f));

		dmgFont->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		dmgFont->MeshRender()->SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"Std2DAlphaMaterial"));
		dmgFont->MeshRender()->GetDynamicMaterial()->SetTexParam(TEX_0, pTex);
		//dmgFont->MeshRender()->GetDynamicMaterial()->SetScalarParam(INT_2, 1);
		m_DamageFonts.push_back(dmgFont);

		pCurLevel->AddObject(9, dmgFont, false);

		Xcnt++;
		getDamage /= 10;
	}
}

#pragma region Save Load
void CMonsterScript::SaveToLevelFile(FILE* file)
{

}

void CMonsterScript::LoadFromLevelFile(FILE* file)
{

}
#pragma endregion