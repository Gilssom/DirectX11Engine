#pragma once
#include "CEntity.h"

class CAsset : public CEntity
{
private:
	wstring				m_Key;			// �ε��� Ű��
	wstring				m_RelativePath; // ��� ���
	const ASSET_TYPE	m_Type;			// Asset �� Type
	int					m_RefCount;		// ���� ī��Ʈ

public:
	const wstring& GetKey() { return m_Key; }
	const wstring& GetRelativePath() { return m_RelativePath; }
	ASSET_TYPE GetAssetType() { return m_Type; }

private:
	virtual int Load(const wstring& FilePath) = 0;
	virtual int Save(const wstring& FilePath) = 0;

private:
	void AddRef() { m_RefCount++; }
	void Release() 
	{ 
		m_RefCount--; 

		// �ƹ��� �� Asset �� �������� �ʴ´ٸ�
		if (m_RefCount <= 0)
		{
			delete this;
		}
	}

public:
	CAsset(ASSET_TYPE type); // �Ǽ��� type �� ���� ������ �� �ִ� ���� ������ ( �⺻ ������ ���� )
	CAsset(const CAsset& _Origin) = delete;
	~CAsset();

	// Ptr ���� ����Ű�� T �� Private �� ���� �����ϰ� �Ѵ�.
	template<typename T>
	friend class Ptr;

	friend class CAssetManager;
};

