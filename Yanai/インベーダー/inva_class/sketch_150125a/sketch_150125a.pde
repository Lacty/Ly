PImage img1, img2;

void setup(){
  size(400, 400);
  img1 = loadImage("invader1.png");
  img2 = loadImage("invader2.png");
}

class invader{
  float x = 0;
  float y = 0;
  float speed = 1;
  float size = 50;
  
  void update(){
    image(img1, x, y, size, size);
  }
}

invader inv = new invader;

void draw(){
  background(0);
  inv.update();
}
