#define Gate 10
#define FAN 9

bool fanState = LOW;               // Inicialmente, el LED está apagado
unsigned long previousMillis = 0;  // Almacena el tiempo del último cambio de velocidad
const long interval = 5000;        // Intervalo de tiempo para cambiar la velocidad del ventilador

void setup() {
  pinMode(FAN, OUTPUT);
  digitalWrite(FAN, HIGH);

  pinMode(Gate, OUTPUT);
  digitalWrite(Gate, LOW);  // Inicialmente, el ventilador está apagado
}

void loop() {
  if (digitalRead(FAN) == HIGH) {
    // put your main code here, to run repeatedly:
    analogWrite(Gate, 100);
    delay(5000);
    analogWrite(Gate, 1000);
    delay(5000);
  }
}
