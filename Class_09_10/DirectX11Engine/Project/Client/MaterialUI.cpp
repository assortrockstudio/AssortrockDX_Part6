#include "pch.h"
#include "MaterialUI.h"


MaterialUI::MaterialUI()
	: AssetUI("MaterialUI", "##MaterialUI", ASSET_TYPE::MATERIAL)
{
}

MaterialUI::~MaterialUI()
{
}

void MaterialUI::render_tick()
{
	render_title();

}