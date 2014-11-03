float angle = 0;

void setup(){
  size(200, 200, P3D);
}

void draw(){
  angle += 0.01;
  background(100, 100, 100);
  translate(100, 100, 0);
  rotateX(angle);
  rotateY(angle);
  noFill();
  box(60);
  //lights();
  //sphere(30);
  textSize(30);
  text("Ly", -15, 10);
}
