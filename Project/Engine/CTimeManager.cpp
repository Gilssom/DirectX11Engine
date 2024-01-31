#include "pch.h"
#include "CTimeManager.h"

#include "CEngine.h"

CTimeManager::CTimeManager()
	: m_llFrequency{}
	, m_llCurCount{}
	, m_llPrevCount{}
	, m_DT(0.f)
	, m_Time(0.f)
	, m_AccTime(0.f)
	, m_FrameCount(0)
{

}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::Init()
{
	// �ʴ� ī��Ʈ ��
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void CTimeManager::Tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	// �����Ӱ� �������� ���� �ð�
	m_DT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	m_llPrevCount = m_llCurCount;

	// ���� �ð�
	m_Time += m_DT;

	// m_AccTime�� 1�ʸ� ���� ����
	m_AccTime += m_DT;
	++m_FrameCount;

	if (1.f < m_AccTime)
	{
		HWND hMainWnd = CEngine::GetInst()->GetMainWnd();	
		wchar_t szText[255] = {};
		swprintf_s(szText, L"FPS : %d,  DeltaTime : %f", m_FrameCount, m_DT);
		SetWindowText(hMainWnd, szText);

		m_AccTime -= 1.f;
		m_FrameCount = 0;
	}
}