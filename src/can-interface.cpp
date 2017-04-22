// Interface for CAN functionality to allow a different driver on the
// Photon and Raspberry Pi

#include "can-interface.h"

BuiltinCAN::BuiltinCAN(HAL_CAN_Channel channel) :
  can(channel)
{
}

void BuiltinCAN::begin(unsigned long baudRate) {
  can.begin(baudRate);
}

bool BuiltinCAN::available() {
  return can.available();
}

bool BuiltinCAN::receive(CANMessage &message) {
  return can.receive(message);
}

bool BuiltinCAN::transmit(const CANMessage &message) {
  return can.transmit(message);
}

