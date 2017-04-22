// Example showing how to listen to all messages

#include "mf2017-can.h"

BuiltinCAN can(CAN_D1_D2);
Communication comms(can);

void setup() {
  Serial.begin();
  comms.begin();
}

void loop() {
  comms.receive();

  // Print the state of receive messages
  static long t = 0;
  if (millis() - t > 1000) {
    Serial.printlnf("P1=%d P2=%d P3=%d P4=%d L=%d D=%d",
      comms.Input1Active,
      comms.Input2Active,
      comms.Input3Active,
      comms.Input4Active,
      comms.LightsActive,
      comms.DisplayActive
    );

    t = millis();
  }
}
