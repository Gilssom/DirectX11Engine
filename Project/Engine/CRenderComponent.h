#pragma once
#include "CComponent.h"

#include "assets.h"

class CRenderComponent : public CComponent
{
private:
	Ptr<CMesh>			m_Mesh;		// 모양

	// 앞으로 Shader, Texture 는 Material 이 관리함 ( Unity Material 과 비슷한 개념 )
	// 사용하고자 하는 Shader 의 종류에 따라 요구하는 Texture 의 갯수가 달라질 수 있음
	Ptr<CMaterial>		m_Material;	// 재질

public:
	virtual void Render() = 0;


public:
	void SetMesh(Ptr<CMesh> mesh) { m_Mesh = mesh; }
	void SetMaterial(Ptr<CMaterial> material) { m_Material = material; }

	Ptr<CMesh> GetMesh() { return m_Mesh; }
	Ptr<CMaterial> GetMaterial() { return m_Material; }

public:
	CRenderComponent(COMPONENT_TYPE type);
	~CRenderComponent();
};

