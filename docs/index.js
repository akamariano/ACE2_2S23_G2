function toggleButtonText(button) {
    if (button.textContent === "Encender") {
        button.textContent = "Apagar";
    } else {
        button.textContent = "Encender";
    }
}

const encenderButton = document.querySelector('.flashcard-button');
encenderButton.addEventListener('click', function () {
    toggleButtonText(this); 
});
function toggleButtonColor(button) {
    button.classList.toggle("red"); 
}

encenderButton.addEventListener('click', function () {
    toggleButtonText(this); 
    toggleButtonColor(this); 
});
var verGraficasButton = document.getElementById('verGraficas');

   
    verGraficasButton.addEventListener('click', function() {
       
        window.open('https://arqui2database.grafana.net/d/f807ac0a-d5be-4390-9048-e9bc4cef28b4/arqui2?orgId=1&from=1697093219717&to=1697266019717', '_blank');
    });