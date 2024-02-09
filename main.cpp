#include <iostream>

#include "src/server.h"
#include "src/client.h"
#include "src/game/player.h"
#include "src/game/world.h"

int main(int argc, char ** argv) {
  if (argc < 2) {
    std::cout << "Need atleast 's' or 'c' as argument.";
  } else if (argv[1][0] == 's') {
    Server s;
    s.run();
  } else if (argv[1][0] == 'c') {
    Player * p = new Player;
    Client * c = new Client{p};
    World w{c, p};
    w.run();

    delete c;
    delete p;
  }
}
