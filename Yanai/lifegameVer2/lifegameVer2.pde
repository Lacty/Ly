int windowSize = 400;
int sideCells = 50;
int cellSize = windowSize / sideCells;
int FPS = 1;
float rand;

boolean[][] cell = new boolean[sideCells][sideCells];


void setup(){
  size(windowSize, windowSize);
  frameRate(FPS);
  for (int y = 0; y < sideCells; y++){
    for (int x = 0; x < sideCells; x++){
      rand = random(50);
      if (rand < 2){
        cell[y][x] = true;
      }else{
        cell[y][x] = false;
      }
    }
  }
}

void update(){
  for (int y = 0; y < sideCells; y++){
    for (int x = 0; x < sideCells; x++){
      if (!cell[y][x]){
        
      }
    }
  }
}

void draw(){
  background(100);
  
  update();
  
  for (int y = 0; y < sideCells; y++){
    for (int x = 0; x < sideCells; x++){
      if (cell[y][x]){
        rect(x*cellSize, y*cellSize, cellSize, cellSize);
      }
    }
  }
}
