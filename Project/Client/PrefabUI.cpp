#include "pch.h"
#include "PrefabUI.h"

PrefabUI::PrefabUI()
	: AssetUI("PrefabUI", "##PrefabUI", ASSET_TYPE::PREFAB)
{

}

PrefabUI::~PrefabUI()
{

}

void PrefabUI::Render_Tick()
{
	Render_Title();
}