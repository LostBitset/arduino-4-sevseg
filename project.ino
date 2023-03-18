#define SEVSEG_N_DIGITS 4

#define PIN_SEVSEG_CATH_1 16
#define PIN_SEVSEG_ANOD_A 15
#define PIN_SEVSEG_ANOD_F 14
#define PIN_SEVSEG_CATH_2 2
#define PIN_SEVSEG_CATH_3 3
#define PIN_SEVSEG_ANOD_B 4
#define PIN_SEVSEG_ANOD_E 5
#define PIN_SEVSEG_ANOD_D 6
#define PIN_SEVSEG_ANOD_H 7
#define PIN_SEVSEG_ANOD_C 8
#define PIN_SEVSEG_CATH_4 9
#define PIN_SEVSEG_ANOD_G 10

char sevseg_anode_table[] = {
  //ABCDEFGH
  0b11111100, // 0
  0b00001100, // 1
  0b11011010, // 2
  0b11110010, // 3
  0b01100110, // 4
  0b10110110, // 5
  0b10111110, // 6
  0b11100000, // 7
  0b11111110, // 8
  0b11110110, // 9
  0b01101100, // mojibake
  0b11101110, // A
  0b00111110, // B
  0b10011100, // C
  0b01111010, // D
  0b10011110, // E
  0b10001110, // F
  0b10111100, // G
  0b00101110, // H
  0b00001000, // I
  0b01110000, // J
  0b00011100, // L
  0b00101010, // N
  0b00111010, // O
  0b11001110, // P
  0b00001010, // R
  0b00100010, // T
  0b01111100, // U (also looks like V)
  0b01001110, // Y
};

char sevseg_latin[] = {
// A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y   Z
  11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 10, 21, 10, 22, 23, 24, 10, 25, 10, 26, 27, 10, 10, 10, 28, 10
};

#define SEVSEG_LTN(X) sevseg_latin[X - 'A']

unsigned int sevseg_num_digits = sizeof(sevseg_anode_table)/sizeof(sevseg_anode_table[0]);

unsigned int sevseg_active = 0;

#define SEVSEG_REFRESH_TIME_MS 20

#define SEVSEG_DIGIT_TIME_MS (SEVSEG_REFRESH_TIME_MS/SEVSEG_N_DIGITS)

void setup() {

  // intialize pins for sevseg
  pinMode(PIN_SEVSEG_ANOD_A, OUTPUT);
  pinMode(PIN_SEVSEG_ANOD_B, OUTPUT);
  pinMode(PIN_SEVSEG_ANOD_C, OUTPUT);
  pinMode(PIN_SEVSEG_ANOD_D, OUTPUT);
  pinMode(PIN_SEVSEG_ANOD_E, OUTPUT);
  pinMode(PIN_SEVSEG_ANOD_F, OUTPUT);
  pinMode(PIN_SEVSEG_ANOD_G, OUTPUT);
  pinMode(PIN_SEVSEG_ANOD_H, OUTPUT);
  pinMode(PIN_SEVSEG_CATH_1, OUTPUT);
  pinMode(PIN_SEVSEG_CATH_2, OUTPUT);
  pinMode(PIN_SEVSEG_CATH_3, OUTPUT);
  pinMode(PIN_SEVSEG_CATH_4, OUTPUT);

  // set initial states for sevseg
  digitalWrite(PIN_SEVSEG_ANOD_A, LOW);
  digitalWrite(PIN_SEVSEG_ANOD_B, LOW);
  digitalWrite(PIN_SEVSEG_ANOD_C, LOW);
  digitalWrite(PIN_SEVSEG_ANOD_D, LOW);
  digitalWrite(PIN_SEVSEG_ANOD_E, LOW);
  digitalWrite(PIN_SEVSEG_ANOD_F, LOW);
  digitalWrite(PIN_SEVSEG_ANOD_G, LOW);
  digitalWrite(PIN_SEVSEG_ANOD_H, LOW);
  digitalWrite(PIN_SEVSEG_CATH_1, HIGH);
  digitalWrite(PIN_SEVSEG_CATH_2, HIGH);
  digitalWrite(PIN_SEVSEG_CATH_3, HIGH);
  digitalWrite(PIN_SEVSEG_CATH_4, HIGH);

}

// Show a digit on the Four-Digit Seven-Segment Display
// which_digit is 0, 1, 2, or 3
void sevseg_show_digit(int digit, int which_digit) {
  // Set anodes high to enable
  char anode_mask = sevseg_anode_table[digit];
  digitalWrite(PIN_SEVSEG_ANOD_A, (anode_mask & (1 << 7)) ? HIGH : LOW);
  digitalWrite(PIN_SEVSEG_ANOD_B, (anode_mask & (1 << 6)) ? HIGH : LOW);
  digitalWrite(PIN_SEVSEG_ANOD_C, (anode_mask & (1 << 5)) ? HIGH : LOW);
  digitalWrite(PIN_SEVSEG_ANOD_D, (anode_mask & (1 << 4)) ? HIGH : LOW);
  digitalWrite(PIN_SEVSEG_ANOD_E, (anode_mask & (1 << 3)) ? HIGH : LOW);
  digitalWrite(PIN_SEVSEG_ANOD_F, (anode_mask & (1 << 2)) ? HIGH : LOW);
  digitalWrite(PIN_SEVSEG_ANOD_G, (anode_mask & (1 << 1)) ? HIGH : LOW);
  digitalWrite(PIN_SEVSEG_ANOD_H, (anode_mask & (1 << 0)) ? HIGH : LOW);
  // Set cathode low to enable
  digitalWrite(PIN_SEVSEG_CATH_1, (which_digit == 0) ? LOW : HIGH);
  digitalWrite(PIN_SEVSEG_CATH_2, (which_digit == 1) ? LOW : HIGH);
  digitalWrite(PIN_SEVSEG_CATH_3, (which_digit == 2) ? LOW : HIGH);
  digitalWrite(PIN_SEVSEG_CATH_4, (which_digit == 3) ? LOW : HIGH);
}

void sevseg_show(int text[]) {
  unsigned int cycle_index = (millis() / SEVSEG_DIGIT_TIME_MS) % SEVSEG_N_DIGITS;
  sevseg_show_digit(text[cycle_index], cycle_index);
}

void loop() {
  // put your main code here, to run repeatedly:
  int test_text[] = {SEVSEG_LTN('H'), SEVSEG_LTN('E'), SEVSEG_LTN('L'), SEVSEG_LTN('O')};
  sevseg_show(test_text);
}
