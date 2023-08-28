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

#define FIREBASE_HOST "ace2-proyecto-1-9e6fe-default-rtdb.firebaseio.com"  // URL de la DB
#define FIREBASE_AUTH "1CXM3tLiaKfGge6KeuwuPTGoUMLmw7SgM4iGgVBB"           // Contraseña de la DB
FirebaseData Proyecto1;                                                    // Objeto de la DB
String ruta = "Datos";                                                 // Ruta para guardar valores de la DB

String ssid = "TIGO-9F32";         // Dirección del WiFi
String password = "2NJ555301879";  // Contraseña del WiFi

// Intentos para la conexión WiFi
byte cont = 0;
byte max_intentos = 50;

// Set del sensor DHT11
#include <DHT.h>
#define DHT_PIN D5
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);  // Objeto DHT

// PINES DEL SENSOR ULTRASONICO
#define PIN_TRIG D4
#define PIN_ECHO D2

#define MQ135_PIN A0  // PIN DEL SENSOR DE AIRE

#define FAN_PIN D7  // PIN DEL VENTILADOR

#define LED_PIN D8  // PIN DEL LED

// Variables de los sensores
float temperature;
float humidity;

float air;

float distance;
float tiempo;

// Avisos y notificaciones
String aviso = "i"; // Inicializando

// Variables para los outputs
String sValue;

// Banderas
bool primer_ciclo;  // Comprueba si se está en el primer ciclo
bool segundo_ciclo; // Comprueba si se está en el segundo ciclo

bool hay_persona; // Esta bandera es para el ejemplo en que se encuentre una persona en la habitación

// Setup
void setup() {
  // Inicia Serial
  Serial.begin(115200);
  Serial.println("\n");
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
  // Conexión firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  // Inicialización del DHT11
  dht.begin();  //Serial.print(F("DHTxx test!"));

  // Validaciones de los sensores (si se desea)
  /*
  if (isnan(temperature) || isnan(humidity)) {
    Serial.print(F("Falla en lectura del sensor")) return
  }
  */
  
  // Inicialización del Sensor Ultrasonico
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  pinMode(MQ135_PIN, INPUT);  // Inicialización del Sensor de Aire

  // Inicialización del LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Inicialización del Ventilador
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
}

// Loop
void loop() {
  delay(10000);

  // Leer datos de los sensores
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  air = analogRead(MQ135_PIN);
  
  // Para lo de distancia
  digitalWrite(PIN_TRIG, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);

  digitalWrite(PIN_TRIG, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  tiempo = pulseIn(PIN_ECHO, HIGH);
  distance = tiempo / 58.3;
  
  //  Imprimir
  Serial.println("--------------");
  Serial.print("Temperatura: ");
  Serial.println(temperature);
  Serial.print("Humedad: ");
  Serial.println(humidity);
  Serial.print("Aire: ");
  Serial.println(air);
  Serial.print("Distancia: ");
  Serial.println(distance);
  
  // Análisis de la presencia de una personas (sensor ultrasonico)
  if (distance<20){
    hay_persona = true; 
  } else {
    hay_persona = false;
  }

  // Análisis de limpieza de la habitación (calidad del aire)
  if (air > 400) {
    // Se determinan las banderas para lanzar la notificación
    if ((primer_ciclo == false) && (segundo_ciclo == false)) {
      primer_ciclo = true;
    } else if ((primer_ciclo == true) && (segundo_ciclo == false)) {
      segundo_ciclo = true;  // Corrección: Cambiar "segundo ciclo" a "segundo_ciclo"
    }
  } else {
    if ((primer_ciclo == true) && (segundo_ciclo == false)) {
      primer_ciclo = false;
    }
  }

  // Se hace lo del primer ciclo
  if ((primer_ciclo == true) && (segundo_ciclo == false)) {
    // Habitación con una calidad de aire deficiente
    aviso = "ad"; // Aire deficiente    
  }

  // Se hace lo del segundo ciclo
  if (segundo_ciclo) {
    // Se prende el ventilador para limpiar el lugar
    digitalWrite(FAN_PIN, HIGH);
    delay(5000);
    digitalWrite(FAN_PIN, LOW);

    // La habitación posee una calidad del aire óptima
    aviso = "ao" ;  // Aire optimo 
  }

  // Subir los los cambiantes a la DB (estos son los que se van mostrando en la app y son las condiciones de los aviso)
  Firebase.setInt(Proyecto1, "/Temperatura1", temperature);
  Firebase.setInt(Proyecto1, "/Humedad1", humidity);
  Firebase.setInt(Proyecto1, "/Aire1", air);
  Firebase.setInt(Proyecto1, "/Distancia1", distance);
  Firebase.setString(Proyecto1, "/Aviso1", aviso);

  // Subir los datos como historial
  Firebase.pushInt(Proyecto1, ruta + "/Temperatura", temperature);
  Firebase.pushInt(Proyecto1, ruta + "/Humedad", humidity);
  Firebase.pushInt(Proyecto1, ruta + "/Aire", air);
  Firebase.pushInt(Proyecto1, ruta + "/Distancia", distance);  

  // Como el enunciado menciona que si hay un persona en la habitacion (sensor ultrasonico) el usuario pueda manipular la iluminación
  // entonces se veritica esto y si hay una persona se podra leer el valor que se mande desde la app para encender la luz
  // y si no hay una persona no va a poder leer el valor porque no se dejará que la persona lo manipule (porque no hay persona XD)
  if (hay_persona){
    // Leer los valores de la DB para encender la luz
    if (Firebase.RTDB.getString(&Proyecto1, "/L1")) {  // Si viene un dato L1 en la DB extraer el valor que contiene, si es 1 encender el LED
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
  /*
  else {
    Serial.println(Proyecto1.errorReason());    // Esto es por si no se encuentra el dato en la DB (al inicio no estará hasta que se haga la acción antes dicha)
  }
  */
}
