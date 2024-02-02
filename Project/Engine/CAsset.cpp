#include "pch.h"
#include "CAsset.h"


CAsset::CAsset(ASSET_TYPE type)
	: m_Type(type)
	, m_RefCount(0)
{

}

CAsset::~CAsset()
{

}
