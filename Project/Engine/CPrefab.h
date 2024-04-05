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


private:
	int Load(const wstring& FilePath) override;
	int Save(const wstring& FilePath) override;


public:
	CPrefab();
	~CPrefab();

};

