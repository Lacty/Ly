#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"

bool Hit(float player_x, float player_y, float player_width, float player_height,
	float object_x, float object_y, float object_width, float object_height){
	if (player_x < (object_x+object_width)){
		if ((player_x+player_width) > object_x){
			if (player_y < (object_y + object_height)){
				if ((player_y+player_height) > object_y) {
					// �������Ă���̂�true
					return true;
				}
			}
		}
	}
	// �������Ă��Ȃ��̂�false
	return false;
}