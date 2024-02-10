#pragma once

#define PI 3.14159265

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "projectile.h"

class Player {
public:
  Player();
  Player(float, float, float);
  void update(float, sf::RenderWindow &);
  void render(sf::RenderWindow &);
  void shoot();

public:
  sf::RectangleShape body;
  sf::RectangleShape cannon;

  float calculationAngle;
  float initialAngle;
  float upperBoundAngle;
  float lowerBoundAngle;

  int playerNumber;
  sf::Vector2f position;

  std::vector<Projectile> projectiles;
};