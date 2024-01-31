#include "pch.h"
#include "CEngine.h"

#include "CDevice.h"
#include "CTimeManager.h"
#include "CPathManager.h"
#include "CKeyManager.h"

#include "Temp.h"

CEngine::CEngine()
	: m_hMainHwnd(nullptr)
	, m_Resolution{}
{
}

CEngine::~CEngine()
{
	TempRelease();
}

int CEngine::Init(HWND hwnd, POINT resolution)
{
	m_hMainHwnd = hwnd;
	m_Resolution = resolution;

	// 윈도우 크기 설정
	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DircetX11
	if (FAILED(CDevice::GetInst()->Init(m_hMainHwnd, m_Resolution)))
	{
		MessageBox(m_hMainHwnd, L"Device 초기화 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// Manager Init
	CTimeManager::GetInst()->Init();
	CKeyManager::GetInst()->Init();
	CPathManager::GetInst()->Init();

	if (FAILED(TempInit()))
	{
		MessageBox(m_hMainHwnd, L"Device 초기화 실패", L"Temp Init 초기화 실패", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void CEngine::Progress()
{
	// ====================
	// Manager Tick
	// ====================
	CTimeManager::GetInst()->Tick();
	CKeyManager::GetInst()->Tick();

	// Object Tick
	TempTick();


	// ====================
	// Rendering
	// ====================
	// Target Clear
	float clearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearTarget(clearColor);

	// Object Render
	TempRender();

	// Present
	CDevice::GetInst()->Present();
}
