#pragma once

#define PI 3.14159265

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Projectile {
public:
  Projectile(sf::Vector2f &, float, float);

  void render(sf::RenderWindow &);
  void update(float);
  void checkCollision();

private:
  sf::CircleShape projectile;
  float angle;
  float gravity;
  sf::Vector2f velocity;
  sf::Vector2f position;
};