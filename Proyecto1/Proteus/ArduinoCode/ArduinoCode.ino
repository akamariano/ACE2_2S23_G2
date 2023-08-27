#include <DHT.h>
// PINES DEL SENSOR ULTRASONICO
#define PIN_TRIG 5
#define PIN_ECHO 4
// PIN DEL SENSOR DE TEMPERATURA Y HUMEDAD
#define DHT_PIN 2
#define DHT_TYPE DHT11
// PIN DEL SENSOR LDR
#define LDR_PIN A1
// PIN DEL SENSOR DE AUIRE
#define MQ135_PIN A0
// PIN DEL VENTILADOR
#define FAN_PIN 7
// PIN DEL LED
#define LED_PIN 6

// UMBRALES
#define MIN_DISTANCE 100
#define MIN_TEMPERATURE 30
#define MIN_CO2 100

// OBJETO DHT
DHT dht(DHT_PIN, DHT_TYPE);

// BANDERAS
bool isFanOn = false;

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Pins de sensor de proximidad
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  // Pins de sensor MQ135
  pinMode(MQ135_PIN, INPUT);

  // Pins de sensor LDR
  pinMode(LDR_PIN, INPUT);

  // Pins de ventilador
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);

  // Pins de LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void generatePullTrigger() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(4);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
}

void loop() {
  // long time, distance;

  generatePullTrigger();
  long time = pulseIn(PIN_ECHO, HIGH);
  long distance = time / 58.3;

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int lightLevel = analogRead(LDR_PIN);
  int airQuality = analogRead(MQ135_PIN);

  Serial.println("--------------");
  Serial.print("Distancia (cm): ");
  Serial.println(distance);
  Serial.print("Temperatura (c): ");
  Serial.println(temperature);
  Serial.print("Luz (lx): ");
  Serial.println(lightLevel);
  Serial.print("Aire (ppm): ");
  Serial.println(airQuality);

  if (temperature > MIN_TEMPERATURE && !isFanOn) {
    digitalWrite(FAN_PIN, HIGH);
    isFanOn = true;
    Serial.println("FAN: ENCENDIENDO VENTILADOR");
  } else if (temperature < MIN_TEMPERATURE && isFanOn) {
    digitalWrite(FAN_PIN, LOW);
    isFanOn = false;
    Serial.println("FAN: APAGANDO VENTILADOR");
  }

  if (distance <= 0) {
    Serial.println("PROXIMIDAD: Nada que medir");
  } else if (distance < MIN_DISTANCE) {
    Serial.println("PROXIMIDAD: HAY PERSONAS CERCA");
  } else {
    Serial.println("PROXIMIDAD: NO HAY PERSONAS CERCA");
  }

  delay(1000);
}