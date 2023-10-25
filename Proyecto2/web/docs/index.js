// ---------------------- SUBSCRIBER ----------------------
const topicsClientWeb = [
    "arqui2_g2_distancia",
    "arqui2_g2_temperatura",
    "arqui2_g2_aire",
    "arqui2_g2_luz",
    "arqui2_g2_alerta"
];

ADDRESS = `broker.hivemq.com:8000`;
const clientWeb = mqtt.connect(`ws://${ADDRESS}/mqtt`);

// Conectarse al broker y suscribirse a los topics
clientWeb.on("connect", () => {
    console.log("ClientWeb - Connected");
    for (const topic of topicsClientWeb) {
        clientWeb.subscribe(topic, () => {
            console.log(`ClientWeb - Subscribed to ${topic}`);
        });
    }
});

// Al recibir un mensaje.
clientWeb.on("message", async (topic, data) => {
    console.log(`ClientWeb - Received message on ${topic}: ${data}`);
    switch (topic) {
        case 'arqui2_g2_distancia':
            document.getElementById("distance_value").innerHTML = data;
            break;
        case 'arqui2_g2_temperatura':
            document.getElementById("temperature_value").innerHTML = data;
            break;
        case 'arqui2_g2_aire':
            document.getElementById("air_value").innerHTML = data;
            break;
        case 'arqui2_g2_luz':
            document.getElementById("light_value").innerHTML = data;
            break;
        case 'arqui2_g2_alerta':
            let content = "";
            if (data == "ad") {
                content = "¡Alerta! Aire en condiciones deficientes.";
            } else if (data == "ao") {
                content = "¡Alerta! Aire en condiciones optimas.";
            } else if (data == "l1") {
                content = "¡Alerta! La luz esta encendida y la habitacion esta vacia.";
            } else if (data == "l2") {
                content = "¡Alerta! Apagando la luz.";
            } else if (data == "t1") {
                content = "¡Alerta! La temperatura ha alcanzado niveles aceptables.";
            }
            alert(content);
        default:
            break;
    }
});

function publishWeb(topic, message) {
    clientWeb.publish(topic, message, (error) => {
        if (!error) {
            console.log(`ClientWeb - Publish:  ${topic} -> ${message}`);
        } else {
            console.error("ClientWeb - Error: ", error);
        }
    });
}

// ---------------------- EVENTOS ----------------------
const powerOnButton = document.querySelector("#power-on-btn");
powerOnButton.addEventListener("click", function () {
    togglePowerOn();
});

const powerOffButton = document.querySelector("#power-off-btn");
powerOffButton.addEventListener("click", function () {
    togglePowerOff();
});

function togglePowerOn() {
    publishWeb("arqui2_g2_led", "1");
}

function togglePowerOff() {
    publishWeb("arqui2_g2_led", "0");
}

const showGraphicsBtn = document.getElementById("verGraficas");

showGraphicsBtn.addEventListener("click", function () {
    window.open(
        "https://arqui2database.grafana.net/d/f807ac0a-d5be-4390-9048-e9bc4cef28b4/arqui2?orgId=1&from=1697093219717&to=1697266019717",
        "_blank"
    );
});

