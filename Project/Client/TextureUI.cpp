#include "pch.h"
#include "TextureUI.h"

TextureUI::TextureUI()
	: AssetUI("TextureUI", "##TextureUI", ASSET_TYPE::TEXTURE)
{

}

TextureUI::~TextureUI()
{

}

void TextureUI::Render_Tick()
{
	Render_Title();
}