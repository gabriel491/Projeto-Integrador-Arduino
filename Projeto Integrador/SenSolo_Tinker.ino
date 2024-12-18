#include <LiquidCrystal.h>

// Conecta os pinos no Arduino
const int rs = 3, en = 4, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int sensorPin = A0; // Pino do sensor de umidade
const int umidadeSeca = 400; // Ajuste de acordo com o seu sensor
const int umidadeUmida = 500; // Ajuste de acordo com o seu sensor

void setup() {
  lcd.begin(16, 2);
  lcd.print("Iniciando...");
  delay(1000);
  lcd.clear();
}

void loop() {
  int umidade = analogRead(sensorPin);

  lcd.setCursor(0, 0);
  lcd.print("Umidade: ");
  lcd.print(umidade);

// Controle com histerese
  if (umidade < umidadeSeca) {
    lcd.setCursor(0, 1);
    lcd.print("Solo muito seco");
  } else if (umidade > umidadeUmida) {
    lcd.setCursor(0, 1);
    lcd.print("Solo muito úmido");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Umidade adequada");
  }

  // 1 hora
  delay(3600000);
}
