const { PORT, ADDRESS } = require('./Config');

const mosca = require('mosca');
const broker = new mosca.Server({ port: PORT });

broker.on("ready", () => {
    console.log("MQTT - Broker is ready on ", ADDRESS);
})

broker.on("clientConnected", (client) =>{
    console.log("MQTT - Client connected: ", client.id);
})

broker.on("clientDisconnected", function onClientDisconnected(client) {
    console.log("MQTT - Client disconnected: ", client.id);
});