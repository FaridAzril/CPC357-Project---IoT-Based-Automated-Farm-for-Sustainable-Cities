#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ESP32Servo.h>


const char* ssid = "far";
const char* pass = "1sampai8";
const char* MQTT_SERVER = "136.114.57.138"; 
const char* TOPIC_SENSORS = "farm/sensors";
const char* TOPIC_CONTROL = "farm/control/temp"; // NEW TOPIC FOR LISTENING
const int MQTT_PORT = 1883;


int fanThreshold = 31;


#define PIN_RAIN 4
#define PIN_DHT 6
#define PIN_MOISTURE 8
#define PIN_SERVO 21
#define PIN_RELAY 14
#define DHTTYPE DHT22 

DHT dht(PIN_DHT, DHTTYPE);
Servo roofServo;
WiFiClient espClient;
PubSubClient mqttClient(espClient);


void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("Message arrived on [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);


  if (String(topic) == TOPIC_CONTROL) {
    fanThreshold = message.toInt();
    Serial.println("New Fan Threshold Set: " + String(fanThreshold));
  }
}

void reconnectMQTT() {
  while (!mqttClient.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (mqttClient.connect("SmartFarm_ESP32")) {
      Serial.println("Connected to MQTT server");
   
      mqttClient.subscribe(TOPIC_CONTROL); 
      Serial.println("Subscribed to control topic");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_RAIN, INPUT);
  pinMode(PIN_RELAY, OUTPUT);
  dht.begin();
  roofServo.attach(PIN_SERVO);
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(callback);
}

void loop() {
  if (!mqttClient.connected()) reconnectMQTT();
  mqttClient.loop();


  float temp = dht.readTemperature();
  int rawSoil = analogRead(PIN_MOISTURE);
  int rain = digitalRead(PIN_RAIN); 


  int soilPercent = map(rawSoil, 4095, 1000, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);
  String weather = (rain == 0) ? "Raining" : "Sunny/Clear";

  String roofStatus;
  String fanStatus;

  if (rain == 0) {
    roofServo.write(0); 
    roofStatus = "Closed (Rain)";
  } else if (temp > fanThreshold) {
    roofServo.write(90);
    roofStatus = "Open (Heat)";
  } else {
    roofServo.write(45);
    roofStatus = "Half-Open";
  }


  if (temp > fanThreshold) {
    digitalWrite(PIN_RELAY, HIGH);
    fanStatus = "ON";
  } else {
    digitalWrite(PIN_RELAY, LOW);
    fanStatus = "OFF";
  }

  String payload = "{\"temp\":" + String(temp) + 
                   ",\"soil\":" + String(soilPercent) + 
                   ",\"weather\":\"" + weather + "\"" +
                   ",\"roof\":\"" + roofStatus + "\"" +
                   ",\"fan\":\"" + fanStatus + "\"" +
                   ",\"limit\":" + String(fanThreshold) + "}";
  
  mqttClient.publish(TOPIC_SENSORS, payload.c_str());
  Serial.println("Sent: " + payload);
  delay(2500); 
}