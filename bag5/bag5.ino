#include "pitches.h"
#define LATCH 9
#define CLK 10
#define DATA 8

#define LATCH1 12
#define CLK1 13
#define DATA1 11

#define finish3 26
#define start3 22
#define track3 24

#define button_start 23
#define button_reset 25

#define buzzer1 53
#define buzzer2 51
#define buzzer3 48
#define buzzer4 50

#define finish1 32
#define start1 28
#define track1 30

#define status_play 35

#define A_0 27
#define A_1 29
#define A_2 31
#define A_3 33

#define finish 38
#define start 34
#define track 36

#define finish2 44
#define start2 40
#define track2 42

#define buzzer 52

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int status_mulai = 0, status_selesai = 0, l = 0, k = 0, j = 0, i = 0, status_jalan = 0, z = 3, status_start = 0, status_start1 = 0, status_start2 = 0, nilai,
    status_start3 = 0, status_track = 0, status_reset = 0, status_track1 = 0, status_track2 = 0, status_track3 = 0, status_finish = 0, status_finish1 = 0, status_finish2 = 0,
    status_finish3 = 0, status_pemain_lost = 0;

unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long currentMillis;
// constants won't change:
const long interval = 1000;

unsigned long previousMillis1 = 0;        // will store last time LED was updated
unsigned long currentMillis1;
// constants won't change:
const long interval1 = 60000;


String highscore = "9999";
//This is the hex value of each number stored in an array by index num
byte digitFour[10] = {0x1, 0xB7, 0x42, 0x12, 0xB4, 0x18, 0x8, 0xB3, 0x0, 0x10};
byte digitThree[10] = {0x1, 0xB7, 0x42, 0x12, 0xB4, 0x18, 0x8, 0xB3, 0x0, 0x10};
byte digitTwo[10] = {0x1, 0xB7, 0x42, 0x12, 0xB4, 0x18, 0x8, 0xB3, 0x0, 0x10};
byte digitOne[10] = {0x1, 0xB7, 0x42, 0x12, 0xB4, 0x18, 0x8, 0xB3, 0x0, 0x10}; //




long buttonTimer = 0;
long longPressTime = 3000;

boolean buttonActive = false;
boolean longPressActive = false;



void setup() {
  Serial.begin(9600);

  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(buzzer3, OUTPUT);
  pinMode(buzzer4, OUTPUT);

  pinMode(A_0, OUTPUT);
  pinMode(A_1, OUTPUT);
  pinMode(A_2, OUTPUT);
  pinMode(A_3, OUTPUT);

  pinMode(status_play, OUTPUT);

  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);

  pinMode(LATCH1, OUTPUT);
  pinMode(CLK1, OUTPUT);
  pinMode(DATA1, OUTPUT);

  pinMode(button_start, INPUT);
  pinMode(button_reset, INPUT);

  pinMode(start, INPUT);
  pinMode(finish, INPUT);
  pinMode(track, INPUT);

  pinMode(start1, INPUT);
  pinMode(finish1, INPUT);
  pinMode(track1, INPUT);

  pinMode(start2, INPUT);
  pinMode(finish2, INPUT);
  pinMode(track2, INPUT);

  pinMode(start3, INPUT);
  pinMode(finish3, INPUT);
  pinMode(track3, INPUT);

  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLK, MSBFIRST, ~digitOne[0]); // digitTwo
  shiftOut(DATA, CLK, MSBFIRST, ~digitTwo[0]); // digitOne
  shiftOut(DATA, CLK, MSBFIRST, ~digitThree[0]); // digitTwo
  shiftOut(DATA, CLK, MSBFIRST, ~digitFour[0]); // digitOne
  digitalWrite(LATCH, HIGH);

  digitalWrite(LATCH1, LOW);
  shiftOut(DATA1, CLK1, MSBFIRST, ~digitOne[0]); // digitTwo
  shiftOut(DATA1, CLK1, MSBFIRST, ~digitTwo[0]); // digitOne
  shiftOut(DATA1, CLK1, MSBFIRST, ~digitThree[0]); // digitTwo
  shiftOut(DATA1, CLK1, MSBFIRST, ~digitFour[0]); // digitOne
  digitalWrite(LATCH1, HIGH);
}

void merah_nyala()
{
  digitalWrite(A_0, HIGH);
  digitalWrite(A_1, LOW);
  digitalWrite(A_2, HIGH);
  digitalWrite(A_3, HIGH);

  tone(buzzer, 262, 250);
  delay(750);
}

