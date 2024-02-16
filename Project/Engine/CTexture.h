#pragma once
#include "CAsset.h"

class CTexture : public CAsset
{
private:
	ScratchImage						m_Image; // Load �Լ��� ������ �� ���� ( �ý��� �޸� )
	ComPtr<ID3D11Texture2D>				m_Tex2D; // GPU �޸�
	ComPtr<ID3D11ShaderResourceView>	m_SRV;	 // GPU �޸𸮿� ���޽�Ű�� ���� �ʿ��� View

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

