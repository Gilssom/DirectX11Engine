#include "pch.h"
#include "CPlayerScript.h"

#include "..\Client\CLevelSaveLoad.h"
#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>

#include <Engine\\CAnim2D.h>

#include <Engine\\CCollider2D.h>

#include "CCameraMoveScript.h"
#include "CPlayerSkillScript.h"
#include "CSkillManager.h"
#include "CUIManager.h"
#include "UIButton.h"

CPlayerScript::CPlayerScript()
	: CScript(SCRIPT_TYPE::PLAYERSCRIPT)
	, m_OriginPosObject(nullptr)
	, m_MaxHp(1000)
	, m_CurHp(m_MaxHp)
	, m_MaxMp(500)
	, m_CurMp(m_MaxMp)
	, m_Damage(1256)
	, m_Speed(250.f)
	, m_TargetMonster(nullptr)
	, m_MoveLeft(false)
	, m_MoveRight(false)
	, m_CanMoveLeft(true)
	, m_IsJumping(false)
	, m_HitDamage(false)
	, m_HitDownTime(2.f)
	, m_CurHitDownTime(0.f)
	, m_JumpSpeed(0.f)
	, m_JumpHeight(0.f)
	, m_Gravity(0.f)
	, m_CanMoveRight(true)
	, m_CanMoveUp(true)
	, m_CanMoveDown(true)
	, m_IsFightLevel(false)
	, m_IsSkill(false)
	, m_IsCombo(false)
	, m_ComboIndex(0)
	, m_ComboTimer(0.f)
	, m_MaxComboTime(5.0f)
	, m_AttackArea{}
	, m_HitTimer(0.f)
	, m_ResetTargetTime(3.f)
	, m_SetTargetTime(0.f)
	, m_KnockBackPower(450.f)
	, m_CanKnockBack(true)
	, m_KnockBackCoolTime(7.5f)
	, m_KnockBackCurTime(0.f)
{
	AddScriptProperty(PROPERTY_TYPE::INT, "Max Hp", &m_MaxHp);
	AddScriptProperty(PROPERTY_TYPE::INT, "Cur Hp", &m_CurHp);
	AddScriptProperty(PROPERTY_TYPE::INT, "Max Mp", &m_MaxMp);
	AddScriptProperty(PROPERTY_TYPE::INT, "Cur Mp", &m_CurMp);
	AddScriptProperty(PROPERTY_TYPE::FLOAT, "Speed", &m_Speed);
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::Begin()
{
	AnimationInit();

	m_ComboIndex = 0;
	m_IsSkill = false;
	m_ComboTimer = 0.5f;

	CSkillManager::Instance().SetUsedPlayer(this);
	CUIManager::GetInst()->SetPlayer(this);

	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();

	if (pCurLevel->GetFightLevel())
	{
		wstring levelName = pCurLevel->GetName();
		CUIManager::GetInst()->ChangeLevel(levelName);
	}

	vector<CGameObject*> child = GetOwner()->GetChildren();
	m_AttackArea.resize(child.size());

	for (size_t i = 0; i < child.size(); i++)
	{
		if (child[i]->Collider2D() == nullptr)
			continue;

		wstring name = L"Attack Area_" + to_wstring(i);

		if (child[i]->GetName() == name)
		{
			m_AttackArea[i] = child[i]->Collider2D();
			m_AttackArea[i]->Deactivate();
		}
	}
}

void CPlayerScript::Tick()
{
	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();
	m_IsFightLevel = pCurLevel->GetFightLevel();

	m_OriginPosObject = GetOwner()->GetParent();

	if (m_HitDamage)
	{
		KnockBack();
		return;
	}

	if(!m_IsSkill || !m_IsCombo)
		Move();

	if (m_IsJumping)
		Jump();

	//if(m_IsFightLevel)
	Skill();

	if (m_MaxHp > m_CurHp)
	{
		m_NaturalHealHp -= DT;

		if (m_NaturalHealHp <= 0.f)
		{
			int addHp = 7;

			if (m_CurHp + addHp > m_MaxHp)
				m_CurHp = m_MaxHp;
			else
				m_CurHp += addHp;

			m_NaturalHealHp = 1.f;
		}
	}

	if (m_MaxMp > m_CurMp)
	{
		m_NaturalHealMp -= DT;

		if (m_NaturalHealMp <= 0.f)
		{
			int addMp = 5;

			if (m_CurMp + addMp > m_MaxMp)
				m_CurMp = m_MaxMp;
			else
				m_CurMp += addMp;

			m_NaturalHealMp = 1.f;
		}
	}

	if (m_HitTimer > 0.f)
	{
		m_HitTimer -= DT;

		if (m_HitTimer <= 0.f)
		{
			GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 0);
			m_HitTimer = 0.f;
		}
	}

	if (m_SetTargetTime > 0.f)
	{
		m_SetTargetTime -= DT;

		if (m_SetTargetTime <= 0.f)
		{
			ResetTarget();
		}
	}

	if (m_KnockBackCurTime > 0.f)
	{
		m_KnockBackCurTime -= DT;

		if (m_KnockBackCurTime <= 0.f)
		{
			m_CanKnockBack = true;
		}
	}
}

