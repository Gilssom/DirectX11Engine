#pragma once
#include "CComponent.h"

#include "assets.h"

class CRenderComponent : public CComponent
{
private:
	Ptr<CMesh>			m_Mesh;		// ���
	Ptr<CGraphicShader> m_Shader;	// ���̴�
	Ptr<CTexture>		m_Tex;		// �ؽ���

public:
	virtual void Render() = 0;


public:
	void SetMesh(Ptr<CMesh> mesh) { m_Mesh = mesh; }
	void SetShader(Ptr<CGraphicShader> shader) { m_Shader = shader; }
	void SetTexture(Ptr<CTexture> tex) { m_Tex = tex; }

	Ptr<CMesh> GetMesh() { return m_Mesh; }
	Ptr<CGraphicShader> GetShader() { return m_Shader; }
	Ptr<CTexture> GetTexture() { return m_Tex; }

public:
	CRenderComponent(COMPONENT_TYPE type);
	~CRenderComponent();
};

