const {SerialPort, ReadlineParser} = require('serialport');
const axios = require('axios');

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
    topic = arduinoData[0].toLowerCase();
    dataSend = arduinoData[1];
        
    console.log(`Arduino - Topic: ${topic} Data: ${dataSend}`)

    // Enviar peticion a la API para publicar en el broker
    await axios.post('http://localhost:3000/publish', {
        topic,
        data: dataSend
    })
})

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

port.on("open", () => {
    console.log("Arduino - Port is open");
});

port.on("close", () => {
    console.log("Arduino - Port is closed");
});

port.on("error", (error) => {
    console.error("Arduino - Port error: ", error);
});

module.exports = {
    sendToArduino
}