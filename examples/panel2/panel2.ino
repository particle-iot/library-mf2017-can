// Example showing how Panel 1 receives messages from other stations
// and transmits its own messages

#include "mf2017-can.h"

BuiltinCAN can(CAN_D1_D2);
Communication comms(can);

void setup() {
  comms.begin();
}

void loop() {
  // Write to comms.<varname> for all your own variables and call
  // comms.transmit() with your panel name
  // Read the state of other module variables in comms.<othervarname>

  // Simulate change of state
  static long t = millis();
  if (millis() - t > 10) {
    t = millis();
    comms.InputColorHue++;
  }

  comms.receive();
  comms.transmit(MachineModules::Panel2);
}