void CPlayerScript::Move()
{
	CAnim2D* pCurAnim = Animator2D()->GetCurAnim();

	// 키 입력에 따른 위치 이동
	Vec3 vCurPos = m_OriginPosObject->Transform()->GetRelativePos();
	Vec3 vPlayerPos = GetOwner()->Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::UP))
	{
		if (!m_CanMoveUp)
			return;

		vCurPos.y += DT * m_Speed * 0.5f;
		vCurPos.z += DT * m_Speed * 0.05f;
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		if (!m_CanMoveDown)
			return;

		vCurPos.y -= DT * m_Speed * 0.5f;
		vCurPos.z -= DT * m_Speed * 0.05f;
	}

	// GameObject 를 양쪽으로 뒤집기 위해선 Relative Scale x 에 음수(좌측), 양수(우측) 값 넣으면 됨.
	if (KEY_TAP(KEY::LEFT))
	{
		if (!Transform()->GetLeft())
		{
			vPlayerPos += Vec3(-80.f, 0.f, 0.f);
			
			GetOwner()->Transform()->SetRelativePos(vPlayerPos);
		}

		pCurAnim->Reset();
		
		if (!m_IsFightLevel)
			Animator2D()->Play(L"Priest_Walk", true);
		else
			Animator2D()->Play(L"Priest_Run", true);
	}
	if (KEY_PRESSED(KEY::LEFT))
	{
		if (!m_CanMoveLeft)
			return;

		m_MoveLeft = true;
		Transform()->SetLeft(true);
		Transform()->SetRight(false);
		vCurPos.x -= DT * m_Speed;
	}
	if (KEY_RELEASED(KEY::LEFT))
	{
		m_MoveLeft = false;

		if(!m_IsFightLevel)
			Animator2D()->Play(L"Priest_Idle", true);
		else
			Animator2D()->Play(L"Priest_Idle2", true);
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		if (!Transform()->GetRight())
		{
			vPlayerPos += Vec3(80.f, 0.f, 0.f);

			GetOwner()->Transform()->SetRelativePos(vPlayerPos);
		}

		pCurAnim->Reset();
		
		if (!m_IsFightLevel)
			Animator2D()->Play(L"Priest_Walk", true);
		else
			Animator2D()->Play(L"Priest_Run", true);
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		if (!m_CanMoveRight)
			return;

		m_MoveRight = true;
		Transform()->SetRight(true);
		Transform()->SetLeft(false);
		vCurPos.x += DT * m_Speed;
	}
	if (KEY_RELEASED(KEY::RIGHT))
	{
		m_MoveRight = false;
		
		if (!m_IsFightLevel)
			Animator2D()->Play(L"Priest_Idle", true);
		else
			Animator2D()->Play(L"Priest_Idle2", true);
	}

	m_OriginPosObject->Transform()->SetRelativePos(vCurPos);
}

