void setup(){
  size(300, 300);
}

float linX1 = 50;
float linY1 = 0;
float linX2 = 200;
float linY2 = 300;

float posX, posY;
float x, y;

float kyori(float lineX1, float lineY1, float lineX2, float lineY2,
            float posX, float posY){
  float a, b, c;
  float dist;
  float root;
  
  a = lineY1 - lineY2;
  b = lineX2 - lineX1;
  c = (-b*lineY1)+(-a*lineX1);
  root = sqrt(a*a + b+b);
  
  if (root == 0.0){
    return -1.0;
  }
  
  dist = ((a*posX)+(b*posY)+c)/root;
  
  if (dist < 0.0){
    dist = -dist;
  }
  
  return dist;
}

void draw(){
  background(100);
  line(150, 0, 150, 300);
  line(0, 150, 300, 150);
  posX = mouseX;
  posY = mouseY;
  line(linX1, linY1, linX2, linY2);
  text(kyori(linX1, linY1, linX2, linY2, posX, posY), 0, 20);
}
