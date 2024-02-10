#pragma once

#define PI 3.14159265

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Projectile {
public:
  Projectile(float, float, float, float);

  void render(sf::RenderWindow &);
  void update(float);

public:
  sf::CircleShape projectile;
  float angle;
  float gravity;
  sf::Vector2f velocity;
  sf::Vector2f position;
};