#define sinal A0
#define LedVermelho 5
#define LedAmarelo 6
#define LedVerde 7

// Valores de calibração (ajustar conforme necessário)
const int umidadeSeca = 100;  // Valor máximo para solo seco
const int umidadeModerada = 500; // Valor máximo para solo moderadamente úmido

int valorAnalogico;
int porcentagemUmidade;

void setup() {
  Serial.begin(9600);
  pinMode(sinal, INPUT);
  pinMode(LedVermelho, OUTPUT);
  pinMode(LedAmarelo, OUTPUT);
  pinMode(LedVerde, OUTPUT);
}

void loop() {
  // Leitura do sensor e conversão para porcentagem
  valorAnalogico = analogRead(sinal);
  // Valor máximo e mínimo de umidade, 0 e 1023, Valor de porcentagem
  porcentagemUmidade = map(valorAnalogico, 0, 1023, 100, 0);

  Serial.print("Umidade: ");
  Serial.print(porcentagemUmidade);
  Serial.println("%");

  // Controle dos LEDs com histerese
 if (porcentagemUmidade > umidadeModerada) {
    apagaleds();
    digitalWrite(LedVerde, HIGH);
    Serial.println("Solo muito úmido");
  } else if (porcentagemUmidade > umidadeSeca) {
    apagaleds();
    digitalWrite(LedAmarelo, HIGH);
    Serial.println("Umidade moderada");
  } else {
    apagaleds();
    digitalWrite(LedVermelho, HIGH);
    Serial.println("Solo seco");
  }

  // 1 hora
  delay(3600000);
}

void apagaleds() {
  digitalWrite(LedVermelho, LOW);
  digitalWrite(LedAmarelo, LOW);
  digitalWrite(LedVerde, LOW);
}
