#include "player.h"

Player::Player() {
  player.setSize( sf::Vector2f{25.f, 25.f} );
  player.setFillColor(sf::Color::Red);
  player.setOrigin( player.getPosition().x / 2, player.getPosition().y / 2 );
  player.setPosition( sf::Vector2f{100.f, 100.f} );
}

Player::Player(float x, float y) {
  player.setSize( sf::Vector2f{25.f, 25.f} );
  player.setFillColor(sf::Color::Red);
  player.setOrigin( player.getPosition().x / 2, player.getPosition().y / 2 );
  player.setPosition( sf::Vector2f{x, y} );
}

void Player::update(float dt, sf::RenderWindow & w) {
  if (w.hasFocus()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      player.move(0, -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      player.move(0, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      player.move(-1, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      player.move(1, 0);
    }
  }
}

void Player::render(sf::RenderWindow & w) {
  w.draw(player);
}