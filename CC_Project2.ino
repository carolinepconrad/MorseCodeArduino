// C++ code for Arduino
//Sketch uses 3696 bytes (11%) of program storage space. Maximum is 32256 bytes.
//Global variables use 289 bytes (14%) of dynamic memory, leaving 1759 bytes for local variables. Maximum is 2048 bytes.


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

// Variables
char letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ',};

// 3 bits at the between each character is represented by the 000 at the beginning of each int in the array,
// the space contains only four 0's (4 bits), so if a space is used, in total it's 7 bits with 3 from the previous character.
unsigned int mcLet[] = {
  0b00011101000, //A
  0b000101010111, //B
  0b00010111010111, //C
  0b0001010111, //D
  0b0001,//E
  0b000101110101, //F
  0b000101110111, //G
  0b0001010101, //H
  0b000101, //I
  0b0001110111011101,//J
  0b000111010111, //K
  0b000101011101, //L
  0b0001110111, //M
  0b00010111, //N
  0b00011101110111, //O
  0b00010111011101,//P
  0b0001110101110111,//Q
  0b0001011101, //R
  0b00010101, //S
  0b000111, //T
  0b0001110101,//U
  0b000111010101, //V
  0b000111011101, //W
  0b00011101010111, //X
  0b0001110111010111, //Y
  0b00010101110111,//Z
  0b0000 //SPACE
};

void blinkMorse(char letter) {
  for (int i = 0; i < sizeof(letters) / sizeof(letters[0]); i++) {
    if (letter == letters[i]) { 
      unsigned int mCode = mcLet[i];
      while (mCode > 0) {
        if (mCode & 1) {
          Serial.println("Dot");
          digitalWrite(LED_BUILTIN, HIGH);
          delay(300); //how long the light is on
        } else {
          Serial.println("Space");
          digitalWrite(LED_BUILTIN, LOW);
          delay(300);//how long the light is off
        }
        mCode >>= 1;
      }
      digitalWrite(LED_BUILTIN, LOW);
      delay(300);

      return;
    }
  }
}

void loop() {
  if (Serial.available()) {
    String word = Serial.readStringUntil('\n');
    for (int i = 0; i < word.length(); i++) {
      blinkMorse(word[i]);
    }
  }
}