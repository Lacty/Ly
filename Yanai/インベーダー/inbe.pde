PImage img;
int winWidth;
int winHeight;
int x, y;
int imgWid, imgHei;
int speed;

void setup(){
  winWidth  = 500;
  winHeight = 500;
  imgWid = 50;
  imgHei = 40;
  size(winWidth, winHeight);
  img = loadImage("inbe.png");
  x = 0;
  y = 0;
  speed = 3;
}

void draw(){
  background(0);
  image(img, x, y, imgWid, imgHei);
  x += speed;
  if (x > winWidth - imgWid){
    speed *= -1;
    y += imgHei;
    if (y >= winHeight - imgHei){
      y = 0;
    }
  }
  if (x < 0){
    speed *= -1;
    y += imgHei;
    if (y >= winHeight - imgHei){
      y = 0;
    }
  }
  
}
