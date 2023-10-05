const { ADDRESS } = require("./Config");
const mqtt = require('mqtt');
const {SerialPort, ReadlineParser} = require('serialport');

// ---------------------- SERIAL COMM ---------------------- 

const port = new SerialPort({    
    path: "COM5",
    baudRate: 9600,
});

const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));

// Leer datos del Arduino
parser.on("data", async (arduinoData) => {
    // Leer la data del arduino
    arduinoData = arduinoData.toString();
    arduinoData = arduinoData.split(" ");
    
    // Publicar la data en el broker
    const topic = arduinoData[0].toLowerCase();
    const data = arduinoData[1];
        
    console.log(`Arduino - Topic: ${topic} Data: ${data}`)

    // Enviar la data al broker
    // publishArduino(topic, data);
})

port.on("open", () => {
    console.log("Arduino - Port is open");
});

port.on("close", () => {
    console.log("Arduino - Port is closed");
});

port.on("error", (error) => {
    console.error("Arduino - Port error: ", error);
});


// ---------------------- MQTT ----------------------

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

// Enviar datos al Arduino
function sendToArduino(topic, data) {
    port.write(`${topic}, ${data}\n`, (error) => {
        if (error) {
            console.error("Arduino - Error on write: ", error.message);
        } else {
            console.log(`Arduino - Message sent: ${topic} ${data}`);
        }
    });
}

// ---------------------- ERROR ----------------------

clientArduino.on("error", (error) => {
    console.error("ClientArduino Error: ", error, "\n");
});
