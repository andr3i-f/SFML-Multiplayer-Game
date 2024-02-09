#pragma once

namespace Settings {
  enum PacketTypes : int {
      NEW_CONNECTION = 1,
      POSITION_CHANGE = 2,
      DISCONNECT = 3
  };
}