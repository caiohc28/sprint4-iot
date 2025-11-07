#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

// ===== Pinos =====
#define LEDPIN 2
#define DHTPIN 12
#define DHTTYPE DHT22
#define LDRPIN 36
#define TRIGPIN 5
#define ECHOPIN 18

DHT dht(DHTPIN, DHTTYPE);

// ===== Config WiFi =====
const char* SECRET_SSID = "Wokwi-GUEST";
const char* SECRET_PW   = "";

// ===== Config ThingSpeak =====
WiFiClient client;
unsigned long channelID = 3086523;
const char* writeAPIKey = "4W1ZFVRLJ2SI1ICW";

// ===== Dados Mockados da Moto (simulando API) =====
struct Moto {
  int id;
  String placa;
  String modelo;
  String situacao;
} motoAtual;

// ===== Leituras dos sensores =====
float temperatura;
float umidade;
int luminosidade;
float distancia;

// ===== Função para inicializar dados mockados =====
void inicializarDadosMock() {
  motoAtual.id = 2;
  motoAtual.placa = "YCM9D73";
  motoAtual.modelo = "Elite 125";
  motoAtual.situacao = ""; // Será detectada pelos sensores
  
  Serial.println("📦 Dados carregados (da API):");
  Serial.print("  ID: "); Serial.println(motoAtual.id);
  Serial.print("  Placa: "); Serial.println(motoAtual.placa);
  Serial.print("  Modelo: "); Serial.println(motoAtual.modelo);
  Serial.println("  Situação: Será detectada pelos sensores");
}

// ===== Função para atualizar situação (simulando PUT/PATCH na API) =====
void atualizarSituacao(String novaSituacao) {
  if (motoAtual.situacao != novaSituacao) {
    Serial.println("🔄 Atualizando situação da moto...");
    Serial.print("  Situação anterior: "); Serial.println(motoAtual.situacao);
    Serial.print("  Nova situação: "); Serial.println(novaSituacao);
    
    motoAtual.situacao = novaSituacao;
    Serial.println("✅ Situação atualizada com sucesso!");
  }
}

// ===== Função para medir distância =====
float medirDistancia() {
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  long duracao = pulseIn(ECHOPIN, HIGH);
  return duracao * 0.034 / 2; // distância em cm
}

// ===== Setup =====
void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH); // LED apagado
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  dht.begin();
  
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  
  Serial.println("🚀 Iniciando MOTOSECURITYX...");
  Serial.println("🔧 Modo: Dados Mockados (Simulação Local)");
  
  // Inicializar dados mockados
  inicializarDadosMock();
}

// ===== Loop =====
void loop() {
  // Conectar ao WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Conectando a rede SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(SECRET_SSID, SECRET_PW);
      Serial.print(".");
      delay(2000);
    }
    Serial.println("\n✅ Wi-Fi conectado!");
  }

  // ===== Leitura dos sensores =====
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  luminosidade = analogRead(LDRPIN);
  distancia = medirDistancia();

  // ===== Lógica de detecção baseada na distância =====
  String situacaoDetectada;
  if (distancia < 50) { // menor que 50 cm = moto presente
    situacaoDetectada = "Dentro";
  } else {
    situacaoDetectada = "Fora";
  }

  // Atualizar situação se mudou
  atualizarSituacao(situacaoDetectada);

  // ===== Exibição Serial =====
  Serial.println("========== Monitoramento MOTOSECURITYX ==========");
  Serial.print("🏍️  ID da Moto: "); Serial.println(motoAtual.id);
  Serial.print("🔖 Placa: "); Serial.println(motoAtual.placa);
  Serial.print("📋 Modelo: "); Serial.println(motoAtual.modelo);
  Serial.print("📍 Situação: "); Serial.println(motoAtual.situacao);
  Serial.println("-------------- Sensores --------------");
  Serial.print("🌡️  Temperatura: "); Serial.print(temperatura); Serial.println(" °C");
  Serial.print("💧 Umidade: "); Serial.print(umidade); Serial.println(" %");
  Serial.print("💡 Luminosidade: "); Serial.println(luminosidade);
  Serial.print("📏 Distância: "); Serial.print(distancia); Serial.println(" cm");

  // ===== Lógica do LED =====
  if (motoAtual.situacao == "Fora") {
    Serial.println("🚨 ALERTA: Moto fora do pátio!");
    digitalWrite(LEDPIN, LOW); // acende LED
  } else {
    Serial.println("✅ Status: Moto no pátio");
    digitalWrite(LEDPIN, HIGH); // apaga LED
  }

  // ===== Envio ThingSpeak =====
  ThingSpeak.setField(1, distancia);                           // Distância medida
  ThingSpeak.setField(2, motoAtual.situacao == "Dentro" ? 1 : 0);  // 1 = dentro, 0 = fora
  ThingSpeak.setField(3, temperatura);                         // Temperatura (°C)
  ThingSpeak.setField(4, umidade);                             // Umidade (%)
  ThingSpeak.setField(5, luminosidade);                        // Luminosidade (0-4095)

  int status = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (status == 200) {
    Serial.println("📡 Dados enviados para ThingSpeak com sucesso!");
  } else {
    Serial.print("❌ Erro ao enviar para ThingSpeak: "); Serial.println(status);
  }

  Serial.println("==================================================\n");
  delay(20000); // respeitar limite do ThingSpeak (15 segundos mínimo)
}