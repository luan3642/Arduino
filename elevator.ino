#include <Adafruit_NeoPixel.h>

// VARIAVEIS GLOBAIS
//-----------------------------------------------------------------

// Flags de controler - Andares
bool floorU[10] = { false,
                    false,
                    false,
                    false,
                    false,
                    false,
                    false,
                    false,
                    false,
                    false};

bool floorD[10] = { false,
                    false,
                    false,
                    false,
                    false,
                    false,
                    false,
                    false,
                    false,
                    false};

int currentFloor = 0;
int demandedFloor = 0;

// Flags de controler - Elevador
bool andar_elevador[10] = { false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false};

bool on = true;

bool door = false;
bool emergency = false;

bool openDoor = false;

// Strip
const byte PIN_STRIP = 7;  // input pin Neopixel is attached to
const byte NUMPIXELS = 10; // number of neopixels in Ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_STRIP, NEO_GRB + NEO_KHZ800);

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

// Enum de estados
//-----------------------------------------------------------------
enum { INOPERANTE,
       OCIOSO,
       ALINHADO_S,
       MOVENDO_S,
       ESTACIONADO_S,
       FIM_S,
       ALINHADO_D,
       MOVENDO_D,
       ESTACIONADO_D,
       FIM_D} estado = INOPERANTE;

// Funcoes de controle mudança de estado
//-----------------------------------------------------------------
bool ha_destino(int andar) {
  return andar_elevador[andar];
}

bool ha_chamada_S(int andar) {
  return floorU[andar];
}

bool ha_chamada_D(int andar) {
  return floorD[andar];
}

bool ha_demanda_acima(int andar) {
  for(int i=andar+1;i<10;i++) {
    if(floorU[i] || floorD[i]) {
      return true;
    }
  }
  return false;
}

bool ha_demanda_abaixo(int andar) {
  for(int i=andar-1;i>=0;i--) {
    if(floorU[i] || floorD[i]) {
      return true;
    }
  }
  return false;
}

bool ha_demanda() {
  for(int i=0;i<10;i++) {
    if (floorD[i] || floorU[i] || andar_elevador[i]) {
      return true;
    }
  }
  return false;
}

bool ha_emergencia() {
  return emergency;
}

void desmarcar_chamadaS(int andar) {
  floorU[andar] = false;
}

void desmarcar_chamadaD(int andar) {
  floorD[andar] = false;
}

void desmarcar_destino(int andar) {
  andar_elevador[andar] = false;
}

void desmarcar_emergencia() {
  emergency = false;
}

// Funcoes de estados
//-----------------------------------------------------------------

void estado_INOPERANTE() {
  if(on) {
    estado = OCIOSO;
  }
}

void estado_OCIOSO() {
  Serial.println("==> OCIOSO");
  if(on && ha_demanda()) {
    if (demandedFloor >= currentFloor) {
      estado = ALINHADO_S;
      delay(3000);
    } else {
      estado = ALINHADO_D;
      delay(3000);
    }
  } else if (!on){
    estado = INOPERANTE;
  }
}

void estado_ALINHADO_S() {
  Serial.println("==> ALINHADO_S");
  if(ha_chamada_S(currentFloor) || ha_destino(currentFloor) || ha_emergencia()) {
    openDoor = true;
    estado = ESTACIONADO_S;
    delay(3000);
  } else if (ha_demanda_acima(currentFloor)) {
    estado = MOVENDO_S;
  } else {
      estado = FIM_S;
      delay(3000);
  }
}

void estado_MOVENDO_S() {
  Serial.println("==> MOVENDO_S");
  currentFloor++;
  estado = ALINHADO_S;
  delay(3000);
}

void estado_ESTACIONADO_S() {
  Serial.println("==> ESTACIONADO_S");
  openDoor = false;
  desmarcar_chamadaS(currentFloor);
  desmarcar_destino(currentFloor);
  desmarcar_emergencia();
  estado = ALINHADO_S;
  delay(3000);
}

void estado_FIM_S() {
  Serial.println("==> FIM_S");
  if(ha_demanda_abaixo(currentFloor) || ha_chamada_D(currentFloor)) {
    estado = ALINHADO_D;
  } else {
    estado = OCIOSO;
  }
}

