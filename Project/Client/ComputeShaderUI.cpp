#include "pch.h"
#include "ComputeShaderUI.h"

ComputeShaderUI::ComputeShaderUI()
	: AssetUI("ComputeShaderUI", "##ComputeShaderUI", ASSET_TYPE::COMPUTE_SHADER)
{

}

ComputeShaderUI::~ComputeShaderUI()
{

}

void ComputeShaderUI::Render_Tick()
{
	Render_Title();
}