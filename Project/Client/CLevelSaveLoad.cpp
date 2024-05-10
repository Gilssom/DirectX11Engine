#include "pch.h"
#include "CLevelSaveLoad.h"

#include <Engine\\CLevel.h>
#include <Engine\\CLevelManager.h>
#include <Engine\\CLayer.h>
#include <Engine\\CGameObject.h>
#include <Engine\\components.h>
#include <Engine\\CCollisionManager.h>

void CLevelSaveLoad::SaveLevel(CLevel* level, const wstring& filePath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, filePath.c_str(), L"wb");

	if (pFile == nullptr)
	{
		MessageBox(nullptr, L"���� ���� ����", L"���� ���� ����", MB_OK);
		return;
	}

	// Level �� �̸� ����
	SaveWString(level->GetName(), pFile);

	// Level �� ������ ��� Layer ������ ����
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		// Layer �̸� ����
		CLayer* pLayer = level->GetLayer(i);
		SaveWString(pLayer->GetName(), pFile);

		// Layer �� ������ ������Ʈ���� ����(�θ� ������Ʈ ����)
		const vector<CGameObject*>& vecParents = pLayer->GetParentObjects();

		// ParentObject ���� ����
		size_t objectCount = vecParents.size();
		fwrite(&objectCount, sizeof(size_t), 1, pFile);

		// �ش� Layer �� �Ҽӵ� ������ GameObject �������� ����
		for (size_t i = 0; i < objectCount; i++)
		{
			SaveGameObject(vecParents[i], pFile);
		}
	}

	fclose(pFile);
}

void CLevelSaveLoad::SaveGameObject(CGameObject* object, FILE* file)
{
	// Name
	SaveWString(object->GetName(), file);

	// Component
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		CComponent* pComponent = object->GetComponent((COMPONENT_TYPE)i);

		if (pComponent == nullptr)
			continue;

		// ���� ���� Component Type �� �ϴ� ����
		COMPONENT_TYPE type = pComponent->GetComponentType();
		fwrite(&type, sizeof(UINT), 1, file);

		// Component Type �� ���� ������ �������� ����
		pComponent->SaveToLevelFile(file);
	}

	COMPONENT_TYPE end = COMPONENT_TYPE::END;
	fwrite(&end, sizeof(UINT), 1, file);

	// Script

	// Child Object
}

CLevel* CLevelSaveLoad::LoadLevel(const wstring& filePath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, filePath.c_str(), L"rb");

	if (pFile == nullptr)
	{
		MessageBox(nullptr, L"���� �ҷ����� ����", L"���� �ҷ����� ����", MB_OK);
		return nullptr;
	}

	CLevel* pLevel = new CLevel;

	// Level �� �̸� �ε�
	wstring strLevelName;
	LoadWString(strLevelName, pFile);
	pLevel->SetName(strLevelName);

	// Level �� ������ ��� Layer ������ �ε�
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		// Layer �̸� �ε�
		CLayer* pLayer = pLevel->GetLayer(i);
		wstring strLayerName();
		LoadWString(strLevelName, pFile);
		pLayer->SetName(strLevelName);

		// ParentObject ���� �ε�
		size_t objectCount = 0;
		fread(&objectCount, sizeof(size_t), 1, pFile);

		// ����� ������Ʈ ������ŭ ������Ʈ���� �ε� �� Layer �� ����(�θ� ������Ʈ ����)
		for (size_t i = 0; i < objectCount; i++)
		{
			CGameObject* pParentObject = LoadGameObject(pFile);
			pLayer->AddObject(pParentObject);
		}
	}


	fclose(pFile);

	return pLevel;
}

CGameObject* CLevelSaveLoad::LoadGameObject(FILE* file)
{
	CGameObject* pObject = new CGameObject;

	// Name
	wstring Name;
	LoadWString(Name, file);
	pObject->SetName(Name);

	// Component
	COMPONENT_TYPE type = COMPONENT_TYPE::END;
	CComponent* pComponent = nullptr;

	while (true)
	{
		// ����� Component Type �� ���� Ȯ��
		fread(&type, sizeof(UINT), 1, file);

		if (type == COMPONENT_TYPE::END)
			break;

		switch (type)
		{
		case COMPONENT_TYPE::TRANSFORM:
			pComponent = new CTransform;
			break;
		case COMPONENT_TYPE::CAMERA:
			pComponent = new CCamera;
			break;
		case COMPONENT_TYPE::COLLIDER2D:
			pComponent = new CCollider2D;
			break;
		case COMPONENT_TYPE::COLLIDER3D:
			//pComponent = new CCollider3D;
			break;
		case COMPONENT_TYPE::ANIMATOR2D:
			pComponent = new CAnimator2D;
			break;
		case COMPONENT_TYPE::ANIMATOR3D:
			//pComponent = new CAnimator3D;
			break;
		case COMPONENT_TYPE::LIGHT2D:
			pComponent = new CLight2D;
			break;
		case COMPONENT_TYPE::LIGHT3D:
			//pComponent = new CLight3D;
			break;
		case COMPONENT_TYPE::MESHRENDER:
			pComponent = new CMeshRender;
			break;
		case COMPONENT_TYPE::DECAL:
			//pComponent = new CDecal;
			break;
		case COMPONENT_TYPE::PARTICLESYSTEM:
			pComponent = new CParticleSystem;
			break;
		case COMPONENT_TYPE::TILEMAP:
			pComponent = new CTileMap;
			break;
		case COMPONENT_TYPE::LANDSCAPE:
			//pComponent = new CLandScape;
			break;
		}

		pObject->AddComponent(pComponent);
		pComponent->LoadFromLevelFile(file);
	}

	// Script

	// Child Object

	return pObject;
}
