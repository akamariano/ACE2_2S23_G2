const { ADDRESS } = require("./Config");
const mqtt = require("mqtt");

const publisher = mqtt.connect(`mqtt://${ADDRESS}`);

// Conectarse al broker y suscribirse a los topics
publisher.on("connect", () => {
    console.log("Publisher is connected");
});

function publishData(topic, data){
    publisher.publish(topic, data, (error) => {
        if (!error) {
            console.log(`Publisher:  ${topic} -> ${data}`);
        } else {
            console.error("Publisher Error: ", error);
        }
    });
}

// Error.
publisher.on("error", (error) => {
    console.error("Subscriber Error: ", error, "\n");
});


module.exports = {
    publishData
}
