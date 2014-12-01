int windowSize = 400;
int sideCells = 100;
int cellSize = windowSize / sideCells;
int FPS = 1;

boolean[] bfield_x = new boolean[sideCells];
boolean[] bfield_y = new boolean[sideCells];
int[] ifield_x = new int[sideCells];
int[] ifield_y = new int[sideCells];


void setup(){
  size(windowSize, windowSize);
  frameRate(FPS);
    for (int i = 0; i < sideCells; i++){
    bfield_x[i] = true;
    bfield_y[i] = true;
  }
  for(int i = 0; i < sideCells; i++){
    ifield_x[i] = i*cellSize;
    ifield_y[i] = i*cellSize;
  }
}

void draw(){
  background(100);
  //println(ifield_x);
  
  for (int i = 0; i < sideCells*sideCells; i++){
    if ((bfield_x[i/sideCells])&&(bfield_y[i%sideCells])){
      rect(ifield_x[i/sideCells], ifield_y[i%sideCells], cellSize, cellSize);
    }
  }
}
