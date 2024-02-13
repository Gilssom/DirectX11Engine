#pragma once
#include "CComponent.h"

#include "assets.h"

class CRenderComponent : public CComponent
{
private:
	Ptr<CMesh>			m_Mesh;		// 모양
	Ptr<CGraphicShader> m_Shader;	// 쉐이더
	Ptr<CTexture>		m_Tex;		// 텍스쳐

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

