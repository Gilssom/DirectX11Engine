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
	// 초당 카운트 수
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void CTimeManager::Tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	// 프레임과 프레임의 간격 시간
	m_DT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	m_llPrevCount = m_llCurCount;

	// 누적 시간
	m_Time += m_DT;

	// m_AccTime는 1초만 세기 위함
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