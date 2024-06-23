#include "pch.h"
#include "CBossScript.h"
#include "CPlayerScript.h"

#include <Engine\\CTaskManager.h>
#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>
#include <Engine\\CAnim2D.h>

#include "CUIManager.h"
#include "UIResult.h"

CBossScript::CBossScript()
	: CMonsterScript(SCRIPT_TYPE::BOSSSCRIPT)
	, m_CurrentState(eBossState::Idle)
	, m_PrevState(eBossState::Idle)
	, m_StateTimer(0.f)
	, m_ChaseCoolTime(0.f)
	, m_CurChaseCoolTime(0.f)
	, m_CurAttackCoolTime(0.f)
	, m_IsAttack(false)
	, m_RushDistance(0.f)
	, m_RushCoolTime(0.f)
	, m_RushTargetPos{}
	, m_BuffCoolTime(0.f)
	, m_PatrolDirection(-1)
	, m_ChangeDirectionCoolTime(0.f)
	, m_Player(nullptr)
{
	m_Speed = 65.f;
	m_Health = 50000;
	m_MaxHealth = m_Health;
	m_Armor = 150;
	m_Damage = 200;
	m_AttackRange = 120.f;
	m_AttackCoolTime = 2.f;
	m_ChaseCoolTime = 2.f;
	m_ChangeDirectionCoolTime = 3.f;
	m_RushDistance = 500.f;

	m_TraceDistance = 500.f;

	AddScriptProperty(PROPERTY_TYPE::FLOAT, "Speed", &m_Speed);
	AddScriptProperty(PROPERTY_TYPE::INT, "Health", &m_Health);
	AddScriptProperty(PROPERTY_TYPE::INT, "Damage", &m_Damage);
	AddScriptProperty(PROPERTY_TYPE::FLOAT, "Attack Range", &m_AttackRange);
}

CBossScript::~CBossScript()
{
}

void CBossScript::Begin()
{
	CMonsterScript::Begin();

	vector<CGameObject*> child = GetOwner()->GetChildren();
	for (size_t i = 0; i < child.size(); i++)
	{
		if (child[i]->Collider2D() == nullptr)
			continue;

		wstring name = L"Boss Attack Area " + to_wstring(i);

		if (child[i]->GetName() == name)
		{
			m_AttackArea.push_back(child[i]->Collider2D());
			m_AttackArea[i]->Deactivate();
		}
	}
}

void CBossScript::Tick()
{
	CMonsterScript::Tick();

	m_Player = CLevelManager::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");

	m_OriginPosObject = GetOwner()->GetParent();

	if (m_IsDeath)
		SetState(eBossState::Death);

	// Tau FSM
	m_StateTimer += DT;
	m_CurChaseCoolTime += DT;

	if (m_CurAttackCoolTime > 0.f)
		m_CurAttackCoolTime -= DT;

	if (m_RushCoolTime > 0.f)
		m_RushCoolTime -= DT;

	if (m_BuffCoolTime > 0.f)
		m_BuffCoolTime -= DT;

	if (m_ChangeDirectionCoolTime > 0.f)
		m_ChangeDirectionCoolTime -= DT;

	if (!m_IsAttack || !m_IsDeath)
		UpdataDirection();

	switch (m_CurrentState)
	{
	case eBossState::Idle:
		Idle();
		break;
	case eBossState::Move:
		Move();
		break;
	case eBossState::Patrol:
		Patrol();
		break;
	case eBossState::Attack:
		Attack();
		break;
	case eBossState::Rush:
		Rush();
		break;
	case eBossState::Buff:
		Buff();
		break;
	case eBossState::Death:
		Death();
		break;
	}
}

void CBossScript::BeginOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	if (otherObject->GetName() == L"Attack Area_0")
		TakeDamage(0.9f, 1.1f);

	if (otherObject->GetName() == L"Attack Area_1")
		TakeDamage(1.1f, 1.4f);

	if (otherObject->GetName() == L"Attack Area_2")
		TakeDamage(1.3f, 1.7f);

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

void CBossScript::Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	if (otherObject->GetName() == L"SaintWall_0_eff")
		KnockBack(otherObject, L"SaintWall");
}

void CBossScript::EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider)
{
	if (otherObject->GetName() == L"SaintWall_0_eff")
		TakeDamage(1.2f, 1.4f);
}

