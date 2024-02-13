#pragma once
#include "CAsset.h"

class CShader : public CAsset
{
protected:
    // Error Blob
    ComPtr<ID3DBlob>		   m_ErrBlob;

public:
    virtual void Binding() = 0;
    virtual int Load(const wstring& _FilePath) override { return S_OK; }
    virtual int Save(const wstring& _FilePath) override { return S_OK; }

public:
    CShader(ASSET_TYPE type);
    ~CShader();
};

