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