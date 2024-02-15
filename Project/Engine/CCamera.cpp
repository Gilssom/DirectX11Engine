#include "pch.h"
#include "CCamera.h"

#include "CLevelManager.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"

#include "CRenderManager.h"

#include "CTransform.h"

#include "CDevice.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_CamPriority(-1)
	, m_Far(1000.f)
{

}

CCamera::~CCamera()
{

}

void CCamera::FinalTick()
{
	// View 행렬 계산
	Vec3 vCamWorldPos = Transform()->GetRelativePos();

	// 1. 이동 행렬 만들기
	// 오브젝트들은 카메라 이동량의 반대만큼 계산을 해주어야함
	Matrix matViewTrans = XMMatrixTranslation(-vCamWorldPos.x, -vCamWorldPos.y, -vCamWorldPos.z);

	// 2. 회전 행렬 만들기 ( 3 x 3 행렬 )
	// 만약 카메라가 월드 상의 Z 축과 동일하지 않다면?
	// ** 그만큼 카메라가 Z 축을 바라볼 수 있는 회전량을 회전 행렬로 구해야 한다. **
	
	// 자동적으로 이동 행렬에서 모든 물체를 카메라 기점으로 만들어 놓았기 때문에
	// 모든 물체는 카메라의 회전에 따라 다 같이 Z 축 기준으로 움직이게 된다.

	// 1 0 0  | X
	// 0 1 0  | Y
	// 0 0 1  | Z

	// 이동 행렬 x 회전 행렬 = 단위 행렬 (사칙연산의 항등원과 동일함)
	// 역원 : 자신의 항등원이 나오게 해주는 수

	// 그럼 카메라의 이동 행렬에 "무언가" 를 곱했을 때 단위행렬이 나온다?
	// 그럼 곱한 행렬은 카메라 이동 행렬의 "역행렬(역원)" 이 된다.

	// 각 행렬이 서로 90도를 이루고 있으면 직교 행렬이라 부른다.

	// 직교 행렬의 역행렬은 전치 행렬이다.
	// 전치 행렬이 곧 회전 행렬이 된다.

	// 카메라의 우, 상, 전 벡터
	Vec3 vR = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);
	Vec3 vU = Transform()->GetRelativeDir(DIR_TYPE::UP);
	Vec3 vF = Transform()->GetRelativeDir(DIR_TYPE::FRONT);

	Matrix matViewtRot = XMMatrixIdentity();

	matViewtRot._11 = vR.x;  matViewtRot._12 = vU.x;	matViewtRot._13 = vF.x;
	matViewtRot._21 = vR.y;  matViewtRot._22 = vU.y;	matViewtRot._23 = vF.y;
	matViewtRot._31 = vR.z;  matViewtRot._32 = vU.z;	matViewtRot._33 = vF.z;
	
	// 행렬은 교환 법칙 성립이 안된다.
	m_matView = matViewTrans * matViewtRot;


	// 3. Proj 행렬 계산 (투영) = 원근투영 | 직교투영
	Vec2 vRenderResol = CDevice::GetInst()->GetRenderResolution();
	float AspectRatio = vRenderResol.x / vRenderResol.y;
	m_matProj = XMMatrixPerspectiveFovLH((XM_PI / 3.f), AspectRatio, 1.f, m_Far);
}

void CCamera::Render()
{
	g_Trans.matView = m_matView;
	g_Trans.matProj = m_matProj;

	// 일단은 모든 Layer 를 다 그릴 수 있게 설정한다.
	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);
		pLayer->Render();
	}
}

void CCamera::SetCameraPriority(int priority)
{
	// 카메라 우선순위 설정
	m_CamPriority = priority;

	if (0 <= m_CamPriority)
	{
		CRenderManager::GetInst()->RegisterCamera(this, m_CamPriority);
	}
}