void CPlayerScript::Jump()
{
	Vec3 vCurPos = m_OriginPosObject->Transform()->GetRelativePos();
	vCurPos.y += m_JumpSpeed * DT;
	m_JumpSpeed -= m_Gravity * DT;

	if (vCurPos.y <= m_PrevPosY && m_JumpSpeed <= 0.f)
	{
		vCurPos.y = m_PrevPosY;
		m_IsJumping = false;

		if (!m_IsFightLevel)
			Animator2D()->Play(L"Priest_Idle", true);
		else
			Animator2D()->Play(L"Priest_Idle2", true);
	}

	m_OriginPosObject->Transform()->SetRelativePos(vCurPos);
}

void CPlayerScript::Skill()
{
	CAnim2D* pCurAnim = Animator2D()->GetCurAnim();

	if (pCurAnim->IsFinish() && !Animator2D()->GetRepeat())
	{
		m_IsSkill = false;
		
		if (!m_IsFightLevel)
			Animator2D()->Play(L"Priest_Idle", true);
		else
			Animator2D()->Play(L"Priest_Idle2", true);
	}

	if (KEY_TAP(KEY::X) && !m_IsCombo)
	{
		m_IsSkill = true;
		m_IsCombo = true;
		AttackCombo(m_ComboIndex);
	}
	ComboCheck();

	if (KEY_TAP(KEY::C))
	{
		m_IsSkill = true;
		Animator2D()->Play(L"Priest_Attack_2", false);
		AttackCombo(2);
	}

	if (KEY_TAP(KEY::V))
	{
		if (!m_IsJumping)
		{
			m_IsJumping = true;
			m_JumpSpeed = 500.f;
			m_Gravity = 800.f;

			m_PrevPosY = m_OriginPosObject->Transform()->GetRelativePos().y;

			PlaySoundEffect(L"Sound\\pw_jump.ogg");

			Animator2D()->Play(L"Priest_Jump", true);

			m_MoveLeft = false;
			m_MoveRight = false;
		}
	}

	if (KEY_TAP(KEY::A))
	{
		if (!CSkillManager::Instance().SkillCoolTime(eSkillType::SaintWall))
		{
			CoolTimeSound();
			return;
		}

		if (!CSkillManager::Instance().SkillUseMana(eSkillType::SaintWall, m_CurMp))
			return;

		m_IsSkill = true;
		Animator2D()->Play(L"Priest_Saint_Wall", false);
		ExecuteSkill(eSkillType::SaintWall);
	}

	if (KEY_TAP(KEY::S))
	{
		if (!CSkillManager::Instance().SkillCoolTime(eSkillType::GrandCrossCrash))
		{
			CoolTimeSound();
			return;
		}

		if (!CSkillManager::Instance().SkillUseMana(eSkillType::GrandCrossCrash, m_CurMp))
			return;

		m_IsSkill = true;
		Animator2D()->Play(L"Preist_Grand_Cross_Crash", false);
		ExecuteSkill(eSkillType::GrandCrossCrash);
	}

	if (KEY_TAP(KEY::D))
	{
		if (!CSkillManager::Instance().SkillCoolTime(eSkillType::RefentenceSmash))
		{
			CoolTimeSound();
			return;
		}

		if (!CSkillManager::Instance().SkillUseMana(eSkillType::RefentenceSmash, m_CurMp))
			return;

		m_IsSkill = true;
		Animator2D()->Play(L"Priest_Refantans_Smash", false);
		ExecuteSkill(eSkillType::RefentenceSmash);
	}

	if (KEY_TAP(KEY::F))
	{
		if (!CSkillManager::Instance().SkillCoolTime(eSkillType::HolyFlash))
		{
			CoolTimeSound();
			return;
		}

		if (!CSkillManager::Instance().SkillUseMana(eSkillType::HolyFlash, m_CurMp))
			return;

		m_IsSkill = true;
		Animator2D()->Play(L"Preist_Miracle_Shine", false);
		ExecuteSkill(eSkillType::HolyFlash);
	}

	if (KEY_TAP(KEY::R))
	{
		if (!CSkillManager::Instance().SkillCoolTime(eSkillType::CrusaderBuff))
		{
			CoolTimeSound();
			return;
		}

		if (!CSkillManager::Instance().SkillUseMana(eSkillType::CrusaderBuff, m_CurMp))
			return;

		m_IsSkill = true;
		//Animator2D()->Play(L"Preist_Miracle_Shine", false);
		ExecuteSkill(eSkillType::CrusaderBuff);
	}

	if (KEY_TAP(KEY::T))
	{
		KnockBack();
	}

	if (KEY_TAP(KEY::F2))
	{
		Collider2D()->SetShow();
	}
}

