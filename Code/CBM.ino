// Complete programming of the PlayTable by Bits Please for CBM SS 2017
// Demomodus, Controls
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6
#define SIZE 16
#define WHITE strip_1.Color(255,255,255)
#define RED strip_1.Color(255,0,0)
#define YELLOW strip_1.Color(255,255,0)
#define GREEN strip_1.Color(0,255,0)
#define TEAL strip_1.Color(0,255,255)
#define BLUE strip_1.Color(0,0,255)
#define MAGENTA strip_1.Color(255,0,255)
#define MATRIX_GREEN strip_1.Color(0,253,0)
#define RIGHT 8
#define LEFT 10
#define DOWN 11
#define TURN 9

//Image Code colors
#define MARIO_RED strip_1.Color(255,10,10)
#define MARIO_BLUE strip_1.Color(0,0,255)
#define MARIO_BROWN strip_1.Color(51,25,0)
#define MARIO_HAUT strip_1.Color(255,178,102)
#define MARIO_KNOEPFE strip_1.Color(255,255,0)
//Image Stern colors
#define MARIO_STERN_INNENGELB strip_1.Color(255,255,51)

Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(128, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(128, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(128, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_4 = Adafruit_NeoPixel(128, 7, NEO_GRB + NEO_KHZ800);

// Images
byte image_pong[16][16]={
  {0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0},
  {0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0},
  {0,0,0,1,0,1,0,0,0,0,1,1,1,0,0,0},
  {0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0},
  {0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

byte image_tetris[16][16]={
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0},
  {0,0,4,0,0,7,0,3,3,0,5,3,3,3,7,7},
  {2,4,4,3,7,7,0,3,6,5,5,4,4,3,7,6},
  {2,4,3,3,4,7,0,6,6,5,4,4,5,5,7,6},
  {2,2,3,4,4,4,0,6,2,2,2,2,5,5,6,6}
};

byte image_snake[16][16]={
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
  {0,0,0,0,0,0,2,2,0,3,0,0,0,0,0,0},
  {0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

byte image_mario[16][16]={
  {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
  {0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
  {0,0,0,0,2,2,2,4,4,3,4,0,0,0,0,0}, // 1 Rot
  {0,0,0,2,4,2,4,4,4,3,4,4,4,0,0,0}, // 2 Braun
  {0,0,0,2,4,2,2,4,4,4,3,4,4,4,0,0}, // 3 Schwarz
  {0,0,0,0,2,4,4,4,4,3,3,3,3,0,0,0}, // 4 Gelb/Hautfarben
  {0,0,0,0,0,4,4,4,4,4,4,0,0,0,0,0}, // 5 Blau
  {0,0,0,0,1,1,5,1,1,5,1,1,0,0,0,0},
  {0,0,0,1,1,1,5,1,1,5,1,1,1,0,0,0},
  {0,0,1,1,1,1,5,5,5,5,1,1,1,1,0,0},
  {0,0,4,4,1,5,8,5,5,8,5,1,4,4,0,0}, //8 Knoepfe
  {0,0,4,4,4,5,5,5,5,5,5,4,4,4,0,0},
  {0,0,4,4,5,5,5,5,5,5,5,5,4,4,0,0},
  {0,0,0,0,5,5,5,0,0,5,5,5,0,0,0,0},
  {0,0,0,2,2,2,0,0,0,0,2,2,2,0,0,0},
  {0,0,2,2,2,2,0,0,0,0,2,2,2,2,0,0}
}; 

byte image_mario_stern[16][16]={
  {0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0}, //3 Schwarz
  {0,0,0,0,0,0,3,7,7,3,0,0,0,0,0,0}, //7 Hautfarben Gelb
  {0,0,0,0,0,0,3,7,7,3,0,0,0,0,0,0},
  {0,0,0,0,0,3,7,7,7,7,3,0,0,0,0,0},
  {3,3,3,3,3,3,7,7,7,7,3,3,3,3,3,3},
  {3,7,7,7,7,7,7,7,7,7,7,7,7,7,7,3}, 
  {0,3,7,7,7,7,3,7,7,3,7,7,7,7,3,0},
  {0,0,3,7,7,7,3,7,7,3,7,7,7,3,0,0},
  {0,0,0,3,7,7,3,7,7,3,7,7,3,0,0,0},
  {0,0,0,3,7,7,3,7,7,3,7,7,3,0,0,0},
  {0,0,3,7,7,7,7,7,7,7,7,7,7,3,0,0},
  {0,0,3,7,7,7,7,7,7,7,7,7,7,3,0,0},
  {0,3,7,7,7,7,7,3,3,7,7,7,7,7,3,0},
  {0,3,7,7,7,3,3,0,0,3,3,7,7,7,3,0},
  {3,7,7,3,3,0,0,0,0,0,0,3,3,7,7,3},
  {3,3,3,0,0,0,0,0,0,0,0,0,0,3,3,3}
};

// numbers which are displayed
byte numbers[11][5][3] = {
  { {1,1,1},
    {1,0,1},
    {1,0,1},
    {1,0,1},
    {1,1,1}},
    
  { {0,1,0},
    {0,1,0},
    {0,1,0},
    {0,1,0},
    {0,1,0}},
    
  { {1,1,1},
    {0,0,1},
    {1,1,1},
    {1,0,0},
    {1,1,1}},
    
  { {1,1,1},
    {0,0,1},
    {1,1,1},
    {0,0,1},
    {1,1,1}},
    
  { {1,0,1},
    {1,0,1},
    {1,1,1},
    {0,0,1},
    {0,0,1}},
    
  { {1,1,1},
    {1,0,0},
    {1,1,1},
    {0,0,1},
    {1,1,1}},
    
  { {1,1,1},
    {1,0,0},
    {1,1,1},
    {1,0,1},
    {1,1,1}},
    
  { {1,1,1},
    {0,0,1},
    {0,0,1},
    {0,0,1},
    {0,0,1}},
    
  { {1,1,1},
    {1,0,1},
    {1,1,1},
    {1,0,1},
    {1,1,1}},
    
  { {1,1,1},
    {1,0,1},
    {1,1,1},
    {0,0,1},
    {1,1,1}},
  
  // for convenience purposes: 10 -> 9 at end of game
  { {1,1,1},
    {1,0,1},
    {1,1,1},
    {0,0,1},
    {1,1,1}}
}; 

// debouncing
int buttonState[4];
int lastButtonState[4] = {LOW, LOW, LOW, LOW};
int reading[4];
unsigned long lastDebounceTime[4];
unsigned long debounceDelay = 5;

void setup() {
  strip_1.begin();
  strip_1.setBrightness(100);
  strip_1.show(); // Initialize all pixels to 'off'
  strip_2.begin();
  strip_2.setBrightness(100);
  strip_2.show(); // Initialize all pixels to 'off'
  strip_3.begin();
  strip_3.setBrightness(100);
  strip_3.show(); // Initialize all pixels to 'off'
  strip_4.begin();
  strip_4.setBrightness(100);
  strip_4.show(); // Initialize all pixels to 'off'
  randomSeed(analogRead(0));
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  Serial.begin(9600);
  
}

byte mode = 0;
int rainbowCounter = 0;
int inactivityCounter = 0;
int demoCounter = 0;
byte drawCounter = 0;

void loop() {
  if(mode == 0) {
    epileppy();
  } else if(mode == 1) {
    checkers();
  } else if(mode == 2) {
    rainbow();
  } else if(mode == 3 ){
    drawImageMario();
  } else if(mode == 4) {
    drawImageStern();
  } else if(mode == 5) {
    showTetris();
  } else if(mode == 6) {
    showSnake();
  } else if(mode == 7) {
    showPong();
  }
  
  // Input handling
  reading[0] = digitalRead(LEFT);
  reading[1] = digitalRead(RIGHT);
  reading[2] = digitalRead(DOWN);
  for(int i = 0; i < 3; i++) {
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
          mode = max(0,mode - 1);
          inactivityCounter = 0;
          myFill(0);
        } else if(i == 1 && buttonState[i] == HIGH) {
          mode = min(7, mode + 1);
          inactivityCounter = 0;
          myFill(0);
        } else if(i == 2 && buttonState[i] == HIGH) { // start a game
          if(mode == 5) {
            startTetris();
          } else if (mode == 6) {
            startSnake();
          } else if (mode == 7) {
            startPong();
          }
          inactivityCounter = 0;
        }
      }
    }
    
    lastButtonState[i] = reading[i];
  }
  
  // after a approx. 15 sec delay it will start to cycle through the mode to demonstrate the modes
  // should be removed for further use
  if(inactivityCounter > 300) {
    demoCounter++;
    if(demoCounter > 80) {
      myFill(0);
      mode = (mode + 1) % 8;
      demoCounter = 0;
    }
  }
  inactivityCounter = min(1501, inactivityCounter + 1);
  delay(10);
}

// Start screen for Pong
void showPong() {
  byte colorNr = 0;
  
  for(byte x = 0; x < SIZE; x++) {
    for(byte y = 0; y < SIZE; y++) {

      colorNr = image_pong[y][x];
      
     switch(colorNr) {
        case 0: myDraw(x,y,0); break;
        case 1: myDraw(x,y,WHITE); break;
      }
    }
  }
  myShow();
}

// Start screen for Snake
void showSnake() {
  byte colorNr = 0;
  
  for(byte x = 0; x < SIZE; x++) {
    for(byte y = 0; y < SIZE; y++) {

      colorNr = image_snake[y][x];
      
     switch(colorNr) {
        case 0: myDraw(x,y,0); break;
        case 1: myDraw(x,y,GREEN); break;
        case 2: myDraw(x,y,YELLOW); break;
        case 3: myDraw(x,y,RED); break;
      }
    }
  }
  myShow();
}

// Start screen for Tetris
void showTetris() {
  byte colorNr = 0;
  
  for(byte x = 0; x < SIZE; x++) {
    for(byte y = 0; y < SIZE; y++) {

      colorNr = image_tetris[y][x];
      
     switch(colorNr) {
        case 0: myDraw(x,y,0); break;
        case 1: myDraw(x,y,WHITE); break;
        case 2: myDraw(x,y,RED); break;
        case 3: myDraw(x,y,GREEN); break;
        case 4: myDraw(x,y,BLUE); break;
        case 5: myDraw(x,y,YELLOW); break;
        case 6: myDraw(x,y,MAGENTA); break;
        case 7: myDraw(x,y,TEAL); break;
      }
    }
  }
  myShow();
}

//Partymode: Rainbows
void rainbow() {
  for(int i=0; i < 512; i++) {
    myDraw(i, Wheel(i+(rainbowCounter*3) % 256));
  }
  rainbowCounter++;
  myShow();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip_1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip_1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip_1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
// END: Rainbow

// Draw Mario
void drawImageMario() {
  byte colorNr = 0;
  
  for(byte x = 0; x < SIZE; x++) {
    for(byte y = 0; y < SIZE; y++) {

      colorNr = image_mario[y][x];
      
     switch(colorNr) {
        case 0: myDraw(x,y,WHITE); break;
        case 1: myDraw(x,y,MARIO_RED); break;
        case 2: myDraw(x,y,MARIO_BROWN); break;
        case 3: myDraw(x,y,strip_1.Color(0,0,0)); break;//NICHTS ;
        case 4: myDraw(x,y,MARIO_HAUT); break;
        case 5: myDraw(x,y,MARIO_BLUE); break;
        case 7: myDraw(x,y,MARIO_STERN_INNENGELB); break;
        case 8: myDraw(x,y,MARIO_KNOEPFE); break;
      }
    }
  }
  myShow();
}

// Draw Star
void drawImageStern() {
  byte colorNr = 0;
  
  for(byte x = 0; x < SIZE; x++) {
    for(byte y = 0; y < SIZE; y++) {

      colorNr = image_mario_stern[y][x];
      
     switch(colorNr) {
        case 0: myDraw(x,y,WHITE); break;
        case 1: myDraw(x,y,MARIO_RED); break;
        case 2: myDraw(x,y,MARIO_BROWN); break;
        case 3: myDraw(x,y,strip_1.Color(0,0,0)); break;//NICHTS ;
        case 4: myDraw(x,y,MARIO_HAUT); break;
        case 5: myDraw(x,y,MARIO_BLUE); break;
        case 7: myDraw(x,y,MARIO_STERN_INNENGELB); break;
        case 8: myDraw(x,y,MARIO_KNOEPFE); break;
      }
    }
  }
  myShow();
}

// Draw checkers board
void checkers() {
  myFill(0);
  for(byte x = 0; x < 16; x+=2) {
    for(byte y = 0; y < 16; y+=2) {
      if((x+y) % 4 == 0) {
        myDraw(x,y,WHITE);
        myDraw(x+1,y,WHITE);
        myDraw(x,y+1,WHITE);
        myDraw(x+1,y+1,WHITE);
      }
    }
  }
  myShow();
}

// Partymode
void epileppy() {
  for(byte x = 0; x < SIZE; x++) {
    for(byte y = 0; y < SIZE; y++) {
      myDraw(x,y,strip_1.Color(random(256),random(256),random(256)));
    }
  }
  myShow();
}

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

// Functions to emulate a matrix on four seperate NeoPixel strips
void myDraw(int i, uint32_t c) {
  switch(i/128) {
  case 0:
    strip_1.setPixelColor(i%128, c);
    break;
  case 1:
    strip_2.setPixelColor(i%128, c);
    break;
  case 2:
    strip_3.setPixelColor(i%128, c);
    break;
  case 3:
    strip_4.setPixelColor(i%128, c);
    break;
  }
}

void myDraw(uint8_t x, uint8_t y, uint32_t c) {
  if(y%2 == 0) {
    myDraw(y*32+(31-x*2), c);
    myDraw(y*32+(31-(x*2+1)), c);
  } else {
    myDraw(y*32+x*2, c);
    myDraw(y*32+x*2+1, c);
  }
}


void myShow() {
  strip_1.show();
  strip_2.show();
  strip_3.show();
  strip_4.show();
}

void myFill(uint32_t c) {
  for(uint16_t pixel = 0; pixel < 512; pixel++) {
    myDraw(pixel, c);
  }
}
