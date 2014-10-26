//
// アプリ雛形
// ※ファイル分割対応版
//

#include "lib/appEnv.hpp"
#include "common.h"
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "title.h"


// ↑他の.cppファイルでは、必要なヘッダファイルを
//   適時インクルードする事

// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, false);
  
  
  // 背景をスクロールさせる変数
  // 背景の画像
  int scroll = 0;
  Texture bg("res/Bac_1.png");

  // プレイヤーの動かすための変数
  float move = 5;
  // 自機の画像
  Texture ziki("res/ziki.png");


  // 弾の初期化
  for (int i = 0; i < SHOT_MAX; ++i) {
	  shot_data[i].active = false;
  }

  // 数字の画像
  Texture numb("res/num.png");

  // 獲得したポイントを保存する変数
  int play_point = 0;

  // 敵の画像
  Texture ene("res/enemy.png");

  // タイトルｂｇ
  Texture titlebg("res/titlebg.png");
  // Ω<-ボタン
  Texture but("res/button.png");

  // Mediaファイル
  Media syobon("res/syobon.wav");//(´・ω・｀)しょぼーん
  Media sonna("res/sona-.wav");//そんなー
  Media an("res/a-n.wav");//あーん
  Media iyan("res/iyan.wav");//いやーん

  int MODE = 0;

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;
    
    // 描画準備
    app_env.setupDraw();

	switch (MODE){
	case 0:
	{
			drawTitle(app_env, MODE, titlebg, but);
	}
		break;

	case 1:
	{
		  // 背景処理
		  backGround(scroll, bg);

		  // 自機の移動処理
		  playerMovement(app_env, player, move);

		  // 自機の描画
		  drawPlayer(ziki, player);

		  // 自機の弾の描画
		  playerShots(app_env, shot_data, player);

		  // エネミーの描画
		  drawEnemy(app_env, enemy, shot_data, play_point,
			  ene, syobon, sonna, an, iyan);

		  // スコア関係
		  score(app_env, enemy, play_point);
		  drawScore(app_env, numb);
	}
		break;

	}

    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
