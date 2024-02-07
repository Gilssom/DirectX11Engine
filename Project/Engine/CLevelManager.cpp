#include "pch.h"
#include "CLevelManager.h"

#include "CLevel.h"
#include "CGameObject.h"

#include "CTransform.h"
#include "CMeshRender.h"
#include "CPlayerScript.h"

#include "CAssetManager.h"

CLevelManager::CLevelManager()
	: m_CurLevel(nullptr)
{

}

CLevelManager::~CLevelManager()
{
	if (m_CurLevel != nullptr)
	{
		delete m_CurLevel;
	}
}

void CLevelManager::Init()
{
	m_CurLevel = new CLevel;

	// 오브젝트에 컴포넌트 등록 후, 컴포넌트의 함수에 접근 후 세팅
	CGameObject* pObject = new CGameObject;
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CPlayerScript);

	pObject->Transform()->SetRelativeScale(0.2f, 0.2f, 0.2f);

	pObject->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetShader(CAssetManager::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	m_CurLevel->AddObject(0, pObject);
}

void CLevelManager::Tick()
{
	if (m_CurLevel != nullptr)
	{
		m_CurLevel->Tick(); 
		m_CurLevel->FinalTick();
	}
}

void CLevelManager::Render()
{
	if (m_CurLevel != nullptr)
		m_CurLevel->Render();
}
