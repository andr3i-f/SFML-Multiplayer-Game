#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <sstream>

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

  sf::Font font;

  sf::Text ableToShoot;
  sf::Text powerText;

  Client * client;
  Player * player;

  std::map<std::string , Player> others;
  std::vector<Projectile> projectiles;

  std::stringstream ss;
};