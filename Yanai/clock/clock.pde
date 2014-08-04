void setup(){
  size(600, 250);
}

void draw(){
  background(200, 200, 200);
  textSize(80);
  fill(255);
  text(second(),second()*8.4, height/2 + 110);
  text(minute(),minute()*8.4, height/2 + 30);
  text(hour(),hour()*21.5, height/2 - 47);
}
