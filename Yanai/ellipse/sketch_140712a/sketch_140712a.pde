float cx, cy, r;
color c = (300);
boolean klick = false;
float x, y;

void setup() {
  size(300, 300);
  cx = width/2;
  cy = height/2;
  r = 100;
}

void draw() {
  background(100, 100, 100);
  fill(c);
  ellipse(cx, cy, 2*r, 2*r);
    if ((mouseX - cx)*(mouseX - cx)+(mouseY - cy)*(mouseY - cy) < r*r) {
    c = 255;
  }
  else {
    c = 300;
  }
}

void mousePressed() {
  x = cx - mouseX;
  y = cy - mouseY;
  if ((mouseX - cx)*(mouseX - cx)+(mouseY - cy)*(mouseY - cy) < r*r) {
    c = 255;
    klick = true;
  }
  println("mousePressed");
}
void mouseDragged() {
    if (klick){
    cx = mouseX + x;
    cy = mouseY + y;
  }
  println("mouseDragged");
}
void mouseReleased() {
  println("mouseReleased");
  klick = false;
}
