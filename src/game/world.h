#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "../client.h"
#include "player.h"

class World {
public:
  World(Client *&, Player *&);

  void run();
  void update(float dt);
  void render();
  void processEvents();

private:
  sf::RenderWindow window{ sf::VideoMode(1200, 800), "Game" };

  Client * client;
  Player * player;
  std::map<std::string , Player> others;
};