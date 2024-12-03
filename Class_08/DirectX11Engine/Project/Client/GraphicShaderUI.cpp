#include "pch.h"
#include "GraphicShaderUI.h"


GraphicShaderUI::GraphicShaderUI()
	: AssetUI("GraphicShaderUI", "##GraphicShaderUI", ASSET_TYPE::GRAPHICS_SHADER)
{
}

GraphicShaderUI::~GraphicShaderUI()
{
}

void GraphicShaderUI::render_tick()
{
	render_title();

}