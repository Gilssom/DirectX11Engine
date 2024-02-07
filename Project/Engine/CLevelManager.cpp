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

}

void CLevelManager::Init()
{
	m_CurLevel = new CLevel;

	// ������Ʈ�� ������Ʈ ��� ��, ������Ʈ�� �Լ��� ���� �� ����
	CGameObject* pObject1 = new CGameObject;
	pObject1->AddComponent(new CTransform);
	pObject1->AddComponent(new CMeshRender);
	pObject1->AddComponent(new CPlayerScript);

	pObject1->Transform()->SetRelativeScale(0.2f, 0.2f, 0.2f);

	pObject1->MeshRender()->SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObject1->MeshRender()->SetShader(CAssetManager::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	m_CurLevel->AddObject(0, pObject1);
}

void CLevelManager::Tick()
{
	if (m_CurLevel != nullptr)
		m_CurLevel->Tick();
}

void CLevelManager::Render()
{
	if (m_CurLevel != nullptr)
		m_CurLevel->Render();
}
