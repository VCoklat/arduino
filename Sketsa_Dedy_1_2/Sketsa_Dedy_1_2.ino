#define NUM_COLS 16

const int row1Pin = 2;
const int row2Pin = 3;
const int row3Pin = 4;
const int row4Pin = 5;
const int row5Pin = 6;
const int row6Pin = 7;

// 74HC595 pins
const int dataPin = 8;
const int latchPin = 9;
const int clockPin = 10;

const int dataPin1 = 11;
const int latchPin1 = 12;
const int clockPin1 = 13;

const int dataPin3 = 5;
const int latchPin3 = 6;
const int clockPin3 = 7;

const int dataPin2 = 2;
const int latchPin2 = 3;
const int clockPin2 = 4;

// bitmasks for scanning columns
int bits[] =
{
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000
};



void setup()
{

  // setup pins output/input mode
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  pinMode(dataPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(latchPin1, OUTPUT);

  pinMode(dataPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(latchPin2, OUTPUT);

  pinMode(dataPin3, OUTPUT);
  pinMode(clockPin3, OUTPUT);
  pinMode(latchPin3, OUTPUT);

  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);

  Serial.begin(9600);
}

void loop()
{

  if ((digitalRead(14) == LOW) && (digitalRead(15) == LOW) && (digitalRead(16) == LOW) && (digitalRead(17) == LOW)) {
    int rand = 100;
    delay(rand);
    for (int i = 1; i <= 4; i++) {
      red(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      green(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      blue(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      yellow(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      bl(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      purple(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      all(i);
    }

    delay(rand);
  }

  if ((digitalRead(14) == HIGH) && (digitalRead(15) == LOW) && (digitalRead(16) == LOW) && (digitalRead(17) == LOW)) {
    int rand = 100;
    delay(rand);
    for (int i = 1; i <= 4; i++) {

      red(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        green(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        blue(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        yellow(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        bl(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        purple(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        all(i);
    }

    delay(rand);
  }

  if ((digitalRead(15) == HIGH) && (digitalRead(14) == LOW) && (digitalRead(16) == LOW) && (digitalRead(17) == LOW)) {
    int rand = 100;
    delay(rand);
    for (int i = 1; i <= 4; i++) {
      red(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        green(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        blue(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        yellow(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        bl(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        purple(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        all(i);
    }

    delay(rand);
  }

  if ((digitalRead(16) == HIGH) && (digitalRead(14) == LOW) && (digitalRead(15) == LOW) && (digitalRead(17) == LOW)) {
    int rand = 100;
    delay(rand);
    for (int i = 1; i <= 4; i++) {
      red(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        green(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        blue(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        yellow(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        bl(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        purple(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        all(i);
    }

    delay(rand);
  }
  if ((digitalRead(17) == HIGH) && (digitalRead(14) == LOW) && (digitalRead(15) == LOW) && (digitalRead(16) == LOW)) {
    int rand = 100;
    delay(rand);
    for (int i = 1; i <= 4; i++) {

      red(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        green(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        blue(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        yellow(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        bl(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        purple(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        all(i);
    }

    delay(rand);
  }
  if ((digitalRead(14) == HIGH) && (digitalRead(15) == HIGH) && (digitalRead(16) == HIGH) && (digitalRead(17) == LOW)) {
    for (int i = 1; i <= 4; i++) {
      yellow(i);
    }
  }

  if ((digitalRead(14) == LOW) && (digitalRead(15) == HIGH) && (digitalRead(16) == LOW) && (digitalRead(17) == HIGH)) {
    for (int i = 1; i <= 4; i++) {
      green(i);
    }
  }

  if ((digitalRead(14) == HIGH) && (digitalRead(15) == LOW) && (digitalRead(16) == HIGH) && (digitalRead(17) == HIGH)) {
    for (int i = 1; i <= 4; i++) {
      red(i);
    }
  }




  if ((digitalRead(14) == HIGH) && (digitalRead(15) == HIGH) && (digitalRead(16) == LOW) && (digitalRead(17) == LOW)) {
    int rand = 100;
    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        red(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      green(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        blue(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        yellow(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        bl(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        purple(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 1) continue; else
        all(i);
    }

    delay(rand);
  }










  if ((digitalRead(16) == HIGH) && (digitalRead(15) == HIGH) && (digitalRead(14) == LOW) && (digitalRead(17) == LOW)) {
    int rand = 100;
    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        red(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      green(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        blue(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        yellow(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        bl(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        purple(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 2) continue; else
        all(i);
    }

    delay(rand);
  }



  if ((digitalRead(16) == HIGH) && (digitalRead(17) == HIGH) && (digitalRead(14) == LOW) && (digitalRead(15) == LOW)) {
    // green(3);
    int rand = 100;
    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        red(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      green(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        blue(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        yellow(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        bl(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        purple(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 3) continue; else
        all(i);
    }

    delay(rand);
  }




  if ((digitalRead(14) == HIGH) && (digitalRead(17) == HIGH) && (digitalRead(15) == LOW) && (digitalRead(16) == LOW)) {
    int rand = 100;
    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        red(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      green(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        blue(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        yellow(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        bl(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        purple(i);
    }

    delay(rand);
    for (int i = 1; i <= 4; i++) {
      if (i == 4) continue; else
        all(i);
    }

    delay(rand);
  }
}

void scanColumn(int player)
{
  if (player == 1) {
    for (int colNum = 0; colNum < NUM_COLS; ++colNum)
    {
      digitalWrite(latchPin, LOW);

      if (0 <= colNum && colNum <= 7)
      {
        shiftOut(dataPin, clockPin, MSBFIRST, B00000000); //right sr
        shiftOut(dataPin, clockPin, MSBFIRST, bits[colNum]); //left sr
      }
      else
      {
        shiftOut(dataPin, clockPin, MSBFIRST, bits[colNum - 8]); //right sr
        shiftOut(dataPin, clockPin, MSBFIRST, B00000000); //left sr
      }
      digitalWrite(latchPin, HIGH);
      delay(200);
    }
  }
  else if (player == 2) {
    for (int colNum = 0; colNum < NUM_COLS; ++colNum)
    {
      digitalWrite(latchPin1, LOW);

      if (0 <= colNum && colNum <= 7)
      {
        shiftOut(dataPin1, clockPin1, MSBFIRST, B00000000); //right sr
        shiftOut(dataPin1, clockPin1, MSBFIRST, bits[colNum]); //left sr
      }
      else
      {
        shiftOut(dataPin1, clockPin1, MSBFIRST, bits[colNum - 8]); //right sr
        shiftOut(dataPin1, clockPin1, MSBFIRST, B00000000); //left sr
      }
      digitalWrite(latchPin1, HIGH);
      delay(200);
    }
  } else if (player == 3) {
    for (int colNum = 0; colNum < NUM_COLS; ++colNum)
    {
      digitalWrite(latchPin2, LOW);

      if (0 <= colNum && colNum <= 7)
      {
        shiftOut(dataPin2, clockPin2, MSBFIRST, B00000000); //right sr
        shiftOut(dataPin2, clockPin2, MSBFIRST, bits[colNum]); //left sr
      }
      else
      {
        shiftOut(dataPin2, clockPin2, MSBFIRST, bits[colNum - 8]); //right sr
        shiftOut(dataPin2, clockPin2, MSBFIRST, B00000000); //left sr
      }
      digitalWrite(latchPin2, HIGH);
      delay(200);
    }
  } else if (player == 4) {
    for (int colNum = 0; colNum < NUM_COLS; ++colNum)
    {
      digitalWrite(latchPin3, LOW);

      if (0 <= colNum && colNum <= 7)
      {
        shiftOut(dataPin3, clockPin3, MSBFIRST, B00000000); //right sr
        shiftOut(dataPin3, clockPin3, MSBFIRST, bits[colNum]); //left sr
      }
      else
      {
        shiftOut(dataPin3, clockPin3, MSBFIRST, bits[colNum - 8]); //right sr
        shiftOut(dataPin3, clockPin3, MSBFIRST, B00000000); //left sr
      }
      digitalWrite(latchPin3, HIGH);
      delay(200);
    }
  }
}
void red(int player)
{
  if (player == 1) {
    digitalWrite(latchPin, LOW);

    shiftOut(dataPin, clockPin, MSBFIRST, B10010010); //right sr
    shiftOut(dataPin, clockPin, MSBFIRST, B01001001); //left sr

    digitalWrite(latchPin, HIGH);
  }
  else if (player == 2) {
    digitalWrite(latchPin1, LOW);


    shiftOut(dataPin1, clockPin1, MSBFIRST, B10010010); //right sr
    shiftOut(dataPin1, clockPin1, MSBFIRST, B01001001); //left sr


    digitalWrite(latchPin1, HIGH);
  } else if (player == 3) {
    digitalWrite(latchPin2, LOW);


    shiftOut(dataPin2, clockPin2, MSBFIRST, B10010010); //right sr
    shiftOut(dataPin2, clockPin2, MSBFIRST, B01001001); //left sr


    digitalWrite(latchPin2, HIGH);
  } else if (player == 4) {
    digitalWrite(latchPin3, LOW);


    shiftOut(dataPin3, clockPin3, MSBFIRST, B10010010); //right sr
    shiftOut(dataPin3, clockPin3, MSBFIRST, B01001001); //left sr


    digitalWrite(latchPin3, HIGH);
  }


}

void green(int player)
{
  if (player == 1) {
    digitalWrite(latchPin, LOW);


    shiftOut(dataPin, clockPin, MSBFIRST, B10100100); //right sr
    shiftOut(dataPin, clockPin, MSBFIRST, B10010010); //left sr


    digitalWrite(latchPin, HIGH);
  }
  else if (player == 2) {
    digitalWrite(latchPin1, LOW);


    shiftOut(dataPin1, clockPin1, MSBFIRST, B10100100); //right sr
    shiftOut(dataPin1, clockPin1, MSBFIRST, B10010010); //left sr


    digitalWrite(latchPin1, HIGH);
  } else if (player == 3) {
    digitalWrite(latchPin2, LOW);


    shiftOut(dataPin2, clockPin2, MSBFIRST, B10100100); //right sr
    shiftOut(dataPin2, clockPin2, MSBFIRST, B10010010); //left sr


    digitalWrite(latchPin2, HIGH);
  } else if (player == 4) {
    digitalWrite(latchPin3, LOW);


    shiftOut(dataPin3, clockPin3, MSBFIRST, B10100100); //right sr
    shiftOut(dataPin3, clockPin3, MSBFIRST, B10010010); //left sr


    digitalWrite(latchPin3, HIGH);
  }


}

void blue(int player)
{
  if (player == 1) {
    digitalWrite(latchPin, LOW);


    shiftOut(dataPin, clockPin, MSBFIRST, B11001001); //right sr
    shiftOut(dataPin, clockPin, MSBFIRST, B00100100); //left sr


    digitalWrite(latchPin, HIGH);
  }
  else if (player == 2) {
    digitalWrite(latchPin1, LOW);


    shiftOut(dataPin1, clockPin1, MSBFIRST, B11001001); //right sr
    shiftOut(dataPin1, clockPin1, MSBFIRST, B00100100); //left sr


    digitalWrite(latchPin1, HIGH);
  } else if (player == 3) {
    digitalWrite(latchPin2, LOW);


    shiftOut(dataPin2, clockPin2, MSBFIRST, B11001001); //right sr
    shiftOut(dataPin2, clockPin2, MSBFIRST, B00100100); //left sr


    digitalWrite(latchPin2, HIGH);
  } else if (player == 4) {
    digitalWrite(latchPin3, LOW);


    shiftOut(dataPin3, clockPin3, MSBFIRST, B11001001); //right sr
    shiftOut(dataPin3, clockPin3, MSBFIRST, B00100100); //left sr


    digitalWrite(latchPin3, HIGH);
  }


}

void yellow(int player)
{
  if (player == 1) {
    digitalWrite(latchPin, LOW);


    shiftOut(dataPin, clockPin, MSBFIRST, B10110110); //right sr
    shiftOut(dataPin, clockPin, MSBFIRST, B11011011); //left sr


    digitalWrite(latchPin, HIGH);
  }
  else if (player == 2) {
    digitalWrite(latchPin1, LOW);


    shiftOut(dataPin1, clockPin1, MSBFIRST, B10110110); //right sr
    shiftOut(dataPin1, clockPin1, MSBFIRST, B11011011); //left sr


    digitalWrite(latchPin1, HIGH);
  } else if (player == 3) {
    digitalWrite(latchPin2, LOW);


    shiftOut(dataPin2, clockPin2, MSBFIRST, B10110110); //right sr
    shiftOut(dataPin2, clockPin2, MSBFIRST, B11011011); //left sr


    digitalWrite(latchPin2, HIGH);
  } else if (player == 4) {
    digitalWrite(latchPin3, LOW);


    shiftOut(dataPin3, clockPin3, MSBFIRST, B10110110); //right sr
    shiftOut(dataPin3, clockPin3, MSBFIRST, B11011011); //left sr


    digitalWrite(latchPin3, HIGH);
  }


}

void all(int player)
{
  if (player == 1) {
    digitalWrite(latchPin, LOW);


    shiftOut(dataPin, clockPin, MSBFIRST, B11111111); //right sr
    shiftOut(dataPin, clockPin, MSBFIRST, B11111111); //left sr


    digitalWrite(latchPin, HIGH);
  }
  else if (player == 2) {
    digitalWrite(latchPin1, LOW);


    shiftOut(dataPin1, clockPin1, MSBFIRST, B11111111); //right sr
    shiftOut(dataPin1, clockPin1, MSBFIRST, B11111111); //left sr


    digitalWrite(latchPin1, HIGH);
  } else if (player == 3) {
    digitalWrite(latchPin2, LOW);


    shiftOut(dataPin2, clockPin2, MSBFIRST, B11111111); //right sr
    shiftOut(dataPin2, clockPin2, MSBFIRST, B11111111); //left sr


    digitalWrite(latchPin2, HIGH);
  } else if (player == 4) {
    digitalWrite(latchPin3, LOW);


    shiftOut(dataPin3, clockPin3, MSBFIRST, B11111111); //right sr
    shiftOut(dataPin3, clockPin3, MSBFIRST, B11111111); //left sr


    digitalWrite(latchPin3, HIGH);
  }


}

void bl(int player)
{
  if (player == 1) {
    digitalWrite(latchPin, LOW);


    shiftOut(dataPin, clockPin, MSBFIRST, B11101101); //right sr
    shiftOut(dataPin, clockPin, MSBFIRST, B10110110); //left sr


    digitalWrite(latchPin, HIGH);
  }
  else if (player == 2) {
    digitalWrite(latchPin1, LOW);


    shiftOut(dataPin1, clockPin1, MSBFIRST, B11101101); //right sr
    shiftOut(dataPin1, clockPin1, MSBFIRST, B10110110); //left sr


    digitalWrite(latchPin1, HIGH);
  } else if (player == 3) {
    digitalWrite(latchPin2, LOW);


    shiftOut(dataPin2, clockPin2, MSBFIRST, B11101101); //right sr
    shiftOut(dataPin2, clockPin2, MSBFIRST, B10110110); //left sr


    digitalWrite(latchPin2, HIGH);
  } else if (player == 4) {
    digitalWrite(latchPin3, LOW);


    shiftOut(dataPin3, clockPin3, MSBFIRST, B11101101); //right sr
    shiftOut(dataPin3, clockPin3, MSBFIRST, B10110110); //left sr


    digitalWrite(latchPin3, HIGH);
  }


}

void purple(int player)
{
  if (player == 1) {
    digitalWrite(latchPin, LOW);


    shiftOut(dataPin, clockPin, MSBFIRST, B11011011); //right sr
    shiftOut(dataPin, clockPin, MSBFIRST, B01101101); //left sr


    digitalWrite(latchPin, HIGH);
  }
  else if (player == 2) {
    digitalWrite(latchPin1, LOW);


    shiftOut(dataPin1, clockPin1, MSBFIRST, B11011011); //right sr
    shiftOut(dataPin1, clockPin1, MSBFIRST, B01101101); //left sr


    digitalWrite(latchPin1, HIGH);
  } else if (player == 3) {
    digitalWrite(latchPin2, LOW);


    shiftOut(dataPin2, clockPin2, MSBFIRST, B11011011); //right sr
    shiftOut(dataPin2, clockPin2, MSBFIRST, B01101101); //left sr


    digitalWrite(latchPin2, HIGH);
  } else if (player == 4) {
    digitalWrite(latchPin3, LOW);


    shiftOut(dataPin3, clockPin3, MSBFIRST, B11011011); //right sr
    shiftOut(dataPin3, clockPin3, MSBFIRST, B01101101); //left sr


    digitalWrite(latchPin3, HIGH);
  }


}


void off(int player)
{
  if (player == 1) {
    digitalWrite(latchPin, LOW);


    shiftOut(dataPin, clockPin, MSBFIRST, B00000000); //right sr
    shiftOut(dataPin, clockPin, MSBFIRST, B00000000); //left sr


    digitalWrite(latchPin, HIGH);
  }
  else if (player == 2) {
    digitalWrite(latchPin1, LOW);


    shiftOut(dataPin1, clockPin1, MSBFIRST, B00000000); //right sr
    shiftOut(dataPin1, clockPin1, MSBFIRST, B00000000); //left sr


    digitalWrite(latchPin1, HIGH);
  } else if (player == 3) {
    digitalWrite(latchPin2, LOW);


    shiftOut(dataPin2, clockPin2, MSBFIRST, B00000000); //right sr
    shiftOut(dataPin2, clockPin2, MSBFIRST, B00000000); //left sr


    digitalWrite(latchPin2, HIGH);
  } else if (player == 4) {
    digitalWrite(latchPin3, LOW);


    shiftOut(dataPin3, clockPin3, MSBFIRST, B00000000); //right sr
    shiftOut(dataPin3, clockPin3, MSBFIRST, B00000000); //left sr


    digitalWrite(latchPin3, HIGH);
  }


}

