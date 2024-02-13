#pragma once
#include "CEntity.h"

class CAsset : public CEntity
{
private:
	wstring				m_Key;			// 로딩된 키값
	wstring				m_RelativePath; // 상대 경로
	const ASSET_TYPE	m_Type;			// Asset 의 Type
	int					m_RefCount;		// 참조 카운트

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

		// 아무도 이 Asset 을 참조하지 않는다면
		if (m_RefCount <= 0)
		{
			delete this;
		}
	}

public:
	CAsset(ASSET_TYPE type); // 실수로 type 을 지정 못해줄 수 있는 것을 방지함 ( 기본 생성자 삭제 )
	CAsset(const CAsset& _Origin) = delete;
	~CAsset();

	// Ptr 에서 가르키는 T 의 Private 에 접근 가능하게 한다.
	template<typename T>
	friend class Ptr;

	friend class CAssetManager;
};

