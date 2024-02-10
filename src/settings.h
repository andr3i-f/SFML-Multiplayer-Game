#pragma once

namespace Settings {
  enum PacketTypes : int {
      NEW_CONNECTION = 1,
      ROTATION_CHANGE = 2,
      PLAYER_SHOOT = 3,
      PROJECTILE_RENDER = 4,
      DISCONNECT = 5
  };
}