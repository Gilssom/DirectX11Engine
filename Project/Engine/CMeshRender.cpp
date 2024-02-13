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
	// ������Ʈ�� ��ġ���� ������۸� ���ؼ� ���ε�
	GetOwner()->Transform()->Binding();

	// ����� ���̴� ���ε�
	GetShader()->Binding();

	// ����� �ؽ�ó ���ε�
	GetTexture()->Binding(0); // �������� 0���� ���

	// Mesh , Shader Render
	GetMesh()->Render();
}