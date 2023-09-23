# Uso de sensores

## Sensor de iluminacion (LDR)

Código para el sensor de iluminación LDR

```c++
    const int ldrPin = A0; // Pin analógico donde está conectado el sensor LDR
    int ldrValue = 0;     // Variable para almacenar el valor leído del sensor

    void setup() {
    Serial.begin(9600); // Inicializamos la comunicación serial
    }

    void loop() {
    ldrValue = analogRead(ldrPin); // Leemos el valor analógico del sensor
    Serial.print("Valor LDR: ");  // Imprimimos un mensaje
    Serial.println(ldrValue);     // Imprimimos el valor leído

    delay(1000); // Esperamos 1 segundo antes de realizar la próxima lectura
    }
```
El código configura un pin analógico de Arduino para leer la señal del sensor LDR y utiliza una función llamada analogRead() para obtener un valor numérico que representa la resistencia del sensor en ese momento. Este valor se almacena en una variable llamada ldrValue.

Luego, el código utiliza la comunicación serial para mostrar este valor en el monitor serial de Arduino. El valor del sensor LDR se imprime junto con un mensaje para indicar qué valor se está mostrando. El programa espera un segundo entre cada lectura del sensor para evitar que los datos se muestren demasiado rápido en el monitor serial.

## Sensor de temperatura y humedad (DHT11)

Código para el sensor de temperatura y humedad DHT11

```c++
    #include <DHT.h> // Incluimos la librería DHT

    #define DHTPIN 2 // Pin donde está conectado el sensor (Pin digital 2)
    #define DHTTYPE DHT11 // Definimos el tipo de sensor

    DHT dht(DHTPIN, DHTTYPE); // Inicializamos el sensor DHT11

    void setup() {
    Serial.begin(9600); // Inicializamos la comunicación serial
    dht.begin(); // Inicializamos el sensor DHT11
    }

    void loop() {
    float h = dht.readHumidity(); // Obtenemos la humedad relativa del ambiente
    float t = dht.readTemperature(); // Obtenemos la temperatura en grados centígrados (por defecto)

    Serial.print("Humedad: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C ");

    delay(2000); // Esperamos 2 segundos antes de volver a leer los sensores
    }
```

El código configura un pin digital de Arduino para leer la señal del sensor DHT11 y utiliza una función llamada readTemperature() para obtener un valor numérico que representa la temperatura del ambiente en ese momento. Este valor se almacena en una variable llamada t.


## Sensor de distancia (HC-SR04)

Código para el sensor de distancia HC-SR04

```c++
    #define echoPin 2 // Pin Echo del sensor conectado a D2 de Arduino
    #define trigPin 3 // Pin Trig del sensor conectado a D3 de Arduino

    void setup() {
    Serial.begin(9600); // Inicializamos la comunicación serial
    pinMode(trigPin, OUTPUT); // Configuramos el pin Trig como salida
    pinMode(echoPin, INPUT); // Configuramos el pin Echo como entrada
    }

    void loop() {
    long duration, distance; // Declaramos variables para la duración del pulso y la distancia

    digitalWrite(trigPin, LOW); // Para generar un pulso limpio ponemos a LOW 4us
    delayMicroseconds(4);
    digitalWrite(trigPin, HIGH); // Generamos Trigger (disparo) de 10us
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH); //Medimos el tiempo entre pulsos, en microsegundos
    distance = duration/58.2; //Convertimos el tiempo a distancia, en cm.

    Serial.print(distance); //Enviamos serialmente el valor de la distancia
    Serial.println(" cm");

    delay(1000); //Hacemos una pausa de 1 segundo y se repite el proceso
    }
```

El código configura dos pines digitales de Arduino para enviar y recibir la señal del sensor HC-SR04. El pin digital 3 se configura como salida y se utiliza para enviar el pulso de disparo al sensor. El pin digital 2 se configura como entrada y se utiliza para leer el pulso de eco del sensor.

Luego, el código utiliza la comunicación serial para mostrar el valor de la distancia en el monitor serial de Arduino. El valor de la distancia se imprime junto con un mensaje para indicar qué valor se está mostrando. El programa espera un segundo entre cada lectura del sensor para evitar que los datos se muestren demasiado rápido en el monitor serial.

## Sensor de CO2 (MQ-135)

