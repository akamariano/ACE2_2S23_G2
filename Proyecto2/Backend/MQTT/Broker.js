const mosca = require('mosca');
const chalk = require('chalk');
const { PORT, ADDRESS } = require('./Config');

const broker = new mosca.Server({ port: PORT });

broker.on("ready", () => {
    console.log(chalk.bold.green("\nMQTT Broker is ready on " + ADDRESS));
})

broker.on("clientConnected", (client) =>{
    console.log("MQTT Client connected: ", client.id);
})

broker.on("clientDisconnected", function onClientDisconnected(client) {
    console.log("MQTT Client disconnected: ", client.id);
});


module.exports = { broker }