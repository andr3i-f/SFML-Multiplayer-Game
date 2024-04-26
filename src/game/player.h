#pragma once

#define PI 3.14159265

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "projectile.h"

class Player {
public:
  Player();
  Player(int);
  void update(float, sf::RenderWindow &);
  void render(sf::RenderWindow &);
  void shoot();
  void setPlayerData();

public:
  sf::Texture texture;

  sf::Sprite body;
  sf::Sprite barrel;

  /*
  sf::RectangleShape body;
  sf::RectangleShape cannon;
  */

  float calculationAngle;
  float initialAngle;
  float upperBoundAngle;
  float lowerBoundAngle;

  bool canShoot{false};
  bool playerHasShot{false};
  bool alive{true};

  int playerNumber;
  sf::Vector2f position;

  float angleInRad;
  float endOfCannonX;
  float endOfCannonY;
  float initialVelocity{ 15.f };

  float power{ 0.f };

  std::vector<Projectile> projectiles;
};