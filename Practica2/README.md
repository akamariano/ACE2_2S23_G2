# Resumen

La pila tecnológica de Internet de las cosas (IoT) se despliega en un innovador proyecto denominado **Weather Sensor & Door Controller**, el cual combina diversas capas de software y hardware para crear un dispositivo meteorológico altamente funcional y conectado, además de incluir un actuador de seguridad para abrir y cerrar una puerta. Este dispositivo está diseñado para recopilar información ambiental crucial, como la cantidad de luz, calidad del aire, humedad y temperatura, y también para proporcionar control de acceso. Además, va un paso más allá al incluir la capacidad de detectar la presencia de personas en su entorno. Es un ejemplo impresionante de la implementación de la tecnología IoT en un dispositivo meteorológico avanzado y un sistema de seguridad, mediante la integración de sensores, análisis de datos, detección de personas, control de acceso y conectividad inalámbrica.

# Introducción

La conexión entre los componentes del sistema se establece mediante la capa de conectividad, la cual habilita la transmisión de datos hacia una plataforma en la nube o una base de datos central. Aquí es donde los datos recopilados se almacenan y organizan de manera eficiente para su posterior análisis.

Sin embargo, la verdadera magia ocurre en la capa de aplicación y análisis. Aquí es donde convergen los datos provenientes de los sensores y del actuador de seguridad de la puerta. El sistema no solo muestra la información tal como se recopila, sino que también realiza un análisis profundo para extraer insights valiosos. Este análisis puede ayudar a identificar patrones climáticos, tendencias de calidad del aire, detección de personas y otras observaciones significativas.

Un aspecto destacado del proyecto es su capacidad para interactuar con el entorno humano y controlar el acceso a una puerta. La detección de la presencia de personas agrega un componente adicional a la funcionalidad del dispositivo. Esto puede ser particularmente útil en la toma de decisiones informadas, como ajustar la iluminación o la climatización en función de la ocupación del espacio, así como en el control de acceso a una puerta mediante un servomotor.

La visualización y acceso a estos datos se logran a través de una conexión inalámbrica utilizando un módulo WiFi. Estos datos se presentan de manera intuitiva y fácil de entender en una aplicación móvil dedicada y en una página web. La aplicación y la página web permiten a los usuarios monitorear en tiempo real las condiciones ambientales, recibir alertas, acceder al histórico de datos para un análisis retrospectivo y controlar la apertura y cierre de la puerta de seguridad mediante un servomotor.

En resumen, el proyecto es un ejemplo impresionante de la implementación de la tecnología IoT en un dispositivo meteorológico avanzado y un sistema de seguridad. Mediante la integración de sensores, análisis de datos, detección de personas, control de acceso mediante un servomotor y conectividad inalámbrica, se brinda una solución completa para comprender y gestionar de manera efectiva el entorno y sus variaciones, así como garantizar la seguridad del espacio.

# Contenido

## Componentes Fundamentales

Los dispositivos y sensores, así como el actuador de seguridad de la puerta (servomotor), están en el centro de este logro. Estas entidades físicas juegan un papel importante en la captura de la rica variedad de datos ambientales y en el control de acceso. Los sensores, que funcionan como órganos sensoriales, pueden registrar datos importantes como temperatura, humedad, calidad del aire e intensidad de la luz. La fusión ideal de estos elementos llevó a la creación de un sofisticado dispositivo meteorológico y de seguridad que tiene como objetivo redefinir cómo percibimos e interactuamos con nuestro entorno atmosférico y físico.

## Capas del Sistema

1. **Dispositivos y Sensores:** Estas son las partes físicas del sistema que recopilan datos del entorno y controlan la puerta de seguridad mediante un servomotor. Los sensores capturan información como temperatura, humedad, calidad del aire, etc.
2. **Conectividad:** Esta capa se encarga de establecer la conexión entre los dispositivos y la red, incluyendo la comunicación MQTT para el control de la puerta y la transmisión de datos hacia la nube.
3. **Gateway:** Los dispositivos pueden estar conectados a través de un gateway, que actúa como intermediario entre los dispositivos y la nube. Ayuda a administrar la comunicación y puede realizar ciertas funciones de procesamiento local.
4. **Plataforma en la Nube:** Los datos recopilados se envían a una plataforma en la nube para su almacenamiento, procesamiento y análisis. Aquí es donde se pueden crear paneles de control, llevar a cabo análisis y tomar decisiones basadas en los datos.
5. **Aplicación Móvil y Página Web:** Los datos se utilizan para la aplicación móvil y se visualizan en una página web. Esto puede incluir visualizaciones, alertas, informes, control de la puerta mediante el servomotor y acciones automatizadas.

