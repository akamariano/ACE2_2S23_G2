# Resumen

La pila tecnológica de Internet de las cosas (IoT) se despliega en un innovador proyecto denominado **Weather Sensor & Door Controller**, el cual combina diversas capas de software y hardware para crear un dispositivo meteorológico altamente funcional y conectado, además de incluir un actuador de seguridad para abrir y cerrar una puerta. Este dispositivo está diseñado para recopilar información ambiental crucial, como la cantidad de luz, calidad del aire, humedad y temperatura, y también para proporcionar control de acceso. Además, va un paso más allá al incluir la capacidad de detectar la presencia de personas en su entorno. Es un ejemplo impresionante de la implementación de la tecnología IoT en un dispositivo meteorológico avanzado y un sistema de seguridad, mediante la integración de sensores, análisis de datos, detección de personas, control de acceso y conectividad inalámbrica.

## Introducción

La conexión entre los componentes del sistema se establece mediante la capa de conectividad, la cual habilita la transmisión de datos hacia una plataforma en la nube o una base de datos central. Aquí es donde los datos recopilados se almacenan y organizan de manera eficiente para su posterior análisis.

Sin embargo, la verdadera magia ocurre en la capa de aplicación y análisis. Aquí es donde convergen los datos provenientes de los sensores y del actuador de seguridad de la puerta. El sistema no solo muestra la información tal como se recopila, sino que también realiza un análisis profundo para extraer insights valiosos. Este análisis puede ayudar a identificar patrones climáticos, tendencias de calidad del aire, detección de personas y otras observaciones significativas.

Un aspecto destacado del proyecto es su capacidad para interactuar con el entorno humano y controlar el acceso a una puerta. La detección de la presencia de personas agrega un componente adicional a la funcionalidad del dispositivo. Esto puede ser particularmente útil en la toma de decisiones informadas, como ajustar la iluminación o la climatización en función de la ocupación del espacio, así como en el control de acceso a una puerta mediante un servomotor.

La visualización y acceso a estos datos se logran a través de una conexión inalámbrica utilizando un módulo WiFi. Estos datos se presentan de manera intuitiva y fácil de entender en una aplicación móvil dedicada y en una página web. La aplicación y la página web permiten a los usuarios monitorear en tiempo real las condiciones ambientales, recibir alertas, acceder al histórico de datos para un análisis retrospectivo y controlar la apertura y cierre de la puerta de seguridad mediante un servomotor.

En resumen, el proyecto es un ejemplo impresionante de la implementación de la tecnología IoT en un dispositivo meteorológico avanzado y un sistema de seguridad. Mediante la integración de sensores, análisis de datos, detección de personas, control de acceso mediante un servomotor y conectividad inalámbrica, se brinda una solución completa para comprender y gestionar de manera efectiva el entorno y sus variaciones, así como garantizar la seguridad del espacio.

## Contenido

### Componentes Fundamentales

Los dispositivos y sensores, así como el actuador de seguridad de la puerta (servomotor), están en el centro de este logro. Estas entidades físicas juegan un papel importante en la captura de la rica variedad de datos ambientales y en el control de acceso. Los sensores, que funcionan como órganos sensoriales, pueden registrar datos importantes como temperatura, humedad, calidad del aire e intensidad de la luz. La fusión ideal de estos elementos llevó a la creación de un sofisticado dispositivo meteorológico y de seguridad que tiene como objetivo redefinir cómo percibimos e interactuamos con nuestro entorno atmosférico y físico.

### Capas del Sistema

1. **Dispositivos y Sensores:** Estas son las partes físicas del sistema que recopilan datos del entorno y controlan la puerta de seguridad mediante un servomotor. Los sensores capturan información como temperatura, humedad, calidad del aire, etc.
2. **Conectividad:** Esta capa se encarga de establecer la conexión entre los dispositivos y la red, incluyendo la comunicación MQTT para el control de la puerta y la transmisión de datos hacia la nube.
3. **Gateway:** Los dispositivos pueden estar conectados a través de un gateway, que actúa como intermediario entre los dispositivos y la nube. Ayuda a administrar la comunicación y puede realizar ciertas funciones de procesamiento local.
4. **Plataforma en la Nube:** Los datos recopilados se envían a una plataforma en la nube para su almacenamiento, procesamiento y análisis. Aquí es donde se pueden crear paneles de control, llevar a cabo análisis y tomar decisiones basadas en los datos.
5. **Aplicación Móvil y Página Web:** Los datos se utilizan para la aplicación móvil y se visualizan en una página web. Esto puede incluir visualizaciones, alertas, informes, control de la puerta mediante el servomotor y acciones automatizadas.

### Funcionamiento General

1. **Inclusión de Librerías:** Se incluyen las librerías necesarias, especialmente DHT (para el sensor de temperatura y humedad) y otras para el control y comunicación de los sensores y el actuador de la puerta (servomotor).
2. **Inicialización y Configuración:** Se inicia la comunicación serial y se configuran los pines para los sensores ultrasónicos, el sensor DHT, el sensor de calidad del aire MQ135, el LDR, el ventilador, el LED y el actuador de la puerta (servomotor). También se establece la conexión MQTT.
3. **Bucle Principal:** La función loop() es donde ocurren las acciones principales en un ciclo: se obtienen lecturas de temperatura y humedad del sensor DHT, se mide la distancia ultrasónica, se obtiene la intensidad lumínica del LDR y se obtiene información sobre la calidad del aire del sensor MQ135. Las lecturas se envían a la plataforma en la nube a través de MQTT y se controla el ventilador según la temperatura. Además, se monitorea la presencia de personas y se permite el control de acceso a la puerta mediante el servomotor a través de la aplicación móvil y la página web.


### Prototipo

A continuación, se presentan los bocetos del prototipo y su construcción:

![Prueba de Lectura de Datos de Sensores](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-29%20at%202.45.10%20PM.jpeg)
![Elaboración del Prototipo](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-29%20at%202.45.10%20PM%20(1).jpeg)
![Interfaz de la App](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.39%20AM%20(2).jpeg)
![Diseño Final](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.38%20AM.jpeg)
![Diseño Final](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.38%20AM%20(1).jpeg)
![Diseño Final](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.39%20AM.jpeg)

### Aplicación Móvil

A continuación, se presentan las pantallas de la app:

![Captura de Pantalla de la Aplicación](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.39%20AM%20(1).jpeg)
![Captura de Pantalla de la Aplicación](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.39%20AM%20(2).jpeg)

### MQTT


## Referencias

1. Oracle. (2023). ¿Qué es el IoT? Recuperado de [https://www.oracle.com/mx/internet-of-things/what-is-iot/](https://www.oracle.com/mx/internet-of-things/what-is-iot/)
2. Kumar, S., Tiwari, P., & Zymbler, M. (2019). Internet of Things is a revolutionary approach for future technology enhancement: a review. Journal of Big Data. Recuperado de [https://journalofbigdata.springeropen.com/articles/10.1186/s40537-019-0268-2](https://journalofbigdata.springeropen.com/articles/10.1186/s40537-019-0268-2)
3. Agar, R. (2022, Noviembre 15). IoT Architecture Guide. Major and additional layers of IoT system. Helpwire Blog. Recuperado de [https://www.helpwire.app/blog/iot-architecture/](https://www.helpwire.app/blog/iot-architecture/)