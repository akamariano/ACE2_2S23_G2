const { ADDRESS } = require("./Config");
const mqtt = require('mqtt');
const { sendToArduino } = require("../ArduinoSerial");

const topicsClientArduino = [
    "estadoactuador",
    "estadoluz",
    "estadofan",
];

const clientArduino = mqtt.connect(`mqtt://${ADDRESS}`);

// Conexion al broker y suscripcion a los topics
clientArduino.on("connect", () => {
    console.log("ClientArduino is connected");
    for (const topic of topicsClientArduino) {
        clientArduino.subscribe(topic, () => {
            console.log(`Subscribed to ${topic}`);
        });
    }
});

// ---------------------- PUBLISHER ----------------------

function publishArduino(topic, message) {
    clientArduino.publish(topic, message, (error) => {
        if (!error) {
            console.log(`ClientArduino:  ${topic} -> ${message}`);
        } else {
            console.error("ClientArduino Error: ", error);
        }
    });
}

// ---------------------- SUBSCRIBER ----------------------

// Al recibir un mensaje.
clientArduino.on("message", (topic, data) => {
    console.log(`Received message on ${topic}: ${data}`);

    // Enviar el dato al Arduino
    sendToArduino(topic, data);
});


// Error.
clientArduino.on("error", (error) => {
    console.error("ClientArduino Error: ", error, "\n");
});

module.exports = {
    publishArduino
}
