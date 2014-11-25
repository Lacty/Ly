#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "Player.h"
#include "common.h"



void Map(){

}

void MapMove(){
	
	// Ž©‹@‚Ìs‚«‰ß‚¬–hŽ~”»’èi‰Ej
	if (player.x > -100) box_x -= 2.5;
	if (player.x + player.width > -100) {
		box_x -= 5;
		player.x -= PLAYER_MOVE;
	}

	// iãj
	if (player.y > 100) box_y -= 6;
	if (player.height / 2 > 100) {
		box_y -= 6;
		player.y -= PLAYER_MOVE;
	}

	// ”wŒi‰æ‘œ‚ÌIŽn‰z‚¦–hŽ~”»’è
	if (box_x > -512) box_x = -512;
	if (box_y > -340) box_y = -340;
	if (box_x + map_width < 518) box_x = -map_width + 518;
	if (box_y + map_height < 346) box_y = -map_height + 346;

}


void drawMap(Texture &background){


	drawTextureBox(box_x, box_y, map_width, map_height,
		0, 0, 4096, 2048,
		background,
		Color(1, 1, 1));


}