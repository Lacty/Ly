
#pragma once

//
//	�l�p�`�̂����蔻��
//

namespace collision {
	//	��`�Ƌ�`�̂����蔻��
	bool rect_to_rect(float player_x, float player_y, float player_width, float player_height,
		float object_x, float object_y, float object_width, float object_height);
	//	�_�Ƌ�`�̂����蔻��
	bool point_to_rect(float point_x, float point_y,
		float object_x, float object_y, float object_width, float object_height);
}
