#ifndef DATABASE_H
#define DATABASE_H

// URL de la DB
#define FIREBASE_HOST "ace2-proyecto-1-9e6fe-default-rtdb.firebaseio.com"

// Contraseña de la DB
#define FIREBASE_AUTH "1CXM3tLiaKfGge6KeuwuPTGoUMLmw7SgM4iGgVBB"

// Objeto de la DB
FirebaseData Proyecto1;

// Ruta para guardar valores de la DB
String ruta = "Datos";

// Variables para el temporizador: Se almacenan datos en historial cada 10 segundos.
const unsigned long intervalRecordsDB = 10000;
unsigned long previousMillisDB = 0;
int timerDB = 0;

// Descripcion: Sube los datos en tiempo real a la DB
//              Estos son los que se van mostrando en la APP y son las condiciones de los avisos
void updateSensorsDB(long distance, float temperature, float humidity, float air) {
  Firebase.setInt(Proyecto1, "/Temperatura1", temperature);
  Firebase.setInt(Proyecto1, "/Humedad1", humidity);
  Firebase.setInt(Proyecto1, "/Aire1", air);
  Firebase.setInt(Proyecto1, "/Distancia1", distance);
}

// Descripcion: Sube los datos al historial de los sensores de la DB
//              Guarda datos despues de 10 segundos.
void updateSensorsRecordDB(long distance, float temperature, float humidity, float air) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisDB >= intervalRecordsDB) {
    Firebase.pushInt(Proyecto1, ruta + "/Temperatura", temperature);
    Firebase.pushInt(Proyecto1, ruta + "/Humedad", humidity);
    Firebase.pushInt(Proyecto1, ruta + "/Aire", air);
    Firebase.pushInt(Proyecto1, ruta + "/Distancia", distance);
    previousMillisDB = currentMillis;
  }
}

#endif