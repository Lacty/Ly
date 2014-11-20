void setup(){
  size(400, 400, P3D);
}

float angle = 0;

void shikaku(PVector v0, PVector v1, PVector v2, PVector v3){
  vertex(v0.x, v0.y, v0.z);
  vertex(v1.x, v1.y, v1.z);
  vertex(v3.x, v3.y, v3.z);
  vertex(v1.x, v1.y, v1.z);
  vertex(v2.x, v2.y, v2.z);
  vertex(v3.x, v3.y, v3.z);
}

void draw(){
  background(100);
  translate(width/2, height/2);
  angle += 0.01;
  rotateY(angle);
  rotateX(angle);
  for (float theta = 0; theta < 2*PI; theta += PI/6){
    beginShape(TRIANGLES);
    PVector v0 = new PVector(100*cos(theta), 100*sin(theta), 0);
    PVector v1 = new PVector(100*cos(theta+PI/6), 100*sin(theta+PI/6), 0);
    PVector v2 = new PVector(100*cos(theta+PI/6), 100*sin(theta+PI/6), -100);
    PVector v3 = new PVector(100*cos(theta), 100*sin(theta), -100);
    shikaku(v0,v1,v2,v3);
    endShape();
  }
}
