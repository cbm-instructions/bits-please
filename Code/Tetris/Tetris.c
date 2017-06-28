//Tetris building blocks
byte shapes[8][4][16]={
// i
{ {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{1, 0, 0,0,1, 0,  0, 0,1, 0,  0, 0, 1,0,  0, 0 },
{ 1, 1, 1, 1,0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0 },
{ 1,0, 0, 0, 1,0,  0, 0,1, 0,  0, 0, 1,0,  0, 0 } },
// s
{ { 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 } },
// z
{ { 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 } },
// j
{ { 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
// o
{ { 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
// l
{ { 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
// _|
{ { 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 } },
// t
{ { 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1,0, 0, 0, 1, 1,0, 0,1, 0, 0, 0, 0, 0, 0, 0 } } };

byte current_block;

//Tetris
byte level;
byte blockType;
byte turnState;
byte blockX;
byte blockY;
byte gameOverTetrisFlag;
byte tetrismap[SIZE][SIZE];
int counter;

// initialize tetris
void startTetris() {
  level = 20;
  counter = 0;
  gameOverTetrisFlag = 0;
  newTetrismap();
  newblock();
  paintTetrismap();
  tetrisLoop();
}

// tetris' own loop
void tetrisLoop() {
  // Input handling
  
  reading[0] = digitalRead(RIGHT);
  reading[1] = digitalRead(LEFT);
  reading[2] = digitalRead(DOWN);
  reading[3] = digitalRead(TURN);
  for(int i = 0; i < 4; i++) {
    if (reading[i] != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:
  
      // if the button state has changed:
      if (reading[i] != buttonState[i]) {
        buttonState[i] = reading[i];
        
        if(i == 3 && buttonState[i] == HIGH) {
          turn();
        }
      }
      
      if(i == 2 && buttonState[i] == HIGH) {
        down();
      } else if(i == 0 && buttonState[i] == HIGH) {
        left();
      } else if(i == 1 && buttonState[i] == HIGH) {
        right();
      }
    }
    
    lastButtonState[i] = reading[i];
  }
  
  // next tick is happening
  counter++;
  if(counter > level) {
    down();
    counter = 0;
  }
  paintTetrismap();
  delay(10);
  if(gameOverTetrisFlag) {
    gameoverTetris();
  } else {
    tetrisLoop();
  }
}

// turn the block
void turn() {
  byte tempturnState = turnState;
  turnState = (turnState + 1) % 4;
  if (collide(blockX, blockY, blockType, turnState) == 0) {
	  clearActiveBlock();
	  addBlock(blockX, blockY, blockType, turnState, 1);
	}
  if (collide(blockX, blockY, blockType, turnState) == 1) {
    turnState = tempturnState;
  }
}

// move block to the left
void left() {
  if(blockX>0) {
    if (collide(blockX - 1, blockY, blockType, turnState) == 0) {
      clearActiveBlock();
      blockX = blockX - 1;
      addBlock(blockX, blockY, blockType, turnState, 1);
    }
  }
}

// move block to the right
void right() {
  if(blockX<15) {
    if (collide(blockX + 1, blockY, blockType, turnState) == 0) {
      clearActiveBlock();
      blockX = blockX + 1;
      addBlock(blockX, blockY, blockType, turnState, 1);
    }
  }
}

// move block down (quicker)
void down() {
  if (collide(blockX, blockY + 1, blockType, turnState) == 0) {
    clearActiveBlock();
    blockY = blockY + 1;
    addBlock(blockX, blockY, blockType, turnState, 1);
  }
  else if (collide(blockX, blockY + 1, blockType, turnState) == 1) {
    clearActiveBlock();
    addBlock(blockX, blockY, blockType, turnState, random(2,8));
    delline();
    newblock();
  }
}

// checks if there are lines to delete
void delline() {
  byte linesToDelete[16];
  byte deletions = 0;
  for(byte y = 0; y < SIZE; y++) {
    byte countBlocks = 0;
    for(byte x = 0; x < SIZE; x++) {
      if(tetrismap[x][y] > 0) {
        countBlocks++;
      }
    }
    if(countBlocks == 16) { // full line
      linesToDelete[y] = 2;
      deletions++;
    } else if(countBlocks > 0) {
      linesToDelete[y] = 1;
    } else {
      linesToDelete[y] = 0;
    }
  }
  
  if(deletions > 0) {
    // animation
    for(byte count = 0; count < 5; count++) {
      for(byte y = 0; y < SIZE; y++) {
        if(linesToDelete[y] == 2) {
          for(byte x = 0; x < SIZE; x++) {
            tetrismap[x][y] = 1;
          }
        }
      }
      paintTetrismap();
      delay(100);
      for(byte y = 0; y < SIZE; y++) {
        if(linesToDelete[y] == 2) {
          for(byte x = 0; x < SIZE; x++) {
            tetrismap[x][y] = 0;
          }
        }
      }
      paintTetrismap();
      delay(100);
    }
    // move blocks down
    for(int i = 0; i < deletions; i++) {
      for(int y = SIZE - 1; y >= 0 ; y--) {
        if(linesToDelete[y] == 2) {
          for(int a = y; a > 0; a--) {
            for(byte x = 0; x < SIZE; x++) {
              tetrismap[x][a] = tetrismap[x][a-1];
            }
            linesToDelete[a] = linesToDelete[a-1];
          }
          // make it harder
          level = max(0,level - 1);
        }
      }
    }
  }
}

// consolidate block to map
void addBlock(byte x, byte y, byte blockType, byte turnState, byte status) {
  byte j = 0;
  for (byte a = 0; a < 4; a++) {
    for (byte b = 0; b < 4; b++) {
      if (tetrismap[x + b][y + a] == 0 && shapes[blockType][turnState][j] == 1) {
        tetrismap[x + b ][y + a] = status;
      }
      j++;
    }
  }
}

// removes active block from tetrismap
void clearActiveBlock() {
  for (byte x = 0; x < 4; x++) {
    for (byte y = 0; y < 4; y++) {
      if(tetrismap[blockX + x][blockY + y] == 1) {
        tetrismap[blockX + x][blockY + y] = 0;
      }
    }
  }
}

// collision detection
byte collide(byte x, byte y, byte blockType, byte turnState) {
  for (byte i = 0; i < 4; i++) {
    for (byte k = 0; k < 4; k++) {
      if (shapes[blockType][turnState][i * 4 + k] == 1) {
        if( (tetrismap[x + k][y + i] > 1) || // hits another block?
            (y+i > 15) || // hits the floor?
            (x+k > 15) ) // hits the wall?
        {
          return 1;
        }
      }
    }
  }
	return 0;
}

// clears tetrismap
void newTetrismap() {
  for (byte i = 0; i < SIZE; i++) {
    for (byte k = 0; k < SIZE; k++) {
      tetrismap[i][k] = 0;
    }
  }
}

// add a new random block at the top
void newblock() {
  blockType = (byte) ((random()) % 8);
  turnState = (byte) ((random()) % 4);
  blockX = 6;
  blockY = 0;
  addBlock(blockX, blockY, blockType, turnState, 1);
  if(collide(blockX, blockY, blockType, turnState) == 1) {
    gameOverTetrisFlag = 1;
  }
}

// paint the map to the LEDs
void paintTetrismap() {
  for (byte x = 0; x < SIZE; x++) {
    for (byte y = 0; y < SIZE; y++){
      switch (tetrismap[x][y]) {
      case 7:
        myDraw(x,y,MAGENTA);
        break;
      case 6:
        myDraw(x,y,TEAL);
        break;
      case 5:
        myDraw(x,y,GREEN);
        break;
      case 4:
        myDraw(x,y,YELLOW);
        break;
      case 3:
        myDraw(x,y,BLUE);
        break;
      case 2:
        myDraw(x,y,RED);
        break;
      case 1:
        myDraw(x,y,WHITE);
        break;
      default:
	      myDraw(x,y,0);
      }
    }
  }
  myShow();
}

// game over animation
void gameoverTetris() {
  for(byte count = 0; count < 10; count++) {
    for (byte x = 0; x < SIZE; x++) {
      for (byte y = 0; y < SIZE; y++){
        if(tetrismap[x][y] != 0) {
          tetrismap[x][y] = 2;
        }
      }
    }
    paintTetrismap();
    delay(200);
    for (byte x = 0; x < SIZE; x++) {
      for (byte y = 0; y < SIZE; y++){
        if(tetrismap[x][y] != 0) {
          tetrismap[x][y] = 1;
        }
      }
    }
    paintTetrismap();
    delay(200);
  }
}
