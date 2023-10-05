const express = require("express");
const { redisClient } = require("./RedisDB");
const { publishArduino } = require("./MQTT/ClientArduino");

const app = express();
const port = 3000;
app.use(express.json());

app.get("/", (req, res) => {
    res.send("Hello World!");
});

app.post("/publish", async (req, res) => {
    const { topic, data } = req.body;
    
    // Publicar en el broker
    publishArduino(topic, data);
    
    res.json({message: "Publicacion enviada"})    
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
