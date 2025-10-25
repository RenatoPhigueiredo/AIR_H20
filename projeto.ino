#include <WiFi.h>
#include <WebServer.h>

// 🔹 Wi-Fi
const char* ssid = "Fernando_2G";
const char* password = "23041986";

// 🔹 Servidor
WebServer server(80);

// 🔹 Pinos dos sensores de nível
const int nivel25 = 33;
const int nivel50 = 32;
const int nivel75 = 35;
const int nivel100 = 34;

int nivelAtual = 0;

// 🔹 Função para ler o nível de água
void lerNivel() {
  if (digitalRead(nivel100) == HIGH) {
    nivelAtual = 100;
  } else if (digitalRead(nivel75) == HIGH) {
    nivelAtual = 75;
  } else if (digitalRead(nivel50) == HIGH) {
    nivelAtual = 50;
  } else if (digitalRead(nivel25) == HIGH) {
    nivelAtual = 25;
  } else {
    nivelAtual = 0;
  }
}

// 🔹 Página principal (HTML simples)
void handleRoot() {
  lerNivel();

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='2'>"; //Atualiza a cada 15 segundos
  html += "<title>Medidor de Nível</title></head><body>";
  html += "<h2>💧 Medidor de Nível de Água</h2>";
  html += "<p><b>Nível atual:</b> " + String(nivelAtual) + "%</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n✅ Wi-Fi conectado!");
  Serial.print("🌐 Acesse em: http://");
  Serial.println(WiFi.localIP());

  // Configura os pinos como entrada
  pinMode(nivel25, INPUT);
  pinMode(nivel50, INPUT);
  pinMode(nivel75, INPUT);
  pinMode(nivel100, INPUT);

  // Inicia o servidor
  server.on("/", handleRoot);
  server.begin();
  Serial.println("🚀 Servidor iniciado!");
}

void loop() {
  server.handleClient();
}
