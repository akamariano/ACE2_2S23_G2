// Definir ESP32 o ESP8266
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Arduino.h>
#include <FirebaseESP8266.h>
#include "definitions.h"
#include "database.h"

// ----------------------------------- WIFI -----------------------------------
// Dirección del WiFi
String ssid = "TIGO-9F32";
// Contraseña del WiFi
String password = "2NJ555301879";
// Intentos para la conexión WiFi
byte cont = 0;
byte max_intentos = 50;

// Objeto DHT
DHT dht(DHT_PIN, DHT_TYPE);

// Banderas para el estado de ciclos
int lightCurrentCycle = CYCLE_ONE;
int airCurrentCycle = CYCLE_ONE;

// Variables para los temporizadores
const unsigned long secondInterval = 1000;
unsigned long previousMillis = 0;
int timerLight = 0;
int timerAir = 0;

void setup() {
  // Inicia comunicacion serial
  Serial.begin(115200);
  Serial.println("\n");

  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and cont < max_intentos) {
    //Cuenta hasta 50 si no se puede conectar lo cancela
    cont++;
    delay(500);
    Serial.print(".");
  }

  Serial.println("");

  if (cont < max_intentos) {
    //Si se conectó
    Serial.println("********************************************");
    Serial.print("Conectado a la red WiFi: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("macAdress: ");
    Serial.println(WiFi.macAddress());
    Serial.println("*********************************************");
  } else {
    //No se conectó
    Serial.println("------------------------------------");
    Serial.println("Error de conexion");
    Serial.println("------------------------------------");
  }

  // Conexión Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setString(Proyecto1, "/Aviso1", INIT_ALERT);

  // Inicialización: Sensor DHT11
  dht.begin();

  // Inicialización: Sensor Ultrasonico
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  // Inicialización: Sensor de Aire
  pinMode(MQ135_PIN, INPUT);
  
  // Inicialización: Sensor de Luz
  pinMode(LDR_PIN, INPUT);

  // Inicialización: LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Inicialización: Ventilador
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
}

void generatePullTrigger() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(4);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
}

bool thereIsPerson(long distance) {
  if (distance <= 0) {
    return false;
  } else if (distance < MIN_DISTANCE) {
    return true;
  } else {
    return false;
  }
}

void printSensorValues(long distance, float temperature, float humidity, float air, float light) {
  Serial.println("--------------");
  Serial.print("Distancia (cm): ");
  Serial.println(distance);
  Serial.print("Temperatura (c): ");
  Serial.println(temperature);
  Serial.print("Humedad (%): ");
  Serial.println(humidity);
  Serial.print("Aire (ppm): ");
  Serial.println(air);
  Serial.print("Luz (Lum): ");
  Serial.println(light);
}

void sendAlert(String keyAlert) {
  Firebase.setString(Proyecto1, "/Aviso1", keyAlert);
}

int updateTimer(int timer) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= secondInterval) {
    previousMillis = currentMillis;
    return (timer + 1);
  }
  return timer;
}

void monitorAirQuality(float airQuality) {
  if (airQuality > MIN_CO2) {
    // Si el aire está contaminado, se actualiza el temporizador.
    timerAir = updateTimer(timerAir);
    switch (airCurrentCycle) {
      case CYCLE_ONE:
        if (timerAir >= TIMER_LIMIT_AIR) {
          // Enviar alerta y pasar al siguiente ciclo
          sendAlert(AIR_ALERT_1);
          airCurrentCycle = CYCLE_TWO;
        }
        break;
      case CYCLE_TWO:
        if (timerAir >= TIMER_LIMIT_AIR) {
          // Iniciar limpieza de aire
          digitalWrite(FAN_PIN, HIGH);

          // Reiniciar temporizador y pasar al siguiente ciclo
          timerAir = 0;
          airCurrentCycle = CYCLE_THREE;
        }
        break;
      case CYCLE_THREE:
        if (timerAir >= TIMER_LIMIT_FAN) {
          // Finalizar limpieza de aire
          digitalWrite(FAN_PIN, LOW);

          // Reiniciar temporizador y reiniciar ciclado
          timerAir = 0;
          airCurrentCycle = CYCLE_ONE;
          sendAlert(AIR_ALERT_2);
        }
        break;
    }
  } else {
    // Si el aire está en nivel aceptable, se reinicia el temporizador y el ciclado
    timerAir = 0;
    airCurrentCycle = CYCLE_ONE;
  }
  return;
}

