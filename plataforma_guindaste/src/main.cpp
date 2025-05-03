#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa LCD no endereço 0x27, com 16 colunas e 2 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pinos dos botões
#define BTN_P1 12
#define BTN_P2 13
#define BTN_P3 14

// Motores
#define MOTOR_DIR 25
#define MOTOR_ESQ 26

// Garra
#define GAR_FG 19 // led vermelho
#define GAR_AG 18 // led azul

// Sensores de posição
#define FIM_CURSO_P1 34
#define FIM_CURSO_P2 35
#define FIM_CURSO_P3 32

// Variáveis de controle
volatile int destino = 0; // 1 para P1, 2 para P2, 3 para P3
int posicaoAtual = 1;     // Consideramos que o carro inicia em P1
bool movimentoEmAndamento = false;
int retornoDestino = 0;

// INICIALIZAÇÃO DAS FUNÇÕES
void fecharGarra();
void abrirGarra();
void executarMovimento(int destinoFinal);
void moverParaDestino(int destinoFinal);
int fimDeCurso(int posto);
void mostrarMensagem(String linha1, String linha2);

// FUNÇÃO DAS INTERRUPÇÕES
// void IRAM_ATTR selecionarP1() { destino = 1; }
// void IRAM_ATTR selecionarP2() { destino = 2; }
// void IRAM_ATTR selecionarP3() { destino = 3; }

void IRAM_ATTR selecionarP1()
{
  if (!movimentoEmAndamento && digitalRead(BTN_P2) == HIGH && digitalRead(BTN_P3) == HIGH)
  {
    destino = 1;
  }
}

void IRAM_ATTR selecionarP2()
{
  if (!movimentoEmAndamento && digitalRead(BTN_P1) == HIGH && digitalRead(BTN_P3) == HIGH)
  {
    destino = 2;
  }
}

void IRAM_ATTR selecionarP3()
{
  if (!movimentoEmAndamento && digitalRead(BTN_P1) == HIGH && digitalRead(BTN_P2) == HIGH)
  {
    destino = 3;
  }
}

void setup()
{

  lcd.init();      // Inicializa o LCD
  lcd.backlight(); // Liga a luz de fundo
  mostrarMensagem("Sistema pronto!", "P" + String(posicaoAtual));

  // Configuração dos pinos
  pinMode(BTN_P1, INPUT_PULLUP);
  pinMode(BTN_P2, INPUT_PULLUP);
  pinMode(BTN_P3, INPUT_PULLUP);

  pinMode(MOTOR_DIR, OUTPUT);
  pinMode(MOTOR_ESQ, OUTPUT);

  pinMode(GAR_FG, OUTPUT);
  pinMode(GAR_AG, OUTPUT);

  pinMode(FIM_CURSO_P1, INPUT_PULLUP);
  pinMode(FIM_CURSO_P2, INPUT_PULLUP);
  pinMode(FIM_CURSO_P3, INPUT_PULLUP);

  // Inicialmente motores e garra desligados
  digitalWrite(MOTOR_DIR, LOW);
  digitalWrite(MOTOR_ESQ, LOW);
  digitalWrite(GAR_FG, LOW);
  digitalWrite(GAR_AG, LOW);

  // Interrupções para botões
  attachInterrupt(digitalPinToInterrupt(BTN_P1), selecionarP1, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_P2), selecionarP2, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_P3), selecionarP3, FALLING);
}

void loop()
{
  if (destino != 0 && !movimentoEmAndamento)
  {
    movimentoEmAndamento = true;
    executarMovimento(destino);
    movimentoEmAndamento = false;
    destino = 0; // Espera novo comando
  }
}

// FUNÇÃO DE MOVIMENTAÇÃO ATÉ O FINAL
void executarMovimento(int destinoFinal)
{
  // Fecha garra antes de mover
  fecharGarra();
  // Movimenta até o destino
  moverParaDestino(destinoFinal);
  //  Abre garra ao chegar
  abrirGarra();
  // Atualiza posição atual
  posicaoAtual = destinoFinal;

  if (retornoDestino == 1 || retornoDestino == 2)
  {
    // mostrarMensagem("Movendo para ", "P" + String(destinoFinal));
    mostrarMensagem("Chegou no ", "P" + String(destinoFinal));
  }
}

void fecharGarra()
{
  digitalWrite(GAR_AG, LOW);  // garra não aberta (garantia)
  digitalWrite(GAR_FG, HIGH); // garra fechada
  delay(1000);                // Tempo de fechamento da garra
}

void abrirGarra()
{
  digitalWrite(GAR_FG, LOW);  // garra não fechada (garantia)
  digitalWrite(GAR_AG, HIGH); // garra aberta
  delay(1000);                // Tempo de abertura da garra
}

void moverParaDestino(int destinoFinal)
{
  if (destinoFinal == posicaoAtual)
  {
    mostrarMensagem("Ja no destino!", String(destinoFinal));
    retornoDestino = 0;
    return; // Já está no destino
  }

  if (destinoFinal > posicaoAtual)
  {
    // Movimento para Direita
    mostrarMensagem("Movendo p/ Direita!", "Para P" + String(destinoFinal));

    // Aguarda o sensor ser desacionado, se já estiver pressionado
    while (fimDeCurso(destinoFinal))
      delay(50);
    digitalWrite(MOTOR_DIR, HIGH);
    // Agora sim espera o sensor ser pressionado
    while (!fimDeCurso(destinoFinal))
      delay(50);

    digitalWrite(MOTOR_DIR, LOW);
    retornoDestino = 1;
    // return 2;
  }
  else
  {
    // Movimento para Esquerda
    mostrarMensagem("Movendo p/ Esquerda!", "Para P" + String(destinoFinal));

    // Aguarda o sensor ser desacionado, se já estiver pressionado
    while (fimDeCurso(destinoFinal))
      delay(50);
    digitalWrite(MOTOR_ESQ, HIGH);

    // Agora sim espera o sensor ser pressionado
    while (!fimDeCurso(destinoFinal))
      delay(50);

    digitalWrite(MOTOR_ESQ, LOW);
    retornoDestino = 2;
    // return 3;
  }
}

int fimDeCurso(int posto)
{
  switch (posto)
  {
  case 1:
    return digitalRead(FIM_CURSO_P1) == LOW;
    // return digitalRead(FIM_CURSO_P1);
  case 2:
    return digitalRead(FIM_CURSO_P2) == LOW;
    // return digitalRead(FIM_CURSO_P2);
  case 3:
    return digitalRead(FIM_CURSO_P3) == LOW;
    // return digitalRead(FIM_CURSO_P3);
  default:
    return false;
  }
}

void mostrarMensagem(String linha1, String linha2)
{
  lcd.clear(); // Limpa qualquer coisa antiga
  lcd.setCursor(0, 0);
  lcd.print(linha1);
  lcd.setCursor(0, 1);
  lcd.print(linha2);
}

// void app_main() {}