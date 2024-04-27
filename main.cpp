#include <iostream>

#include "src/server.h"
#include "src/client.h"
#include "src/game/player.h"
#include "src/game/world.h"

int main(int argc, char ** argv) {
  Player * p = new Player;
  World * w = new World{p};


  Client c{p, w};
  c.run();

  delete w;
  delete p;
}
