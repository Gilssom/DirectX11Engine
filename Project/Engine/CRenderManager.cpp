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
	// 이미 등록되어 있는 Camera 인지 확인
	for (size_t i = 0; i < m_vecCam.size(); i++)
	{
		if (m_vecCam[i] == newCamera)
		{
			// 이미 등록되어 있는데 같은 우선순위가 들어오면 return
			if (priority == i)
				return;
			// 이미 등록되어 있는데 우선순위 변경이 요청들어오면 이전 Index 초기화
			else
				m_vecCam[i] = nullptr;
		}
	}

	// 카메라 등록 | Vector Size 는 필요에 따라 계속 늘리기
	if (m_vecCam.size() <= priority)
	{
		m_vecCam.resize(priority + 1);
	}

	m_vecCam[priority] = newCamera;
}
