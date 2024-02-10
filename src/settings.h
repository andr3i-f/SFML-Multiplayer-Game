#pragma once

namespace Settings {
  enum PacketTypes : int {
      NEW_CONNECTION = 1,
      ROTATION_CHANGE = 2,
      PLAYER_SHOOT = 3,
      DISCONNECT = 4
  };
}