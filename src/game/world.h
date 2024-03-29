#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <sstream>

#include "player.h"

class World {
public:
  World(Player *&);
  ~World();

  void run();
  void update(float dt);
  void render();
  void processEvents();
  void checkCollision();
  void deleteProjectiles();

  sf::RenderWindow window;

  sf::Font font;

  sf::Text ableToShoot;
  sf::Text powerText;

  Player * player;

  sf::RectangleShape playerPowerBackGround;
  sf::RectangleShape playerPowerIndicator;

  std::map<std::string , Player*> others;
  std::vector<Projectile> projectiles;
  std::vector<sf::RectangleShape> objects;

  std::stringstream ss;
};