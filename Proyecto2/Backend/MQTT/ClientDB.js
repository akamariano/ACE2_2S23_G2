const mqtt = require("mqtt");
const chalk = require('chalk');
const { ADDRESS } = require("./Config");
const { redisClient } = require("../Database/RedisDB");

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
    console.log(chalk.bold.green("\nClientDB - Connected"));
    for (const topic of topicsClientDB) {
        clientDB.subscribe(topic, () => {
            console.log(`ClientDB - Subscribed to ${topic}`);
        });
    }
});

// Al recibir un mensaje.
clientDB.on("message", async (topic, data) => {
    console.log(`ClientDB - Received message on ${topic}: ${data}`);

    // Guardar el dato en Redis
    await redisClient.set(topic, data);

    // Guardar el dato en el historial
    await redisClient.rPush(topic + "_historial", data)
});

// Error.
clientDB.on("error", (error) => {
    console.error("ClientDB - Subscriber Error: ", error, "\n");
});

module.exports = { clientDB }

