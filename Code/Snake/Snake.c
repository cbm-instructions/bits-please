//Snake
byte snakeP1[SIZE*SIZE];
byte snakeP2[SIZE*SIZE];
byte lengthP1;
byte lengthP2;
//Directions: 1 = up, 2 = right, 3 = down, 4 = left
byte directionP1;
byte directionP2;
byte xP1;
byte yP1;
byte xP2;
byte yP2;
byte appleX;
byte appleY;
bool gameOverSnakeFlag;
byte lastDirP1;
byte lastDirP2;
byte snakeSpeed;

// initialize snake
void startSnake() {
  // Start position P1:
  xP1 = 2;
  yP1 = 0;
  directionP1 = 3;
  lengthP1 = 4;
  snakeP1[0] = 3;
  snakeP1[1] = 3;
  snakeP1[2] = 3;
  snakeP1[3] = 3;
  
  // Start position P2:
  xP2 = 11;
  yP2 = 13;
  directionP2 = 1;
  lengthP2 = 4;
  snakeP2[0] = 1;
  snakeP2[1] = 1;
  snakeP2[2] = 1;
  snakeP2[3] = 1;
  
  snakeSpeed = 30;
  
  gameOverSnakeFlag = false;
  drawCounter = 0;
  
  generateApple();
  
  snakeDraw(GREEN, YELLOW, 0);
  snakeLoop();
}

// snake's own loop
void snakeLoop() {
  // Input handling
  reading[0] = digitalRead(DOWN);
  reading[1] = digitalRead(TURN);
  reading[2] = digitalRead(LEFT);
  reading[3] = digitalRead(RIGHT);
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
        
        if(i == 0 && buttonState[i] == HIGH) {
          turnLeft(1);
        } else if(i == 1 && buttonState[i] == HIGH) {
          turnRight(2);
        } else if(i == 2 && buttonState[i] == HIGH) {
          turnRight(1);
        } else if(i == 3 && buttonState[i] == HIGH) {
          turnLeft(2);
        }
      }
    }
    
    lastButtonState[i] = reading[i];
  }
  
  // the snakes move on
  if(drawCounter > 40) {
    snakeMove();
    
    lastDirP1 = directionP1;
    lastDirP2 = directionP2;
    
    // a player will loose if either he crashes into another snake, himself or a wall
    if(snakeCollision(xP1, yP1, 1) > 0 || outOfBounds(1)) {
      if(snakeCollision(xP2, yP2, 2) > 0 || outOfBounds(2)) {
        // both lost? wtf
        gameOverSnake(3);
      } else {
        gameOverSnake(1);
      }
    } else if(snakeCollision(xP2, yP2, 2) > 0 || outOfBounds(2)) {
      gameOverSnake(2);
    } else {
      snakeDraw(GREEN, YELLOW, 0);
    }
    drawCounter = 0;
  }
  drawCounter++;
  delay(snakeSpeed/2); // the speed will increase every two apples
  if(!gameOverSnakeFlag) {
    snakeLoop();
  }
}

// hits given player a wall?
bool outOfBounds(byte player) {
  if(player == 1) {
    if(xP1 > 15 || xP1 < 0 || yP1 > 15 || yP1 < 0) {
      return true;
    }
  } else if(player == 2) {
    if(xP2 > 15 || xP2 < 0 || yP2 > 15 || yP2 < 0) {
      return true;
    }
  }
  
  return false;
}

void gameOverSnake(byte player) {
  gameOverSnakeFlag = true;
  switch(player) {
    case 3:
      for(int i = 0; i < 100; i++) {
        snakeDraw((i % 2 == 0) ? YELLOW : GREEN, (i % 2 == 1) ? YELLOW : GREEN, strip_1.Color(random(256),random(256),random(256)));
        delay(20);
      }
      break;
    case 2:
      for(int i = 0; i < 100; i++) {
        snakeDraw(GREEN, (i % 2 == 0) ? YELLOW : RED, strip_1.Color(i*2,i*2,i*2));
        delay(20);
      }
      break;
    case 1:
      for(int i = 0; i < 100; i++) {
        snakeDraw((i % 2 == 0) ? GREEN : RED, YELLOW, strip_1.Color(i*2,i*2,i*2));
        delay(20);
      }
      break;
  }
}

