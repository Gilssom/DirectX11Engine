#include "pch.h"
#include "CPlayerSkillScript.h"

#include "CPlayerScript.h"

#include <Engine\\CAnim2D.h>

CPlayerSkillScript::CPlayerSkillScript()
	: CScript(SCRIPT_TYPE::PLAYERSKILLSCRIPT)
	, m_SkillType(eSkillType::End)
	, m_SkillInfo{}
	, m_IsMove(false)
	, m_Speed(800.f)
	, m_LifeTimer(0.f)
{

}

CPlayerSkillScript::~CPlayerSkillScript()
{

}

void CPlayerSkillScript::Begin()
{

}

void CPlayerSkillScript::Tick()
{
	Vec3 vCurPos = GetOwner()->Transform()->GetRelativePos();

	if (m_IsMove)
	{
		if (m_SkillInfo.isLeft)
		{
			vCurPos.x -= DT * m_Speed;
		}
		else
		{
			vCurPos.x += DT * m_Speed;
		}
	}
	
	GetOwner()->Transform()->SetRelativePos(vCurPos);

	if (m_LifeTimer > 0.f)
	{
		m_LifeTimer -= DT;

		if (m_LifeTimer <= 0.f)
			GetOwner()->Destroy();;
	}
}

void CPlayerSkillScript::FinalExecuteSkill()
{
	CGameObject* pOwner = GetOwner();

	GetOwner()->Transform()->SetRelativePos(m_SkillInfo.pos);

	GetOwner()->SetName(m_SkillInfo.animName);

	if (m_SkillInfo.isLeft)
	{
		GetOwner()->Transform()->SetRight(false);
		GetOwner()->Transform()->SetLeft(true);
	}
	else
	{
		GetOwner()->Transform()->SetLeft(false);
		GetOwner()->Transform()->SetRight(true);
	}

	if (m_SkillType == eSkillType::SaintWall)
	{
		ExecuteSaintWall();
		return;
	}

	if (m_SkillType == eSkillType::RefentenceSmash)
	{
		ExecuteRefentence();
		return;
	}

	if (m_SkillType == eSkillType::GrandCrossCrash || m_SkillType == eSkillType::GrandCrossCrash_1)
	{
		ExecuteGrandCrossCrash();
		return;
	}

	if (m_SkillType == eSkillType::GrandCrossCrash_Aura)
	{
		GrandCrossCrashAura();
		return;
	}

	if (m_SkillType == eSkillType::HolyFlash)
	{
		ExecuteHolyFlash();
		return;
	}

	if (m_SkillType == eSkillType::HolyFlash_Ball)
	{
		HolyFlashBall();
		return;
	}

	if (m_SkillType == eSkillType::CrusaderBuff)
	{
		ExecuteCrusaderBuff();
		return;
	}


	GetOwner()->Animator2D()->LoadAnimation(m_SkillInfo.animPath);
	GetOwner()->Animator2D()->Play(m_SkillInfo.animName, false);
	GetOwner()->Animator2D()->GetCurAnim()->SetEndCallBack([pOwner]()
		{
			pOwner->Destroy();
		});
}

void CPlayerSkillScript::ExecuteSaintWall()
{
	GetOwner()->Animator2D()->LoadAnimation(m_SkillInfo.animPath);
	GetOwner()->Animator2D()->Play(m_SkillInfo.animName, false);

	PlaySoundEffect(L"Sound\\pw_saintwall_01.ogg");
	PlaySoundEffect(L"Sound\\saintwall.ogg");

	GetOwner()->Animator2D()->GetCurAnim()->SetEndCallBack([this]()
		{
			wstring animPath = L"Animation\\SaintWall_1_eff.anim";
			wstring animName = L"SaintWall_1_eff";

			m_IsMove = true;

			GetOwner()->Animator2D()->LoadAnimation(animPath);
			GetOwner()->Animator2D()->Play(animName, false);

			PlaySoundEffect(L"Sound\\pw_saintwall_03.ogg");
			PlaySoundEffect(L"Sound\\saintwall_Hit.ogg");

			GetOwner()->Animator2D()->GetCurAnim()->SetStartCallBack([this]()
				{
					GetOwner()->AddComponent(new CCollider2D);
					GetOwner()->Collider2D()->SetOffset(Vec3(-0.23f, 0.15f, 0.f));
					GetOwner()->Collider2D()->SetScale(Vec3(0.1f, 0.32f, 1.f));
				});

			GetOwner()->Animator2D()->GetCurAnim()->SetEndCallBack([this]()
				{
					GetOwner()->Collider2D()->Deactivate();

					m_IsMove = false;
					SaintWallHit();
				});
		});
}

