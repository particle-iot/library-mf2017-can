// Example showing how to listen to all messages

#include "mf2017-can.h"

Communication comms;

void setup() {
  Serial.begin();
  comms.begin();
}

void loop() {
  comms.receive();

  // Print the state of receive messages
  static long t = 0;
  if (millis() - t > 1000) {
    Serial.printlnf("S1=%d S2=%d S3=%d S4=%d S5=%d",
      comms.testCounter[0],
      comms.testCounter[1],
      comms.testCounter[2],
      comms.testCounter[3],
      comms.testCounter[4]
    );

    t = millis();
  }
}
