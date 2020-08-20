#include <LiquidCrystal.h>

const byte // Pins
  RS = 2, E = 3,
  D4 = 8, D5 = 9, D6 = 10, D7 = 11,
  LED = 13,
  LEFT = 5, RIGHT = 6
;
const String TO = " - ";

/*
  Hitachi HD44780 supports codepoints 0x00 to 0xFF,
  which is the range allocated with a byte.
  For most architectures,
  unsigned char allocates the same amount as a byte,
  though this is not guaranteed and therefore its use is discouraged.

  You can find a summary of the characters and font at:
  https://en.wikipedia.org/wiki/Special:PermanentLink/970146382#Font
*/
byte
  prevState = 0, state,
  row = 0x20, c, rowEnd // c and rowEnd only used in draw()
;

const LiquidCrystal LCD(RS, E, D4, D5, D6, D7);

void setup() {
  LCD.begin(16, 2);
  pinMode(LED, OUTPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  draw();
}

void loop() {
  state = digitalRead(RIGHT) == HIGH;
  if(digitalRead(LEFT) == HIGH) state += 2;
  if(prevState) {
    if(!state) digitalWrite(LED, LOW);
  } else switch(state) {
    case 1: // Right
      row += 16;
      draw();
      break;
    case 2: // Left
      row -= 16;
      draw();
  }
  prevState = state;
}

void draw() {
///

digitalWrite(LED, HIGH);
LCD.clear();

// Warps around blank rows
switch(row) {
  case 0x00: row = 0x20; break;
  case 0x80: row = 0xA0; break;
  case 0x10: row = 0xF0; break;
  case 0x90: row = 0x70;
}

LCD.print(row, HEX);
LCD.print(TO);
LCD.print(rowEnd = row + 15, HEX);
LCD.setCursor(0, 1);

for(c = row; c < rowEnd;) LCD.write(c++);
LCD.write(c);

///
}
