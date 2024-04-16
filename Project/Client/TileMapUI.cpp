#include "pch.h"
#include "TileMapUI.h"

TileMapUI::TileMapUI()
	: ComponentUI("TileMap", "##TileMapUI", COMPONENT_TYPE::TILEMAP)
{
	SetSize(ImVec2(0, 200));
}

TileMapUI::~TileMapUI()
{

}

void TileMapUI::Render_Tick()
{
	Render_Title();
}