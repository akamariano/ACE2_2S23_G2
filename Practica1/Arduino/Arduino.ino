#include <DHT.h>

#define DHT_PIN   4 
#define DHT_TYPE  DHT11
#define MQ135_PIN A0 
#define LDR_PIN   A1  

DHT dht(DHT_PIN, DHT_TYPE);
  
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  dht.begin();
}

void loop() {
  // Lectura de temperatura y humedad con DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Lectura de calidad del aire con MQ135
  int airQuality = analogRead(MQ135_PIN);

  // Lectura de cantidad de luz con LDR
  int lightLevel = analogRead(LDR_PIN);

  // Imprimir los datos en el Monitor Serie
  Serial.print("Temperatura ");
  Serial.println(temperature);
  Serial1.println(temperature);
  delay(100);

  Serial.print("Humedad ");
  Serial.println(humidity);
  Serial1.println(humidity);
  delay(100);

  Serial.print("Aire ");
  Serial.println(airQuality);
  Serial1.println(airQuality);
  delay(100);

  Serial.print("Luz ");
  Serial.println(lightLevel);
  Serial1.println(lightLevel);
  delay(100);

  // Esperar unos segundos antes de tomar nuevas lecturas
  delay(5000);
}
