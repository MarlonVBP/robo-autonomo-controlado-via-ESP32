#include "motor_control.h"

// Matriz de sequência de passos para motores de passo (modo full-step)
const int stepSequence[8][4] = {
  {1, 0, 0, 1},
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1}
};

// Variável global para controle de parada
bool parar = false;

// Função para mover um motor
void moveMotor(int motor, int direction, int steps) {
  int pins[4];
  if (motor == 1) {
    pins[0] = M1_IN1; pins[1] = M1_IN2; pins[2] = M1_IN3; pins[3] = M1_IN4;
  } else {
    pins[0] = M2_IN1; pins[1] = M2_IN2; pins[2] = M2_IN3; pins[3] = M2_IN4;
  }

  for (int s = 0; s < steps && !parar; s++) {
    for (int i = 0; i < 8 && !parar; i++) {
      int stepIndex = direction ? i : 7 - i;
      for (int j = 0; j < 4; j++) {
        digitalWrite(pins[j], stepSequence[stepIndex][j]);
      }
      delay(2);
    }
  }

  if (parar) {
    parar = false;
    pararMotores();
  }
}

// Parar todos os motores
void pararMotores() {
  int motorPins[] = {M1_IN1, M1_IN2, M1_IN3, M1_IN4, M2_IN1, M2_IN2, M2_IN3, M2_IN4};
  for (int i = 0; i < 8; i++) {
    digitalWrite(motorPins[i], LOW);
  }
}

// Movimentos simultâneos dos dois motores
void moverAmbos(int dir1, int dir2, int steps) {
  for (int s = 0; s < steps && !parar; s++) {
    for (int i = 0; i < 8 && !parar; i++) {
      int stepIndex1 = dir1 ? i : 7 - i;
      int stepIndex2 = dir2 ? i : 7 - i;

      digitalWrite(M1_IN1, stepSequence[stepIndex1][0]);
      digitalWrite(M1_IN2, stepSequence[stepIndex1][1]);
      digitalWrite(M1_IN3, stepSequence[stepIndex1][2]);
      digitalWrite(M1_IN4, stepSequence[stepIndex1][3]);

      digitalWrite(M2_IN1, stepSequence[stepIndex2][0]);
      digitalWrite(M2_IN2, stepSequence[stepIndex2][1]);
      digitalWrite(M2_IN3, stepSequence[stepIndex2][2]);
      digitalWrite(M2_IN4, stepSequence[stepIndex2][3]);

      delay(2);
    }
  }

  if (parar) {
    parar = false;
    pararMotores();
  }
}

// Funções de movimento do robô
void frente(int steps) {
  moverAmbos(0, 1, steps);
}

void re(int steps) {
  moverAmbos(1, 0, steps);
}

void esquerda(int steps) {
  moverAmbos(1, 1, steps);
}

void direita(int steps) {
  moverAmbos(0, 0, steps);
}