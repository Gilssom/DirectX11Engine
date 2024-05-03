#include "pch.h"
#include "CEngine.h"

#include "CDevice.h"
#include "CTimeManager.h"
#include "CPathManager.h"
#include "CKeyManager.h"
#include "CAssetManager.h"
#include "CLevelManager.h"
#include "CRenderManager.h"
#include "CDbgRenderManager.h"
#include "CCollisionManager.h"
#include "CTaskManager.h"

CEngine::CEngine()
	: m_hMainHwnd(nullptr)
	, m_Resolution{}
{
}

CEngine::~CEngine()
{

}

int CEngine::Init(HWND hwnd, Vec2 resolution)
{
	m_hMainHwnd = hwnd;
	m_Resolution = resolution;

	// ������ ũ�� ����
	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DircetX11
	if (FAILED(CDevice::GetInst()->Init(m_hMainHwnd, m_Resolution)))
	{
		MessageBox(m_hMainHwnd, L"Device �ʱ�ȭ ����", L"���� �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// Manager Init
	CPathManager::GetInst()->Init();
	CTimeManager::GetInst()->Init();
	CKeyManager::GetInst()->Init();
	CAssetManager::GetInst()->Init();
	CRenderManager::GetInst()->Init();
	CLevelManager::GetInst()->Init();

	return S_OK;
}

void CEngine::Progress()
{
	// ====================
	// Manager Tick
	// ====================
	CTimeManager::GetInst()->Tick();
	CKeyManager::GetInst()->Tick();
	CAssetManager::GetInst()->Tick();


	// Object Tick
	CLevelManager::GetInst()->Tick();
	CCollisionManager::GetInst()->Tick();


	// ====================
	// Rendering
	// ====================
	CRenderManager::GetInst()->Render();
	CDbgRenderManager::GetInst()->Render();


	// Task Execute
	CTaskManager::GetInst()->Tick();
}