void biru_nyala()
{
  digitalWrite(A_0, HIGH);
  digitalWrite(A_1, LOW);
  digitalWrite(A_2, HIGH);
  digitalWrite(A_3, LOW);
  tone(buzzer, 262, 250);
  delay(750);
}

void hijau_nyala()
{
  digitalWrite(A_0, LOW);
  digitalWrite(A_1, HIGH);
  digitalWrite(A_2, LOW);
  digitalWrite(A_3, HIGH);

  tone(buzzer, 330, 1000);
  delay(750);
}

void kuning_nyala()
{
  digitalWrite(A_0, HIGH);
  digitalWrite(A_1, HIGH);
  digitalWrite(A_2, HIGH);
  digitalWrite(A_3, LOW);

  tone(buzzer, 262, 250);
  delay(750);
}

int count_down()
{
  digitalWrite(status_play,LOW);
  unsigned long currentMillis = millis();
  if (z > 0) {
    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;

      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLK, MSBFIRST, ~digitOne[0]); // digitTwo
      shiftOut(DATA, CLK, MSBFIRST, ~digitTwo[0]); // digitOne
      shiftOut(DATA, CLK, MSBFIRST, ~digitThree[0]); // digitTwo
      shiftOut(DATA, CLK, MSBFIRST, ~digitFour[z]); // digitOne
      digitalWrite(LATCH, HIGH);
      if (z == 3) {
        merah_nyala();
      }
      if (z == 2) {
        biru_nyala();

      }
      if (z == 1) {
        kuning_nyala();
        status_mulai = 1;
      }
      z--;
    }
  }
}

