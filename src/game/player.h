#pragma once

#define PI 3.14159265

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "projectile.h"

class Player {
public:
  Player();
  Player(float, float);
  void update(float, sf::RenderWindow &);
  void render(sf::RenderWindow &);
  void shoot();

public:
  sf::RectangleShape player;

  sf::RectangleShape body;
  sf::RectangleShape cannon;

  float calculationAngle;

  std::vector<Projectile> projectiles;
};