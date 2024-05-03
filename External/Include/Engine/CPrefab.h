#pragma once
#include "CAsset.h"

class CGameObject;

class CPrefab : public CAsset
{
	// Level Manager 에서 하드코딩으로 Object 를 생성 및 설정을 할 것이 아니라,
	// Editor 를 통해 해당 작업을 할 예정이다.

	// Unity 의 Prefab 구도와 매우 유사하다.

	// 얕은 복사로는 해결이 불가능 (복사 대상의 정보 전체를 복제를 해야함. 복사X )

private:
	CGameObject* m_ProtoObject;

public:
	CGameObject* Instantiate();

	CLONE(CPrefab);

private:
	int Load(const wstring& FilePath) override { return S_OK; }
	int Save(const wstring& FilePath) override { return S_OK; }

public:
	CPrefab(bool bEngine = false);
	CPrefab(CGameObject* proto);
	CPrefab(const CPrefab& other);
	~CPrefab();

};