void CBossScript::SetState(eBossState nextState)
{
	if (m_CurrentState != nextState)
	{
		m_PrevState = m_CurrentState;
		m_CurrentState = nextState;
		m_StateTimer = 0.f;

		switch (nextState)
		{
		case eBossState::Idle:
			PlayAnimation(L"Boss_Idle", true);
			break;
		case eBossState::Move:
			PlayAnimation(L"Boss_Move", true);
			break;
		case eBossState::Patrol:
			PlayAnimation(L"Boss_Move", true);
			break;
		case eBossState::Rush:
			PlayAnimation(L"Boss_Attack_1", false);
			break;
		case eBossState::Buff:
			PlayAnimation(L"Boss_Skill", false);
			break;
		case eBossState::Death:
			PlayAnimation(L"Boss_Death", false);
			break;
		}
	}
}

void CBossScript::Idle()
{
	if (m_CurChaseCoolTime >= m_ChaseCoolTime && m_Player)
	{
		if (GetRandomFloat(0.f, 1.f) < 0.4f && m_RushCoolTime <= 0.f)
		{
			PlaySoundEffect(L"Sound\\tau_rush.ogg");
			SetState(eBossState::Rush);
			m_RushCoolTime = 5.f;
		}
		else if (GetRandomFloat(0.f, 1.f) < 0.2f && m_BuffCoolTime <= 0.f)
		{
			PlaySoundEffect(L"Sound\\tau_roar.ogg");
			SetState(eBossState::Buff);
			m_BuffCoolTime = 10.f;
		}
		else
		{
			PlaySoundEffect(L"Sound\\tau_comm.ogg");
			SetState(eBossState::Move);
			m_CurChaseCoolTime = 0.f;
		}
	}
}

void CBossScript::Move()
{
	if (m_Player)
	{
		CPlayerScript* pPlayerScript = m_Player->GetScript<CPlayerScript>();

		Vec3 playerPos = pPlayerScript->GetOriginPos()->Transform()->GetRelativePos();
		Vec3 tauPos = m_OriginPosObject->Transform()->GetRelativePos();
		Vec3 direction = playerPos - tauPos;
		direction.Normalize();

		tauPos += direction * m_Speed * DT;
		m_OriginPosObject->Transform()->SetRelativePos(tauPos);

		if (IsPlayerTarget())
		{
			SetState(eBossState::Attack);
		}
		else if (Vec3::Distance(playerPos, tauPos) > m_TraceDistance)
		{
			SetState(eBossState::Patrol);
		}
	}
}

void CBossScript::Patrol()
{
	CPlayerScript* pPlayerScript = m_Player->GetScript<CPlayerScript>();

	Vec3 playerPos = pPlayerScript->GetOriginPos()->Transform()->GetRelativePos();
	Vec3 tauPos = m_OriginPosObject->Transform()->GetRelativePos();

	if (m_ChangeDirectionCoolTime <= 0.f)
	{
		int direction = static_cast<int>(GetRandomFloat(0.f, 4.f));
		m_PatrolDirection = direction;
		m_ChangeDirectionCoolTime = 3.f;
	}

	switch (m_PatrolDirection)
	{
	case 0:
		tauPos.y += m_Speed * DT * 0.5f;
		break;
	case 1:
		tauPos.y -= m_Speed * DT * 0.5f;
		break;
	case 2:
		tauPos.x += m_Speed * DT;
		break;
	case 3:
		tauPos.x -= m_Speed * DT;
		break;
	}

	m_OriginPosObject->Transform()->SetRelativePos(tauPos);

	if (Vec3::Distance(playerPos, tauPos) <= m_TraceDistance)
	{
		SetState(eBossState::Move);
	}
}

void CBossScript::Attack()
{
	CAnim2D* pCurAnim = Animator2D()->GetCurAnim();

	int attackIndex = 5;

	if (m_CurAttackCoolTime <= 0.f)
	{
		if (m_Player && IsPlayerTarget())
		{
			PlayAnimation(L"Boss_Attack_0", false);
			m_CurAttackCoolTime = m_AttackCoolTime;
		}
	}

	if (pCurAnim)
	{
		auto callback = std::bind([this, attackIndex, pCurAnim]()
			{
				if (pCurAnim->GetCurIndex() == attackIndex)
				{
					PlaySoundEffect(L"Sound\\tau_axeswing.ogg");
					m_AttackArea[0]->Activate();
					m_IsAttack = true;
				}
			});

		pCurAnim->SetEventCallBack(callback);

		pCurAnim->SetEndCallBack([this]()
			{
				PlaySoundEffect(L"Sound\\tau_crash.ogg");
				SetState(eBossState::Idle);
				m_AttackArea[0]->Deactivate();
				m_IsAttack = false;
			});
	}
}

