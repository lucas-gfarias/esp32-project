// imports
#include <DHT.h>
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PulseSensorPlayground.h>

// pinout
#define hTempPin 18
#define roomPin 16
#define buzPin 14

// firebase
#define FIREBASE_HOST "https://yourfirebares.com/"
#define FIREBASE_AUTH "random cryptografed authentication key"
#define WIFI_SSID "YOUR SSID"
#define WIFI_PASSWORD "YOURPASSWORD"

#define USE_ARDUINO_INTERRUPTS true
#define DHTTYPE DHT11

// set objects
OneWire oneWire(hTempPin);
DallasTemperature tempSensor(&oneWire);
DHT dht(roomPin, DHTTYPE);

PulseSensorPlayground pulseSensor;


const int OUTPUT_TYPE = SERIAL_PLOTTER;
const int PULSE_INPUT = 36;
const int PULSE_BLINK = 2;
const int PULSE_FADE = 5;
const int THRESHOLD = 660;



void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.print(" connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.print(" connected to the database ");
  Serial.println(FIREBASE_HOST);

  // start pins
  pinMode(buzPin, OUTPUT);
  pinMode(roomPin, INPUT);

  // start dht and others
  dht.begin();
  tempSensor.begin();

  // start pulsesensor
  pulseSensor.analogInput(PULSE_INPUT);   
  pulseSensor.blinkOnPulse(2);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(THRESHOLD);
  
}

void loop() {
  bool alright = true;
  /* scatter values 
     1. room temperature and humidity
     2. heart beating
     3. patient's temperature
  */

  //1. DHT INFO
  delay(1000);
  float humidity = dht.readHumidity();
  float rTemp = dht.readTemperature();

  if (humidity > 61 || humidity < 49) {
    alright = false;
  }
  if (rTemp > 25 || rTemp < 20) {
    alright = false;
  }

  //2. PULSESENSOR INFO
  delay(10000);
  int pBPM = pulseSensor.getBeatsPerMinute();
  if (pBPM > 100 || pBPM < 60) {
    alright = false;
  }

  //3 TERMOMETER INFO
  tempSensor.requestTemperatures();
  float bTemp = tempSensor.getTempCByIndex(0);
  if (bTemp > 25 || bTemp < 20) {
    alright = false;
  }

  // set value
  Serial.println("humidade");
  Serial.println(humidity);
  Serial.println("rt");
  Serial.println(rTemp);
  Serial.println("bt");
  Serial.println(bTemp);
  Serial.println("bpm");
  Serial.println(pBPM);
  Serial.println("status");
  Serial.println(alright);

  Firebase.setFloat("projeto/humidityValue", humidity);
  delay(500);
  Firebase.setFloat("projeto/roomTemperature", rTemp);
  delay(500);
  Firebase.setFloat("projeto/bodyTemperature", bTemp);
  delay(500);
  Firebase.setFloat("projeto/BPM", pBPM);
  delay(500);
  Firebase.setBool("projeto/status", alright);
  delay(100);
}
