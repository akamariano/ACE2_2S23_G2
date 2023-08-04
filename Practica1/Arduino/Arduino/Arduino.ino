#include <DHT.h>

#define CO2_PIN   A0
#define DHT_PIN   2 
#define DHT_TYPE  DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  // Serial1.begin(9600);
  Serial1.begin(9600);
  dht.begin();
  pinMode(CO2_PIN, INPUT);

  
  Serial1.println(">> TESTING");
}

void loop() {
  // ---- Obtener el valor de la humedad con el sensor ----
  float humidity = dht.readHumidity();
  // ---- Obtener el valor de la temperatura con el sensor ----
  float temperature = dht.readTemperature();

  // Comprobamos si ha habido algún error en la lectura
  if (isnan(humidity) || isnan(temperature)) {
    Serial1.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
  
  Serial1.print("Humedad: ");
  Serial1.print(humidity);
  Serial1.print(" %\t");
  Serial1.print("Temperatura: ");
  Serial1.print(temperature);
  Serial1.print(" *C ");
  Serial1.println("");

  // CAMBIAR A DELAY DE 5 SEGUNDOS MINIMO.
  delay(400); // <- TEST PURPOSES ONLY

  // ---- Obtener el valor del CO2 detectado con el sensor ----
  
  // int co2_data = analogRead(CO2_PIN);
  // Serial1.print("CO2 PPM: ");
  // Serial1.println(co2_data);
  // delay(400);
}