/*
  Descripcion:  Leer la bandera de encendido de la DB para encender la luz.
                Si viene un dato L1 en la DB extraer el valor que contiene.
                1: Encender LED
                2: Apagar LED
*/
void switchLight() {
  String sValue;
  if (Firebase.RTDB.getString(&Proyecto1, "/L1")) {
    if (Proyecto1.dataType() == "string") {
      sValue = Proyecto1.stringData();
      int a = sValue.toInt();
      if (a == 1) {
        digitalWrite(LED_PIN, HIGH);
      } else {
        digitalWrite(LED_PIN, LOW);
      }
    }
  }
}

void monitorLight(long distance) {
  // Verificar si hay alguna persona en la habitacion
  if (thereIsPerson(distance)) {
    // Reiniciar temporizador y el ciclo actual a 1.
    timerLight = 0;
    lightCurrentCycle = CYCLE_ONE;
    // TODO: La luz puede ser manipulada manualmente
    switchLight();
    return;
  }

  // Verificar si no hay alguna persona y la luz está encendida
  if (!thereIsPerson(distance) && (digitalRead(LED_PIN) == HIGH)) {
    // Actualizar temporizador
    timerLight = updateTimer(timerLight);

    switch (lightCurrentCycle) {
      case CYCLE_ONE:
        // Verificar si terminó el temporizador
        if (timerLight >= TIMER_LIMIT_LIGHT) {
          // Enviar alerta
          sendAlert(LIGHT_ALERT_1);

          // Reiniciar temporizador y pasar al siguiente ciclo
          timerLight = 0;
          lightCurrentCycle = CYCLE_TWO;
        }
        break;
      case CYCLE_TWO:
        // Verificar si terminó el temporizador
        if (timerLight >= TIMER_LIMIT_LIGHT) {
          // Enviar alerta
          sendAlert(LIGHT_ALERT_2);

          // Reiniciar temporizador y reiniciar el ciclo.
          timerLight = 0;
          lightCurrentCycle = CYCLE_ONE;

          // Apagar la luz
          digitalWrite(LED_PIN, LOW);
        }
        break;
    }
  }
  return;
}

void switchTemperatureFan() {
  String sValue;
  if (Firebase.RTDB.getString(&Proyecto1, "/T1")) {
    if (Proyecto1.dataType() == "string") {
      sValue = Proyecto1.stringData();
      int a = sValue.toInt();
      if (a == 1) {
        digitalWrite(FAN_PIN, HIGH);
      } else {
        digitalWrite(FAN_PIN, LOW);
      }
    }
  }
}

void monitorTemperature(float temperature) {
  // Si el FAN está apagado, detectar cambios
  if (digitalRead(FAN_PIN) == LOW) {
    switchTemperatureFan();
    return;
  }

  // Si la temperatura está arriba del máximo y el FAN está activo: Continuar
  if (temperature >= MAX_TEMPERATURE && digitalRead(FAN_PIN) == HIGH){
    return;
  }
  
  // Si la temperatura está debajo del máximo y el FAN está activo: Apagar FAN
  if (temperature < MAX_TEMPERATURE && digitalRead(FAN_PIN) == HIGH){
    Firebase.setString(Proyecto1, "/T1", "0");
    sendAlert(TEMP_ALERT_1);
    switchTemperatureFan();
    return;
  }
}

void loop() {
  // Leer datos de los sensores
  generatePullTrigger();
  long time = pulseIn(PIN_ECHO, HIGH);
  long distance = time / 58.3;
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float air = analogRead(MQ135_PIN);
  float light = analogRead(LDR_PIN);

  // Imprimir datos de los sensores
  printSensorValues(distance, temperature, humidity, air, light);

  // Monitor de luz
  monitorLight(distance);

  // Monitor de calidad de aire
  monitorAirQuality(air);

  // Monitor de temperatura
  monitorTemperature(temperature);

  // Actualizar los datos de tiempo real en la DB.
  updateSensorsDB(distance, temperature, humidity, air, light);

  // Subir los datos como historial a la DB. (Guarda cada 10 segundos)
  updateSensorsRecordDB(distance, temperature, humidity, air, light);

  delay(1000);
}