void count_up()
{
  
    digitalWrite(status_play,HIGH);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {

    previousMillis = currentMillis;

    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLK, MSBFIRST, ~digitOne[l]); // digitTwo
    shiftOut(DATA, CLK, MSBFIRST, ~digitTwo[k]); // digitOne
    shiftOut(DATA, CLK, MSBFIRST, ~digitThree[i]); // digitTwo
    shiftOut(DATA, CLK, MSBFIRST, ~digitFour[j]); // digitOne
    digitalWrite(LATCH, HIGH);
    if ((j == 0) && (k == 0) && (i == 0) && (l == 0)) {
      hijau_nyala();
    } else {

//      digitalWrite(A_0, HIGH);
//      digitalWrite(A_1, HIGH);
//      digitalWrite(A_2, HIGH);
//      digitalWrite(A_3, HIGH);
    }

    if (j == 9) {
      j = -1;
      i++;
    }
    if (i == 6) {
      i = 0;
      k++;
    }
    if (k == 9) {
      k = 0;
      l++;
    }
    j++;
  }

}
int tekan = 0;
void loop()
{

  if ((status_mulai == 0) && (digitalRead(button_start) == HIGH)) {
    digitalWrite(buzzer1, LOW);
    digitalWrite(buzzer2, LOW);
    digitalWrite(buzzer3, LOW);
    digitalWrite(buzzer4, LOW);
    i = 0;
    j = 0;
    k = 0;
    l = 0;
    z = 3;
    status_jalan = 0;
    tekan = 1;

  }


  //check reset
  if (digitalRead(button_reset) == HIGH) {
    if (buttonActive == false) {

      buttonActive = true;
      buttonTimer = millis();

    }
    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {

      longPressActive = true;
      digitalWrite(LATCH1, LOW);
      shiftOut(DATA1, CLK1, MSBFIRST, ~digitOne[0]); // digitTwo
      shiftOut(DATA1, CLK1, MSBFIRST, ~digitTwo[0]); // digitOne
      shiftOut(DATA1, CLK1, MSBFIRST, ~digitThree[0]); // digitTwo
      shiftOut(DATA1, CLK1, MSBFIRST, ~digitFour[0]); // digitOne
      digitalWrite(LATCH1, HIGH);
      highscore = 9999;
    } else {
      digitalWrite(status_play,LOW);
      digitalWrite(A_0, HIGH);
      digitalWrite(A_1, HIGH);
      digitalWrite(A_2, HIGH);
      digitalWrite(A_3, HIGH);
    }

  } else {

    if (buttonActive == true) {

      if (longPressActive == true) {

        longPressActive = false;

      } else {

      }

      buttonActive = false;

    }

  }


  //////////////START/////////////
  //check pemain 1 kondisi start
  if (digitalRead(start) == HIGH) {
    status_start = 1;
    status_track = 0;
    status_finish = 0;
    digitalWrite(A_0,LOW);
    digitalWrite(buzzer1, LOW);
    Serial.println("start 1");
  } else {
    status_start = 0;
  }

  //  check pemain 2 kondisi start
  if (digitalRead(start1) == HIGH) {
    status_start1 = 1;
    status_track1 = 0;
    status_finish1 = 0;
    digitalWrite(A_1,LOW);
    digitalWrite(buzzer2, LOW);
    Serial.println("start 2");
  } else {
    status_start1 = 0;
  }

  //  check pemain 3 kondisi start
  if (digitalRead(start2) == HIGH) {
    status_start2 = 1;
    status_track2 = 0;
    status_finish2 = 0;
    digitalWrite(A_2,LOW);
    digitalWrite(buzzer3, LOW);
    Serial.println("start 3");
  } else {
    status_start2 = 0;
  }
  //check pemain 4 kondisi start
  if (digitalRead(start3) == HIGH) {
    status_start3 = 1;
    status_track3 = 0;
    status_finish3 = 0;
    digitalWrite(A_3,LOW);
    digitalWrite(buzzer4, LOW);
    Serial.println("start 4");
  } else {
    status_start3 = 0;
  }

  //////////////LOST/////////////
  // check apakah pemain 1 lost
  if (digitalRead(track) == HIGH) {
    status_track = 1;
    Serial.println("track 1");
  }
  // check apakah pemain 2 lost
  if (digitalRead(track1) == HIGH) {
    status_track1 = 1;
    Serial.println("track 2");
  }
  // check apakah pemain 3 lost
  if (digitalRead(track2) == HIGH) {
    status_track2 = 1;
    Serial.println("track 3");
  }
  // check apakah pemain 4 lost
  if (digitalRead(track3) == HIGH) {
    status_track3 = 1;
    Serial.println("track 4");

  }

  ////FINISH///////////
  //check status pemain 1 menang
  if (digitalRead(finish) == HIGH) {
    status_finish = 1;
    Serial.println("finish 1");
  }
  //check status pemain 2 menang
  if (digitalRead(finish1) == HIGH) {
    status_finish1 = 1;
    Serial.println("finish 2");
  }
  //check status pemain 3 menang
  if (digitalRead(finish2) == HIGH) {
    status_finish2 = 1;

    Serial.println("finish 3");
  }
  //check status pemain 4 menang
  if (digitalRead(finish3) == HIGH) {
    status_finish3 = 1;
  }

  //////////PERMAINAN////////////
  //jika tombol mulai ditekan dan semua pemain sudah di start
  if ( status_mulai == 1 && status_jalan == 1) {
    count_up();
    unsigned long currentMillis1 = millis();
  if (currentMillis1 - previousMillis1 >= interval1)
  {
      tone(buzzer, 330, 1000);
  //delay(500);
    previousMillis1 = currentMillis1;
    
  }
  
    if (status_track == 1)
    {
      digitalWrite(A_0, HIGH);
//      digitalWrite(A_1, LOW);
//      digitalWrite(A_2, LOW);
//      digitalWrite(A_3, LOW);
      digitalWrite(buzzer1, HIGH);
      count_up();
    }
    //
    if (status_track1 == 1)
    {

//      digitalWrite(A_0, LOW);
      digitalWrite(A_1, HIGH);
//      digitalWrite(A_2, LOW);
//      digitalWrite(A_3, LOW);
      digitalWrite(buzzer2, HIGH);
      count_up();
    }
    //
    if (status_track2 == 1)
    {
      digitalWrite(buzzer3, HIGH);

//      digitalWrite(A_0, LOW);
//      digitalWrite(A_1, LOW);
      digitalWrite(A_2, HIGH);
//      digitalWrite(A_3, LOW);
      count_up();
    }
    //
    if (status_track3 == 1)
    {
//      digitalWrite(A_0, LOW);
//      digitalWrite(A_1, LOW);
//      digitalWrite(A_2, LOW);
      digitalWrite(A_3, HIGH);
      digitalWrite(buzzer4, HIGH);
      count_up();
    }

    if ((status_finish == 1) && (status_track == 0))
    {
digitalWrite(status_play,LOW);
      digitalWrite(A_0, HIGH);
      digitalWrite(A_1, HIGH);
      digitalWrite(A_2, LOW);
      digitalWrite(A_3, LOW);
      for (int thisNote = 0; thisNote < 8; thisNote++) {

        // to calculate the note duration, take one second divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(52, melody[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(52);
      }
      String temp = String(l) + String(k) + String(i) + String(j - 1);
      int temp_number = temp.toInt();
      int highscore_number = highscore.toInt();
      if (temp_number < highscore_number) {
        digitalWrite(LATCH1, LOW);
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitOne[l]); // digitTwo
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitTwo[k]); // digitOne
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitThree[i]); // digitTwo
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitFour[j - 1]); // digitOne
        digitalWrite(LATCH1, HIGH);
        highscore = temp;
      }
      //digitalWrite(buzzer1, HIGH);
      status_mulai = 0;
      status_jalan = 0;
    }

    if ((status_finish1 == 1) && (status_track1 == 0))
    {
      digitalWrite(status_play,LOW);
      digitalWrite(A_0, LOW);
      digitalWrite(A_1, HIGH);
      digitalWrite(A_2, HIGH);
      digitalWrite(A_3, LOW);

      for (int thisNote = 0; thisNote < 8; thisNote++) {

        // to calculate the note duration, take one second divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(52, melody[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(52);
      }
      String temp = String(l) + String(k) + String(i) + String(j - 1);
      int temp_number = temp.toInt();
      int highscore_number = highscore.toInt();
      if (temp_number < highscore_number) {
        digitalWrite(LATCH1, LOW);
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitOne[l]); // digitTwo
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitTwo[k]); // digitOne
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitThree[i]); // digitTwo
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitFour[j - 1]); // digitOne
        digitalWrite(LATCH1, HIGH);
        highscore = temp;
      }
      //digitalWrite(buzzer2, HIGH);
      status_mulai = 0;
      status_jalan = 0;
    }
    //
    if ((status_finish2 == 1) && (status_track2 == 0))
    {
      digitalWrite(status_play,LOW);
      digitalWrite(A_0, LOW);
      digitalWrite(A_1, LOW);
      digitalWrite(A_2, HIGH);
      digitalWrite(A_3, HIGH);
      for (int thisNote = 0; thisNote < 8; thisNote++) {

        // to calculate the note duration, take one second divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(52, melody[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(52);
      }
      String temp = String(l) + String(k) + String(i) + String(j - 1);
      int temp_number = temp.toInt();
      int highscore_number = highscore.toInt();
      if (temp_number < highscore_number) {
        digitalWrite(LATCH1, LOW);
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitOne[l]); // digitTwo
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitTwo[k]); // digitOne
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitThree[i]); // digitTwo
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitFour[j - 1]); // digitOne
        digitalWrite(LATCH1, HIGH);
        highscore = temp;
      }
      //digitalWrite(buzzer3, HIGH);
      status_mulai = 0;
      status_jalan = 0;
    }
    //
    if ((status_finish3 == 1) && (status_track3 == 0))
    {
      digitalWrite(status_play,LOW);
      digitalWrite(A_0, HIGH);
      digitalWrite(A_1, LOW);
      digitalWrite(A_2, LOW);
      digitalWrite(A_3, HIGH);
      for (int thisNote = 0; thisNote < 8; thisNote++) {

        // to calculate the note duration, take one second divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(52, melody[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(52);
      }
      String temp = String(l) + String(k) + String(i) + String(j - 1);
      int temp_number = temp.toInt();
      int highscore_number = highscore.toInt();
      if (temp_number < highscore_number) {
        digitalWrite(LATCH1, LOW);
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitOne[l]); // digitTwo
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitTwo[k]); // digitOne
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitThree[i]); // digitTwo
        shiftOut(DATA1, CLK1, MSBFIRST, ~digitFour[j - 1]); // digitOne
        digitalWrite(LATCH1, HIGH);
        highscore = temp;
      }
      //digitalWrite(buzzer4, HIGH);
      status_mulai = 0;
      status_jalan = 0;
    }

  }
  else if (tekan == 1) {
    digitalWrite(status_play,LOW);
    unsigned long currentMillis = millis();
    if (z > 0) {
      if (currentMillis - previousMillis >= interval)
      {
        previousMillis = currentMillis;

        digitalWrite(LATCH, LOW);
        shiftOut(DATA, CLK, MSBFIRST, ~digitOne[0]); // digitTwo
        shiftOut(DATA, CLK, MSBFIRST, ~digitTwo[0]); // digitOne
        shiftOut(DATA, CLK, MSBFIRST, ~digitThree[0]); // digitTwo
        shiftOut(DATA, CLK, MSBFIRST, ~digitFour[z]); // digitOne
        digitalWrite(LATCH, HIGH);
        if (z == 3) {
          merah_nyala();
        }
        if (z == 2) {
          biru_nyala();
        }
        if (z == 1) {
          kuning_nyala();
          status_mulai = 1;
        }
        z--;
      }
    }
    if ((status_start3 == 1) && (status_start1 == 1) && (status_start2 == 1) && (status_start == 1))
    {
      status_jalan = 1;

    }
  }
}
