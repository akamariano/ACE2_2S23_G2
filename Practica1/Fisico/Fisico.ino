#include <DHT.h>

#define DHTPIN 4 // Pin de conexión del DHT11 al Arduino (cambia esto según tu configuración)
#define DHTTYPE DHT11 // Tipo de sensor DHT (puedes cambiarlo a DHT21 o DHT22 si estás utilizando esos modelos)

DHT dht(DHTPIN, DHTTYPE);
    
#define MQ135PIN A0 // Pin de conexión del sensor MQ135 al Arduino (cambia esto según tu configuración)
#define LDRPIN A1  // Pin de conexión del LDR al Arduino (cambia esto según tu configuración)

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
  int airQuality = analogRead(MQ135PIN); // El valor leído será proporcional a la calidad del aire

  // Lectura de cantidad de luz con LDR
  int lightLevel = analogRead(LDRPIN); // El valor leído será proporcional a la cantidad de luz

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
  delay(800); // Puedes ajustar este valor según la frecuencia deseada de las lecturas
}