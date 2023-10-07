const express = require("express");
const { redisClient } = require("./Database/RedisDB");
const { publishData } = require("./MQTT/TestPublisher");

const app = express();
const port = 3000;
app.use(express.json());

app.get("/", (req, res) => {
    res.send("Hello World!");
});

app.post("/publish", async (req, res) => {
    const { topic, data } = req.body;

    // Publicar la data en el broker
    publishData(topic, data);

    // Guardar el dato en Redis
    await redisClient.set(topic, data);

    // Guardar el dato en el historial
    await redisClient.rPush(topic + "_historial", data)
    
    res.json({message: "Datos enviados"})    
});

app.get("/history/:param", async (req, res) => {
    const topic = req.params.param;
    const hash = topic + "_historial";

    // Obtener el historial de datos de Redis
    const data = await redisClient.lRange(hash, 0, -1)
    res.json({data})
});

app.get("/realtime/:param", async (req, res) => {
    const topic = req.params.param;

    // Obtener el dato en tiempo real de Redis
    const data = await redisClient.get(topic)
    res.json({data})
});

app.listen(port, () => {
    console.log("Express server on PORT:", port);
});
