#pragma once
#include "EditorUI.h"

// 추상 클래스 (상속 용도)
class AssetUI : public EditorUI
{
private:
	Ptr<CAsset>			m_TargetAsset;
	const ASSET_TYPE	m_Type;


public:
	void SetTarget(Ptr<CAsset> target) { m_TargetAsset = target; }
	Ptr<CAsset> GetTarget() { return m_TargetAsset; }

	ASSET_TYPE GetAssetType() { return m_Type; }

public:
	virtual void Render_Tick() = 0;

protected:
	void Render_Title();

public:
	AssetUI(const string& name, const  string& id, ASSET_TYPE type);
	~AssetUI();
};