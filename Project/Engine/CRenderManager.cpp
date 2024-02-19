#include "pch.h"
#include "CRenderManager.h"

#include "CDevice.h"
#include "CCamera.h"

CRenderManager::CRenderManager()
{

}

CRenderManager::~CRenderManager()
{

}

void CRenderManager::Init()
{
}

void CRenderManager::Tick()
{
}

void CRenderManager::Render()
{
	// Target Clear
	float clearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearTarget(clearColor);

	// Camera Draw in Render Target
	for (size_t i = 0; i < m_vecCam.size(); i++)
	{
		m_vecCam[i]->Render();
	}
}

void CRenderManager::RegisterCamera(CCamera* newCamera, int priority)
{
	// �̹� ��ϵǾ� �ִ� Camera ���� Ȯ��
	for (size_t i = 0; i < m_vecCam.size(); i++)
	{
		if (m_vecCam[i] == newCamera)
		{
			// �̹� ��ϵǾ� �ִµ� ���� �켱������ ������ return
			if (priority == i)
				return;
			// �̹� ��ϵǾ� �ִµ� �켱���� ������ ��û������ ���� Index �ʱ�ȭ
			else
				m_vecCam[i] = nullptr;
		}
	}

	// ī�޶� ��� | Vector Size �� �ʿ信 ���� ��� �ø���
	if (m_vecCam.size() <= priority)
	{
		m_vecCam.resize(priority + 1);
	}

	m_vecCam[priority] = newCamera;
}
