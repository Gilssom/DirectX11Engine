#include "pch.h"
#include "CAssetManager.h"

CAssetManager::CAssetManager()
{

}

CAssetManager::~CAssetManager()
{

}

Ptr<CTexture> CAssetManager::CreateTexture(const wstring& strKey, UINT width, UINT height
										, DXGI_FORMAT pixelFormat, UINT bindFlag, D3D11_USAGE usage)
{
	Ptr<CTexture> pTex = FindAsset<CTexture>(strKey);

	if (pTex != nullptr)
	{
		return pTex;
	}

	pTex = new CTexture;
	pTex->Create(width, height, pixelFormat, bindFlag, usage);
	pTex->m_Key = strKey;

	m_mapAsset[(UINT)ASSET_TYPE::TEXTURE].insert(make_pair(strKey, pTex.Get()));

	return pTex;
}

Ptr<CTexture> CAssetManager::CreateTexture(const wstring& strKey, ComPtr<ID3D11Texture2D> tex2D)
{
	Ptr<CTexture> pTex = FindAsset<CTexture>(strKey);

	if (pTex != nullptr)
	{
		return pTex;
	}

	pTex = new CTexture;
	pTex->Create(tex2D);
	pTex->m_Key = strKey;

	m_mapAsset[(UINT)ASSET_TYPE::TEXTURE].insert(make_pair(strKey, pTex.Get()));

	return pTex;
}