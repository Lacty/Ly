PImage img, img2;
float img_alpha = 255;
float img2_alpha = 0;
int angle = 0;
int num_of_invader = 5;
int[] x = new int[num_of_invader];
int y;
int imgWidth, imgHeight;
int speed;

int mode = 0;
int time = 0;

void setup() {
  imgWidth = 50;
  imgHeight = 40;
  size(500, 500);
  img  = loadImage("invader.png");
  img2 = loadImage("invader2.png");
  /*
  img  = loadImage("img1.jpg");
   img2 = loadImage("img2.png");
   */
  for (int i = 0; i < num_of_invader; i++) {
    x[i] = i*imgWidth;
  }
  y = 0;
  speed = 3;
}


void draw() {
  background(0);
  time++;
  if (time > 0 && time < 40) {
    mode = 0;
  }
  if (time > 40 && time < 80) {
    mode = 1;
  }
  if (time > 80) {
    time = 0;
  }

  switch(mode) {
  case 0:
    for (int i = 0; i < num_of_invader; i++) {
      image(img, x[i], y, imgWidth, imgHeight);
      x[i] += speed;
      if (x[i] > width - imgWidth) {
        speed *= -1;
        y += imgHeight;
        if (y >= height - imgHeight) {
          y = 0;
        }
      }
      if (x[i] < 0) {
        speed *= -1;
        y += imgHeight;
        if (y >= height - imgHeight) {
          y = 0;
        }
      }
    }
    break;

  case 1:
    for (int i = 0; i < num_of_invader; i++) {
      image(img2, x[i], y, imgWidth, imgHeight);
      x[i] += speed;
      if (x[i] > width - imgWidth) {
        speed *= -1;
        y += imgHeight;
        if (y >= height - imgHeight) {
          y = 0;
        }
      }
      if (x[i] < 0) {
        speed *= -1;
        y += imgHeight;
        if (y >= height - imgHeight) {
          y = 0;
        }
      }
    }
    break;
  }
}

