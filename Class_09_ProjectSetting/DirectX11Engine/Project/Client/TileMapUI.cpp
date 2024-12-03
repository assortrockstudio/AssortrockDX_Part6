#include "pch.h"
#include "TileMapUI.h"


TileMapUI::TileMapUI()
	: ComponentUI("TileMap", "##TileMapUI", COMPONENT_TYPE::TILEMAP)
{
}

TileMapUI::~TileMapUI()
{
}


void TileMapUI::render_tick()
{
	render_title();


}