void CPlayerSkillScript::SaintWallHit()
{
	wstring animPath = L"Animation\\SaintWall_Hit_1_eff.anim";
	wstring animName = L"SaintWall_Hit_1_eff";

	GetOwner()->Animator2D()->LoadAnimation(animPath);
	GetOwner()->Animator2D()->Play(animName, false);
	GetOwner()->Animator2D()->GetCurAnim()->SetEndCallBack([this, animPath, animName]()
		{
			GetOwner()->Destroy();
		});
}

void CPlayerSkillScript::ExecuteRefentence()
{
	GetOwner()->Animator2D()->LoadAnimation(m_SkillInfo.animPath);
	GetOwner()->Animator2D()->Play(m_SkillInfo.animName, false);

	PlaySoundEffect(L"Sound\\pw_repentence_01.ogg");

	GetOwner()->Animator2D()->GetCurAnim()->SetEndCallBack([this]()
		{
			wstring animPath = L"Animation\\Repentence_1_eff.anim";
			wstring animName = L"Repentence_1_eff";

			vector<pair<int, int>> eventIdx = { {1, 3}, {7, 9} };

			GetOwner()->Animator2D()->LoadAnimation(animPath);
			GetOwner()->Animator2D()->Play(animName, false);

			PlaySoundEffect(L"Sound\\pw_repentence_02.ogg");

			GetOwner()->Animator2D()->GetCurAnim()->SetEventCallBack([this, eventIdx]()
				{
					// active = 1 , 7  deactive = 3 , 9
					if (GetOwner()->Animator2D()->GetCurAnim()->GetCurIndex() == eventIdx[0].first
						|| GetOwner()->Animator2D()->GetCurAnim()->GetCurIndex() == eventIdx[1].first)
					{
						PlaySoundEffect(L"Sound\\cross_hit_03.ogg");
						CSkillManager::Instance().GetUsedPlayer()->GetAttackArea(4)->Activate();
					}

					if (GetOwner()->Animator2D()->GetCurAnim()->GetCurIndex() == eventIdx[0].second
						|| GetOwner()->Animator2D()->GetCurAnim()->GetCurIndex() == eventIdx[1].second)
					{
						PlaySoundEffect(L"Sound\\cross_hit_04.ogg");
						CSkillManager::Instance().GetUsedPlayer()->GetAttackArea(4)->Deactivate();
					}
				});

			GetOwner()->Animator2D()->GetCurAnim()->SetEndCallBack([this]()
				{
					GetOwner()->Destroy();
				});
		});
}

