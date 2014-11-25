float angle = 0;
float move = 1;
float x;

void setup(){
  size(200, 200, P3D);
}

void draw(){
  angle += 0.01;
  x += move;
  background(100, 100, 100);
  translate(100, 100, 0);
  rotateX(angle);
  rotateY(angle);
  noFill();
  box(60);
  fill(200, 130, 200);
  textSize(30);
  if (x > 0){
    move *= -1;
  }
  else if (x < -30){
    move *= -1;
  }
  text("Ly", x, 10);
}
