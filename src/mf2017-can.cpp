/* particle-mf2017-can library by Julien Vanier <jvanier@gmail.com>
 */

#include "mf2017-can.h"
#include "bitset.h"

enum MessageIds {
  STATION_1_STATUS = 0x101,
  STATION_2_STATUS = 0x102,
  STATION_3_STATUS = 0x103,
  STATION_4_STATUS = 0x104,
  STATION_5_STATUS = 0x105,
};

Communication::Communication(HAL_CAN_Channel channel) :
  ballEntering(),
  ballExiting(),
  ballsWaiting(),
  testCounter(),
  statusLastTransmit(),
  myTestCounter(),
  can(channel)
{
}

void Communication::begin() {
  can.begin(baudRate);
}

CANChannel& Communication::rawCAN() {
  return can;
}

void Communication::receive() {
  CANMessage m;
  while (can.receive(m)) {
    decodeMessage(m);
  }
}

void Communication::decodeMessage(CANMessage m) {
  switch (m.id) {
    case STATION_1_STATUS:
      ballEntering[0] = getBit(m.data, 0, 0);
      ballExiting[0] = getBit(m.data, 0, 1);
      ballsWaiting[0] = getU8(m.data, 1);
      testCounter[0] = getU8(m.data, 7);
      break;
    case STATION_2_STATUS:
      ballEntering[1] = getBit(m.data, 0, 0);
      ballExiting[1] = getBit(m.data, 0, 1);
      ballsWaiting[1] = getU8(m.data, 1);
      testCounter[1] = getU8(m.data, 7);
      break;
    // etc
    // OR refactor in case all stations send the same data in status message
  }
}

void Communication::transmit(MachineModules module) {
  switch(module) {
    case MachineModules::Station1:
      if (millis() - statusLastTransmit > 100) {
        CANMessage m;
        m.id = STATION_1_STATUS;
        m.len = 8;
        setBit(m.data, ballEntering[0], 0, 0);
        setBit(m.data, ballExiting[0], 0, 1);
        setU8(m.data, ballsWaiting[0], 1);
        setU8(m.data, myTestCounter++, 7);
        can.transmit(m);
        statusLastTransmit = millis();
      }

      // transmit next message, etc

      break;

    case MachineModules::Station2:
      if (millis() - statusLastTransmit > 100) {
        CANMessage m;
        m.id = STATION_2_STATUS;
        m.len = 8;
        setBit(m.data, ballEntering[1], 0, 0);
        setBit(m.data, ballExiting[1], 0, 1);
        setU8(m.data, ballsWaiting[1], 1);
        setU8(m.data, myTestCounter++, 7);
        can.transmit(m);
        statusLastTransmit = millis();
      }

      // transmit next message, etc

      break;
  }
}
