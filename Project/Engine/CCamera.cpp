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
	// View ��� ���
	Vec3 vCamWorldPos = GetOwner()->Transform()->GetRelativePos();

	// ������Ʈ���� ī�޶� �̵����� �ݴ븸ŭ ����� ���־����
	m_matView = XMMatrixTranslation(-vCamWorldPos.x, -vCamWorldPos.y, -vCamWorldPos.z);

	// Proj ��� ��� (����) = �������� | ��������
	Vec2 vRenderResol = CDevice::GetInst()->GetRenderResolution();
	float AspectRatio = vRenderResol.x / vRenderResol.y;
	m_matProj = XMMatrixPerspectiveFovLH((XM_PI / 3.f), AspectRatio, 1.f, m_Far);
}

void CCamera::Render()
{
	g_Trans.matView = m_matView;
	g_Trans.matProj = m_matProj;

	// �ϴ��� ��� Layer �� �� �׸� �� �ְ� �����Ѵ�.
	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);
		pLayer->Render();
	}
}

void CCamera::SetCameraPriority(int priority)
{
	// ī�޶� �켱���� ����
	m_CamPriority = priority;

	if (0 <= m_CamPriority)
	{
		CRenderManager::GetInst()->RegisterCamera(this, m_CamPriority);
	}
}