float cx, cy, r;
float rx, ry, rr;
float in_x, in_y, in_r;

boolean isCollision(float mx, float my){
  float dx = mx - cx;
  float dy = my - cy;
  
  return dx*dx + dy*dy < rr*rr;
}

void setup() {
  size (400, 400);
  cx = width/2;
  cy = height/2;
  rx = width/2;
  ry = height/2;
  r = 130;
  in_r = 30;
  rr = 100;
}

void draw() {
  background(100);
  ellipse(cx, cy, 2*r, 2*r);
  ellipse(rx, ry, 2*rr, 2*rr);
  
  if (isCollision(mouseX, mouseY)){
    in_x = mouseX;
    in_y = mouseY;
  ellipse(in_x, in_y, 2*in_r, 2*in_r);
  }
  else{
    in_x = 0;
    in_y = 0;
    ellipse(in_x, in_y, 2*in_r, 2*in_r);
  }
  
}
