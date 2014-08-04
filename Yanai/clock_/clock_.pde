void setup(){
  size(400, 400);
}

void draw(){
  float hx = 150;
    if (hour() < 10){
    hx = 175;
  }
  
  background(200, 200, 200);
  textSize(40);
  fill(255);
  text(":", 200, height/2 - 2);
  text(hour(), hx, height/2);
  text(minute(), 210, height/2);
}
