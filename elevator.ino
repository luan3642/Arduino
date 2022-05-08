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
  if(emergency) {
    openDoor = true;
    estado = ESTACIONADO_S;
    delay(3000);
  } else if (hasDemand) {
    switch (currentFloor) {
      case 0:
        estado = MOVENDO_S;
      case 1:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else if(firstU[1]) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 2:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else if(firstU[2]) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 3:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else if(firstU[3]) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 4:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else if(firstU[4]) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 5:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else if(firstU[5]) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 6:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else if(firstU[6]) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 7:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else if(firstU[7]) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 8:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else if(firstU[8]) {
          openDoor = true;
          estado = ESTACIONADO_S;
        } else {
          estado = MOVENDO_S;
        }
        break;
      case 9:
        openDoor = true;
        estado = ESTACIONADO_S;
        break;
      default:
        break;
    }
    delay(3000);
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
  estado = ALINHADO_S;
  delay(3000);
}

void estado_FIM_S() {
  Serial.println("==> FIM_S");
  estado = OCIOSO;
}

void estado_ALINHADO_D() {
  Serial.println("==> ALINHADO_D");
  estado = ESTACIONADO_D;
  if(emergency) {
    openDoor = true;
    estado = ESTACIONADO_D;
    delay(3000);
  } else if (hasDemand) {
    switch (currentFloor) {
      case 0:
        estado = MOVENDO_D;
      case 1:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else if(firstU[1]) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 2:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else if(firstU[2]) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 3:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else if(firstU[3]) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 4:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else if(firstU[4]) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 5:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else if(firstU[5]) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 6:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else if(firstU[6]) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 7:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else if(firstU[7]) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 8:
        if(demandedFloor == currentFloor) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else if(firstU[8]) {
          openDoor = true;
          estado = ESTACIONADO_D;
        } else {
          estado = MOVENDO_D;
        }
        break;
      case 9:
        estado = MOVENDO_D;
        break;
      default:
        break;
    }
    delay(3000);
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
  estado = ALINHADO_D;
  delay(3000);
}

void estado_FIM_D() {
  Serial.println("==> FIM_D");
  estado = OCIOSO;
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

  // delay(1000); // apenas para teste inicial da máquina de estados
}
