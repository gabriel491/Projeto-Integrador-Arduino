#include <LiquidCrystal.h>

// Inicializa a biblioteca com os números dos pinos digitais
// sãos os pinos RS, Enable, 
LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

// Variáveis para leitura e interpretação das leituras do TMP36
const int temperaturapin = A1; // Pino do sensor de Temperatura
int val = 0;
float celsius = 0.0;

void setup() {
    // Configurar o numero de colunas e linhas do LCD:
    lcd.begin(16.2);
    // Texto a ser mostrado no LCD (texto fixo primeira linha):
    lcd.print("Temp. °C");
}

void loop() {
    // Posicionar o cursor na coluna 0 e linha 1 (segunda linha):
    lcd.setCursor(0, 1);

    // Ler valor enviado pelo sensor
    val = analogRead(temperaturapin);

    // Medir e ajustar a temperatura em graus Celsius
    // Mapeia o valor ajustado em  MiliVolts para ointervalo de temperatura em graus Celsius
    celsius = map(((val - 20) * 3.04), 0, 1023, -40, 125);

    // Imprimir no LCD a temperatura
    lcd.print(celsius);
}