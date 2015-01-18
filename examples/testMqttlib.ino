#include <SoftwareSerial.h>
#include <MqttSerial.h>
#include <JsonParser.h>


SoftwareSerial bluetoothSerial(10,11);
MqttSerial mqttSerial ("arduino_lib",bluetoothSerial);
void callback(String, String) ;

void setup() {
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Serial initialized");
  bluetoothSerial.begin(9600);
  pinMode(13, OUTPUT);
  mqttSerial.begin("broker.mqttdashboard.com", "8000", "test", "test");  
  mqttSerial.connect();
  mqttSerial.publish("testing", "testing123");
  mqttSerial.subscribe("helloout");
  mqttSerial.subscribe("helloout2");
  

}
void callback(String topic, String payload) {
  if (topic == "helloout") digitalWrite(13, HIGH);
  if (topic == "helloout2") digitalWrite(13, LOW);
  Serial.println(topic + " : " + payload);
}
void loop() {
  mqttSerial.loop(callback);
}
