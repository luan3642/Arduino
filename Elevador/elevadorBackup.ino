// Strip
#include <Adafruit_NeoPixel.h>
const byte PIN_STRIP = 7;  // input pin Neopixel is attached to
const byte NUMPIXELS = 10; // number of neopixels in Ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_STRIP, NEO_GRB + NEO_KHZ800);
bool subindo = false;
bool descendo = false;

int delayval = 200; // timing delay

int redColor = 0;
int greenColor = 0;
int blueColor = 255;

// Floor button
const byte PORTA_INTERRUPCAO_BOTOES_ANDAR = 2;

// Elevator button
const byte PORTA_INTERRUPCAO_BOTOES_ELEVADOR = 3;

// LEDS
const byte LED_VERMELHO = 8;
const byte LED_AZUL = 9;
const byte LED_AMARELO = 10;

bool operante = false;
bool porta_aberta = false;
bool emergencia = false;

int counter = 1;

void ligue(int porta) {
  digitalWrite(porta, HIGH);
}

void desligue(int porta) {
  digitalWrite(porta, LOW);
}



//-----------------------------------------------------------------
// função para tratamento da interrupção gerada pelo botão do andar

void int_botao_floor() {
  int codigo = analogRead(A5);
  switch (codigo) {
    case 40:
      Serial.println("Terreo subindo");
      break;
    case 77:
      Serial.println("1o andar subindo");
      break;
    case 112:
      Serial.println("2o andar subindo");
      break;
    case 144:
      Serial.println("3o andar subindo");
      break;
    case 173:
      Serial.println("4o andar subindo");
      break;
    case 201:
      Serial.println("5o andar subindo");
      break;
    case 227:
      Serial.println("6o andar subindo");
      break;
    case 252:
      Serial.println("7o andar subindo");
      break;
    case 275:
      Serial.println("8o andar subindo");
      break;
    case 296:
      Serial.println("1o andar descendo");
      break;
    case 317:
      Serial.println("2o andar descendo");
      break;
    case 336:
      Serial.println("3o andar descendo");
      break;
    case 355:
      Serial.println("4o andar descendo");
      break;
    case 372:
      Serial.println("5o andar descendo");
      break;
    case 388:
      Serial.println("6o andar descendo");
      break;
    case 404:
      Serial.println("7o andar descendo");
      break;
    case 419:
      Serial.println("8o andar descendo");
      break;
    case 433:
      Serial.println("9o andar descendo");
      break;
  }
}

//--------------------------------------------------------------------
// função para tratamento da interrupção gerada pelo botão do elevador

void int_botao_elevador() {
  Serial.print("Botao apertado: ");
  int codigo = analogRead(A0);
  Serial.println(codigo);

 switch (codigo) {
    case 40:
      Serial.println("Terreo subindo");
      break;
    case 77:
      Serial.println("1o andar");
      break;
    case 112:
      Serial.println("2o andar");
      break;
    case 144:
      Serial.println("3o andar");
      break;
    case 173:
      Serial.println("4o andar");
      break;
    case 201:
      Serial.println("5o andar");
      break;
    case 227:
      Serial.println("6o andar");
      break;
    case 252:
      Serial.println("7o andar");
      break;
    case 275:
      Serial.println("8o andar");
      break;
    case 296:
      Serial.println("9o andar");
      break;
    case 317:
      Serial.println("PORTA");
      break;
    case 336:
      Serial.println("ON");
      break;
    case 355:
      Serial.println("OFF");
      break;
    case 372:
      Serial.println("EMERGENCIA");
      break;
  }
}

//--------------------------------------------------------

void setup() {
  Serial.begin(9600);

  pixels.begin(); // Initializes the NeoPixel library.

  pinMode(PORTA_INTERRUPCAO_BOTOES_ANDAR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PORTA_INTERRUPCAO_BOTOES_ANDAR), int_botao_floor, FALLING);

  pinMode(PORTA_INTERRUPCAO_BOTOES_ELEVADOR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PORTA_INTERRUPCAO_BOTOES_ELEVADOR), int_botao_elevador, FALLING);

  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO , OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
}

//--------------------------------------------------------

void loop() {
  subindo = true;

  if(subindo) {
    for(int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
        delay(1000);
        pixels.setPixelColor(i+1, pixels.Color(redColor, greenColor, blueColor));
        pixels.show();
        delay(1000);
        pixels.setPixelColor(i,0,0,0);
    pixels.show();
    }
    descendo = true;
    subindo = false;
  }
  delay(1000);

  if(descendo) {
    for(int i = 9; i != -1; i--){
      pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
        delay(1000);
        pixels.setPixelColor(i-1, pixels.Color(redColor, greenColor, blueColor));
        pixels.show();
        delay(1000);
        pixels.setPixelColor(i,0,0,0);
    pixels.show();
    }
    descendo = false;
    subindo = true;
  }

  operante = true;
  emergencia = false;
  porta_aberta = false;
  if(counter%3== 0){
  	porta_aberta = true;
  }
  if(counter%5 == 0) {
  	emergencia = true;
  }
  if(counter%10 == 0) {
  	operante = false;
  }
  if(operante) {
  	ligue(LED_AMARELO);
  }
  if(operante == false) {
  	desligue(LED_AMARELO);
  }
  if(porta_aberta) {
  	ligue(LED_AZUL);
  }
  if(porta_aberta == false) {
  	desligue(LED_AZUL);
  }
  if(emergencia) {
  	ligue(LED_VERMELHO);
    desligue(LED_AMARELO);
    desligue(LED_AZUL);
  }
  if(emergencia == false) {
  	desligue(LED_VERMELHO);
  }
  counter++;
  delay(3000);
}
