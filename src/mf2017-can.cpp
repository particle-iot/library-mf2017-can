/* particle-mf2017-can library by Julien Vanier <jvanier@gmail.com>
 */

#include "mf2017-can.h"
#include "bitset.h"

enum MessageIds {
  Panel1Status = 0x101,
  Panel2Status = 0x102,
  Panel3Status = 0x103,
  Panel4Status = 0x104,
  LightsStatus = 0x110,
  DisplayStatus = 0x120,
  SupervisorControl = 0x030,
  Panel3Config = 0x500,
};

Communication::Communication(CANInterface &can) :
  can(can)
{
}

void Communication::begin() {
  can.begin(baudRate);
}

void Communication::receive() {
  CANMessage m;
  while (can.receive(m)) {
    decodeMessage(m);
  }
}

void Communication::decodeMessage(CANMessage m) {
  switch (m.id) {
    case Panel1Status:
      Panel1StatusLastRx = millis();
      Input1Active = getBit(m.data, 0, 0);
      Reservoir1Status = static_cast<ReservoirStatus>(getU8(m.data, 1));
      RedButtonPressed = getBit(m.data, 2, 0);
      GreenButtonPressed = getBit(m.data, 2, 1);
      BlueButtonPressed = getBit(m.data, 2, 2);
      break;
    case Panel2Status:
      Panel2StatusLastRx = millis();
      Input2Active = getBit(m.data, 0, 0);
      Reservoir2Status = static_cast<ReservoirStatus>(getU8(m.data, 1));
      InputColorHue = getU8(m.data, 2);
      break;
    case Panel3Status:
      Panel3StatusLastRx = millis();
      Input3Active = getBit(m.data, 0, 0);
      Reservoir3Status = static_cast<ReservoirStatus>(getU8(m.data, 1));
      InputCrankSpeed = getFloat(m.data, 4);
      break;
    case Panel4Status:
      Panel4StatusLastRx = millis();
      Input4Active = getBit(m.data, 0, 0);
      Reservoir4Status = static_cast<ReservoirStatus>(getU8(m.data, 1));
      LeftJoystickUp = getBit(m.data, 2, 0);
      LeftJoystickDown = getBit(m.data, 2, 1);
      RightJoystickUp = getBit(m.data, 2, 2);
      RightJoystickDown = getBit(m.data, 2, 3);
      break;
    case LightsStatus:
      LightsStatusLastRx = millis();
      LightsActive = getBit(m.data, 0, 0);
      break;
    case DisplayStatus:
      DisplayStatusLastRx = millis();
      DisplayActive = getBit(m.data, 0, 0);
      break;
    case SupervisorControl:
      SupervisorControlLastRx = millis();
      MachineStart = getBit(m.data, 0, 0);
      MachineStop = getBit(m.data, 0, 1);
      break;
    case Panel3Config:
      Panel3StatusLastRx = millis();
      InputCrankBallWheelSpeedRatio = getFloat(m.data, 0);
      break;
  }
}

void Communication::transmit(MachineModules module) {
  switch(module) {
    case MachineModules::Panel1:
      if (millis() - Panel1StatusLastTx > 100) {
        Panel1StatusLastTx = millis();
        CANMessage m;
        m.id = Panel1Status;
        m.len = 8;
        setBit(m.data, Input1Active, 0, 0);
        setU8(m.data, static_cast<uint8_t>(Reservoir1Status), 1);
        setBit(m.data, RedButtonPressed, 2, 0);
        setBit(m.data, GreenButtonPressed, 2, 1);
        setBit(m.data, BlueButtonPressed, 2, 2);
        can.transmit(m);
      }

      break;

    case MachineModules::Panel2:
      if (millis() - Panel2StatusLastTx > 100) {
        Panel2StatusLastTx = millis();
        CANMessage m;
        m.id = Panel2Status;
        m.len = 8;
        setBit(m.data, Input2Active, 0, 0);
        setU8(m.data, static_cast<uint8_t>(Reservoir2Status), 1);
        setU8(m.data, InputColorHue, 2);
        can.transmit(m);
      }

      break;

    case MachineModules::Panel3:
      if (millis() - Panel3StatusLastTx > 100) {
        Panel3StatusLastTx = millis();
        CANMessage m;
        m.id = Panel3Status;
        m.len = 8;
        setBit(m.data, Input3Active, 0, 0);
        setU8(m.data, static_cast<uint8_t>(Reservoir3Status), 1);
        setFloat(m.data, InputCrankSpeed, 4);
        can.transmit(m);
      }

      break;

    case MachineModules::Panel4:
      if (millis() - Panel4StatusLastTx > 100) {
        Panel2StatusLastTx = millis();
        CANMessage m;
        m.id = Panel4Status;
        m.len = 8;
        setBit(m.data, Input4Active, 0, 0);
        setU8(m.data, static_cast<uint8_t>(Reservoir4Status), 1);
        setBit(m.data, LeftJoystickUp, 2, 0);
        setBit(m.data, LeftJoystickDown, 2, 1);
        setBit(m.data, RightJoystickUp, 2, 2);
        setBit(m.data, RightJoystickDown, 2, 3);
        can.transmit(m);
      }

      break;

    case MachineModules::Lights:
      if (millis() - LightsStatusLastTx > 100) {
        LightsStatusLastTx = millis();
        CANMessage m;
        m.id = LightsStatus;
        m.len = 1;
        setBit(m.data, LightsActive, 0, 0);
        can.transmit(m);
      }

      break;

    case MachineModules::Display:
      if (millis() - DisplayStatusLastTx > 100) {
        DisplayStatusLastTx = millis();
        CANMessage m;
        m.id = DisplayStatus;
        m.len = 1;
        setBit(m.data, DisplayActive, 0, 0);
        can.transmit(m);
      }

      break;

    case MachineModules::Supervisor:
      if (millis() - SupervisorControlLastTx > 100) {
        SupervisorControlLastTx = millis();
        CANMessage m;
        m.id = SupervisorControl;
        m.len = 1;
        setBit(m.data, MachineStart, 0, 0);
        setBit(m.data, MachineStop, 0, 1);
        can.transmit(m);
      }

      if (millis() - Panel3ConfigLastTx > 1000) {
        Panel3ConfigLastTx = millis();
        CANMessage m;
        m.id = Panel3Config;
        m.len = 8;
        setFloat(m.data, InputCrankBallWheelSpeedRatio, 0);
        can.transmit(m);
      }

      break;
  }
}