void CBossScript::Rush()
{
	CAnim2D* pCurAnim = Animator2D()->GetCurAnim();

	if (pCurAnim)
	{
		pCurAnim->SetStartCallBack([this]()
			{
				m_IsAttack = true;
				m_AttackArea[1]->Activate();
			});

		pCurAnim->SetEndCallBack([this]()
			{
				SetState(eBossState::Idle);
				m_AttackArea[1]->Deactivate();
				m_IsAttack = false;
			});
	}

	Vec3 tauPos = m_OriginPosObject->Transform()->GetRelativePos();

	if (m_Player)
	{
		CPlayerScript* pPlayerScript = m_Player->GetScript<CPlayerScript>();

		Vec3 playerPos = pPlayerScript->GetOriginPos()->Transform()->GetRelativePos();
		Vec3 direction = playerPos - tauPos;
		direction.Normalize();
		m_RushTargetPos = tauPos + direction * m_RushDistance;
	}
	else
	{
		SetState(eBossState::Idle);
		return;
	}

	Vec3 direction = m_RushTargetPos - tauPos;

	if (direction.Length() > m_AttackRange)
	{
		direction.Normalize();
		tauPos += direction * m_Speed * DT * 6.f;
		m_OriginPosObject->Transform()->SetRelativePos(tauPos);
	}
	else
	{
		SetState(eBossState::Idle);
	}
}

void CBossScript::Buff()
{
	CAnim2D* pCurAnim = Animator2D()->GetCurAnim();

	if (pCurAnim == nullptr)
		return;

	if (pCurAnim->IsFinish())
		SetState(eBossState::Idle);

	float armorValue = 2.f;

	// Set Defense
}

void CBossScript::HitEvent()
{
	int random = GetRandomInt(1, 3);
	wstring soundPath = L"Sound\\tau_dmg_0" + to_wstring(random) + L".ogg";
	PlaySoundEffect(soundPath);

	random = GetRandomInt(3, 4);
	soundPath = L"Sound\\cross_hit_0" + to_wstring(random) + L".ogg";
	PlaySoundEffect(soundPath);
}

void CBossScript::Death()
{
	CAnim2D* pCurAnim = Animator2D()->GetCurAnim();

	pCurAnim->SetStartCallBack([this]()
		{
			Ptr<CSound> pNewBgm = CAssetManager::GetInst()->FindAsset<CSound>(L"Sound\\result.ogg");
			CLevelManager::GetInst()->GameEndEvent(pNewBgm, 1);

			CUIManager::GetInst()->FindUIElementByType<UIResult>()->SetGetEnd(true);

			PlaySoundEffect(L"Sound\\tau_die.ogg");
		});

	if (pCurAnim->IsFinish())
	{
		//tTask task = {};
		//task.Type = TASK_TYPE::DESTROY_OBJECT;
		//task.dwParam_0 = (DWORD_PTR)GetOwner()->GetParent();
		//CTaskManager::GetInst()->AddTask(task);
	}
}

void CBossScript::UpdataDirection()
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

bool CBossScript::IsPlayerTarget()
{
	if (!m_Player)
		return false;

	CPlayerScript* pPlayerScript = m_Player->GetScript<CPlayerScript>();

	Vec3 playerPos = pPlayerScript->GetOriginPos()->Transform()->GetRelativePos();
	Vec3 goblinPos = m_OriginPosObject->Transform()->GetRelativePos();
	float distance = Vec3::Distance(playerPos, goblinPos);
	return distance <= m_AttackRange;
}

void CBossScript::AnimationInit()
{
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Boss_Idle.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Boss_Move.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Boss_Attack_0.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Boss_Attack_1.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Boss_Skill.anim");
	GetOwner()->Animator2D()->LoadAnimation(L"Animation\\Boss_Death.anim");
}