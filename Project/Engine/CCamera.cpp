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
	, m_ProjType(PROJ_TYPE::PERSPECTIVE)
	, m_CamPriority(-1)
	, m_FOV((XM_PI) / 3.f)
	, m_Far(10000.f)
	, m_Width(0.f)
	, m_Scale(1.f)
{
	Vec2 vRenderResol = CDevice::GetInst()->GetRenderResolution();
	m_Width = vRenderResol.x;
	m_AspectRatio = vRenderResol.x / vRenderResol.y;
}

CCamera::~CCamera()
{

}

void CCamera::FinalTick()
{
	// View ��� ���
	Vec3 vCamWorldPos = Transform()->GetRelativePos();

	// 1. �̵� ��� �����
	// ������Ʈ���� ī�޶� �̵����� �ݴ븸ŭ ����� ���־����
	Matrix matViewTrans = XMMatrixTranslation(-vCamWorldPos.x, -vCamWorldPos.y, -vCamWorldPos.z);

	// 2. ȸ�� ��� ����� ( 3 x 3 ��� )
	// ���� ī�޶� ���� ���� Z ��� �������� �ʴٸ�?
	// ** �׸�ŭ ī�޶� Z ���� �ٶ� �� �ִ� ȸ������ ȸ�� ��ķ� ���ؾ� �Ѵ�. **
	
	// �ڵ������� �̵� ��Ŀ��� ��� ��ü�� ī�޶� �������� ����� ���ұ� ������
	// ��� ��ü�� ī�޶��� ȸ���� ���� �� ���� Z �� �������� �����̰� �ȴ�.

	// 1 0 0  | X
	// 0 1 0  | Y
	// 0 0 1  | Z

	// �̵� ��� x ȸ�� ��� = ���� ��� (��Ģ������ �׵���� ������)
	// ���� : �ڽ��� �׵���� ������ ���ִ� ��

	// �׷� ī�޶��� �̵� ��Ŀ� "����" �� ������ �� ��������� ���´�?
	// �׷� ���� ����� ī�޶� �̵� ����� "�����(����)" �� �ȴ�.

	// �� ����� ���� 90���� �̷�� ������ ���� ����̶� �θ���.

	// ���� ����� ������� ��ġ ����̴�.
	// ��ġ ����� �� ȸ�� ����� �ȴ�.

	// ī�޶��� ��, ��, �� ����
	Vec3 vR = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);
	Vec3 vU = Transform()->GetRelativeDir(DIR_TYPE::UP);
	Vec3 vF = Transform()->GetRelativeDir(DIR_TYPE::FRONT);

	Matrix matViewtRot = XMMatrixIdentity();

	matViewtRot._11 = vR.x;  matViewtRot._12 = vU.x;	matViewtRot._13 = vF.x;
	matViewtRot._21 = vR.y;  matViewtRot._22 = vU.y;	matViewtRot._23 = vF.y;
	matViewtRot._31 = vR.z;  matViewtRot._32 = vU.z;	matViewtRot._33 = vF.z;
	
	// ����� ��ȯ ��Ģ ������ �ȵȴ�.
	m_matView = matViewTrans * matViewtRot;


	// 3. Proj ��� ��� (����) = �������� | ��������
	if (m_ProjType == PROJ_TYPE::PERSPECTIVE)
	{
		m_matProj = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, 1.f, m_Far);
	}
	else
	{
		// ���� ������ ī�޶��� �þ߰��� �ʿ����
		// ���������� ������ �� ���̱� ������ ������ ���� ���� ���̸� �ʿ���
		m_matProj = XMMatrixOrthographicLH(m_Width * m_Scale, (m_Width / m_AspectRatio) * m_Scale, 1.f, m_Far);
	}
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