int MODE = 0;
int mon;
int mon1,mon10;
int day;
int day1,day10;

void setup(){
  size(600, 250);
  mon = month();
  mon10 = mon/10;
  mon1 = mon%10;
  day = day();
  day10 = day/10;
  day1 = day%10;
}

void draw(){
  background(200, 200, 200);
  fill(255);
  if (count == second()){
    MODE = 0;
  }
  switch (MODE){
    case 0:
    {
      textSize(80);
      text(second(),second()*8.4, height/2 + 110);
      text(minute(),minute()*8.4, height/2 + 30);
      text(hour(),hour()*21.5, height/2 - 47);
    }break;
    
    case 1:
    {
      textSize(60);
      text(year(),width/2-180,height/2+26);
      text("/",width/2-35,height/2+23);
      text(mon10,width/2-10,height/2+26);
      text(mon1,width/2+30,height/2+26);
      text("/",width/2+60,height/2+23);
      text(mon10,width/2+85,height/2+26);
      text(mon1,width/2+125,height/2+26);
    }
  }
}

int count;

void mousePressed(){
  MODE = 1;
  count = second()+2;
  println(count);
}
