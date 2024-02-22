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


	// 오브젝트의 계층 구조 관계 필요
	CGameObject*			m_Parent;		// 부모 오브젝트 포인터
	vector<CGameObject*>	m_vecChild;		// 자식 오브젝트들 포인터 vector

	int						m_LayerIdx;		// GameObject 가 소속되어 있는 Layer


public:
	void Begin();		// 레벨이 시작 될 때, 레벨에 합류할 때
	void Tick();		// 매 프레임마다 호출되는 함수 Delta Time
	void FinalTick();	// Tick 에서 발생한 일들의 마무리 작업 or 리소스 바인딩 및 관련 데이터 연산
	void Render();		// 화면에 그려지는 함수


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

	// Layer 에서만 Layer Index 를 건들일 수 있게
	friend class CLayer;
};