void estado_ALINHADO_D() {
  Serial.println("==> ALINHADO_D");
  if(ha_chamada_D(currentFloor) || ha_destino(currentFloor) || ha_emergencia()) {
    openDoor = true;
    estado = ESTACIONADO_D;
    delay(3000);
  } else if (ha_demanda_abaixo(currentFloor)) {
    estado = MOVENDO_D;
  } else {
      estado = FIM_D;
      delay(3000);
  }
}

void estado_MOVENDO_D() {
  Serial.println("==> MOVENDO_D");
  currentFloor--;
  estado = ALINHADO_D;
  delay(3000);
}

void estado_ESTACIONADO_D() {
  Serial.println("==> ESTACIONADO_D");
  openDoor = false;
  desmarcar_chamadaD(currentFloor);
  desmarcar_destino(currentFloor);
  desmarcar_emergencia();
  estado = ALINHADO_D;
  delay(3000);
}

void estado_FIM_D() {
  Serial.println("==> FIM_D");
  if(ha_demanda_acima(currentFloor) || ha_chamada_S(currentFloor)) {
    estado = ALINHADO_S;
  } else {
    estado = OCIOSO;
  }
}

//-----------------------------------------------------------------
// função para tratamento da interrupção gerada pelo botão do andar

void int_botao_floor() {
  int codigo = analogRead(A5);
  switch (codigo) {
    case 40:
      floorU[0] = true;
      break;
    case 77:
      floorU[1] = true;
      break;
    case 112:
      floorU[2] = true;
      break;
    case 144:
      floorU[3] = true;
      break;
    case 173:
      floorU[4] = true;
      break;
    case 201:
      floorU[5] = true;
      break;
    case 227:
      floorU[6] = true;
      break;
    case 252:
      floorU[7] = true;
      break;
    case 275:
      floorU[8] = true;
      break;
    case 296:
      floorD[1] = true;
      break;
    case 317:
      floorD[2] = true;
      break;
    case 336:
      floorD[3] = true;
      break;
    case 355:
      floorD[4] = true;
      break;
    case 372:
      floorD[5] = true;
      break;
    case 388:
      floorD[6] = true;
      break;
    case 404:
      floorD[7] = true;
      break;
    case 419:
      floorD[8] = true;
      break;
    case 433:
      floorD[9] = true;
      break;
  }
}

//--------------------------------------------------------------------
// função para tratamento da interrupção gerada pelo botão do elevador

void int_botao_elevador() {
  int codigo = analogRead(A0);
  Serial.println(codigo);

 switch (codigo) {
    case 40:
      andar_elevador[0] = true;
      break;
    case 77:
      andar_elevador[1] = true;
      break;
    case 112:
      andar_elevador[2] = true;
      break;
    case 144:
      andar_elevador[3] = true;
      break;
    case 173:
      andar_elevador[4] = true;
      break;
    case 201:
      andar_elevador[5] = true;
      break;
    case 227:
      andar_elevador[6] = true;
      break;
    case 252:
      andar_elevador[7] = true;
      break;
    case 275:
      andar_elevador[8] = true;
      break;
    case 296:
      andar_elevador[9] = true;
      break;
    case 317:
      door = true;
      break;
    case 336:
      on = true;
      break;
    case 355:
      on = false;
      break;
    case 372:
      emergency = true;
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
  switch (estado) {
    case INOPERANTE: estado_INOPERANTE(); break;
    case OCIOSO: estado_OCIOSO(); break;
    case ALINHADO_S: estado_ALINHADO_S(); break;
    case MOVENDO_S: estado_MOVENDO_S(); break;
    case ESTACIONADO_S: estado_ESTACIONADO_S(); break;
    case FIM_S: estado_FIM_S(); break;
    case ALINHADO_D: estado_ALINHADO_D(); break;
    case MOVENDO_D: estado_MOVENDO_D(); break;
    case ESTACIONADO_D: estado_ESTACIONADO_D(); break;
    case FIM_D: estado_FIM_D(); break;
    default: Serial.println("ESTADO INVÁLIDO");
  }
}
