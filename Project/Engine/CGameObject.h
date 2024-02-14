#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CTransform;
class CMeshRender;
class CCamera;

class CScript;

class CGameObject : public CEntity
{
private:
	CComponent*			m_arrCom[(UINT)COMPONENT_TYPE::END];
	CRenderComponent*	m_RenderCom;

	vector<CScript*>	m_vecScripts;


public:
	void Begin();		// ������ ���� �� ��, ������ �շ��� ��
	void Tick();		// �� �����Ӹ��� ȣ��Ǵ� �Լ� Delta Time
	void FinalTick();	// Tick ���� �߻��� �ϵ��� ������ �۾� or ���ҽ� ���ε� �� ���� ������ ����
	void Render();		// ȭ�鿡 �׷����� �Լ�


public:
	void AddComponent(CComponent* component);
	CComponent* GetComonent(COMPONENT_TYPE type) { return m_arrCom[(UINT)type]; }

	CTransform* Transform() { return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]; }
	CMeshRender* MeshRender() { return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]; }
	CCamera* Camera() { return (CCamera*)m_arrCom[(UINT)COMPONENT_TYPE::CAMERA]; }


public:
	CGameObject();
	~CGameObject();

};