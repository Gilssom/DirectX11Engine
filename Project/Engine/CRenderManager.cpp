#include "pch.h"
#include "CRenderManager.h"

#include "CDevice.h"
#include "CConstBuffer.h"
#include "CStructuredBuffer.h"

#include "CCamera.h"
#include "CLight2D.h"

CRenderManager::CRenderManager()
	: m_Light2DBuffer(nullptr)
{
	m_Light2DBuffer = new CStructuredBuffer;
}

CRenderManager::~CRenderManager()
{
	delete m_Light2DBuffer;
}

void CRenderManager::Init()
{
}

void CRenderManager::Tick()
{
}

void CRenderManager::Render()
{
	// 렌더링에 필요한 데이터 바인딩
	DataBinding();

	// Target Clear
	float clearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearTarget(clearColor);

	// Camera Draw in Render Target
	for (size_t i = 0; i < m_vecCam.size(); i++)
	{
		m_vecCam[i]->Render();
	}

	// 데이터 클리어
	DataClear();
}

void CRenderManager::DataBinding()
{
	// Global Data Binding
	g_GlobalData.Light2DCount = (int)m_vecLight2D.size();
	//g_GlobalData.Light3DCount = (int)m_vecLight3D.size();

	static CConstBuffer* GlobalBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::GLOBAL);
	GlobalBuffer->SetData(&g_GlobalData);
	GlobalBuffer->Binding();


	// Light 구조화 버퍼로 Binding
	// 크기가 더 커지면 새롭게 Create ( 공간이 부족한 일이 없어짐 )
	// 광원 개수보다 구조화 버퍼 요소크기가 더 작으면 확장.
	if (m_Light2DBuffer->GetElementCount() < m_vecLight2D.size())
	{
		m_Light2DBuffer->Create(sizeof(tLightInfo), (UINT)m_vecLight2D.size());
	}

	// m_vecLight2D 에 모인 광원의 정보를 구조화 버퍼로 전달
	static vector<tLightInfo> vecLightInfo;
	vecLightInfo.clear();

	for (size_t i = 0; i < m_vecLight2D.size(); i++)
	{
		vecLightInfo.push_back(m_vecLight2D[i]->GetLightInfo());
	}

	m_Light2DBuffer->SetData(vecLightInfo.data(), m_vecLight2D.size());
	m_Light2DBuffer->Binding(15);
}

void CRenderManager::DataClear()
{
	m_vecLight2D.clear();
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