void CPlayerSkillScript::ExecuteGrandCrossCrash()
{
	GetOwner()->Animator2D()->LoadAnimation(m_SkillInfo.animPath);
	GetOwner()->Animator2D()->Play(m_SkillInfo.animName, false);

	GetOwner()->Animator2D()->GetCurAnim()->SetStartCallBack([this]()
		{
			if (GetOwner()->GetName() == L"GrandCrossCrash_0_eff")
			{
				PlaySoundEffect(L"Sound\\pw_grandcross_01.ogg");
				PlaySoundEffect(L"Sound\\grandcross.ogg");
			}

			if (GetOwner()->GetName() == L"GrandCrossCrash_1_eff")
			{
				CSkillManager::Instance().GetUsedPlayer()->GetAttackArea(3)->Activate();
			}
		});

	GetOwner()->Animator2D()->GetCurAnim()->SetEndCallBack([this]()
		{
			if (GetOwner()->GetName() == L"GrandCrossCrash_0_eff")
			{
				PlaySoundEffect(L"Sound\\pw_grandcross_02.ogg");
				CSkillManager::Instance().GetUsedPlayer()->ExecuteSkill(eSkillType::GrandCrossCrash_1);
				CSkillManager::Instance().GetUsedPlayer()->ExecuteSkill(eSkillType::GrandCrossCrash_Aura);
			}

			if (GetOwner()->GetName() == L"GrandCrossCrash_1_eff")
			{
				CSkillManager::Instance().GetUsedPlayer()->GetAttackArea(3)->Deactivate();
			}

			GetOwner()->Destroy();
		});
}

void CPlayerSkillScript::GrandCrossCrashAura()
{
	GetOwner()->Animator2D()->LoadAnimation(m_SkillInfo.animPath);
	GetOwner()->Animator2D()->Play(m_SkillInfo.animName, true);
	m_LifeTimer = 3.f;
}

void CPlayerSkillScript::ExecuteHolyFlash()
{
	GetOwner()->Animator2D()->LoadAnimation(m_SkillInfo.animPath);
	GetOwner()->Animator2D()->Play(m_SkillInfo.animName, true);
	PlaySoundEffect(L"Sound\\holyflash_cast.ogg");

	GetOwner()->Animator2D()->GetCurAnim()->SetEndCallBack([this]()
		{
			CSkillManager::Instance().GetUsedPlayer()->ExecuteSkill(eSkillType::HolyFlash_Ball);

			wstring animPath = L"Animation\\HolyFlash_0_eff.anim";
			wstring animName = L"HolyFlash_0_eff";

			GetOwner()->Animator2D()->LoadAnimation(animPath);
			GetOwner()->Animator2D()->Play(animName, false);
			PlaySoundEffect(L"Sound\\pw_holyflash.ogg");

			GetOwner()->Animator2D()->GetCurAnim()->SetEndCallBack([this]()
				{
					GetOwner()->Destroy();
				});
		});
}

void CPlayerSkillScript::HolyFlashBall()
{
	GetOwner()->Animator2D()->LoadAnimation(m_SkillInfo.animPath);
	GetOwner()->Animator2D()->Play(m_SkillInfo.animName, false);

	m_IsMove = true;

	GetOwner()->Animator2D()->GetCurAnim()->SetStartCallBack([this]()
		{
			GetOwner()->AddComponent(new CCollider2D);
			GetOwner()->Collider2D()->SetOffset(Vec3(-0.29f, 0.28f, 0.f));
			GetOwner()->Collider2D()->SetScale(Vec3(0.1f, 0.2f, 1.f));
		});

	GetOwner()->Animator2D()->GetCurAnim()->SetEndCallBack([this]()
		{
			m_IsMove = false;

			GetOwner()->Destroy();
		});
}

void CPlayerSkillScript::ExecuteCrusaderBuff()
{
	GetOwner()->Animator2D()->LoadAnimation(m_SkillInfo.animPath);
	GetOwner()->Animator2D()->Play(m_SkillInfo.animName, false);
	PlaySoundEffect(L"Sound\\pw_blesscourage.ogg");
	PlaySoundEffect(L"Sound\\blessangel.ogg");

	GetOwner()->Animator2D()->GetCurAnim()->SetEndCallBack([this]()
		{
			GetOwner()->Destroy();
		});
}

void CPlayerSkillScript::PlaySoundEffect(const wstring& soundPath)
{
	Ptr<CSound> pNewBgm = CAssetManager::GetInst()->FindAsset<CSound>(soundPath);
	pNewBgm->Play(1, 0.3f, true);
}

void CPlayerSkillScript::SaveToLevelFile(FILE* file)
{

}

void CPlayerSkillScript::LoadFromLevelFile(FILE* file)
{

}