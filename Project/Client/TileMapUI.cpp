#include "pch.h"
#include "TileMapUI.h"

TileMapUI::TileMapUI()
	: ComponentUI("TileMap", "##TileMapUI", COMPONENT_TYPE::TILEMAP)
{
	SIZE;
}

TileMapUI::~TileMapUI()
{

}

void TileMapUI::Render_Tick()
{
	Render_Title();
}