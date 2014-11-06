#include "SoftwareSerial.h"
#include "MqttSerial.h"
#include "JsonParser.h"

using namespace ArduinoJson::Parser;

MqttSerial::MqttSerial(String clientName, SoftwareSerial &serial)  {
  this->clientName = clientName;
  this->serial = &serial;
}

void MqttSerial::printToSerialPort(int command, String value) {
  serial->write(command);
  serial->print(value);
  serial->write(245);  
}

void MqttSerial::begin(String hostname, String port, String username, String password) {
  
  printToSerialPort(1, clientName);
  printToSerialPort(2, hostname);
  printToSerialPort(3, port);
  printToSerialPort(4, username);
  printToSerialPort(5, password);
}

void MqttSerial::connect()
{
  printToSerialPort(6, "");
}

void MqttSerial::disconnect()
{
  printToSerialPort(7, "");
}

void MqttSerial::publish(String topic, String payload) {
  printToSerialPort(8, topic);
  printToSerialPort(9, payload);
  
}

void MqttSerial::subscribe(String topic) {
  printToSerialPort(10, topic);
  
}


void MqttSerial::loop(void (*callback) (String topic, String payload)) {
	 
  if (serial->available() > 1) {
     char buff[1000];
     int i =0;
     int data = serial->read();	
     JsonParser<16> parser;


     while (true) {
       if (data == -1) continue;
       if (data == 254) break;       
       buff[i++] = data;
       data = serial->read();
       delay(10);
     }
     buff[i] = '\0';

     JsonObject root = parser.parse(buff);
     char* topic = root["topic"];
     char* payload = root["payload"];

     String topicS(topic);
     String payloadS(payload); 
    	 
     callback(topicS, payloadS);

  }	

    
}


