#pragma once
#include "CAsset.h"

class CTexture : public CAsset
{
private:
	ScratchImage						m_Image; // Load �Լ��� ������ �� ���� ( �ý��� �޸� )
	ComPtr<ID3D11Texture2D>				m_Tex2D; // GPU �޸�
	ComPtr<ID3D11ShaderResourceView>	m_SRV;	 // GPU �޸𸮿� ���޽�Ű�� ���� �ʿ��� View

	D3D11_TEXTURE2D_DESC				m_Desc;  // Animation �� �����ϱ� ���� Texture ������ ���޽�Ű�� ����

public:
	float GetWidth() { return (float)m_Desc.Width; }
	float GetHeight() { return (float)m_Desc.Height; }

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

