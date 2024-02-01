#pragma once
#include "CEntity.h"

class CAsset : public CEntity
{
private:
	wstring				m_Key;			// 로딩된 키값
	wstring				m_RelativePath; // 상대 경로

	const ASSET_TYPE	m_Type;			// Asset 의 Type

public:
	const wstring& GetKey() { return m_Key; }
	const wstring& GetRelativePath() { return m_RelativePath; }

	ASSET_TYPE GetAssetType() { return m_Type; }

public:
	CAsset(ASSET_TYPE type); // 실수로 type 을 지정 못해줄 수 있는 것을 방지함 ( 기본 생성자 삭제 )
	~CAsset();
};

