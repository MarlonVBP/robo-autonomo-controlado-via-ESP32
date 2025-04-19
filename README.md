# 🤖 Robô Autônomo Controlado via ESP32 🚗

Este projeto implementa um robô autônomo controlado remotamente usando um ESP32 🎮. O robô utiliza dois motores de passo para movimentação, controlados por drivers ULN2003, e um servidor web assíncrono para receber comandos via Wi-Fi 📡. Uma interface web permite controlar o robô (frente, ré, esquerda, direita) e os motores individualmente 🕹️.

## ✨ Funcionalidades

- Controle remoto via Wi-Fi usando um ESP32 📶.
- Interface web com botões para movimentar o robô: frente ⬆️, ré ⬇️, esquerda ⬅️, direita ➡️.
- Controle individual dos motores (horário 🔄 e anti-horário 🔄).
- Botão de parada de emergência para interromper os motores 🚨.

## 📂 Estrutura do Projeto

O projeto está organizado em três arquivos principais:

- `main.ino` 📄: Configuração do Wi-Fi, inicialização dos pinos e servidor web assíncrono.
- `motor_control.h` 📜: Definições de pinos, constantes e protótipos das funções de controle dos motores.
- `motor_control.cpp` 💻: Implementação das funções de controle dos motores.

## 🛠️ Requisitos

### ⚙️ Hardware

- ESP32 (qualquer modelo compatível, ex.: ESP32 DevKit V1) 🖥️.
- 2x Motores de passo unipolares (ex.: 28BYJ-48) 🔧.
- 2x Drivers ULN2003 para motores de passo 🔌.
- Fonte de alimentação de 5V (para o ESP32 e lógica dos ULN2003) 🔋.
- Fonte de alimentação de 12V (para os motores) 🔋.
- Cabos jumper e protoboard para conexões 🪢.

### 💾 Software

- Arduino IDE (ou outra IDE compatível com ESP32) 🖥️.
- Bibliotecas:
  - `WiFi.h` (incluída na instalação do ESP32 na Arduino IDE) 📚.
  - `ESPAsyncWebServer.h` (instale via Library Manager ou GitHub) 📦.

## 🔧 Diagrama Elétrico

O diagrama elétrico mostra as conexões entre o ESP32, os drivers ULN2003 e os motores de passo ⚡:

- **ESP32** 🖥️:
  - Motor 1: GPIO 13 → IN1, GPIO 4 → IN2, GPIO 14 → IN3, GPIO 27 → IN4.
  - Motor 2: GPIO 26 → IN1, GPIO 25 → IN2, GPIO 33 → IN3, GPIO 32 → IN4.
  - VIN → +5V, GND → Terra comum 🌍.
- **ULN2003 (Motor 1 e Motor 2)** 🔌:
  - IN1 a IN4 conectados aos GPIOs do ESP32.
  - OUT1 a OUT4 conectados às bobinas A, B, C, D de cada motor.
  - VCC → +5V, COM → +12V, GND → Terra comum 🌍.
- **Motores de Passo** 🔧:
  - Motor 1 e Motor 2 conectados às saídas OUT1 a OUT4 dos respectivos ULN2003.
- **Fontes de Alimentação** 🔋:
  - 5V para o ESP32 (VIN) e VCC dos ULN2003.
  - 12V para os motores (COM dos ULN2003).

**Nota** 📝: Certifique-se de conectar todos os GNDs (ESP32, ULN2003, fontes) a um único ponto comum para evitar problemas elétricos ⚠️.

## 🚀 Instruções de Instalação

1. **Clone o Repositório** 📥:

   ```bash
   git clone https://github.com/seu-usuario/seu-repositorio.git
   cd seu-repositorio
   ```

2. **Abra o Projeto na Arduino IDE** 🖥️:

   - Abra o arquivo `main.ino` na Arduino IDE.
   - Certifique-se de que os arquivos `motor_control.h` e `motor_control.cpp` estão no mesmo diretório 📂.

3. **Instale as Bibliotecas Necessárias** 📚:

   - No Arduino IDE, vá em "Sketch" &gt; "Include Library" &gt; "Manage Libraries...".
   - Procure e instale `ESPAsyncWebServer` (autor: me-no-dev) 📦.
   - A biblioteca `WiFi.h` já vem com a instalação do ESP32.

4. **Configure o Wi-Fi** 📡:

   - Abra `main.ino` e edite as credenciais do Wi-Fi:

     ```cpp
     const char* ssid = "Wireless-N";
     const char* password = "josemaria";
     ```

   - Substitua `Wireless-N` e `josemaria` pelo SSID e senha da sua rede Wi-Fi 🔑.

5. **Monte o Circuito** 🔧:

   - Conecte os componentes conforme o diagrama elétrico descrito acima ⚡.
   - Verifique todas as conexões antes de ligar as fontes de alimentação 🔍.

6. **Faça Upload do Código** ⬆️:

   - Conecte o ESP32 ao computador via USB 🔌.
   - Na Arduino IDE, selecione a placa correta (ex.: "ESP32 Dev Module") em "Tools" &gt; "Board" 🛠️.
   - Selecione a porta correta em "Tools" &gt; "Port" 🔗.
   - Clique em "Upload" para carregar o código no ESP32 🚀.

## 🎮 Como Usar

1. **Inicie o ESP32** 🌟:

   - Após o upload, abra o Monitor Serial (em "Tools" &gt; "Serial Monitor", 115200 baud) 📡.
   - O ESP32 tentará se conectar à rede Wi-Fi. Quando conectado, ele exibirá o endereço IP no Monitor Serial (ex.: `192.168.1.x`) 📍.

2. **Acesse a Interface Web** 🌐:

   - No seu computador ou celular, conecte-se à mesma rede Wi-Fi 📶.
   - Abra um navegador e digite o endereço IP do ESP32 (ex.: `http://192.168.1.x`) 🔗.
   - A interface web será exibida com botões para controlar o robô 🎉.

3. **Controle o Robô** 🚗:

   - **Movimentos do Robô** 🕹️:
     - "Frente" ⬆️: Move o robô para frente (Motor 1 anti-horário, Motor 2 horário).
     - "Reverso" ⬇️: Move o robô para trás (Motor 1 horário, Motor 2 anti-horário).
     - "Esquerda" ⬅️: Vira o robô à esquerda (ambos os motores horário).
     - "Direita" ➡️: Vira o robô à direita (ambos os motores anti-horário).
   - **Motor Individual** 🔄:
     - "Motor 1 - Horário" 🔃: Gira o Motor 1 no sentido horário.
     - "Motor 1 - Anti-horário" 🔄: Gira o Motor 1 no sentido anti-horário.
     - "Motor 2 - Horário" 🔃: Gira o Motor 2 no sentido horário.
     - "Motor 2 - Anti-horário" 🔄: Gira o Motor 2 no sentido anti-horário.
   - **Parar/Continuar** 🚨: Interrompe os motores (botão vermelho). Clique novamente para permitir novos movimentos.

## 🌟 Possíveis Melhorias

- Adicionar sensores (ex.: ultrassom para detecção de obstáculos) 📡.
- Implementar controle proporcional para ajustar a velocidade dos motores ⚙️.
- Criar um aplicativo móvel para substituir a interface web 📱.

## 📜 Licença

Este projeto está licenciado sob a MIT License. Sinta-se à vontade para usar, modificar e compartilhar! 🎉

---

Feito com 💡 por Marlon Victor Bezerra dos Passos. 🚀
