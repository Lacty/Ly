void setup(){
  size(300, 300);
}

float linX1 = 50;
float linY1 = 0;
float linX2 = 150;
float linY2 = 300;

PVector vA, vB, vP;
PVector AB, AP;

float ABdis;
float ABdis(float linX1, float linY1, float linX2, float linY2){
  float PointX, PointY;
  float ABdis;
  PointX = linX1 - linX2;
  PointY = linY1 - linY2;
  ABdis = sqrt(PointX*PointX + PointY*PointY);
  return ABdis;
}

float menseki;
float menseki(PVector AB, PVector AP){
  float menseki;
  menseki = AB.x*AP.y - AB.y*AP.x;
  return menseki;
}

float dist;

void draw(){
  background(100);
  line(150, 0, 150, 300);
  line(0, 150, 300, 150);
  line(linX1, linY1, linX2, linY2);
  
  vA = new PVector(linX1, linY1);
  vB = new PVector(linX2, linY2);
  vP = new PVector(mouseX, mouseY);
  
  AB = new PVector((vB.x-vA.x),(vB.y-vA.y));
  AP = new PVector((vP.x-vA.x),(vP.y-vA.y));
  
  ABdis = ABdis(linX1, linY1, linX2, linY2);
  text("ABdis", 0, 20); text(ABdis, 30, 20);
  
  menseki = abs(menseki(AB, AP));
  text("menseki", 0, 40); text(menseki, 45, 40);
  
  dist = menseki/ABdis;
  text("dist", 0, 60); text(dist, 20, 60);
}
