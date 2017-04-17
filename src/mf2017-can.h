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
  None, // Special module for listening only
};

class Communication {
public:
  constexpr int StationCount = 5;

  Communication(MachineModule myself, HAL_CAN_Channel channel = CAN_D1_D2);
  void begin();
  void process();

  CANChannel& rawCAN();

  // All the variables shared between the modules
  bool ballEntering[StationCount];
  bool ballExiting[StationCount];
  uint8_t ballsWaiting[StationCount];

  long statusLastTransmit;

private:
  void decodeMessage(CANMessage m);
  void transmitModuleMessages();

private:
  MachineModule myself;
  CANChannel can;
};
