#pragma once
#include "CComponent.h"

#include "assets.h"

class CRenderComponent : public CComponent
{
private:
	Ptr<CMesh>			m_Mesh;		// ���

	// ������ Shader, Texture �� Material �� ������ ( Unity Material �� ����� ���� )
	// ����ϰ��� �ϴ� Shader �� ������ ���� �䱸�ϴ� Texture �� ������ �޶��� �� ����
	Ptr<CMaterial>		m_Material;	// ����

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

