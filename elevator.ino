// Fiz algumas coisinhas 

#include <Adafruit_NeoPixel.h>

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

// Flags de controler - Andares
bool floorU[9] = [false,
                  false,
                  false,
                  false,
                  false,
                  false,
                  false,
                  false,
                  false];

bool floorD[9] = [false,
                  false,
                  false,
                  false,
                  false,
                  false,
                  false,
                  false,
                  false];

int currentFloor = 0;
int demandedFloor = 0;

// Flags de controler - Elevador
bool andar_elevador[10] = [ false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false];

bool on = true;

bool door = false;
bool emergency = false;

bool openDoor = false;

bool hasDemand = false;

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

// Funcoes de estados
//-----------------------------------------------------------------

void estado_INOPERANTE() {
  if(on) {
    estado = OCIOSO;
  }
}

void estado_OCIOSO() {
  Serial.println("==> OCIOSO");
  if(on && hasDemand) {
    if (currentFloor <= demandedFloor) {
      estado = ALINHADO_S;
    } else {
      estado = ALINHADO_D;
    }
  } else {
    estado = INOPERANTE;
  }
}

void estado_ALINHADO_S() {
  Serial.println("==> ALINHADO_S");
  if(emergency) {
    estado = ESTACIONADO_S;
    return;
  } else if (hasDemand) {
    switch (currentFloor) {
      case 0:
        estado = MOVENDO_S;
      case 1:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_S;
        } else if(firstU[1]) {
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 2:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_S;
        } else if(firstU[2]) {
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 3:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_S;
        } else if(firstU[3]) {
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 4:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_S;
        } else if(firstU[4]) {
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 5:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_S;
        } else if(firstU[5]) {
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 6:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_S;
        } else if(firstU[6]) {
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 7:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_S;
        } else if(firstU[7]) {
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 8:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_S;
        } else if(firstU[8]) {
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 9:
        estado = ESTACIONADO_S;
        break;
      default:
        break;
    }
  } else {
      estado = FIM_S;
  }
}

void estado_MOVENDO_S() {
  Serial.println("==> MOVENDO_S");
  currentFloor++;
  estado = ALINHADO_S;
}

void estado_ESTACIONADO_S() {
  Serial.println("==> ESTACIONADO_S");
  openDoor = true;

  if (emergency) {
    emergency = false;
    // acredito que nesse estado a porta está aberta
    openDoor = true;
    estado = ALINHADO_S;
  } else if (currentFloor == demandedFloor) {
      estado = ESTACIONADO_S
  }


  estado = ALINHADO_S;
}

void estado_FIM_S() {
  Serial.println("==> FIM_S");
  estado = OCIOSO;
  //estado = ALINHADO_D;
}

void estado_ALINHADO_D() {
  Serial.println("==> ALINHADO_D");
  if(emergency) {
    estado = ESTACIONADO_D;
    return;
  } else if (hasDemand) {
    switch (currentFloor) {
      case 0:
        estado = MOVENDO_D;
      case 1:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_D;
        } else if(firstU[1]) {
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 2:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_D;
        } else if(firstU[2]) {
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 3:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_D;
        } else if(firstU[3]) {
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 4:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_D;
        } else if(firstU[4]) {
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 5:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_D;
        } else if(firstU[5]) {
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 6:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_D;
        } else if(firstU[6]) {
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 7:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_D;
        } else if(firstU[7]) {
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 8:
        if(demandedFloor == currentFloor) {
          estado = ESTACIONADO_D;
        } else if(firstU[8]) {
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 9:
        estado = ESTACIONADO_D;
        break;
      default:
        break;
    }
  } else {
      estado = FIM_D;
  }
}

void estado_MOVENDO_D() {
  Serial.println("==> MOVENDO_S");
  currentFloor--;
  estado = ALINHADO_S;
}

void estado_ESTACIONADO_D() {
  Serial.println("==> ESTACIONADO_D");
  openDoor = true;

  if (emergency) {
    emergency = false;
    // acredito que nesse estado a porta está aberta
    openDoor = true;
    estado = ALINHADO_S;
  } else if (currentFloor == demandedFloor) {
      estado = ESTACIONADO_S
  }


  estado = ALINHADO_S;
}

void estado_FIM_D() {
  Serial.println("==> FIM_D");
  estado = OCIOSO;
  //estado = ALINHADO_D;
}

//-----------------------------------------------------------------
// função para tratamento da interrupção gerada pelo botão do andar

void int_botao_floor() {
  hasDemand = true;
  int codigo = analogRead(A5);
  switch (codigo) {
    case 40:
      floorU[0] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 0;
      }
      break;
    case 77:
      firstU[1] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 1;
      }
      break;
    case 112:
      firstU[2] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 2;
      }
      break;
    case 144:
      firstU[3] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 3;
      }
      break;
    case 173:
      firstU[4] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 4;
      }
      break;
    case 201:
      firstU[5] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 5;
      }
      break;
    case 227:
      firstU[6] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 6;
      }
      break;
    case 252:
      firstU[7] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 7;
      }
      break;
    case 275:
      firstU[8] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 8;
      }
      break;
    case 296:
      firstD[0] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 1;
      }
      break;
    case 317:
      firstD[1] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 2;
      }
      break;
    case 336:
      firstD[2] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 3;
      }
      break;
    case 355:
      firstD[3] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 4;
      }
      break;
    case 372:
      firstD[4] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 5;
      }
      break;
    case 388:
      firstD[5] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 6;
      }
      break;
    case 404:
      firstD[6] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 7;
      }
      break;
    case 419:
      firstD[7] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 8;
      }
      break;
    case 433:
      firstD[8] = true;
      if (!(demandedFloor == currentFloor)) {
        demandedFloor = 9;
      }
      break;
  }
}

//--------------------------------------------------------------------
// função para tratamento da interrupção gerada pelo botão do elevador

void int_botao_elevador() {
  hasDemand = true;
  int codigo = analogRead(A0);
  Serial.println(codigo);

 switch (codigo) {
    case 40:
      floor = true;
      break;
    case 77:
      first = true;
      break;
    case 112:
      second = true;
      break;
    case 144:
      third = true;
      break;
    case 173:
      fourth = true;
      break;
    case 201:
      fifth = true;
      break;
    case 227:
      sixth = true;
      break;
    case 252:
      seventh = true;
      break;
    case 275:
      eighth = true;
      break;
    case 296:
      ninth = true;
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
  Serial.print("Entrando no loop ");
  Serial.print("[");
  Serial.print(estado);
  Serial.print("] ");

  switch (estado)
  {
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

  delay(1000); // apenas para teste inicial da máquina de estados
}
