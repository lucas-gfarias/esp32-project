# Auto-ala médica
Projeto feito em **ESP32** com as linguagens *C* e *C++*. Permite ver informações como: temperatura e humidade da sala, temperatura e batimento cardíaco do paciente em um aplicativo só.

<h3 align="left">Languages and Tools:</h3>
<p align="left"> <a href="https://www.cprogramming.com/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="c" width="40" height="40"/> </a> <a href="https://www.w3schools.com/cpp/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="cplusplus" width="40" height="40"/> </a> <a href="https://firebase.google.com/" target="_blank" rel="noreferrer"> <img src="https://www.vectorlogo.zone/logos/firebase/firebase-icon.svg" alt="firebase" width="40" height="40"/> </a> </p>

Feito pelo estudantes:  
Lucas Gerent de Farias, João Vitor Costa Morais, Arthur dos Santos e Vinicius Goulart.  
Turma: 201.

# Instalação    

## Libraries
Primeiro é preciso baixar as libraries:  
``` DTH.H; WiFi.h; IOXhop_FirebaseESP32; OneWire.h; DallasTemperature.h; PulseSensorPlayground.h ``` 

## Montagem do circuito  
**Pino do buzzer.............:** 14(GPIO14)  
**Pino do termômetro corporal:** 18(GPIO18)  
**Pino do sensor DHT.........:** 16(GPIO16)  
**Pinos do Oxímetro..........:** SDA(GPIO21) & SCL(GPIO22)  

Utilizar ***5V***.
