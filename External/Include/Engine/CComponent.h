#pragma once
#include "CEntity.h"

#include "CGameObject.h"

#define GET_OTHER_COMPONENT(Type) C##Type* Type() { return m_Owner->Type(); }

// �߻� Ŭ���� ����
class CComponent : public CEntity
{
private:
	CGameObject*		 m_Owner; // �ش� ������Ʈ�� �����ϰ� �ִ� ������Ʈ �ּ�
	const COMPONENT_TYPE m_Type;  // ������ ���� ������Ʈ������ ���� ����


public:
	virtual	void Begin() {};
	virtual	void Tick() {};
	virtual	void FinalTick() = 0; // �ݵ�� ����


public:
	COMPONENT_TYPE GetComponentType() { return m_Type; }
	CGameObject* GetOwner() { return m_Owner; }

	GET_OTHER_COMPONENT(Transform);
	GET_OTHER_COMPONENT(MeshRender);
	GET_OTHER_COMPONENT(Camera);
	GET_OTHER_COMPONENT(Collider2D);

public:
	CComponent(COMPONENT_TYPE type);
	~CComponent();

	friend class CGameObject;
};

