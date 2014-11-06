#ifndef MqttSerial_h
#define MqttSerial_h
#include "Arduino.h"	

class MqttSerial {
private:
   void printToSerialPort(int command, String value);
   int readtopicname = 1;
   String topicName;
   String clientName;
   SoftwareSerial *serial; 

public:
   MqttSerial(String , SoftwareSerial&);
   void begin(String host, String port, String username, String password);
   void connect();
   void publish(String topic, String payload);
   void subscribe(String filterTopic);
   void disconnect();
   void loop(void(*) (String , String));
};


#endif
