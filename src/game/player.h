#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:
  Player();
  Player(float, float);
  void update(float, sf::RenderWindow &);
  void render(sf::RenderWindow &);

public:
  sf::RectangleShape player;
};