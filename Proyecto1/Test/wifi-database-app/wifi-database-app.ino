// Libería de arduino
#include <Arduino.h> 
// Definir ESP32 o ESP8266
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
// Librería Firebase
#include <FirebaseESP8266.h>
// Libería Ticker
#include <Ticker.h>

#define FIREBASE_HOST "ace2-proyecto-1-9e6fe-default-rtdb.firebaseio.com" // URL de la DB
#define FIREBASE_AUTH "1CXM3tLiaKfGge6KeuwuPTGoUMLmw7SgM4iGgVBB"          // Contraseña de la DB
FirebaseData Proyecto1;     // Objeto de la DB
String ruta = "Proyecto1";  // Ruta para guardar valores de la DB

String ssid = "TIGO-9F32";         // Dirección del WiFi
String password = "2NJ555301879";  // Contraseña del WiFi

#define ledWifi D4  // PIN DEL LED WIFI

// Set del sensor DHT11
#include <DHT.h>
#define DHT_PIN D5
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE); // Objeto DHT

#define LED_PIN D8  // PIN DEL LED

// Variables de los sensores
float temperature;
float humidity;

// Variables para los outputs
String sValue, sValue2;

Ticker tic_WifiLed; // Objeto Ticker

// Intentos para la conexión WiFi
byte cont = 0;
byte max_intentos = 50;

// Método que hace parpadear la tarjeta cuando se conecta a WiFi
void parpadeoLedWifi() {
  byte estado = digitalRead(ledWifi);
  digitalWrite(ledWifi, !estado);
}

// Setup
void setup() {
  // Inicia Serial
  Serial.begin(115200);
  Serial.println("\n");
  // Parpadeo del LED Wifi
  pinMode(ledWifi, OUTPUT);
  tic_WifiLed.attach(0.2, parpadeoLedWifi);
  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and cont < max_intentos) {  //Cuenta hasta 50 si no se puede conectar lo cancela
    cont++;
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  if (cont < max_intentos) {  //Si se conectó
    Serial.println("********************************************");
    Serial.print("Conectado a la red WiFi: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("macAdress: ");
    Serial.println(WiFi.macAddress());
    Serial.println("*********************************************");
  } else {  //No se conectó
    Serial.println("------------------------------------");
    Serial.println("Error de conexion");
    Serial.println("------------------------------------");
  }
  // Dejar prendido el LED
  tic_WifiLed.detach();
  digitalWrite(ledWifi, LOW);
  // Conexión firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  // Inicialización del DHT11
  dht.begin();   //Serial.print(F("DHTxx test!"));
  
  // Validaciones de los sensores
  /*
  if (isnan(temperature) || isnan(humidity)) {
    Serial.print(F("Falla en lectura del sensor")) return
  }
  */
  // Inicialización del LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

// Loop
void loop() {
  delay(10000);
  // Leer datos de los sensores
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  //  Imprimir
  Serial.println("--------------");
  Serial.print("Temperatura: ");
  Serial.println(temperature);
  Serial.print("Humedad: ");
  Serial.println(humidity);
  // Subirlos a la DB
  Firebase.setInt(Proyecto1, "Temperatura1", temperature);
  Firebase.setInt(Proyecto1, "Humedad1", humidity);
  // Leer los valores de la DB  
  if (Firebase.RTDB.getString(&Proyecto1, "/L1")) {   // Si viene un dato L1 en la DB extraer el valor que contiene, si es 1 encender el LED
    if (Proyecto1.dataType() == "string") {
      sValue = Proyecto1.stringData();
      int a = sValue.toInt();
      Serial.println(a);
      if (a == 1) {
        digitalWrite(LED_PIN, HIGH);
      } else {
        digitalWrite(LED_PIN, LOW);
      }
    }
  } else {
    Serial.println(Proyecto1.errorReason());
  }
}