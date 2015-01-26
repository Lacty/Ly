PImage img, img2;
float img_alpha = 255;
float img2_alpha = 0;
int angle = 0;
int winWidth;
int winHeight;
int num_of_invader = 5;
int[] x = new int[num_of_invader];
int y;
int imgWidth, imgHeight;
int speed;

int mode = 0;
int a = 0;

void setup(){
  winWidth  = 500;
  winHeight = 500;
  imgWidth = 50;
  imgHeight = 40;
  size(winWidth, winHeight);
  img  = loadImage("invader.png");
  img2 = loadImage("invader2.png");
  /*
  img  = loadImage("img1.jpg");
  img2 = loadImage("img2.png");
  */
  for (int i = 0; i < num_of_invader; i++){
    x[i] = i*imgWidth;
  }
  y = 0;
  speed = 3;
}


void draw(){
  background(0);
  a++;
  if (a > 0 && a < 40){
    mode = 0;
  }
  if (a > 40 && a < 80){
    mode = 1;
  }
  if (a > 80){
    a = 0;
  }
  
  switch(mode){
  case 0:
  for (int i = 0; i < num_of_invader; i++){
    image(img, x[i], y, imgWidth, imgHeight);
    x[i] += speed;
    if (x[i] > winWidth - imgWidth){
      speed *= -1;
      y += imgHeight;
      if (y >= winHeight - imgHeight){
        y = 0;
      }
    }
    if (x[i] < 0){
      speed *= -1;
      y += imgHeight;
      if (y >= winHeight - imgHeight){
        y = 0;
      }
    }
  }
  break;
  
  case 1:
  for (int i = 0; i < num_of_invader; i++){
    image(img2, x[i], y, imgWidth, imgHeight);
    x[i] += speed;
    if (x[i] > winWidth - imgWidth){
      speed *= -1;
      y += imgHeight;
      if (y >= winHeight - imgHeight){
        y = 0;
      }
    }
    if (x[i] < 0){
      speed *= -1;
      y += imgHeight;
      if (y >= winHeight - imgHeight){
        y = 0;
      }
    }
  }
  break;
  }
}
