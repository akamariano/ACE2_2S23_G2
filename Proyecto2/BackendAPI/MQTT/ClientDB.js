const { ADDRESS } = require("./Config");
const mqtt = require("mqtt");
const { redisClient } = require("../RedisDB");

// ---------------------- SUBSCRIBER ----------------------
const topicsClientDB = [
    "distancia",
    "temperatura",
    "humedad",
    "aire",
    "luz"
];

const clientDB = mqtt.connect(`mqtt://${ADDRESS}`);

// Conectarse al broker y suscribirse a los topics
clientDB.on("connect", () => {
    console.log("ClientDB is connected");
    for (const topic of topicsClientDB) {
        clientDB.subscribe(topic, () => {
            console.log(`Subscribed to ${topic}`);
        });
    }
});

// Al recibir un mensaje.
clientDB.on("message", (topic, data) => {
    console.log(`Received message on ${topic}: ${data}`);

    // Guardar el dato en Redis
    redisClient.set(topic, data);

    // Guardar el dato en el historial
    redisClient.rPush(topic + "_historial", data)
});

// Error.
clientDB.on("error", (error) => {
    console.error("Subscriber Error: ", error, "\n");
});


