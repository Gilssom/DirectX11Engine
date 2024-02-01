#pragma once
#include "CAsset.h"

class CMesh : public CAsset
{
private:
	// 정점 정보를 저장하는 Buffer
	ComPtr<ID3D11Buffer> m_VB;
	D3D11_BUFFER_DESC	 m_VBdesc;
	UINT				 m_VtxCount;
	Vtx*				 m_VtxSysMem;

	// Vertex Buffer 내에서 사용할 정점을 가르키는 인덱스 정보를 저장하는 Buffer
	ComPtr<ID3D11Buffer> m_IB;
	D3D11_BUFFER_DESC	 m_IBdesc;
	UINT				 m_IdxCount;
	UINT*				 m_IdxSysMem;

private:
	void Binding();

public:
	int Create(Vtx* VtxSysMem, size_t VtxCount, UINT* IdxSysMem, size_t IdxCount);
	void Render();

public:
	CMesh();
	~CMesh();
};