Código para el sensor de CO2 MQ-135

```c++
    int sensorPin = A0; // Pin analógico donde está conectado el sensor
    int sensorValue = 0; // Variable para almacenar el valor leído del sensor

    void setup() {
    Serial.begin(9600); // Inicializamos la comunicación serial
    }

    void loop() {
    sensorValue = analogRead(sensorPin); // Leemos el valor analógico del sensor
    Serial.print("Calidad del aire: "); // Imprimimos un mensaje
    Serial.println(sensorValue); // Imprimimos el valor leído

    delay(1000); // Esperamos 1 segundo antes de realizar la próxima lectura
    }
```

El código configura un pin analógico de Arduino para leer la señal del sensor MQ-135 y utiliza una función llamada analogRead() para obtener un valor numérico que representa la resistencia del sensor en ese momento. Este valor se almacena en una variable llamada sensorValue.

Luego, el código utiliza la comunicación serial para mostrar este valor en el monitor serial de Arduino. El valor del sensor MQ-135 se imprime junto con un mensaje para indicar qué valor se está mostrando. El programa espera un segundo entre cada lectura del sensor para evitar que los datos se muestren demasiado rápido en el monitor serial.

## Servomotor

Código para el servomotor

```c++
    #include <Servo.h>

    Servo myservo;  // Crea una instancia del objeto servo

    int pos = 0;   // Variable para almacenar la posición del servo

    void setup() {
        myservo.attach(9);  // Asigna el servo al pin 9
    }

    void loop() {
        for (pos = 0; pos <= 180; pos += 1) {  // Gira desde 0 grados a 180 grados
            myservo.write(pos);                 // Envía el valor de posición al servo
            delay(15);                          // Espera un breve tiempo para el movimiento
        }
        for (pos = 180; pos >= 0; pos -= 1) {  // Gira desde 180 grados a 0 grados
            myservo.write(pos);                 // Envía el valor de posición al servo
            delay(15);                          // Espera un breve tiempo para el movimiento
        }
    }
```

El código configura un pin digital de Arduino para enviar la señal de control al servomotor. El pin digital 9 se configura como salida y se utiliza para enviar la señal de control al servomotor.

Luego, el código utiliza la librería Servo.h para controlar el servomotor. El servomotor se mueve desde 0 grados hasta 180 grados y luego regresa a 0 grados. El programa espera 15 milisegundos entre cada movimiento del servomotor para evitar que el servomotor se mueva demasiado rápido.

## Motor DC / Ventilador

Codigo para el ventilador con dos flujos de corriente diferentes utilizando relés.

```c++
        // Definir los pines de control de relé para las dos velocidades
    const int relayVelocidadAlta = 8;
    const int relayVelocidadBaja = 9;

    void setup() {
        // Configurar los pines de relé como salidas
        pinMode(relayVelocidadAlta, OUTPUT);
        pinMode(relayVelocidadBaja, OUTPUT);

        // Apagar ambos relés al inicio
        digitalWrite(relayVelocidadAlta, LOW);
        digitalWrite(relayVelocidadBaja, LOW);
    }

    void loop() {
        // Encender la velocidad alta durante 5 segundos
        digitalWrite(relayVelocidadAlta, HIGH);
        digitalWrite(relayVelocidadBaja, LOW);
        delay(5000);  // Esperar 5 segundos

        // Cambiar a velocidad baja durante 5 segundos
        digitalWrite(relayVelocidadAlta, LOW);
        digitalWrite(relayVelocidadBaja, HIGH);
        delay(5000);  // Esperar 5 segundos
    }
```
En este código, utilizamos dos pines de relé (relayVelocidadAlta y relayVelocidadBaja) para controlar dos velocidades del ventilador. Debes conectar las entradas de alta velocidad y baja velocidad del ventilador a los relés correspondientes. El programa alterna entre las dos velocidades durante un período de 5 segundos cada una y repite el ciclo en el bucle loop().

# Lógica y Metodos implementados
En general, los métodos implementados son para el control de los sensores y el envío de alertas.

Se utilizaron variables de control de estado.
En términos generales, se utilizó la lógica e idea principal del patrón de diseño de maquina de estados finitos y del patrón super loop.

