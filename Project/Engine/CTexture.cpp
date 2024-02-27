#include "pch.h"
#include "CTexture.h"

#include "CDevice.h"

CTexture::CTexture()
    : CAsset(ASSET_TYPE::TEXTURE)
{
}

CTexture::~CTexture()
{
}

void CTexture::Binding(int registerNum)
{
    CONTEXT->PSSetShaderResources(registerNum, 1, m_SRV.GetAddressOf());
}

void CTexture::Clear(int registerNum)
{
    ID3D11ShaderResourceView* pSRV = nullptr;
    CONTEXT->PSSetShaderResources(registerNum, 1, &pSRV);
}

int CTexture::Load(const wstring& FilePath)
{
    // �Ʒ� �Լ� ��� DirectXTex ���̺귯���� �ִ� ��ɵ�
    // Ȯ���ڿ� �˸°� �ε带 ���ش�.
    
    wchar_t Ext[50] = {};
    _wsplitpath_s(FilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, Ext, 50);

    wstring strExt = Ext;

    HRESULT hr = E_FAIL;

    if (strExt == L".dds" || strExt == L".DDS")
    {
        // .dds .DDS
        hr = LoadFromDDSFile(FilePath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_Image);
    }
    else if (strExt == L".tga" || strExt == L".TGA")
    {
        // .tag. .TGA
        hr = LoadFromTGAFile(FilePath.c_str(), nullptr, m_Image);
    }
    else
    {
        // .png .jpg .jpeg .bmp
        hr = LoadFromWICFile(FilePath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, m_Image);
    }

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"�ؽ��� �ε� ����", L"�ؽ��� �ε� ����", MB_OK);

        return E_FAIL;
    }

    // �̹��� ��ü�� ����ִ� �������� GPU �޸𸮿� ��������� ��

    // Texture2D Descrition �ۼ��ؼ� Texture2D ��ü ����


    // Texture2D ��ü �̿��ؼ� ShaderResourceView ����
    // DirectX Engine ���� �׳� �ѹ��� ������ �� �ְ� ���ִ� �Լ��� ������
    hr = CreateShaderResourceView(DEVICE
                            , m_Image.GetImages()
                            , m_Image.GetImageCount()
                            , m_Image.GetMetadata()
                            , m_SRV.GetAddressOf());

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"Shader Resource View ���� ����", L"�ؽ��� �ε� ����", MB_OK);

        return E_FAIL;
    }

    // Texture 2D �� �Ѱ��ֱ� ( �ѹ��� ������ �ع��ȱ� ������ ������ �ٽ� �־������ )
    m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());
    m_Tex2D->GetDesc(&m_Desc);

    return hr;
}

int CTexture::Save(const wstring& FilePath)
{
    return 0;
}
