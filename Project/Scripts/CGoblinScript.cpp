#include "pch.h"
#include "CGoblinScript.h"
#include "CPlayerScript.h"
#include "CGateScript.h"

#include <Engine\\CTaskManager.h>
#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>
#include <Engine\\CAnim2D.h>

CGoblinScript::CGoblinScript()
	: CMonsterScript(SCRIPT_TYPE::GOBLINSCRIPT)
	, m_CurrentState(eGoblinState::Idle)
	, m_PrevState(eGoblinState::Idle)
	, m_StateTimer(0.f)
	, m_ChaseCoolTime(0.f)
	, m_CurChaseCoolTime(0.f)
	, m_CurAttackCoolTime(0.f)
	, m_IsAttack(false)
	, m_CurHitTime(0.f)
	, m_IsAirborne(false)
	, m_AirborneDuration(0.f)
	, m_AirbornePower(0.f)
	, m_AirborneVelocity {}
	, m_Player(nullptr)
	, m_PatrolDirection(-1)
	, m_ChangeDirectionCoolTime(0.f)
{
	m_Speed = 100.f;
	m_Health = 10000;
	m_MaxHealth = m_Health;
	m_Armor = 30;
	m_Damage = 100;
	m_AttackRange = 80.f;
	m_AttackCoolTime = 5.f;
	m_ChaseCoolTime = 4.f;
	m_AirbornePower = 450.f;
	m_ChangeDirectionCoolTime = 2.f;

	m_TraceDistance = 200.f;

	AddScriptProperty(PROPERTY_TYPE::FLOAT, "Speed", &m_Speed);
	AddScriptProperty(PROPERTY_TYPE::INT, "Health", &m_Health);
	AddScriptProperty(PROPERTY_TYPE::INT, "Damage", &m_Damage);
	AddScriptProperty(PROPERTY_TYPE::FLOAT, "Attack Range", &m_AttackRange);
	AddScriptProperty(PROPERTY_TYPE::FLOAT, "Airborne Power", &m_AirbornePower);
}

CGoblinScript::~CGoblinScript()
{
	
}

void CGoblinScript::Begin()
{
	CMonsterScript::Begin();

	vector<CGameObject*> child = GetOwner()->GetChildren();
	for (size_t i = 0; i < child.size(); i++)
	{
		if (child[i]->Collider2D() == nullptr)
			continue;

		wstring name = L"Goblin Attack Area " + to_wstring(i);

		if (child[i]->GetName() == name)
		{
			m_AttackArea.push_back(child[i]->Collider2D());
			m_AttackArea[i]->Deactivate();
		}
	}
}

void CGoblinScript::Tick()
{
	CMonsterScript::Tick();

	m_Player = CLevelManager::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	m_CurGate = CLevelManager::GetInst()->GetCurrentLevel()->FindObjectByName(L"GatePortal");

	m_OriginPosObject = GetOwner()->GetParent();

	if (m_IsDeath)
		SetState(eGoblinState::Death);

	// Gobline FSM
	m_StateTimer += DT;
	m_CurChaseCoolTime += DT;

	if (m_CurAttackCoolTime > 0.f)
		m_CurAttackCoolTime -= DT;

	if (m_CurHitTime > 0.f)
		m_CurHitTime -= DT;

	if (m_ChangeDirectionCoolTime > 0.f)
		m_ChangeDirectionCoolTime -= DT;

	if(!m_IsAttack || !m_IsDeath)
		UpdataDirection();

	switch (m_CurrentState)
	{
	case eGoblinState::Idle:
		Idle();
		break;
	case eGoblinState::Move:
		Move();
		break;
	case eGoblinState::Patrol:
		Patrol();
		break;
	case eGoblinState::Attack:
		Attack();
		break;
	case eGoblinState::Hit:
		Hit();
		break;
	case eGoblinState::Airborne:
		Airborne();
		break;
	case eGoblinState::Death:
		Death();
		break;
	}
}

#pragma region Collision Contents Script
void CGoblinScript::BeginOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	if (otherObject->GetName() == L"Attack Area_0")
		TakeDamage(0.9f, 1.1f);

	if (otherObject->GetName() == L"Attack Area_1")
		TakeDamage(1.1f, 1.4f);

	if (otherObject->GetName() == L"Attack Area_2")
	{
		TakeDamage(1.3f, 1.7f);
		SetState(eGoblinState::Airborne);
		m_AirborneDuration = 2.f;
		m_AirborneVelocity = Vec3(50.f, 200.f, 0.f);
		m_PrevPosY = m_OriginPosObject->Transform()->GetRelativePos().y;
	}

	if (otherObject->GetName() == L"Attack Area_3")
		TakeDamage(1.3f, 1.7f);

	if (otherObject->GetName() == L"Attack Area_4")
		TakeDamage(1.7f, 2.5f, L"Refentence");

	if (otherObject->GetName() == L"HolyFlash_Ball_eff")
	{
		TakeDamage(0.6f, 0.8f, L"HolyFlash");
		otherObject->Destroy();
	}

	if (otherObject->GetName() == L"SaintWall_0_eff")
		TakeDamage(0, 0);

	if (otherObject->GetName() == L"East_Wall")
	{
		m_ChangeDirectionCoolTime = 3.f;
		m_PatrolDirection = 3;
	}

	if (otherObject->GetName() == L"West_Wall")
	{
		m_ChangeDirectionCoolTime = 3.f;
		m_PatrolDirection = 2;
	}

	if (otherObject->GetName() == L"North_Wall")
	{
		m_ChangeDirectionCoolTime = 3.f;
		m_PatrolDirection = 1;
	}

	if (otherObject->GetName() == L"South_Wall")
	{
		m_ChangeDirectionCoolTime = 3.f;
		m_PatrolDirection = 0;
	}
}