Los métodos implementados principales son:
- monitorLight(distance);
- monitorAirQuality(air);
- monitorTemperature(temperature);
- updateSensorsDB(distance, temperature, humidity, air, light);
- updateSensorsRecordDB(distance, temperature, humidity, air, light);

## Loop
En el bucle principal solo se hacen las llamadas a los métodos principales que se encargan de controlar los sensores y enviar las alertas con el fin de mantener el código limpio y ordenado; además de evitar el estado de absorción.

```c++
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
```

## MonitorLight

### Parametros
- distance: Distancia del sensor de ultrasonido

### Descripcion
Monitorea la luz y activa la luz si hay una persona en la habitación. Si la luz está encendida y no hay nadie, se apaga después de un tiempo establecido.
Si hay alguien en la habitación, se habilita la opción de apagar y encender la luz manualmente.

```c++
void monitorLight(long distance) {
  // Verificar si hay alguna persona en la habitacion
  if (thereIsPerson(distance)) {
    // Reiniciar temporizador y el ciclo actual a 1.
    timerLight = 0;
    lightCurrentCycle = CYCLE_ONE;
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
```

## MonitorAirQuality

### Parametros
- airQuality: Calidad del aire del sensor MQ-135
  
### Descripcion
Monitorea la calidad del aire y activa el FAN si es necesario. Si el FAN está activo, se apaga después de un tiempo establecido.

```c++
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
                if (fanIsUsed == 0){
                    fanIsUsed = 1;
                    digitalWrite(FAN_PIN, HIGH);

                }        
                // Reiniciar temporizador y pasar al siguiente ciclo
                timerAir = 0;
                airCurrentCycle = CYCLE_THREE;
                }
                break;
            case CYCLE_THREE:
                if (timerAir >= TIMER_LIMIT_FAN) {
                // Finalizar limpieza de aire
                if(fanIsUsed == 1){
                    fanIsUsed = 0;
                    digitalWrite(FAN_PIN, LOW);
                }
                
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

```

## MonitorTemperature

### Parametros
- temperature: Temperatura del sensor DHT11

### Descripcion
Monitorea la temperatura y activa el FAN si es necesario. Si el FAN está activo, se apaga si la temperatura baja del máximo.

```c++
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
        if (temperature < MAX_TEMPERATURE && digitalRead(FAN_PIN) == HIGH && fanIsUsed == 2){
            Firebase.setString(Proyecto1, "/T1", "0");
            sendAlert(TEMP_ALERT_1);
            switchTemperatureFan();
            return;
        }
    }
```

## UpdateSensorsDB

### Parametros
- distance: Distancia del sensor de ultrasonido
- temperature: Temperatura del sensor DHT11
- humidity: Humedad del sensor DHT11
- air: Calidad del aire del sensor MQ-135
- light: Luz del sensor LDR

### Descripcion
Sube los datos en tiempo real a la DB. Estos son los que se van mostrando en la APP y son las condiciones de los avisos

```c++
    void updateSensorsDB(long distance, float temperature, float humidity, float air, float light) {
        Firebase.setInt(Proyecto1, "/Temperatura1", temperature);
        Firebase.setInt(Proyecto1, "/Humedad1", humidity);
        Firebase.setInt(Proyecto1, "/Aire1", air);
        Firebase.setInt(Proyecto1, "/Distancia1", distance);
        Firebase.setInt(Proyecto1, "/Luz1", light);
    }
```

## UpdateSensorsRecordDB

### Parametros
- distance: Distancia del sensor de ultrasonido
- temperature: Temperatura del sensor DHT11
- humidity: Humedad del sensor DHT11
- air: Calidad del aire del sensor MQ-135
- light: Luz del sensor LDR

### Descripcion
Sube los datos al historial de los sensores de la DB. Guarda datos despues de 10 segundos.

```c++
    void updateSensorsRecordDB(long distance, float temperature, float humidity, float air, float light) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillisDB >= intervalRecordsDB) {
            Firebase.pushInt(Proyecto1, ruta + "/Temperatura", temperature);
            Firebase.pushInt(Proyecto1, ruta + "/Humedad", humidity);
            Firebase.pushInt(Proyecto1, ruta + "/Aire", air);
            Firebase.pushInt(Proyecto1, ruta + "/Distancia", distance);
            Firebase.pushInt(Proyecto1, ruta + "/Luz", light);
            previousMillisDB = currentMillis;
        }
    }
```