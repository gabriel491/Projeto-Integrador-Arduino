int ldr = A1;
int valor;

void setup() {
  Serial.begin(9600);
}

void loop() {
    valor = analogRead(ldr);
    Serial.println(valor);
}