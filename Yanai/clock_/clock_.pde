float hx = 150;
int min;
int min1,min10;
int sec;
float sec_move;

void setup(){
  size(400, 400);
  //sec_move=second()*PI/30;
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
  
  sec = second();
  sec_move=second()*PI/30;
  //sec_move += PI/30/60;
  if(sec < 10)
  text(sec, width/2 + cos(sec_move-PI/2) * 120, height/2 + sin(sec_move-PI/2) * 120);
  if(sec >= 10)
  text(sec, width/2 - 20 + cos(sec_move-PI/2) * 120, height/2 + sin(sec_move-PI/2) * 120);
}
