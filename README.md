# Particle Maker Faire 2017 Machine Communication

Share state between all machine modules over CAN.

## Overview

Create a `Communication` object. Read variables that contain state from
other modules you care about, write state about your own module. Call
`receive()` to update other module states and
`transmit(MachimeModules::<my_module>)` to send your own state to other
modules.

```
#include "mf2017-can.h"

Communication comms;

void setup() {
  pinMode(D0, INPUT);
  comms.begin();
}

void loop() {
  // Send your state
  comms.ballsEntering[0] = digitalRead(D0);
  // Read other state
  if (comms.machineState == 0) {
    // disable this station
  }

  // Update CAN bus
  comms.receive();
  comms.transmit(MachineModules::Station1);
}
```

## LICENSE
Copyright 2017 Particle

Licensed under the MIT license
