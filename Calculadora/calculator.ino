#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(A4, A5, 3, 2, 1, 0);

long first = 0;
long second = 0;
double total = 0;

char customKey;
const byte ROWS = 4;
const byte COLS = 4;

const int MAX_DEC_LENGTH = 3;
const int MAX_BIN_LENGTH = 3;

char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {11,10,9,8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7,6,5,4}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

enum {
  DECIMAL,
  BINARY,
  OCTAL,
  DECIMAL_TO_BINARY,
  DECIMAL_TO_OCTAL,
  BINARY_TO_DECIMAL,
  BINARY_TO_OCTAL,
  OCTAL_TO_DECIMAL,
  OCTAL_TO_BINARY
} mode = DECIMAL ;

void decimalCalculator() {
  switch(customKey) {
  case '0' ... '9': // This keeps collecting the first value until a operator is pressed "+-*/"
    lcd.setCursor(0,0);
    first = first * 10 + (customKey - '0');
    lcd.print(first);
    break;

  case '+':
    first = (total != 0 ? total : first);
    // lcd.setCursor(0,1);
    lcd.print("+");
    second = SecondNumber(); // get the collected the second number
    total = first + second;
    lcd.setCursor(0,1);
    lcd.print(total);
    first = 0, second = 0; // reset values back to zero for next use
    break;

  case '-':
    first = (total != 0 ? total : first);
    // lcd.setCursor(0,1);
    lcd.print("-");
    second = SecondNumber();
    total = first - second;
    lcd.setCursor(0,1);
    lcd.print(total);
    first = 0, second = 0;
    break;

  case '*':
    first = (total != 0 ? total : first);
    // lcd.setCursor(0,1);
    lcd.print("*");
    second = SecondNumber();
    total = first * second;
    lcd.setCursor(0,1);
    lcd.print(total);
    first = 0, second = 0;
    break;

  case '/':
    first = (total != 0 ? total : first);
    // lcd.setCursor(0,1);
    lcd.print("/");
    second = SecondNumber();
    lcd.setCursor(0,1);

    second == 0 ? lcd.print("Invalid") : total = (float)first / (float)second;

    lcd.print(total);
    first = 0, second = 0;
    break;

  case 'C':
    total = 0;
    lcd.clear();
    break;
  }
}

void binaryCalculator() {
  switch(customKey) {
  case '0' ... '1': // This keeps collecting the first value until a operator is pressed "+-*/"
    lcd.setCursor(0,0);
    first = first * 10 + (customKey - '0');
    lcd.print(first);
    break;

  case '+':
    first = (total != 0 ? total : first);
    // lcd.setCursor(0,1);
    lcd.print("+");
    second = SecondNumber(); // get the collected the second number
    total = first + second;
    lcd.setCursor(0,1);
    lcd.print(total);
    first = 0, second = 0; // reset values back to zero for next use
    break;

  case '-':
    first = (total != 0 ? total : first);
    // lcd.setCursor(0,1);
    lcd.print("-");
    second = SecondNumber();
    total = first - second;
    lcd.setCursor(0,1);
    lcd.print(total);
    first = 0, second = 0;
    break;

  case '*':
    first = (total != 0 ? total : first);
    // lcd.setCursor(0,1);
    lcd.print("*");
    second = SecondNumber();
    total = first * second;
    lcd.setCursor(0,1);
    lcd.print(total);
    first = 0, second = 0;
    break;

  case '/':
    first = (total != 0 ? total : first);
    // lcd.setCursor(0,1);
    lcd.print("/");
    second = SecondNumber();
    lcd.setCursor(0,1);

    second == 0 ? lcd.print("Invalid") : total = (float)first / (float)second;

    lcd.print(total);
    first = 0, second = 0;
    break;

  case 'C':
    total = 0;
    lcd.clear();
    break;
  }
}

void octalCalculator() {

}

void decimalToBinaryCalculator() {

}

void decimalToOctalCalculator() {

}

void binaryToDecimalCalculator() {

}

void binaryToOctalCalculator() {

}

void octalToBinaryCalculator() {

}

void octalToDecimalCalculator() {

}

void setup() {
  lcd.begin(16, 2);               // start lcd
  lcd.setCursor(0,0);
}

void loop() {
  char key = keypad.getKey();

  while(!(key >= '0' && key <= '9') && (key != 'C') && (key != '='))
    key = keypad.getKey();

  lcd.print(key);

}

long SecondNumber() {
  while(1) {
    customKey = keypad.getKey();
    if(customKey >= '0' && customKey <= '9') {
      second = second * 10 + (customKey - '0');
      // lcd.setCursor(0,2);
      lcd.print(" ");
      lcd.print(second);
    }

    if(customKey == '=') {
      lcd.print("=");
      break;  //return second;
    }
  }
 return second;
}
