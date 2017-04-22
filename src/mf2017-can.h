/* mf2017-can library by Julien Vanier <jvanier@gmail.com>
 */

#pragma once

#include "Particle.h"
#include "can-interface.h"

enum class MachineModules {
  Panel1,
  Panel2,
  Panel3,
  Panel4,
  Panel5,
  Lights,
  Display,
  Supervisor,
};

enum class ReservoirStatus : uint8_t {
  OK,
  Full,
  Empty
};

class Communication {
private:
  CANInterface &can;

public:
  constexpr static long baudRate = 500000;

  Communication(CANInterface &can);
  void begin();
  void receive();
  void transmit(MachineModules module);

public:
  // All the variables shared between the modules

  // Panel1
  bool Input1Active;
  ReservoirStatus Reservoir1Status;
  bool GreenButtonPressed;
  bool BlueButtonPressed;
  bool RedButtonPressed;

  long Panel1StatusLastTx;
  long Panel1StatusLastRx;

  // Panel2
  bool Input2Active;
  ReservoirStatus Reservoir2Status;
  uint8_t InputColorHue;

  long Panel2StatusLastTx;
  long Panel2StatusLastRx;

  // Panel3
  bool Input3Active;
  ReservoirStatus Reservoir3Status;
  float InputCrankSpeed;

  long Panel3StatusLastTx;
  long Panel3StatusLastRx;

  // Panel4
  bool Input4Active;
  ReservoirStatus Reservoir4Status;
  bool LeftJoystickUp;
  bool LeftJoystickDown;
  bool RightJoystickUp;
  bool RightJoystickDown;

  long Panel4StatusLastTx;
  long Panel4StatusLastRx;

  // Lights
  bool LightsActive;

  long LightsStatusLastTx;
  long LightsStatusLastRx;

  // Display
  bool DisplayActive;

  long DisplayStatusLastTx;
  long DisplayStatusLastRx;

  // Supervisor
  bool MachineStart;
  bool MachineStop;

  long SupervisorControlLastTx;
  long SupervisorControlLastRx;
  
  // machine config
  float InputCrankBallWheelSpeedRatio;

  long Panel3ConfigLastTx;
  long Panel3ConfigLastRx;

private:
  void decodeMessage(CANMessage m);
};
