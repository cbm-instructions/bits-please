//Pong
byte posPlayer1; // min 1, max 14
byte posPlayer2;
byte posBallX;
byte posBallY;
short ballDirX;
short ballDirY;
byte scorePlayer1;
byte scorePlayer2;
byte pongSpeed;

// initialize Pong
void startPong() {
  posPlayer1 = 3;
  posPlayer2 = 12;
  posBallX = 7;
  posBallY = 5;
  ballDirX = 1;
  ballDirY = 1;
  scorePlayer1 = 0;
  scorePlayer2 = 0;
  drawCounter = 0;
  pongSpeed = 20;
  
  myFill(0);
  pongLoop();
}

// Pong's own loop
void pongLoop() {
  
    // Input handling
  
  reading[0] = digitalRead(LEFT);
  reading[1] = digitalRead(RIGHT);
  reading[2] = digitalRead(DOWN);
  reading[3] = digitalRead(TURN);
  for(int i = 0; i < 4; i++) {
    if (reading[i] != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
    }
    // here the debounce is allowing holding a button to go quick
    if ((millis() - lastDebounceTime[i]) > debounceDelay+5) {
      buttonState[i] = reading[i];
      if(i == 0 && buttonState[i] == HIGH) {
          posPlayer2 = max(1, posPlayer2 - 1);
        } else if(i == 1 && buttonState[i] == HIGH) {
          posPlayer1 = max(1, posPlayer1 - 1);
        } else if(i == 2 && buttonState[i] == HIGH) {
          posPlayer2 = min(14, posPlayer2 + 1);
        } else if(i == 3 && buttonState[i] == HIGH) {
          posPlayer1 = min(14, posPlayer1 + 1);
        }
    }
    
    lastButtonState[i] = reading[i];
  }

  // the ball moves
  if(drawCounter > pongSpeed) {
    byte result = processPhysics();
    switch(result) {
      case 1:
        scorePlayer1++;
        newBall(2); // ball for the other player
      break;
      case 2:
        scorePlayer2++;
        newBall(1);
      break;
    }
    drawCounter = 0;
  }
  drawCounter++;
  
  myFill(0);
  drawScore(strip_1.Color(80,80,80), true, true);
  drawGame();
  myShow();
  
  // is the game won?
  if(scorePlayer1 > 9) {
    gameOverPong(1);
  } else if(scorePlayer2 > 9) {
    gameOverPong(2);
  } else {
    pongLoop();
  }
}

// game over animation
void gameOverPong(byte player) {
  if(player == 2) {
    for(byte i = 0; i < 255; i++) {
      uint32_t color = strip_1.Color(random(255),random(255),random(255));
      myDraw(15, posPlayer2 - 1, color);
      myDraw(15, posPlayer2, color);
      myDraw(15, posPlayer2 + 1, color);
      drawScore(color, false, true);
      myShow();
    }
  } else if(player == 1) {
    for(byte i = 0; i < 255; i++) {
      uint32_t color = strip_1.Color(random(255),random(255),random(255));
      myDraw(0, posPlayer1 - 1, color);
      myDraw(0, posPlayer1, color);
      myDraw(0, posPlayer1 + 1, color);
      drawScore(color, true, false);
      myShow();
    }
  }
}

// scoring animation and initializing a new ball
void newBall(byte player) {
  
  myDraw(posBallX-ballDirX, posBallY-ballDirY, 0);
  myShow();
  
  if(player == 1) {
    for(byte i = 127; i > 0; i--) {
      byte val = sin(((float)i*2)/180) * 160 + 80;
      myDraw(posBallX, posBallY, strip_1.Color(val-80,val-80,val-80));
      drawScore(strip_1.Color(val,val,val), false, true);
      myShow();
    }
  } else if(player == 2) {
    for(byte i = 127; i > 0; i--) {
      byte val = sin(((float)i*2)/180) * 160 + 80;
      myDraw(posBallX, posBallY, strip_1.Color(val-80,val-80,val-80));
      drawScore(strip_1.Color(val,val,val), true, false);
      myShow();
    }
  }
  
  // direction
  if(player == 1) {
    posBallX = 8;
    posBallY = 5;
    ballDirX = -1;
    ballDirY = -1;
  } else {
    posBallX = 7;
    posBallY = 5;
    ballDirX = 1;
    ballDirY = 1;
  }
  
  pongSpeed = 18;
}

