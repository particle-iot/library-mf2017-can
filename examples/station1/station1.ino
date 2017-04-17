// Example showing how station 1 receives messages from other stations
// and transmits its own messages

#include "mf2017-can.h"

Communication comms;

void setup() {
  comms.begin();
}

void loop() {
  // Write to comms.<varname> for all your own variables and call comms.transmit()
  // Read the state of other module variables in comms.<othervarname>

  // Simulate change of state every second
  static long t = millis();
  if (millis() - t > 1000) {
    comms.ballEntering[0] = !comms.ballEntering[0];
    t = millis();
  }

  comms.receive();
  comms.transmit(MachineModules::Station1);
}
