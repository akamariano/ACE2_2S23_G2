#include <DHT.h>

// PINES DEL SENSOR ULTRASONICO
#define PIN_TRIG D4
#define PIN_ECHO D2

// PIN DEL SENSOR DE TEMPERATURA Y HUMEDAD
#define DHT_PIN D5
#define DHT_TYPE DHT11
// OBJETO DHT
DHT dht(DHT_PIN, DHT_TYPE);

// PIN DEL SENSOR LDR
#define LDR_PIN D6   

// PIN DEL SENSOR DE AUIRE
#define MQ135_PIN A0  

// PIN DEL VENTILADOR
#define FAN_PIN D7

// PIN DEL LED
#define LED_PIN D8

float tiempo;
float distancia;
float temperature;
float humidity;

void setup() {
  Serial.begin(9600);
  
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  dht.begin();

  pinMode(MQ135_PIN, INPUT);

  pinMode(LDR_PIN, INPUT);

  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void loop() {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  
  
  digitalWrite(PIN_TRIG, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);

  digitalWrite(PIN_TRIG, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  

  tiempo = pulseIn(PIN_ECHO, HIGH);
  distancia = tiempo / 58.3;
  

  int lightLevel = analogRead(LDR_PIN);

  //int airQuality = analogRead(MQ135_PIN);
  int airQuality = analogRead(MQ135_PIN);

  Serial.println("--------------");
  Serial.print("Distancia: ");
  Serial.println(distancia);
  Serial.print("Temperatura: ");
  Serial.println(temperature);
  Serial.print("Humendad: ");
  Serial.println(humidity);
  Serial.print("Luz: ");
  Serial.println(lightLevel);
  Serial.print("AIre: ");
  Serial.println(airQuality);

  if (temperature > 30) {
    digitalWrite(FAN_PIN, HIGH);
    Serial.println("VENTILADOR");
  } else {
    digitalWrite(FAN_PIN, LOW);
  }

  delay(1000);
}
