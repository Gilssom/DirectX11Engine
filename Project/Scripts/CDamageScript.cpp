#include "pch.h"
#include "CDamageScript.h"

#include <Engine\CTaskManager.h>

CDamageScript::CDamageScript()
	: CScript(SCRIPT_TYPE::DAMAGESCRIPT)
	, m_LiftTime(2.f)
	, m_CurTime(0.f)
	, m_Alpha(0.99f)
{

}

CDamageScript::~CDamageScript()
{

}

void CDamageScript::Begin()
{

}

void CDamageScript::Tick()
{
	if (m_CurTime >= m_LiftTime)
	{
		tTask task = {};
		task.Type = TASK_TYPE::DESTROY_OBJECT;
		task.dwParam_0 = (DWORD_PTR)GetOwner();
		CTaskManager::GetInst()->AddTask(task);
		return;
	}

	m_CurTime += DT;
	m_Alpha -= DT * 0.33f;

	Vec3 curPos = GetOwner()->Transform()->GetRelativePos();
	GetOwner()->Transform()->SetRelativePos(Vec3(curPos.x, curPos.y + (DT * 75.f), curPos.z + (DT * 0.1f)));
	GetOwner()->MeshRender()->GetDynamicMaterial()->SetScalarParam(FLOAT_1, m_Alpha);
}