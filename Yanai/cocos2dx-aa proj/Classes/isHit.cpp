
#include "isHit.h"

bool collision::rect_to_rect(float player_x, float player_y, float player_width, float player_height,
    float object_x, float object_y, float object_width, float object_height){
    if (player_x < (object_x + object_width)){
        if ((player_x + player_width) > object_x){
            if (player_y < (object_y + object_height)){
                if ((player_y + player_height) > object_y) {
                    // �������Ă���̂�true
                    return true;
                }
            }
        }
    }
    // �������Ă��Ȃ��̂�false
    return false;
}

bool collision::point_to_rect(float point_x, float point_y,
    float object_x, float object_y, float object_width, float object_height){
    if ((point_x > object_x) && (point_x < object_x + object_width)){
        if ((point_y > object_y) && (point_y < object_y + object_height)){
            // �����Ă���̂�true
            return true;
        }
    }
    // �����ĂȂ��̂�false
    return false;
}
