void setup(){
  size(300, 300);
}

float linX1 = 50;
float linY1 = 0;
float linX2 = 200;
float linY2 = 300;

float posX, posY;

float a;
float a(float linX1, float linY1, float linX2, float linY2){
  float y, x, a;
  y = linY2 - linY1;
  x = linX2 - linX1;
  a = y/x;
  return a;
}

float b;
float b(float a, float linX1){
  float b;
  b = -a*linX1;
  return b;
}

float x;
float x(float a, float b, float posX, float posY){
  float x;
  x = (a*(posY - b)+posX) / (a*a + 1);
  return x;
}

float y;
float y(float a, float b, float posX, float posY){
  float y;
  y = a*(a*(posY - b)+posX) / (a*a + 1) + b;
  return y;
}

float kyori(float posX, float posY){
  float x1 = 0;
  float y1 = 0;
  float distance;
  
  distance = sqrt((posX - x1)*(posX - x1) + (posY - y1)*(posY - y1));
  return distance;
}

void draw(){
  background(100);
  line(150, 0, 150, 300);
  line(0, 150, 300, 150);
  posX = mouseX;
  posY = mouseY;
  line(linX1, linY1, linX2, linY2);
  
  a = a(linX1, linY1, linX2, linY2);
  b = b(a, linX1);
  x = x(a, b, posX, posY);
  y = y(a, b, posX, posY);
  
  text(a, 0, 20);
  text(b, 0, 40);
  text(x, 0, 60);
  text(y, 0, 80);
  text(kyori(posX, posY), 0, 100);
  
  line(x, y, posX, posY);
}
