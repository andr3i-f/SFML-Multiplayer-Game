#include "player.h"

Player::Player() {
  body.setSize( sf::Vector2f{35.f , 20.f} );
  cannon.setSize( sf::Vector2f{30.f , 8.f} );

  body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
  cannon.setOrigin(cannon.getSize().x - cannon.getSize().x, cannon.getSize().y / 2);

  body.setPosition(100.f, 800.f - (body.getSize().y / 2));
  cannon.setPosition(body.getPosition());

  body.setFillColor(sf::Color::Blue);
  cannon.setFillColor(sf::Color::Red);
}

Player::Player(float x, float y, float rotation) {
  body.setSize( sf::Vector2f{35.f, 20.f} );
  cannon.setSize( sf::Vector2f{30.f, 8.f} );

  body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
  cannon.setOrigin(cannon.getSize().x - cannon.getSize().x, cannon.getSize().y / 2);

  body.setPosition(x, y);
  cannon.setPosition(body.getPosition());

  body.setFillColor(sf::Color::Red);
  cannon.setFillColor(sf::Color::Blue);

  cannon.setRotation(rotation);
}

void Player::update(float dt, sf::RenderWindow & w) {
  if (w.hasFocus()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      cannon.rotate(-0.25);
      if (cannon.getRotation() <= lowerBoundAngle) {
        cannon.setRotation(lowerBoundAngle);
      }
      //std::cout << "angle: " << cannon.getRotation()  << '\n';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      cannon.rotate(0.25);
      if (cannon.getRotation() >= upperBoundAngle) {
        cannon.setRotation(upperBoundAngle);
      }
      //std::cout << "angle: " << cannon.getRotation() << '\n';
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