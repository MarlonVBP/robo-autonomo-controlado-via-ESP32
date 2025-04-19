#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "motor_control.h"

const char* ssid = "Wireless-N";
const char* password = "josemaria";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  int motorPins[] = {M1_IN1, M1_IN2, M1_IN3, M1_IN4, M2_IN1, M2_IN2, M2_IN3, M2_IN4};
  for (int i = 0; i < 8; i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW);
  }

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 15000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFalha ao conectar! Reiniciando...");
    ESP.restart();
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    String html = R"rawliteral(
<html>
<head>
  <title>Controle de Motores</title>
  <style>
    button {
      padding: 10px 20px;
      margin: 5px;
      font-size: 16px;
      border-radius: 8px;
      border: none;
      background-color: #007bff;
      color: white;
      cursor: pointer;
      transition: background-color 0.3s ease, transform 0.1s ease;
    }
    button:hover {
      background-color: #0056b3;
    }
    button:active {
      transform: scale(0.95);
    }
    button:disabled {
      background-color: #999;
      cursor: not-allowed;
    }
    #status {
      margin-top: 20px;
      font-size: 18px;
      font-weight: bold;
    }
  </style>
  <script>
    let movendo = false;

    function setStatus(text) {
      document.getElementById('status').innerText = text;
    }

    function disableButtons(disable) {
      const ids = ['frente', 're', 'esquerda', 'direita', 'motor1h', 'motor1a', 'motor2h', 'motor2a'];
      ids.forEach(id => {
        document.getElementById(id).disabled = disable;
      });
      movendo = disable;
    }

    async function enviarComando(caminho, mensagemStatus) {
      if (movendo && caminho !== '/parar') return;
      if (caminho !== '/parar') {
        setStatus(mensagemStatus);
        disableButtons(true);
      }
      await fetch(caminho);
      if (caminho !== '/parar') {
        setStatus('O carro est\u00e1 parado.');
        disableButtons(false);
      }
    }
  </script>
</head>
<body>
  <h1>Controle de Motores de Passo</h1>
  <h3>Movimentos do Robô</h3>
  <button id="frente" onclick="enviarComando('/frente', 'O carro está andando para frente')">Frente</button>
  <button id="re" onclick="enviarComando('/re', 'O carro está andando para trás')">Reverso</button>
  <button id="esquerda" onclick="enviarComando('/esquerda', 'O carro está virando para a esquerda')">Esquerda</button>
  <button id="direita" onclick="enviarComando('/direita', 'O carro está virando para a direita')">Direita</button>
  <h3>Motor Individual</h3>
  <button id="motor1h" onclick="enviarComando('/motor1?dir=1&steps=256', 'Motor 1 girando horário')">Motor 1 - Horário</button>
  <button id="motor1a" onclick="enviarComando('/motor1?dir=0&steps=256', 'Motor 1 girando anti-horário')">Motor 1 - Anti-horário</button>
  <br>
  <button id="motor2h" onclick="enviarComando('/motor2?dir=1&steps=256', 'Motor 2 girando horário')">Motor 2 - Horário</button>
  <button id="motor2a" onclick="enviarComando('/motor2?dir=0&steps=256', 'Motor 2 girando anti-horário')">Motor 2 - Anti-horário</button>
  <br><br>
  <button style="color:red; font-weight:bold;" onclick="enviarComando('/parar', 'Parado!')">PARAR / CONTINUAR</button>
  <div id="status">O carro está parado.</div>
</body>
</html>
    )rawliteral";
    request->send(200, "text/html", html);
  });

  server.on("/motor1", HTTP_GET, [](AsyncWebServerRequest* request) {
    int direction = request->hasParam("dir") ? request->getParam("dir")->value().toInt() : 1;
    int steps = request->hasParam("steps") ? request->getParam("steps")->value().toInt() : 512;
    moveMotor(1, direction, steps);
    request->send(200, "text/plain", "Motor 1 acionado.");
  });

  server.on("/motor2", HTTP_GET, [](AsyncWebServerRequest* request) {
    int direction = request->hasParam("dir") ? request->getParam("dir")->value().toInt() : 1;
    int steps = request->hasParam("steps") ? request->getParam("steps")->value().toInt() : 512;
    moveMotor(2, direction, steps);
    request->send(200, "text/plain", "Motor 2 acionado.");
  });

  server.on("/frente", HTTP_GET, [](AsyncWebServerRequest* request) {
    frente(256);
    request->send(200, "text/plain", "Movendo para frente.");
  });

  server.on("/re", HTTP_GET, [](AsyncWebServerRequest* request) {
    re(256);
    request->send(200, "text/plain", "Movendo em reverso.");
  });

  server.on("/esquerda", HTTP_GET, [](AsyncWebServerRequest* request) {
    esquerda(256);
    request->send(200, "text/plain", "Virando para esquerda.");
  });

  server.on("/direita", HTTP_GET, [](AsyncWebServerRequest* request) {
    direita(256);
    request->send(200, "text/plain", "Virando para direita.");
  });

  server.on("/parar", HTTP_GET, [](AsyncWebServerRequest* request) {
    parar = true;
    request->send(200, "text/plain", "Motores parados.");
  });

  server.begin();
}

void loop() {
  // Nada no loop, servidor é assíncrono
}