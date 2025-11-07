# MOTOSECURITYX - Sistema de Monitoramento de Motos

## 📋 Descrição do Projeto

O **MOTOSECURITYX** é um sistema IoT completo para monitoramento de motocicletas que utiliza sensores para detectar a presença da moto no pátio e monitorar condições ambientais. O sistema envia dados em tempo real para a plataforma ThingSpeak e fornece alertas visuais quando a moto está fora da área monitorada.

## 🛠️ Tecnologias Utilizadas

### Hardware
- **ESP32**: Microcontrolador principal
- **Sensor DHT22**: Temperatura e umidade
- **Sensor HC-SR04**: Ultrassônico para medição de distância
- **LDR (Light Dependent Resistor)**: Sensor de luminosidade
- **LED**: Indicador visual de status

### Software
- **Arduino IDE**: Ambiente de desenvolvimento
- **WiFi**: Conexão com internet
- **ThingSpeak**: Plataforma IoT para dashboard e analytics
- **Bibliotecas**:
  - `WiFi.h`: Conexão WiFi
  - `ThingSpeak.h`: Integração com ThingSpeak
  - `DHT.h`: Comunicação com sensor DHT22

## 📦 Estrutura do Projeto

### Sensores Implementados
1. **Sensor Ultrassônico**: Detecta presença da moto (distância < 50cm)
2. **Sensor DHT22**: Mede temperatura e umidade ambiente
3. **Sensor LDR**: Monitora nível de luminosidade
4. **LED**: Alerta visual quando moto está fora

### Funcionalidades Principais
- ✅ Detecção automática de presença da moto
- ✅ Monitoramento ambiental contínuo
- ✅ Alertas em tempo real
- ✅ Dashboard online no ThingSpeak
- ✅ Dados mockados para simulação

## 🔧 Instruções de Uso

### Pré-requisitos
1. **Hardware**:
   - ESP32
   - Sensor DHT22
   - Sensor HC-SR04 (Ultrassônico)
   - LDR e resistor de 10kΩ
   - LED e resistor de 220Ω
   - Protoboard e jumpers

2. **Software**:
   - Arduino IDE 1.8+
   - Bibliotecas: WiFi, ThingSpeak, DHT

### Conexões dos Sensores

| Componente | Pino ESP32 |
|------------|------------|
| LED | GPIO 2 |
| DHT22 | GPIO 12 | 
| LDR | GPIO 36 (VP) | 
| HC-SR04 Trig | GPIO 5 | 
| HC-SR04 Echo | GPIO 18 |

# 📊 Resultados finais

🚀 Iniciando MOTOSECURITYX...
📦 Dados carregados (da API):
  ID: 2
  Placa: YCM9D73
  Modelo: Elite 125
  Situação: Será detectada pelos sensores

========== Monitoramento MOTOSECURITYX ==========

🏍️  ID da Moto: 2

🔖 Placa: YCM9D73

📋 Modelo: Elite 125

📍 Situação: Dentro

-------------- Sensores --------------

🌡️  Temperatura: 25.3 °C

💧 Umidade: 60.2 %

💡 Luminosidade: 2048

📏 Distância: 35.4 cm

✅ Status: Moto no pátio

📡 Dados enviados para ThingSpeak com sucesso!


# 👥 Integrantes
```
Caio Henrique - RM 554600
Antônio Lino - RM 554518
Carlos Eduardo - RM 555223
```
