
#include "isHit.h"

bool collision::rect_to_rect(float player_x, float player_y, float player_width, float player_height,
    float object_x, float object_y, float object_width, float object_height){
    if (player_x < (object_x + object_width)){
        if ((player_x + player_width) > object_x){
            if (player_y < (object_y + object_height)){
                if ((player_y + player_height) > object_y) {
                    // “–‚½‚Á‚Ä‚¢‚é‚Ì‚Åtrue
                    return true;
                }
            }
        }
    }
    // “–‚½‚Á‚Ä‚¢‚È‚¢‚Ì‚Åfalse
    return false;
}

bool collision::point_to_rect(float point_x, float point_y,
    float object_x, float object_y, float object_width, float object_height){
    if ((point_x > object_x) && (point_x < object_x + object_width)){
        if ((point_y > object_y) && (point_y < object_y + object_height)){
            // “ü‚Á‚Ä‚¢‚é‚Ì‚Åtrue
            return true;
        }
    }
    // “ü‚Á‚Ä‚È‚¢‚Ì‚Åfalse
    return false;
}
