#pragma once
#include "CAsset.h"

class CTexture : public CAsset
{
private:
	ScratchImage						m_Image; // Load 함수를 구현할 수 있음 ( 시스템 메모리 )
	ComPtr<ID3D11Texture2D>				m_Tex2D; // GPU 메모리
	ComPtr<ID3D11ShaderResourceView>	m_SRV;	 // GPU 메모리에 전달시키기 위해 필요한 View

public:
	void Binding(int registerNum);
	static void Clear(int registerNum);

private:
	virtual int Load(const wstring& FilePath) override;
	virtual int Save(const wstring& FilePath) override;

public:
	CTexture();
	~CTexture();
};