void CGoblinScript::Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	if (otherObject->GetName() == L"SaintWall_0_eff")
		KnockBack(otherObject, L"SaintWall");
}

void CGoblinScript::EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	if (otherObject->GetName() == L"SaintWall_0_eff")
		TakeDamage(1.2f, 1.4f);
}
#pragma endregion

void CGoblinScript::SetState(eGoblinState nextState)
{
	if (m_CurrentState != nextState)
	{
		m_PrevState = m_CurrentState;
		m_CurrentState = nextState;
		m_StateTimer = 0.f;

		switch (nextState)
		{
		case eGoblinState::Idle:
			PlayAnimation(L"Goblin_Idle", true);
			break;
		case eGoblinState::Move:
			PlayAnimation(L"Goblin_Move", true);
			break;
		case eGoblinState::Patrol:
			PlayAnimation(L"Goblin_Move", true);
			break;
		case eGoblinState::Hit:
			PlayAnimation(L"Goblin_Hit", true);
			break;
		case eGoblinState::Death:
			PlayAnimation(L"Goblin_Death", false);
			break;
		}
	}
}

void CGoblinScript::Idle()
{
	if (m_CurChaseCoolTime >= m_ChaseCoolTime && m_Player)
	{
		if (IsPlayerTarget())
		{
			SetState(eGoblinState::Attack);
		}
		else
		{
			PlaySoundEffect(L"Sound\\gbn_comm.ogg");
			SetState(eGoblinState::Move);
			m_CurChaseCoolTime = 0.f;
		}
	}
}

void CGoblinScript::Move()
{
	if (m_Player)
	{
		CPlayerScript* pPlayerScript = m_Player->GetScript<CPlayerScript>();

		Vec3 playerPos = pPlayerScript->GetOriginPos()->Transform()->GetRelativePos();
		Vec3 goblinPos = m_OriginPosObject->Transform()->GetRelativePos();
		Vec3 direction = playerPos - goblinPos;
		direction.Normalize();

		m_Direction = direction;
		goblinPos += direction * m_Speed * DT;
		m_OriginPosObject->Transform()->SetRelativePos(goblinPos);

		if (IsPlayerTarget())
		{
			SetState(eGoblinState::Attack);
		}
		else if (Vec3::Distance(playerPos, goblinPos) > m_TraceDistance)
		{
			SetState(eGoblinState::Patrol);
		}
	}
}

void CGoblinScript::Patrol()
{
	CPlayerScript* pPlayerScript = m_Player->GetScript<CPlayerScript>();

	if (!pPlayerScript)
		return;

	Vec3 playerPos = pPlayerScript->GetOriginPos()->Transform()->GetRelativePos();
	Vec3 goblinPos = m_OriginPosObject->Transform()->GetRelativePos();

	if (m_ChangeDirectionCoolTime <= 0.f)
	{
		int direction = static_cast<int>(GetRandomFloat(0.f, 4.f));
		m_PatrolDirection = direction;
		m_ChangeDirectionCoolTime = 3.f;
	}

	switch (m_PatrolDirection)
	{
	case 0:
		goblinPos.y += m_Speed * DT * 0.5f;
		break;
	case 1:
		goblinPos.y -= m_Speed * DT * 0.5f;
		break;
	case 2:
		goblinPos.x += m_Speed * DT;
		break;
	case 3:
		goblinPos.x -= m_Speed * DT;
		break;
	}

	m_OriginPosObject->Transform()->SetRelativePos(goblinPos);

	if (Vec3::Distance(playerPos, goblinPos) <= m_TraceDistance)
	{
		SetState(eGoblinState::Move);
	}
}

