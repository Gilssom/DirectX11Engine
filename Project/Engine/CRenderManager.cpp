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
	// �������� �ʿ��� ������ ���ε�
	DataBinding();

	// Target Clear
	float clearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearTarget(clearColor);

	// Camera Draw in Render Target
	for (size_t i = 0; i < m_vecCam.size(); i++)
	{
		m_vecCam[i]->Render();
	}

	// ������ Ŭ����
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


	// Light ����ȭ ���۷� Binding
	// ũ�Ⱑ �� Ŀ���� ���Ӱ� Create ( ������ ������ ���� ������ )
	// ���� �������� ����ȭ ���� ���ũ�Ⱑ �� ������ Ȯ��.
	if (m_Light2DBuffer->GetElementCount() < m_vecLight2D.size())
	{
		m_Light2DBuffer->Create(sizeof(tLightInfo), (UINT)m_vecLight2D.size());
	}

	// m_vecLight2D �� ���� ������ ������ ����ȭ ���۷� ����
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
