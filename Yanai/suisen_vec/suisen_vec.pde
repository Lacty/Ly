void setup(){
  size(300, 300);
}

float linX1 = 50;
float linY1 = 0;
float linX2 = 150;
float linY2 = 300;

float qx;
float qy;

float Avec;
float Avec(float linX1, float linY1, float linX2, float linY2){
  float PointX, PointY;
  float Avec;
  PointX = linX1 - linX2;
  PointY = linY1 - linY2;
  Avec = sqrt(PointX*PointX + PointY*PointY);
  return Avec;
}

float Bvec;
float Bvec(float qx, float qy, float linX1, float linY1){
  float PointX, PointY;
  float Bvec;
  PointX = linX1 - qx;
  PointY = linY1 - qy;
  Bvec = sqrt(PointX*PointX + PointY*PointY);
  return Bvec;
}

float ABcos;
float ABcos(float qx, float qy, float linX1, float linY1, float linX2, float linY2){
  float PointX1, PointY1;
  float PointX2, PointY2;
  float ab;//ue
  float AB;//sita
  PointX1 = linX1 - linX2;
  PointY1 = linY1 - linY2;
  PointX2 = linX1 - qx;
  PointY2 = linY1 - qy;
  ab = PointX1*PointX2 + PointY1*PointY2;
  AB = sqrt(PointX1*PointX1 + PointY1*PointY1)*sqrt(PointX2*PointX2 + PointY2*PointY2);
  ABcos = ab/AB;
  return ABcos;
}

void draw(){
  background(100);
  line(150, 0, 150, 300);
  line(0, 150, 300, 150);
  line(linX1, linY1, linX2, linY2);
  
  qx = mouseX;
  qy = mouseY;
  
  Avec = Avec(linX1, linY1, linX2, linY2);
  text("Avec", 0, 20); text(Avec, 30, 20);
  
  Bvec = Bvec(qx, qy, linX1, linY1);
  text("Bvec", 0, 40); text(Bvec, 30, 40);
  
  ABcos = ABcos(qx, qy, linX1, linY1, linX2, linY2);
  text("ABcos", 0, 60); text(ABcos, 40, 60);
}