void CPlayerScript::AttackCombo(int comboIndex)
{
	wstring animName;
	int attackIndex = comboIndex + 2;

	switch (comboIndex)
	{
		case 0:
			animName = L"Priest_Attack_0";
			break;
		case 1:
			animName = L"Priest_Attack_1";
			break;
		case 2:
			animName = L"Priest_Attack_2";
			break;
		default:
			return;
	}

	auto pCurAnim = Animator2D()->FindAnimation(animName);
	if (pCurAnim)
	{
		pCurAnim->SetStartCallBack([this, comboIndex]()
		{
			ExecuteComboSkill(comboIndex);
		});

		pCurAnim->SetEventCallBack([this, comboIndex, attackIndex, pCurAnim]()
		{
			if (pCurAnim->GetCurIndex() == attackIndex)
			{
				PlaySoundEffect(L"Sound\\Attack_" + to_wstring(comboIndex) + L".ogg");
				PlaySoundEffect(L"Sound\\pw_Attack_" + to_wstring(comboIndex) + L".ogg");

				if (comboIndex == 2)
				{
					PlaySoundEffect(L"Sound\\hk1_counter.ogg");
				}

				m_AttackArea[comboIndex]->Activate();
			}
		});

		pCurAnim->SetEndCallBack([this, comboIndex]()
		{
			if (KEY_PRESSED(KEY::X) && comboIndex < 2)
			{
				m_ComboIndex++;
				AttackCombo(m_ComboIndex);
				m_AttackArea[comboIndex]->Deactivate();
			}
			else
			{
				m_IsSkill = false;
				m_IsCombo = false;
				m_ComboIndex = 0;
				m_AttackArea[comboIndex]->Deactivate();
			}
		});

		Animator2D()->Play(animName, false);	
	}
}

void CPlayerScript::ExecuteComboSkill(int comboIndex)
{
	eSkillType skillType;

	if (comboIndex == 0)
	{
		skillType = eSkillType::Attack_0;
	}
	else if (comboIndex == 1)
	{
		skillType = eSkillType::Attack_1;
	}
	else if (comboIndex == 2)
	{
		skillType = eSkillType::Attack_2;
	}

	ExecuteSkill(skillType);
}

void CPlayerScript::ExecuteSkill(eSkillType skillType)
{
	Vec3 vSpawnPos = m_OriginPosObject->Transform()->GetRelativePos();
	CGameObject* skillEffect = nullptr;

	if (Transform()->GetRight())
	{
		skillEffect = CSkillManager::Instance().CreateSkill(skillType, vSpawnPos, false);
	}
	else
	{
		skillEffect = CSkillManager::Instance().CreateSkill(skillType, vSpawnPos, true);
	}

	if (skillEffect)
	{
		CPlayerSkillScript* skillScript = skillEffect->GetScript<CPlayerSkillScript>();

		if (skillScript)
			skillScript->FinalExecuteSkill();
	}
}

void CPlayerScript::ComboCheck()
{
	if (m_IsCombo)
	{
		m_ComboTimer += DT;
		if (m_ComboTimer > m_MaxComboTime)
		{
			m_IsCombo = false;
			m_IsSkill = false;
			m_ComboIndex = 0;
			m_ComboTimer = 0.0f;
		}
	}
}

void CPlayerScript::TakeDamage(int damage)
{
	// Hit Damage Event
	GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 1);

	m_HitTimer = 0.25f;

	m_CurHp -= damage;
}

