#include "pch.h"
#include "PrefabUI.h"


PrefabUI::PrefabUI()
	: AssetUI("PrefabUI", "##PrefabUI", ASSET_TYPE::PREFAB)
{
}

PrefabUI::~PrefabUI()
{
}

void PrefabUI::render_tick()
{
	render_title();

}