void snakeMove() {
  // Eat apples
  if(snakeCollision(appleX, appleY, 0) == 1) {
    lengthP1++;
    snakeSpeed--; // the delay between loop()-calls decreases
    generateApple();
  } else if(snakeCollision(appleX, appleY, 0) == 2) {
    lengthP2++;
    snakeSpeed--;
    generateApple();
  }
  
  // The snake moves on
  switch(directionP1) {
    case 1: yP1--; break;
    case 2: xP1++; break;
    case 3: yP1++; break;
    case 4: xP1--; break;
  }
  for(byte i = lengthP1 - 1; i > 0; i--) {
    snakeP1[i] = snakeP1[i-1];
  }
  snakeP1[0] = directionP1;
  
  switch(directionP2) {
    case 1: yP2--; break;
    case 2: xP2++; break;
    case 3: yP2++; break;
    case 4: xP2--; break;
  }
  for(byte i = lengthP2 - 1; i > 0; i--) {
    snakeP2[i] = snakeP2[i-1];
  }
  snakeP2[0] = directionP2;
}

void turnLeft(byte player) {
  if(player == 1) {
    switch(lastDirP1) { // so multiple presses on left or right don't let you turn backwards or to the other direction
      case 4: directionP1 = 3; break;
      case 3: directionP1 = 2; break;
      case 2: directionP1 = 1; break;
      case 1: directionP1 = 4; break;
    }
  }
  
  if(player == 2) {
    switch(lastDirP2) {
      case 4: directionP2 = 3; break;
      case 3: directionP2 = 2; break;
      case 2: directionP2 = 1; break;
      case 1: directionP2 = 4; break;
    }
  }
}

void turnRight(byte player) {
  if(player == 1) {
    switch(lastDirP1) {
      case 4: directionP1 = 1; break;
      case 3: directionP1 = 4; break;
      case 2: directionP1 = 3; break;
      case 1: directionP1 = 2; break;
    }
  }
  
  if(player == 2) {
    switch(lastDirP2) {
      case 4: directionP2 = 1; break;
      case 3: directionP2 = 4; break;
      case 2: directionP2 = 3; break;
      case 1: directionP2 = 2; break;
    }
  }
}

void generateApple() {
  do {
    appleX = random(16);
    appleY = random(16);
  } // find a place where no snake is
  while(snakeCollision(appleX, appleY, 0) > 0);
}

// checks if given player at his head position x and y collides with himself or another snake
byte snakeCollision(byte x, byte y, byte player) {
  byte tempX = xP1;
  byte tempY = yP1;
  byte i = 0;
  if(player == 1) {
    switch(snakeP1[i]) {
      case 4: tempX++; break;
      case 3: tempY--; break;
      case 2: tempX--; break;
      case 1: tempY++; break;
    }
    i = 1; // so he cannot collide with his own head
  } else {
    i = 0;
  }
  for(; i <= lengthP1; i++) { // the snake consists of an array of directions where the actual shape can be reconstructed through iteration
    if(tempX == x && tempY == y) {
      return 1;
    }
    switch(snakeP1[i]) {
      case 4: tempX++; break;
      case 3: tempY--; break;
      case 2: tempX--; break;
      case 1: tempY++; break;
    }
  }
  
  // same procedure for player 2
  tempX = xP2;
  tempY = yP2;
  i = 0;
  if(player == 2) {
    switch(snakeP2[i]) {
      case 4: tempX++; break;
      case 3: tempY--; break;
      case 2: tempX--; break;
      case 1: tempY++; break;
    }
    i = 1;
  } else {
    i = 0;
  }
  for(; i <= lengthP2; i++) {
    if(tempX == x && tempY == y) {
      return 2;
    }
    switch(snakeP2[i]) {
      case 4: tempX++; break;
      case 3: tempY--; break;
      case 2: tempX--; break;
      case 1: tempY++; break;
    }
  }
  
  return 0;
}

// draws player 1 with color c1 and player 2 with c2 and given background color
void snakeDraw(uint32_t c1, uint32_t c2, uint32_t background) {
  myFill(background);
  // Apple
  myDraw(appleX, appleY, RED);
  // Player 1
  byte tempX = xP1;
  byte tempY = yP1;
  myDraw(tempX, tempY, c1);
  // iterate through snake chain
  for(byte i = 0; i < lengthP1; i++) {
    switch(snakeP1[i]) {
      case 4: tempX++; break;
      case 3: tempY--; break;
      case 2: tempX--; break;
      case 1: tempY++; break;
    }
    myDraw(tempX, tempY, c1);
  }
  
  // Player 2
  tempX = xP2;
  tempY = yP2;
  myDraw(tempX, tempY, c2);
  for(byte i = 0; i < lengthP2; i++) {
    switch(snakeP2[i]) {
      case 4: tempX++; break;
      case 3: tempY--; break;
      case 2: tempX--; break;
      case 1: tempY++; break;
    }
    myDraw(tempX, tempY, c2);
  }
  
  myShow();
}
