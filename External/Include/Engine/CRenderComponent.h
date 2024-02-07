#pragma once
#include "CComponent.h"

#include "assets.h"

class CRenderComponent : public CComponent
{
private:
	Ptr<CMesh>			m_Mesh;		// ¸ð¾ç
	Ptr<CGraphicShader> m_Shader;	// ½¦ÀÌ´õ


public:
	virtual void Render() = 0;


public:
	void SetMesh(Ptr<CMesh> mesh) { m_Mesh = mesh; }
	void SetShader(Ptr<CGraphicShader> shader) { m_Shader = shader; }

	Ptr<CMesh> GetMesh() { return m_Mesh; }
	Ptr<CGraphicShader> GetShader() { return m_Shader; }

public:
	CRenderComponent(COMPONENT_TYPE type);
	~CRenderComponent();
};

