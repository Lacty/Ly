#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "Player.h"
#include "common.h"


struct Map{
	int x, y;
	int width, height;
};

Map map{ -512, -340, 8192, 2048 };

int yuka_x = 0;
int yuka_y = 0;

int hime_x = 0;
int hime_y = 0;

void MapMove(){
	
	// é©ã@ÇÃçsÇ´âﬂÇ¨ñhé~îªíËÅiâEï«Åj
	if (box_x + map_width == player.x + player.width) player.x -= PLAYER_MOVE;
	if (box_x + map_width == 518) player.x += PLAYER_MOVE;
		if (player.x > -100) box_x -= map_move_x1;
		if (player.x + player.width > -100) {
			box_x -= map_move_x2;
			player.x -= PLAYER_MOVE;
		}
		
	// Åiè„Åj
	if (player.y > 100) box_y -= map_move_y1;
	if (player.y + player.height > 100) {
		box_y -= map_move_y2;
		player.y -= PLAYER_MOVE;
	}

	// Åiç∂Åj
	if (player.x < -300) box_x += map_move_x1;


	// îwåiâÊëúÇÃèIénâzÇ¶ñhé~îªíË
	if (box_x > -512) box_x = -512;
	if (box_y > -340) box_y = -340;
	if (box_x + map_width < 518) box_x = -map_width + 518;
	if (box_y + map_height < 346) box_y = -map_height + 346;

	map.x = box_x*1.9;
	map.y = box_y;

	yuka_x = box_x+4300;
	yuka_y = box_y+1700;

	hime_x = box_x + 4550;
	hime_y = box_y + 1750;
}

void drawMap(Texture &background, Texture& tyuke_image, Texture& castle_image, Texture& show, Texture& himesama){

	drawTextureBox(box_x, box_y, map_width, map_height,
		0, 0, 4096, 2048,
		background,
		Color(1, 1, 1));

	drawTextureBox(map.x, map.y, map.width, map.height,
		0, 0, 8192, 2048,
		tyuke_image,
		Color(1, 1, 1));

	drawTextureBox(box_x, box_y, map_width, map_height,
		0, 0, 4096, 2048,
		castle_image,
		Color(1, 1, 1));

	drawTextureBox(box_x, box_y, map_width, map_height,
		0, 0, 4096, 2048,
		show,
		Color(1, 1, 1));

	drawTextureBox(hime_x, hime_y, 200, 200,
		0, 0, 128, 128,
		himesama,
		Color(1, 1, 1));

	if (Hit(player.x, player.y, player.width, player.height,
		hime_x+50, hime_y, 150, 150)){
		GameFlag = 3;
	}

	//drawFillBox(yuka_x, yuka_y, 500, 50, Color(1, 1, 1));

	if (player.x > yuka_x){
		if ((player.y < (yuka_y + 50)) && ((player.y + player.height) > yuka_y)){
			player.y = yuka_y + 50;
			jump = false;
		}
	}

}