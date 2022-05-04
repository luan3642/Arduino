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

void setup() {
  Serial.begin(9600);
}

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

void estado_INOPERANTE()
{
  Serial.println("==> INOPERANTE");
  estado = OCIOSO;
}

void estado_OCIOSO()
{
  Serial.println("==> OCIOSO");
  estado = ALINHADO_S;
  //estado = ALINHADO_D;
  //estado = INOPERANTE;
}

void estado_ALINHADO_S()
{
  Serial.println("==> ALINHADO_S");
  //estado = ESTACIONADO_S;
  //estado = MOVENDO_S;
  estado = FIM_S;
}

void estado_MOVENDO_S()
{
  Serial.println("==> MOVENDO_S");
  estado = ALINHADO_S;
}

void estado_ESTACIONADO_S()
{ 
  Serial.println("==> ESTACIONADO_S");
  estado = ALINHADO_S; 
}

void estado_FIM_S()
{
  Serial.println("==> FIM_S");
  estado = OCIOSO;
  //estado = ALINHADO_D;
}

void estado_ALINHADO_D()
{
  Serial.println("==> ALINHADO_D");
  estado = ESTACIONADO_D;
  //estado = MOVENDO_D;
  //estado = FIM_D;
}

void estado_MOVENDO_D()
{
  Serial.println("==> MOVENDO_D");
  estado = ALINHADO_D;
}

void estado_ESTACIONADO_D()
{
  Serial.println("==> ESTACIONADO_D");
  estado = ALINHADO_D;
}

void estado_FIM_D()
{
  Serial.println("==> FIM_D");
  estado = OCIOSO;
  //estado = ALINHADO_S;
}
