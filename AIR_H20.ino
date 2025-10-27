// Projeto: Medidor de nível de água com ESP32 (WROOM32)
// Versão com filtro anti-ruído para sensores com pull-down externo

#define SENSOR_25 33
#define SENSOR_50 32
#define SENSOR_75 35
#define SENSOR_100 34

#define LED_25 25
#define LED_50 26
#define LED_75 27
#define LED_100 14

void setup() {
  Serial.begin(115200);
  Serial.println("=== Sistema de Nível de Água Iniciado ===");

  pinMode(SENSOR_25, INPUT);
  pinMode(SENSOR_50, INPUT);
  pinMode(SENSOR_75, INPUT);
  pinMode(SENSOR_100, INPUT);

  pinMode(LED_25, OUTPUT);
  pinMode(LED_50, OUTPUT);
  pinMode(LED_75, OUTPUT);
  pinMode(LED_100, OUTPUT);
}

int leituraEstavel(int pino) {
  // Faz 10 leituras rápidas e tira a média
  int soma = 0;
  for (int i = 0; i < 10; i++) {
    soma += digitalRead(pino);
    delay(2);
  }
  return (soma > 5) ? HIGH : LOW;
}

void loop() {
  int s25 = leituraEstavel(SENSOR_25);
  int s50 = leituraEstavel(SENSOR_50);
  int s75 = leituraEstavel(SENSOR_75);
  int s100 = leituraEstavel(SENSOR_100);

  digitalWrite(LED_25, s25);
  digitalWrite(LED_50, s50);
  digitalWrite(LED_75, s75);
  digitalWrite(LED_100, s100);

  int nivel = 0;
  if (s25 == HIGH) nivel = 25;
  if (s50 == HIGH) nivel = 50;
  if (s75 == HIGH) nivel = 75;
  if (s100 == HIGH) nivel = 100;

  Serial.print("Nível atual da água: ");
  Serial.print(nivel);
  Serial.println("%");

  delay(1000);
}
