#pragma once
#include "CComponent.h"

#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CAssetManager.h"

#include "CTransform.h"

// �߻� Ŭ���� ����
class CScript : public CComponent
{
private:


public:
	virtual void Tick() = 0; // Tick �� �� �����ϵ��� ����
	virtual void FinalTick() final {} // �� �����δ� FinalTick �� override �� �� ����


public:
	CScript();
	~CScript();
};

