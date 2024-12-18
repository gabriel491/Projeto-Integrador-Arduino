// Definição dos pinos dos sensores
const int TEMPERATURA_PIN = A1;  // Pino analógico para o sensor de temperatura
const int LDR_PIN = A5;          // Pino analógico para o sensor de luz (LDR)
const int UMIDADE_PIN = A0;      // Pino analógico para o sensor de umidade do solo

// Constantes para calibração dos sensores
const int UMIDADE_SECA = 400;    // Valor limite para solo considerado seco
const int UMIDADE_UMIDA = 500;   // Valor limite para solo considerado úmido
const float TEMP_OFFSET = 20.0;  // Offset para calibração do sensor de temperatura
const float TEMP_SCALE = 3.04;   // Fator de escala para o sensor de temperatura

// Variáveis globais para armazenar as leituras dos sensores
float temperatura = 0.0;
int umidade = 0;
int luminosidade = 0;

void setup() {
  Serial.begin(9600); 
  // Configura os pinos dos sensores como entradas
  pinMode(TEMPERATURA_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(UMIDADE_PIN, INPUT);
}

void loop() {
  lerSensores();    // Chama a função para ler todos os sensores
  exibirDados();    // Chama a função para exibir os dados lidos
  delay(5000);      // Aguarda 5 segundos antes da próxima leitura
}

// Função para ler os valores de todos os sensores
void lerSensores() {
  // Lê e converte o valor do sensor de temperatura
  int rawTemp = analogRead(TEMPERATURA_PIN);
  temperatura = map((rawTemp - TEMP_OFFSET) * TEMP_SCALE, 0, 1023, -40, 125);
  
  // Lê os valores dos sensores de umidade e luminosidade
  umidade = analogRead(UMIDADE_PIN);
  luminosidade = analogRead(LDR_PIN);
}

// Função para exibir os dados lidos no monitor serial
void exibirDados() {
  Serial.println("-------- Leitura de Sensores --------");
  
  // Exibe a temperatura
  Serial.print("Temperatura: ");
  Serial.print(temperatura, 1);  // Exibe com uma casa decimal
  Serial.println(" °C");
  
  // Exibe a umidade
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.print(" (");
  Serial.print(avaliarUmidade());  // Chama função para avaliar o nível de umidade
  Serial.println(")");
  
  // Exibe a luminosidade
  int luzPorcentagem = map(luminosidade, 0, 1023, 0, 100);  // Converte para porcentagem
  Serial.print("Luminosidade: ");
  Serial.print(luminosidade);
  Serial.print(" (");
  Serial.print(luzPorcentagem);
  Serial.println("%)");
  
  Serial.println("-------------------------------------");
}

// Função para avaliar o nível de umidade do solo
String avaliarUmidade() {
  if (umidade < UMIDADE_SECA) {
    return "Solo muito seco";
  } else if (umidade > UMIDADE_UMIDA) {
    return "Solo muito úmido";
  } else {
    return "Umidade adequada";
  }
}

// ############################ CÓDIGO SEM O LCD #########################
#include <LiquidCrystal.h>

// Variáveis para leitura e interpretação das leituras do TMP36
const int temperaturapin = A1; // Pino do sensor de Temperatura
int val = 0;
float celsius = 0.0;
int ldr = A5; // pino do sensor de luminosidade
int valor;

// Índices de umidade do solo
const int sensorPin = A0; // Pino do sensor de umidade
const int umidadeSeca = 400;
const int umidadeUmida = 500;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int umidade = analogRead(sensorPin);

  // Medir e ajustar a temperatura em graus Celsius
  val = analogRead(temperaturapin);
    // Mapeia o valor ajustado em  MiliVolts para o intervalo de temperatura em graus Celsius
  celsius = map(((val - 20) * 3.04), 0, 1023, -40, 125);

  // Imprimir os dados no monitor serial
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.print("  Temperatura: ");
  Serial.print(celsius);
  Serial.println(" °C");

  // Controle com histerese e impressão no serial
  if (umidade < umidadeSeca) {
    Serial.println("Solo muito seco");
  } else if (umidade > umidadeUmida) {
    Serial.println("Solo muito umido");
  } else {
    Serial.println("Umidade adequada");
  }
  
  valor = analogRead(ldr);
  int luzPorcentagem = map(valor, 0, 1023, 0, 100);
  Serial.print("Luz: ");
  Serial.print(valor);
  Serial.print(" (");
  Serial.print(luzPorcentagem);
  Serial.println("%)");

  delay(5000);
}