## Funcionamiento General

1. **Inclusión de Librerías:** Se incluyen las librerías necesarias, especialmente DHT (para el sensor de temperatura y humedad) y otras para el control y comunicación de los sensores y el actuador de la puerta (servomotor).
2. **Inicialización y Configuración:** Se inicia la comunicación serial y se configuran los pines para los sensores ultrasónicos, el sensor DHT, el sensor de calidad del aire MQ135, el LDR, el ventilador, el LED y el actuador de la puerta (servomotor). También se establece la conexión MQTT.
3. **Bucle Principal:** La función loop() es donde ocurren las acciones principales en un ciclo: se obtienen lecturas de temperatura y humedad del sensor DHT, se mide la distancia ultrasónica, se obtiene la intensidad lumínica del LDR y se obtiene información sobre la calidad del aire del sensor MQ135. Las lecturas se envían a la plataforma en la nube a través de MQTT y se controla el ventilador según la temperatura. Además, se monitorea la presencia de personas y se permite el control de acceso a la puerta mediante el servomotor a través de la aplicación móvil y la página web.


## Prototipo

A continuación, se presentan los bocetos del prototipo y su construcción:

![Prueba de Lectura de Datos de Sensores](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-29%20at%202.45.10%20PM.jpeg)
![Elaboración del Prototipo](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-29%20at%202.45.10%20PM%20(1).jpeg)
![Interfaz de la App](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.39%20AM%20(2).jpeg)
![Diseño Final](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.38%20AM.jpeg)
![Diseño Final](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.38%20AM%20(1).jpeg)
![Diseño Final](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.39%20AM.jpeg)
### Aplicación Web
![Mockup de la Aplicación](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Practica2/images/Muckup.png)
### Aplicación Móvil
![Captura de Pantalla de la Aplicación](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.39%20AM%20(1).jpeg)
![Captura de Pantalla de la Aplicación](https://github.com/akamariano/ACE2_2S23_G2/blob/main/Proyecto1/Docs/Images/WhatsApp%20Image%202023-08-31%20at%2010.24.39%20AM%20(2).jpeg)

## Smart Connected Design Framework

- **Capa 0: Things**
    Estación meteorológica IoT.

- **Capa 1: Hardware**
    Estas son las partes físicas del sistema que recopilan datos del entorno
    - Sensor de temperatura: DHT
    - Sensor ultrasónico para detectar presencia humana: HC-SR04
    - Sensor de iluminación: LDR
    - Sensor de medición de calidad de aire (CO2 en el ambiente): MQ135
    - Ventilador.
    - Actuador.

    Las partes están conectadas a través de un Arduino.

- **Capa 2: Software**
    Programación a través de Arduino IDE, qué utiliza como base C++, y librerías desarrolladas para el control de los sensores respectivos.

- **Capa 3: Communication**
    La comunicación con el dispositivo se realiza mediante WiFi o mediante cable USB que envía los datos a una API que conecta con internet.

- **Capa 4: Cloud Platform**
    Los datos del dispositivo llegan a una API que está conectada con un MQTT y a una base de datos en la nube.

- **Capa 5: Cloud Applications**
    Visualización de los datos a través de una página web y una aplicación móvil. Esto puede incluir visualizaciones, alertas, informes y acciones en el dispositivo. Además, se utiliza Grafana para la visualización de datos en la página web.

## Diagramas


## MQTT

MQTT, que significa Message Queuing Telemetry Transport, es un protocolo de comunicación ligero y eficiente para transferir mensajes entre dispositivos en una red. Desarrollado por IBM en la década de 1990, se ha convertido en un estándar ampliamente utilizado en Internet de las cosas (IoT) y aplicaciones de comunicación de dispositivo a dispositivo.

Características:

- Voluntad del cliente: los clientes MQTT pueden configurar un mensaje de "voluntad" para que se envíe automáticamente si el cliente se desconecta inesperadamente. Esto es útil para notificar a otros dispositivos que un cliente se ha desconectado.

- Ligero: MQTT es un protocolo de comunicación ligero y eficiente en términos de consumo de ancho de banda y recursos de hardware. Esto lo hace adecuado para dispositivos con recursos limitados, como sensores y dispositivos IoT.

- Eficiencia del ancho de banda: MQTT está diseñado para utilizar el ancho de banda de manera eficiente, reduciendo la sobrecarga de comunicación. Los encabezados de los mensajes son pequeños y el protocolo está diseñado para minimizar la cantidad de datos innecesarios transferidos.

- Escalabilidad: MQTT es altamente escalable y puede manejar una gran cantidad de dispositivos y clientes conectados simultáneamente. La arquitectura cliente-agente le permite conectar y administrar dispositivos de manera eficiente.

### Broker
---

Un broker en MQTT (Message Queuing Telemetry Transport) es un componente central en la arquitectura de este protocolo de comunicación. MQTT es un protocolo de mensajería ligero y eficiente diseñado para la comunicación entre dispositivos en redes con ancho de banda limitado o en condiciones de conectividad intermitente. Un broker MQTT actúa como intermediario entre los dispositivos que desean intercambiar mensajes.

- Recepción y enrutamiento de mensajes: El broker MQTT recibe los mensajes publicados por los dispositivos y los enruta a los dispositivos suscritos adecuados. Cada mensaje enviado a través de MQTT tiene un "tema" (topic), y los dispositivos pueden suscribirse a temas específicos para recibir solo los mensajes que les interesan.

- Almacenamiento temporal: El broker puede retener los mensajes publicados durante un tiempo determinado, lo que permite a los dispositivos que se conectan más tarde recibir los mensajes que se perdieron mientras estaban desconectados. Esto es especialmente útil en situaciones de conectividad intermitente.

- Garantía de entrega: El broker MQTT puede proporcionar diferentes niveles de garantía de entrega, como QoS (Quality of Service), que permite especificar cuántas veces se debe entregar un mensaje y si se debe almacenar en el broker hasta que se confirme su entrega.

- Gestión de sesiones: El broker mantiene un registro de las sesiones de los clientes MQTT para garantizar una comunicación confiable incluso si los dispositivos se desconectan y vuelven a conectarse.
Autenticación y autorización: Los brokers MQTT pueden implementar medidas de seguridad, como autenticación de clientes y autorización para controlar quién puede publicar o suscribirse a ciertos temas.

- Escalabilidad: Los brokers MQTT pueden ser configurados para manejar una gran cantidad de dispositivos y mensajes, lo que los hace adecuados para aplicaciones de IoT (Internet de las cosas) y M2M (Machine-to-Machine).

**Tipos de Broker**

Los tipos de broker son:

- Broker Centralizado: Este es el tipo de broker más común. Un broker centralizado actúa como un intermediario central que recibe todos los mensajes publicados por los dispositivos y los enruta a los dispositivos suscritos apropiados. Todos los dispositivos se conectan al mismo broker para enviar y recibir mensajes. Este enfoque es sencillo de configurar y administrar, pero puede convertirse en un punto único de fallo y una limitación en términos de escalabilidad si se trata de un sistema muy grande.

- Broker Descentralizado: En un broker descentralizado, no hay un único broker central que gestione todas las comunicaciones. En su lugar, varios brokers se comunican entre sí mediante un protocolo de enrutamiento para permitir la comunicación entre dispositivos en diferentes dominios de broker. Esto puede ser útil para distribuir la carga y mejorar la escalabilidad. 

- Broker Autocontenido (Broker Empotrado o Broker Integrado): En algunos casos, MQTT se implementa como un broker embebido en los propios dispositivos. Cada dispositivo actúa como su propio broker MQTT y puede comunicarse directamente con otros dispositivos. Esto es útil en escenarios de comunicación de punto a punto o en dispositivos con recursos limitados, pero no es tan adecuado para soluciones de IoT a gran escala.

**Brokers Gratuitos**

Algunos ejemplos de brokers gratuitos son:

- Eclipse Mosquitto: Eclipse Mosquitto es un broker MQTT de código abierto y gratuito ampliamente utilizado. Es ligero y adecuado para implementaciones pequeñas y medianas.

- HiveMQ CE (Community Edition): HiveMQ CE es la versión gratuita de HiveMQ, un broker MQTT altamente escalable. La edición gratuita es adecuada para proyectos más pequeños y de desarrollo.

- EMQX: EMQX es un broker MQTT de código abierto que ofrece una versión gratuita. Es conocido por ser escalable y adecuado para proyectos IoT de gran envergadura.

- RabbitMQ: RabbitMQ es un sistema de mensajería de código abierto ampliamente utilizado. Puedes habilitar el soporte MQTT mediante un plugin, lo que lo convierte en un broker MQTT gratuito.

**Brokers de Paga**

Algunos ejemplos de brokers de paga son:

- HiveMQ: HiveMQ también ofrece una versión de pago llamada HiveMQ Enterprise, que proporciona características avanzadas y soporte para implementaciones empresariales de alta demanda.

- AWS IoT Core: Amazon Web Services (AWS) ofrece un servicio llamado AWS IoT Core que es un broker MQTT completamente administrado. Es de pago y escalable para aplicaciones IoT en la nube de AWS.

- Microsoft Azure IoT Hub: Azure IoT Hub de Microsoft es un servicio de IoT que incluye capacidades de broker MQTT. Es parte de la plataforma Azure IoT y tiene un modelo de precios basado en el uso.

- Google Cloud IoT Core: Google Cloud IoT Core es un servicio de Google Cloud que proporciona capacidades de broker MQTT gestionado. Al igual que otros servicios de la nube, tiene una estructura de precios basada en el uso.

### Publisher
---

En el contexto de MQTT (Message Queuing Telemetry Transport), el término "Publisher" se refiere a un componente o entidad que envía mensajes o publica información en un tema (topic) en el servidor MQTT.

El flujo de datos en MQTT se organiza en torno a temas (topics), que actúan como canales de comunicación a los que los dispositivos pueden suscribirse o desde los cuales pueden publicar mensajes. Los publicadores (Publishers) son responsables de enviar mensajes a uno o varios temas en el servidor MQTT. Estos mensajes pueden contener información de sensores, comandos o cualquier tipo de dato que se deba transmitir a los suscriptores (Subscribers) interesados en este tema en particular.
Los publicadores envían mensajes a un tema específico utilizando el servidor MQTT como intermediario, y luego los suscriptores que estén suscritos a ese tema recibirán los mensajes para su procesamiento o visualización.


### Subscriber
---
En el contexto del transporte de telemetría de colas de mensajes (MQTT), un suscriptor es un componente o entidad que se suscribe a uno o más temas específicos en el sistema MQTT para recibir mensajes publicados sobre esos temas. Los suscriptores son uno de los dos roles principales en MQTT, el otro es el de "editor".

Un suscriptor MQTT puede realizar múltiples suscripciones a diferentes temas o incluso al mismo tema con diferentes niveles de calidad de servicio (QoS). Esto permite a un suscriptor recibir una variedad de datos de múltiples fuentes o controlar diferentes aspectos de un sistema IoT.


# Referencias

1. Oracle. (2023). ¿Qué es el IoT? Recuperado de [https://www.oracle.com/mx/internet-of-things/what-is-iot/](https://www.oracle.com/mx/internet-of-things/what-is-iot/)
2. Kumar, S., Tiwari, P., & Zymbler, M. (2019). Internet of Things is a revolutionary approach for future technology enhancement: a review. Journal of Big Data. Recuperado de [https://journalofbigdata.springeropen.com/articles/10.1186/s40537-019-0268-2](https://journalofbigdata.springeropen.com/articles/10.1186/s40537-019-0268-2)
3. Agar, R. (2022, Noviembre 15). IoT Architecture Guide. Major and additional layers of IoT system. Helpwire Blog. Recuperado de [https://www.helpwire.app/blog/iot-architecture/](https://www.helpwire.app/blog/iot-architecture/)