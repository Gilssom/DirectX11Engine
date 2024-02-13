#include "pch.h"
#include "CMeshRender.h"

#include "CTransform.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{

}

CMeshRender::~CMeshRender()
{

}

void CMeshRender::FinalTick()
{

}

void CMeshRender::Render()
{
	// 오브젝트의 위치값을 상수버퍼를 통해서 바인딩
	GetOwner()->Transform()->Binding();

	// 사용할 쉐이더 바인딩
	GetShader()->Binding();

	// 사용할 텍스처 바인딩
	GetTexture()->Binding(0); // 레지스터 0번에 등록

	// Mesh , Shader Render
	GetMesh()->Render();
}