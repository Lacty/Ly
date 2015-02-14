
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"


enum Window {
  WIDTH  = 512,
  HEIGHT = 256
};

struct Player{
  Vec2f point;
  float vy;
  bool isJump;
};

const float JumpPower = 20.0f;
const float Gravity   = -1.0f;

int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);
  
  Player player = {
    Vec2f(0.0f, 0.0f),
    0,
    false
  };

  while (env.isOpen()) {

    // クリックしたらジャンプする処理
    if (env.isPushButton(Mouse::LEFT)){
      if (!player.isJump){
        player.isJump = true;
        player.vy = JumpPower;
      }
    }

    // ジャンプ中の処理
    if (player.isJump){
      player.point.y() += player.vy;
      player.vy += Gravity;

      // 着地
      if (player.point.y() <= 0.0f){
        player.point.y() = 0.0f;
        player.isJump = false;
      }
    }

    env.setupDraw();

    drawPoint(player.point.x(), player.point.y(),
              10,
              Color(1, 1, 1));

    env.update();
  }
}
