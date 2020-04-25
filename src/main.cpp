#include <Arduino.h>
// Loading the ESP8266WiFi library and the PubSubClient library
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "floor_leds.hpp"

// Change the credentials below, so your ESP8266 connects to your router
const char* ssid = "apartment_led_demo";
const char* password = "raven_apartment";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* MQTT_SERVER = "192.168.4.1";
const int MQTT_PORT = 1883;

#if defined(ESP_FLOOR_1)
const char* MQTT_CLIENT_NAME = "ESP8266ClientFloor1";
const char* MQTT_TOPIC_SUB = "floor/1";
#elif defined(ESP_FLOOR_2)
const char* MQTT_CLIENT_NAME = "ESP8266ClientFloor2";
const char* MQTT_TOPIC_SUB = "floor/2";
#elif defined(ESP_FLOOR_3)
const char* MQTT_CLIENT_NAME = "ESP8266ClientFloor3";
const char* MQTT_TOPIC_SUB = "floor/3";
#elif defined(ESP_FLOOR_4)
const char* MQTT_CLIENT_NAME = "ESP8266ClientFloor4";
const char* MQTT_TOPIC_SUB = "floor/4";
#elif defined(ESP_FLOOR_5)
const char* MQTT_CLIENT_NAME = "ESP8266ClientFloor5";
const char* MQTT_TOPIC_SUB = "floor/5";
#elif defined(ESP_FLOOR_6)
const char* MQTT_CLIENT_NAME = "ESP8266ClientFloor6";
const char* MQTT_TOPIC_SUB = "floor/6";
#elif defined(ESP_FLOOR_7)
const char* MQTT_CLIENT_NAME = "ESP8266ClientFloor7";
const char* MQTT_TOPIC_SUB = "floor/7";
#elif defined(ESP_FLOOR_8)
const char* MQTT_CLIENT_NAME = "ESP8266ClientFloor8";
const char* MQTT_TOPIC_SUB = "floor/8";
#endif

// Initializes the espClient
WiFiClient espClient;
PubSubClient client(espClient);

// Don't change the function below. This functions connects your ESP8266 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// const values for callback
const int MAX_MESSAGE_LENGTH = 32;
const char MESSAGE_DELIMITER = '/';

int delimiterIndex = 0;
String roomNumber;
String action;

// This functions is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);

  if (length > MAX_MESSAGE_LENGTH) {
    Serial.print("message length too big: ");
    Serial.println(length);
  }

  Serial.print(". Message: ");
  String messageTemp;

  // construct message into string
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // separate message into substring
  delimiterIndex = messageTemp.indexOf(MESSAGE_DELIMITER);
  if (delimiterIndex == -1) {
    Serial.println("message missing delimiter");
  }
  roomNumber = messageTemp.substring(0, delimiterIndex);
  action = messageTemp.substring(delimiterIndex+1);

  Serial.print("room number: "); Serial.print(roomNumber);
  Serial.print(", action: "); Serial.println(action);

  // handle all case
  if (roomNumber == "all" && action == "1") {
    for (auto room : floorLeds) {
				room->on();
		}
		return;
	}
	if (roomNumber == "all" && action == "0") {
      for (auto room : floorLeds) {
  			room->off();
		}
		return;
	}

  // handle specific room
  for (auto room : floorLeds) {
    if (roomNumber == room->roomNum) {
      Serial.print("Changing room "); Serial.print(roomNumber);
      if(action == "1"){
        room->on();
        Serial.println(" On");
      }
      else if(action == "0"){
        room->off();
        Serial.println(" Off");
      }
    }
  }

}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
     /*
     YOU  NEED TO CHANGE THIS NEXT LINE, IF YOU'RE HAVING PROBLEMS WITH MQTT MULTIPLE CONNECTIONS
     To change the ESP device ID, you will have to give a unique name to the ESP8266.
     Here's how it looks like now:
       if (client.connect("ESP8266Client")) {
     If you want more devices connected to the MQTT broker, you can do it like this:
       if (client.connect("ESPOffice")) {
     Then, for the other ESP:
       if (client.connect("ESPGarage")) {
      That should solve your MQTT multiple connections problem

     THE SECTION IN loop() function should match your device name
    */
    if (client.connect(MQTT_CLIENT_NAME)) {
      Serial.println("connected");
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe(MQTT_TOPIC_SUB);

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// The setup function sets your ESP GPIOs to Outputs, starts the serial communication at a baud rate of 115200
// Sets your mqtt broker and sets the callback function
// The callback function is what receives messages and actually controls the LEDs
void setup() {

  // set all led pins to output mode and off
  for (auto room : floorLeds) {
    room->begin();
  }

  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  Serial.print("mqtt client: "); Serial.println(MQTT_CLIENT_NAME);
  Serial.print("topic: "); Serial.println(MQTT_TOPIC_SUB);
}

// For this project, you don't need to change anything in the loop function.
// Basically it ensures that you ESP is connected to your broker
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
     /*
     YOU  NEED TO CHANGE THIS NEXT LINE, IF YOU'RE HAVING PROBLEMS WITH MQTT MULTIPLE CONNECTIONS
     To change the ESP device ID, you will have to give a unique name to the ESP8266.
     Here's how it looks like now:
       client.connect("ESP8266Client");
     If you want more devices connected to the MQTT broker, you can do it like this:
       client.connect("ESPOffice");
     Then, for the other ESP:
       client.connect("ESPGarage");
      That should solve your MQTT multiple connections problem

     THE SECTION IN reconnect() function should match your device name
    */
    client.connect(MQTT_CLIENT_NAME);
}
