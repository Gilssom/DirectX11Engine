#pragma once
#include "CAsset.h"

class CGameObject;

class CPrefab : public CAsset
{
	// Level Manager ���� �ϵ��ڵ����� Object �� ���� �� ������ �� ���� �ƴ϶�,
	// Editor �� ���� �ش� �۾��� �� �����̴�.

	// Unity �� Prefab ������ �ſ� �����ϴ�.

	// ���� ����δ� �ذ��� �Ұ��� (���� ����� ���� ��ü�� ������ �ؾ���. ����X )

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

