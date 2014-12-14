
#pragma once

//
//	四角形のあたり判定
//

namespace collision {
	//	矩形と矩形のあたり判定
	bool rect_to_rect(float player_x, float player_y, float player_width, float player_height,
		float object_x, float object_y, float object_width, float object_height);
	//	点と矩形のあたり判定
	bool point_to_rect(float point_x, float point_y,
		float object_x, float object_y, float object_width, float object_height);
}
