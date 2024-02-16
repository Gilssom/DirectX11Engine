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
    // 아래 함수 모두 DirectXTex 라이브러리에 있는 기능들
    // 확장자에 알맞게 로드를 해준다.
    
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
        MessageBox(nullptr, L"텍스쳐 로딩 실패", L"텍스쳐 로딩 실패", MB_OK);

        return E_FAIL;
    }

    // 이미지 객체가 들고있는 정보들을 GPU 메모리에 전달해줘야 함

    // Texture2D Descrition 작성해서 Texture2D 객체 생성


    // Texture2D 객체 이용해서 ShaderResourceView 생성
    // DirectX Engine 에서 그냥 한번에 구현할 수 있게 해주는 함수가 존재함
    hr = CreateShaderResourceView(DEVICE
                            , m_Image.GetImages()
                            , m_Image.GetImageCount()
                            , m_Image.GetMetadata()
                            , m_SRV.GetAddressOf());

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"Shader Resource View 생성 실패", L"텍스쳐 로딩 실패", MB_OK);

        return E_FAIL;
    }

    // Texture 2D 로 넘겨주기 ( 한번에 구현을 해버렸기 때문에 꺼내서 다시 넣어줘야함 )
    m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());

    return hr;
}

int CTexture::Save(const wstring& FilePath)
{
    return 0;
}
