PImage img, img2;
int winWidth;
int winHeight;
int num_of_invader = 5;
int[] x = new int[num_of_invader];
int[] y = new int[num_of_invader];
int imgWidth, imgHeight;
int speed;

void setup(){
  winWidth  = 500;
  winHeight = 500;
  imgWidth = 50;
  imgHeight = 40;
  size(winWidth, winHeight);
  img  = loadImage("invader.png");
  img2 = loadImage("invader2.png");
  for (int i = 0; i < num_of_invader; i++){
    x[i] = i*imgWidth;
    y[i] = 0;
  }
  speed = 3;
}

class invaders{
  
  
}

void draw(){
  background(0);
  image(img, x, y, imgWidth, imgHeight);
  x += speed;
  if (x > winWidth - imgWidth){
    speed *= -1;
    y += imgHeight;
    if (y >= winHeight - imgHeight){
      y = 0;
    }
  }
  if (x < 0){
    speed *= -1;
    y += imgHeight;
    if (y >= winHeight - imgHeight){
      y = 0;
    }
  }
  
}
