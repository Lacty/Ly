float hx = 150;
int min;
int min1,min10;

void setup(){
  size(400, 400);
}

void draw(){
  if (hour() < 10){
    hx = 175;
  }
  
  min = minute();
  min10 = min/10;
  min1 = min%10;
  
  background(200, 200, 200);
  textSize(40);
  fill(255);
  text(":", 200, height/2 - 2);
  text(hour(), hx, height/2);
  text(min10, 210, height/2);
  text(min1, 235, height/2);
}
