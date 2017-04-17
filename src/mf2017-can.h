#pragma once

/* mf2017-can library by Julien Vanier <jvanier@gmail.com>
 */

#include "Particle.h"

enum class MachineModules {
  Station1,
  Station2,
  Station3,
  Station4,
  Station5,
  Lights,
  Display,
};

class Communication {
public:
  constexpr static int StationCount = 5;
  constexpr static long baudRate = 500000;

  Communication(HAL_CAN_Channel channel = CAN_D1_D2);
  void begin();
  CANChannel& rawCAN();
  void receive();
  void transmit(MachineModules module);

  // All the variables shared between the modules
  bool ballEntering[StationCount];
  bool ballExiting[StationCount];
  uint8_t ballsWaiting[StationCount];
  uint8_t testCounter[StationCount];

  long statusLastTransmit;
  uint8_t myTestCounter;

private:
  void decodeMessage(CANMessage m);

private:
  CANChannel can;
};
