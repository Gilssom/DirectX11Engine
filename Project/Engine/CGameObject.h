#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CScript;

#define GET_COMPONENT(Type, TYPE) class C##Type* Type() { return (C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::TYPE]; }

class CGameObject : public CEntity
{
private:
	CComponent*				m_arrCom[(UINT)COMPONENT_TYPE::END];
	CRenderComponent*		m_RenderCom;
	vector<CScript*>		m_vecScripts;


	// ������Ʈ�� ���� ���� ���� �ʿ�
	CGameObject*			m_Parent;		// �θ� ������Ʈ ������
	vector<CGameObject*>	m_vecChild;		// �ڽ� ������Ʈ�� ������ vector

	int						m_LayerIdx;		// GameObject �� �ҼӵǾ� �ִ� Layer


public:
	void Begin();		// ������ ���� �� ��, ������ �շ��� ��
	void Tick();		// �� �����Ӹ��� ȣ��Ǵ� �Լ� Delta Time
	void FinalTick();	// Tick ���� �߻��� �ϵ��� ������ �۾� or ���ҽ� ���ε� �� ���� ������ ����
	void Render();		// ȭ�鿡 �׷����� �Լ�


public:
	void AddComponent(CComponent* component);
	CComponent* GetComonent(COMPONENT_TYPE type) { return m_arrCom[(UINT)type]; }

	GET_COMPONENT(Transform, TRANSFORM);
	GET_COMPONENT(MeshRender, MESHRENDER);
	GET_COMPONENT(Camera, CAMERA);
	GET_COMPONENT(Collider2D, COLLIDER2D);

	void AddChild(CGameObject* object);
	const vector<CGameObject*>& GetChildren() { return m_vecChild; }
	CGameObject* GetParent() { return m_Parent; }

private:
	void SetLayerIdx(int idx) { m_LayerIdx = idx; }

public:
	CGameObject();
	~CGameObject();

	// Layer ������ Layer Index �� �ǵ��� �� �ְ�
	friend class CLayer;
};