#include "player.h"

Player::Player() {
  player.setSize( sf::Vector2f{25.f, 25.f} );
  player.setFillColor(sf::Color::Red);
  player.setOrigin( player.getPosition().x / 2, player.getPosition().y / 2 );
  //player.setPosition( sf::Vector2f{100.f, 100.f} );

  body.setSize( sf::Vector2f{35.f , 20.f} );
  cannon.setSize( sf::Vector2f{30.f , 8.f} );

  body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
  cannon.setOrigin(cannon.getSize().x - cannon.getSize().x, cannon.getSize().y / 2);

  body.setPosition(100.f, 800.f - (body.getSize().y / 2));
  cannon.setPosition(body.getPosition());

  body.setFillColor(sf::Color::Blue);
  cannon.setFillColor(sf::Color::Red);
}

Player::Player(float x, float y) {
  player.setSize( sf::Vector2f{25.f, 25.f} );
  player.setFillColor(sf::Color::Red);
  player.setOrigin( player.getPosition().x / 2, player.getPosition().y / 2 );
  player.setPosition( sf::Vector2f{x, y} );
}

void Player::update(float dt, sf::RenderWindow & w) {
  if (w.hasFocus()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      cannon.rotate(-0.25);
      if (cannon.getRotation() <= lowerBoundAngle) {
        cannon.setRotation(lowerBoundAngle);
      }
      std::cout << "angle: " << cannon.getRotation()  << '\n';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      cannon.rotate(0.25);
      if (cannon.getRotation() >= upperBoundAngle) {
        cannon.setRotation(upperBoundAngle);
      }
      std::cout << "angle: " << cannon.getRotation() << '\n';
    }

    this->calculationAngle = cannon.getRotation() - 270;
    if (this->calculationAngle == -270) {
      this->calculationAngle = 90;
    }
    //std::cout << calculationAngle << '\n';

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      shoot();
    }
  }
  for (Projectile & p : projectiles) {
    p.update(dt);
  }
}

void Player::render(sf::RenderWindow & w) {
  w.draw(body);
  w.draw(cannon);

  for (Projectile & p : projectiles) {
    p.render(w);
  }
}

void Player::shoot() {
  float angleInRad = static_cast<float>(calculationAngle * PI / 180);
  //std::cout << angleInRad << '\n';
  float endOfCannonX{ cannon.getPosition().x + cannon.getSize().x * std::sin(angleInRad) };
  float endOfCannonY{ cannon.getPosition().y - cannon.getSize().x * std::cos(angleInRad) };
  sf::Vector2f endOfCannonPosition{ endOfCannonX, endOfCannonY };
  float initialVelocity{ 15.f };

  projectiles.push_back(Projectile{endOfCannonPosition, angleInRad, initialVelocity});
}