// draw the score with given color c for player1 and/or player2
void drawScore(uint32_t c, bool player1, bool player2) {
  // score player 1
  if(player1) {
    for(byte x = 0; x < 3; x++) {
      for(byte y = 0; y < 5; y++) {
        if(numbers[scorePlayer1][y][x]) {
          myDraw(5-x, y, c);
        } else {
          myDraw(5-x, y, 0);
        }
      }
    }
  }
  
  // score player 2
  if(player2) {
    for(byte x = 0; x < 3; x++) {
      for(byte y = 0; y < 5; y++) {
        if(numbers[scorePlayer2][y][x]) {
          myDraw(12-x, y, c);
        } else {
          myDraw(12-x, y, 0);
        }
      }
    }
  }
}

// draw paddles and ball
void drawGame() {
  
  myDraw(posBallX, posBallY, WHITE);
  
  // player 1
  myDraw(0, posPlayer1 - 1, WHITE);
  myDraw(0, posPlayer1, WHITE);
  myDraw(0, posPlayer1 + 1, WHITE);
  
  // player 2
  myDraw(15, posPlayer2 - 1, WHITE);
  myDraw(15, posPlayer2, WHITE);
  myDraw(15, posPlayer2 + 1, WHITE);
  
}

// process ball movement
byte processPhysics() {
  //hitting wall
  if(posBallY == 0) {
    ballDirY = 1;
  } else if(posBallY == 15) {
    ballDirY = -1;
  }
  
  if(ballDirX == 1) { // ball goes to the right
    if(posBallX == 14) { // and in hit range
      switch(ballDirY) { // depending on ball direction and relative position to paddle it will bounce in different directions
        case -1:
        switch(posBallY - posPlayer2 + 1) {
          case 3: ballDirX = -1; ballDirY = 1; break;
          case 2: ballDirX = -1; ballDirY = 0; pongSpeed--; break;
          case 1: 
          case 0: ballDirX = -1; break;
        }
        break;
        case 0:
        switch(posBallY - posPlayer2 + 1) {
          case 0: ballDirX = -1; ballDirY = -1; break;
          case 1: ballDirX = -1; ballDirY = 0; pongSpeed--; break;
          case 2: ballDirX = -1; ballDirY = 1; break;
        }
        break;
        case 1:
        switch(posBallY - posPlayer2 + 2) {
          case 0: ballDirX = -1; ballDirY = -1; break;
          case 1: ballDirX = -1; ballDirY = 0; pongSpeed--; break;
          case 2: 
          case 3: ballDirX = -1; break;
        }
        break;
      }
    }
  } else { // ball goes to the left
    if(posBallX == 1) { // and in hit range
      switch(ballDirY) {
        case -1:
        switch(posBallY - posPlayer1 + 1) {
          case 3: ballDirX = 1; ballDirY = 1; break;
          case 2: ballDirX = 1; ballDirY = 0; pongSpeed--; break;
          case 1: 
          case 0: ballDirX = 1; break;
        }
        break;
        case 0:
        switch(posBallY - posPlayer1 + 1) {
          case 0: ballDirX = 1; ballDirY = -1; break;
          case 1: ballDirX = 1; ballDirY = 0; pongSpeed--; break;
          case 2: ballDirX = 1; ballDirY = 1; break;
        }
        break;
        case 1:
        switch(posBallY - posPlayer1 + 2) {
          case 0: ballDirX = 1; ballDirY = -1; break;
          case 1: ballDirX = 1; ballDirY = 0; pongSpeed--; break;
          case 2: 
          case 3: ballDirX = 1; break;
        }
        break;
      }
    }
  }
  
  // change position
  posBallX += ballDirX;
  posBallY += ballDirY;
  
  if(posBallX == 15) { // player 1 scored
    return 1;
  } else if(posBallX == 0) { // player 2 scored
    return 2;
  } else {
    pongSpeed = max(2,pongSpeed - 1);
    return 0;
  }
}
