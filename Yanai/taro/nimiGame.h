
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"
#include "nimiPlayer.h"
#include "nimiMarron.h"
#include "score.h"
#include "timeCounter.h"
#include "BlackOut.h"

//	�Q�[���̕`��
void nimiGame(AppEnv& app_env, Texture& number_image){
	switch (miniMODE){
	case 0:{
	   if (!isReady){
		   if (miniTimer > 1){
			   drawFillBox(0, 0, 30, 30, Color(1, 0, 0));
			   if (app_env.isPushKey(GLFW_KEY_ENTER)){
				   isReady = true;
			   }
		   }
	   }
	   else if (app_env.isPushKey(GLFW_KEY_ENTER)){
		   isReady = false;
	   }
	   /*	�`�揈��
		   �I
		   �v���C���[
		   �X�R�A
		   */
	   drawMarron(app_env);
	   drawPlayer(app_env);
	   drawScore(number_image, number_mini);
	   drawCount();
	   //	�^�C����0�ɂȂ����Ƃ���BlackOut�����鏈��
	   if (miniTimer == 0) {
		   drawBlackOut();
		   if (!drawBlackOut()){
			   miniMODE = 1;
			   miniTimer = 60 * 10;
			   alfa = 0;
		   }
	   }
	} break;

	case 1:{
			   drawFillBox(0, 0, 20, 20, Color(1, 1, 1));
			   if (app_env.isPushKey(GLFW_KEY_ENTER)){
				   miniMODE = 0;
			   }
	}break;
	}
}