void CPlayerScript::KnockBack()
{
	if (!m_CanKnockBack)
		return;

	if (m_HitDamage == false)
	{
		m_HitDamage = true;
		m_CurHitDownTime = m_HitDownTime;

		m_KnockBackVelocity = Vec3(50.f, 250.f, 0.f);
		m_PrevPosY = m_OriginPosObject->Transform()->GetRelativePos().y;

		Animator2D()->Play(L"Priest_HitDown", false);  // 피격 애니메이션 재생
	}

	if (m_CurHitDownTime > 0.f)
	{
		m_CurHitDownTime -= DT;

		Vec3 pos = m_OriginPosObject->Transform()->GetRelativePos();
		m_KnockBackVelocity.x *= -1.f;
		pos += m_KnockBackVelocity * DT;
		m_OriginPosObject->Transform()->SetRelativePos(pos);

		m_KnockBackVelocity.y -= m_KnockBackPower * DT;

		if (pos.y <= m_PrevPosY)
		{
			pos.y = m_PrevPosY;
			m_OriginPosObject->Transform()->SetRelativePos(pos);			
		}
	}
	else if (m_CurHitDownTime <= 0.f)
	{
		m_HitDamage = false;
		m_CanKnockBack = false;
		m_KnockBackCurTime = m_KnockBackCoolTime;
	}
}

void CPlayerScript::CoolTimeSound()
{
	wstring soundPath[2] = { L"Sound\\pw_cooltime_sorceress_01.ogg", L"Sound\\pw_cooltime_sorceress_02.ogg" };
	int random = GetRandomInt(0, 1);

	PlaySoundEffect(soundPath[random]);
}

void CPlayerScript::SetTarget(CMonsterScript* target)
{
	m_TargetMonster = target;
	m_SetTargetTime = m_ResetTargetTime;
}

void CPlayerScript::AnimationInit()
{
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Priest_Walk.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Priest_Run.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Priest_Idle.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Priest_Idle2.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Priest_Jump.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Priest_HitDown.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Priest_Attack_0.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Priest_Attack_1.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Priest_Attack_2.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Preist_Grand_Cross_Crash.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Preist_Miracle_Shine.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Priest_Saint_Wall.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Priest_Refantans_Smash.anim");
}

#pragma region Collision Contents Script
void CPlayerScript::BeginOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	if (otherObject->GetName() == L"East_Wall")
		m_CanMoveRight = false;

	if (otherObject->GetName() == L"West_Wall")
		m_CanMoveLeft = false;

	if (otherObject->GetName() == L"North_Wall")
		m_CanMoveUp = false;

	if (otherObject->GetName() == L"South_Wall")
		m_CanMoveDown = false;

	if (otherObject->GetName() == L"GatePortal")
		CLevelManager::GetInst()->ChangeNextLevel();

	if (otherObject->GetName() == L"Goblin Attack Area 0")
	{
		TakeDamage(80);
		KnockBack();
	}

	if (otherObject->GetName() == L"Tau Attack Area 0")
		TakeDamage(100);

	if (otherObject->GetName() == L"Tau Attack Area 1")
	{
		TakeDamage(100);
		KnockBack();
	}

	if (otherObject->GetName() == L"Boss Attack Area 0")
		TakeDamage(200);

	if (otherObject->GetName() == L"Boss Attack Area 1")
	{
		TakeDamage(200);
		KnockBack();
	}
}

void CPlayerScript::Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{

}

void CPlayerScript::EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	if (otherObject->GetName() == L"East_Wall")
		m_CanMoveRight = true;

	if (otherObject->GetName() == L"West_Wall")
		m_CanMoveLeft = true;

	if (otherObject->GetName() == L"North_Wall")
		m_CanMoveUp = true;

	if (otherObject->GetName() == L"South_Wall")
		m_CanMoveDown = true;
}
#pragma endregion

void CPlayerScript::SaveToLevelFile(FILE* file)
{
	fwrite(&m_Speed, sizeof(float), 1, file);
}

void CPlayerScript::LoadFromLevelFile(FILE* file)
{
	fread(&m_Speed, sizeof(float), 1, file);
}