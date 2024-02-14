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
	Vec3 vCamWorldPos = GetOwner()->Transform()->GetRelativePos();

	// 오브젝트들은 카메라 이동량의 반대만큼 계산을 해주어야함
	m_matView = XMMatrixTranslation(-vCamWorldPos.x, -vCamWorldPos.y, -vCamWorldPos.z);

	// Proj 행렬 계산 (투영) = 원근투영 | 직교투영
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