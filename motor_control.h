#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

// Pinos do Motor 1
#define M1_IN1 13
#define M1_IN2 4
#define M1_IN3 14
#define M1_IN4 27

// Pinos do Motor 2
#define M2_IN1 26
#define M2_IN2 25
#define M2_IN3 33
#define M2_IN4 32

// Matriz de sequência de passos para motores de passo (modo full-step)
extern const int stepSequence[8][4];

// Variável global para controle de parada
extern bool parar;

// Funções para controle dos motores
void moveMotor(int motor, int direction, int steps);
void pararMotores();
void moverAmbos(int dir1, int dir2, int steps);
void frente(int steps);
void re(int steps);
void esquerda(int steps);
void direita(int steps);

#endif