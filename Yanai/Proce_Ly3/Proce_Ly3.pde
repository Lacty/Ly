float x, y, x2, y2, x3, y3;

void setup() {
   size(300, 300);
   x = width / 2 - 100;
   y = height / 2 + 50;
   
   x2 = width / 2 - 100;
   y2 = height / 2 + 50;
   
   x3 = width / 2 - 100;
   y3 = height / 2 + 50;
}

void draw() {
   background(100, 100, 100);
   textSize(30);
   fill(255);
   x += 0.1 * (mouseX - x);
   y += 0.1 * (mouseY - y);
   text("Ly", x, y);


   x2 += 0.06 * (mouseX - x2);
   y2 += 0.06 * (mouseY - y2);
   text("Ly", x2, y2);
   
   x3 += 0.03 * (mouseX - x3);
   y3 += 0.03 * (mouseY - y3);
   text("Ly", x3, y3);
}
