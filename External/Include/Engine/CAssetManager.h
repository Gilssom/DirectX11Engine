#pragma once
#include "Singletone.h"

#include "assets.h"
#include "CPathManager.h"

class CAssetManager : public CSingleton<CAssetManager>
{
    SINGLE(CAssetManager)

private:
    // Asset ���� > 8������ Ű������ ����
    map<wstring, Ptr<CAsset>>   m_mapAsset[(UINT)ASSET_TYPE::END];


public:
    void Init();
    void CreateDefaultMesh();
    void CreateDefaultTexture();
    void CreateDefaultMaterial();
    void CreateDefaultGraphicShader();
    void CreateDefaultComputeShader();


public:
    // Asset �˻�
    template<typename T>
    Ptr<T> FindAsset(const wstring& strKey); // ������ ����Ʈ �����ͷ� ���� �� �ְ�

    // Asset ���
    template<typename T>
    void AddAsset(const wstring& strKey, Ptr<T> pAsset);

};


// ���� ���ø�
//template<typename T1, typename T2>
//constexpr bool mybool = false;
// �κ� Ư��ȭ
//template<typename T1>
//constexpr bool mybool<T1, T1> = true; // �� typename �� ������ �� �ɾ��� �� �ִ� Ư��ȭ
// const �� ���� �� ���� ������ ���ȭ ( ��Ÿ�� )
// constexpr �� ���� �� ���� ������ ������ ���ȭ ( ������ )
// = std::is_same_v ( ������ ��� )

template<typename T>
ASSET_TYPE GetAssetType()
{
    // type_info �� ��Ÿ�� ���� ������ ��
    //const type_info& info = typeid(T);

    // constexpr =>> ������ �� if ���� Ȯ���� > false �� ��ȯ�ϸ� if ���� ������ �� ������ ���ֹ���
    if constexpr (std::is_same_v<T, CMesh>)
    {
        return ASSET_TYPE::MESH;
    }
    if constexpr (std::is_same_v<T, CGraphicShader>)
    {
        return ASSET_TYPE::GRAPHICS_SHADER;
    }
    if constexpr (std::is_same_v<T, CComputeShader>)
    {
        return ASSET_TYPE::COMPUTE_SHADER;
    }
}


template<typename T>
inline Ptr<T> CAssetManager::FindAsset(const wstring& strKey)
{
    ASSET_TYPE type = GetAssetType<T>();

    map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)type].find(strKey);

    if (iter == m_mapAsset[(UINT)type].end())
    {
        return nullptr;
    }

#ifdef _DEBUG
    // Mesh �� map �� Texture �� �ٸ� T �� �� �� �ִ� ��Ȳ�� �߻��� ���� �ִ�.
    T* pAsset = dynamic_cast<T*> (iter->second.Get());
    return pAsset;
#else
    return (T*)iter->second;
#endif
}

template<typename T>
inline void CAssetManager::AddAsset(const wstring& strKey, Ptr<T> pAsset)
{
    Ptr<T> pFindAsset = FindAsset<T>(strKey);

    assert(pFindAsset.Get() == nullptr); // �ߺ� Ȯ��

    ASSET_TYPE type = GetAssetType<T>();

    m_mapAsset[(UINT)type].insert(make_pair(strKey, pAsset.Get()));
    pAsset->m_Key = strKey;
}

