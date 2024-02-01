#pragma once

class CEntity
{
private:
	static UINT g_NextID;


private:
	wstring m_Name;
	UINT	m_ID;


public:
	const wstring& GetName() { return m_Name; }
	void SetName(const wstring& name) { m_Name = name; }
	UINT GetID() { return m_ID; }

public:
	CEntity();
	CEntity(const CEntity& _Origin); // 汗荤 积己磊 流立 备泅
	~CEntity();
};