void CGoblinScript::Attack()
{
	CAnim2D* pCurAnim = Animator2D()->GetCurAnim();

	int attackIndex = 4;

	if (m_CurAttackCoolTime <= 0.f)
	{
		if (m_Player && IsPlayerTarget())
		{
			PlayAnimation(L"Goblin_Attack", false);
			m_CurAttackCoolTime = m_AttackCoolTime;
		}
	}

	if (pCurAnim)
	{
		auto callback = std::bind([this, attackIndex, pCurAnim]()
			{
				if (pCurAnim->GetCurIndex() == attackIndex)
				{
					PlaySoundEffect(L"Sound\\gbn_thw.ogg");
					m_AttackArea[0]->Activate();
					m_IsAttack = true;
				}
			});

		pCurAnim->SetEventCallBack(callback);

		pCurAnim->SetEndCallBack([this]()
		{
			SetState(eGoblinState::Idle);
			m_AttackArea[0]->Deactivate();
			m_IsAttack = false;
		});
	}
}

void CGoblinScript::Hit()
{
	if (m_CurHitTime <= 0.f)
	{
		SetState(eGoblinState::Idle);
	}
}

void CGoblinScript::Airborne()
{
	if (m_AirborneDuration > 0.f)
	{
		m_AirborneDuration -= DT;

		Vec3 pos = m_OriginPosObject->Transform()->GetRelativePos();
		m_AirborneVelocity.x *= m_Direction.x;
		pos += m_AirborneVelocity * DT;
		m_OriginPosObject->Transform()->SetRelativePos(pos);

		m_AirborneVelocity.y -= m_AirbornePower * DT;

		if (pos.y <= m_PrevPosY)
		{
			pos.y = m_PrevPosY;
			m_OriginPosObject->Transform()->SetRelativePos(pos);
			SetState(eGoblinState::Idle);
		}
	}
}

void CGoblinScript::HitEvent()
{
	SetState(eGoblinState::Hit);
	m_CurHitTime = 1.f;

	CPlayerScript* pPlayerScript = m_Player->GetScript<CPlayerScript>();
	Vec3 playerPos = pPlayerScript->GetOriginPos()->Transform()->GetRelativePos();
	Vec3 goblinPos = m_OriginPosObject->Transform()->GetRelativePos();
	Vec3 direction = playerPos - goblinPos;
	direction.Normalize();

	goblinPos.x += -direction.x * 25.f;
	m_OriginPosObject->Transform()->SetRelativePos(goblinPos);

	int random = GetRandomInt(1, 4);
	wstring soundPath = L"Sound\\gbn_dmg_0" + to_wstring(random) + L".ogg";
	PlaySoundEffect(soundPath);

	random = GetRandomInt(3, 4);
	soundPath = L"Sound\\cross_hit_0" + to_wstring(random) + L".ogg";
	PlaySoundEffect(soundPath);
}

void CGoblinScript::Death()
{
	CAnim2D* pCurAnim = Animator2D()->GetCurAnim();

	pCurAnim->SetStartCallBack([this]()
		{
			int random = GetRandomInt(1, 2);
			wstring soundPath = L"Sound\\gbn_die_0" + to_wstring(random) + L".ogg";
			PlaySoundEffect(soundPath);
		});

	pCurAnim->SetEndCallBack([this]()
		{
			if (m_CurGate != nullptr)
				m_CurGate->GetScript<CGateScript>()->DeathMonsterCount();
		});

	if (pCurAnim->IsFinish())
	{
		tTask task = {};
		task.Type = TASK_TYPE::DESTROY_OBJECT;
		task.dwParam_0 = (DWORD_PTR)GetOwner()->GetParent();
		CTaskManager::GetInst()->AddTask(task);
	}
}

void CGoblinScript::UpdataDirection()
{
	if (m_Player)
	{
		CPlayerScript* pPlayerScript = m_Player->GetScript<CPlayerScript>();

		if (pPlayerScript->GetOriginPos() == nullptr)
			return;

		Vec3 playerPos = pPlayerScript->GetOriginPos()->Transform()->GetRelativePos();
		Vec3 goblinPos = m_OriginPosObject->Transform()->GetRelativePos();

		if (playerPos.x < goblinPos.x)
		{
			m_OriginPosObject->Transform()->SetRight(false);
			m_OriginPosObject->Transform()->SetLeft(true);
		}
		else
		{
			m_OriginPosObject->Transform()->SetRight(true);
			m_OriginPosObject->Transform()->SetLeft(false);
		}
	}
}

bool CGoblinScript::IsPlayerTarget()
{
	if (!m_Player)
		return false;

	CPlayerScript* pPlayerScript = m_Player->GetScript<CPlayerScript>();

	Vec3 playerPos = pPlayerScript->GetOriginPos()->Transform()->GetRelativePos();
	Vec3 goblinPos = m_OriginPosObject->Transform()->GetRelativePos();
	float distance = Vec3::Distance(playerPos, goblinPos);
	return distance <= m_AttackRange;
}

void CGoblinScript::AnimationInit()
{
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Goblin_Idle.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Goblin_Move.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Goblin_Attack.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Goblin_Hit.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Goblin_Death.anim");
}