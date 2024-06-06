#include "pch.h"
#include "CPlayerScript.h"

#include "..\Client\CLevelSaveLoad.h"
#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>

#include <Engine\\CAnim2D.h>

#include <Engine\\CCollider2D.h>

#include "CCameraMoveScript.h"

CPlayerScript::CPlayerScript()
	: CScript(SCRIPT_TYPE::PLAYERSCRIPT)
	, m_Speed(250.f)
	, m_TargetMonster(nullptr)
	, m_MoveLeft(false)
	, m_MoveRight(false)
	, m_CanMoveLeft(true)
	, m_CanMoveRight(true)
	, m_CanMoveUp(true)
	, m_CanMoveDown(true)
	, m_IsFightLevel(false)
	, m_IsSkill(false)
	, m_IsCombo(false)
	, m_ComboIndex(0)
	, m_ComboTimer(0.f)
	, m_MaxComboTime(5.0f)
{
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
}

void CPlayerScript::Tick()
{
	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();
	m_IsFightLevel = pCurLevel->GetFightLevel();

	if(!m_IsSkill || !m_IsCombo)
		Move();

	//if(m_IsFightLevel)
		Skill();
}

void CPlayerScript::Move()
{
	CAnim2D* pCurAnim = Animator2D()->GetCurAnim();

	// 키 입력에 따른 위치 이동
	Vec3 vCurPos = GetOwner()->Transform()->GetRelativePos();

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
			vCurPos += Vec3(-90.f, 0.f, 0.f);
			GetOwner()->Transform()->SetRelativePos(vCurPos);
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
			vCurPos += Vec3(90.f, 0.f, 0.f);
			GetOwner()->Transform()->SetRelativePos(vCurPos);
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

	Transform()->SetRelativePos(vCurPos);
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
	}

	if (KEY_TAP(KEY::V))
	{
		m_IsSkill = true;
		Animator2D()->Play(L"Priest_Jump", false);
	}

	if (KEY_TAP(KEY::A))
	{
		m_IsSkill = true;
		Animator2D()->Play(L"Priest_Saint_Wall", false);
	}

	if (KEY_TAP(KEY::S))
	{
		m_IsSkill = true;
		Animator2D()->Play(L"Preist_Grand_Cross_Crash", false);
	}

	if (KEY_TAP(KEY::D))
	{
		m_IsSkill = true;
		Animator2D()->Play(L"Priest_Refantans_Smash", false);
	}

	if (KEY_TAP(KEY::F))
	{
		m_IsSkill = true;
		Animator2D()->Play(L"Preist_Miracle_Shine", false);
	}
}

void CPlayerScript::AttackCombo(int comboIndex)
{
	wstring animName;

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

	auto anim = Animator2D()->FindAnimation(animName);
	if (anim)
	{
		anim->SetEndCallBack([this, comboIndex]()
		{
			if (KEY_PRESSED(KEY::X) && comboIndex < 2)
			{
				m_ComboIndex++;
				AttackCombo(m_ComboIndex);
			}
			else
			{
				m_IsSkill = false;
				m_IsCombo = false;
				m_ComboIndex = 0;
			}
		});

		Animator2D()->Play(animName, false);
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