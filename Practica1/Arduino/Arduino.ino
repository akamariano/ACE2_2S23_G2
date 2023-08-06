#include <DHT.h>

#define MQ135_PIN A0  
#define LDR_PIN   A1  
#define DHT_PIN   2
#define DHT_TYPE  DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  dht.begin();

  pinMode(MQ135_PIN, INPUT);
  Serial1.println(">> TESTING");
}

void loop() {
  // Lectura de temperatura y humedad con DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Lectura de calidad del aire con MQ135
  int airQuality = analogRead(MQ135_PIN); // El valor leído será proporcional a la calidad del aire

  // Lectura de cantidad de luz con LDR
  int lightLevel = analogRead(LDR_PIN); // El valor leído será proporcional a la cantidad de luz

  // Imprimir los datos en el Monitor Serie

  // 1. TEMPERATURA
  Serial1.print("Temperatura: ");
  Serial1.print(temperature);
  Serial1.println(" °C");

  Serial.print("S1/");
  Serial.println(temperature);
  delay(100);

  // 2. HUMEDAD
  Serial1.print("Humedad: ");
  Serial1.print(humidity);
  Serial1.println(" %");

  Serial.print("S2/");
  Serial.println(humidity);
  delay(100);

  // 3. CO2
  Serial1.print("Calidad del aire: ");
  Serial1.println(airQuality);

  Serial.print("S3/");
  Serial.println(airQuality);
  delay(100);

  // 4. CANTIDAD DE LUZ
  Serial1.print("Cantidad de luz: ");
  Serial1.println(lightLevel);

  Serial.print("S4/");
  Serial.println(lightLevel);
  delay(100);

  // Esperar unos segundos antes de tomar nuevas lecturas
  delay(500);
}
