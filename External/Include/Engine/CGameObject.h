#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CTransform;
class CMeshRender;
class CCamera;

class CScript;

#define GET_COMPONENT(Type, TYPE) C##Type* Type() { return (C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::TYPE]; }

class CGameObject : public CEntity
{
private:
	CComponent*			m_arrCom[(UINT)COMPONENT_TYPE::END];
	CRenderComponent*	m_RenderCom;

	vector<CScript*>	m_vecScripts;


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

public:
	CGameObject();
	~CGameObject();

};