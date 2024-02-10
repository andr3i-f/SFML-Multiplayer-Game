#include "projectile.h"

Projectile::Projectile(sf::Vector2f & initialPosition, float angleInRad, float initialVelocity) {
  projectile.setRadius(6.f);
  projectile.setOrigin(projectile.getRadius() / 2, projectile.getRadius() / 2);

  this->position = initialPosition;

  //std::cout << angle << '\n';
  this->angle = angleInRad;

  this->velocity.x = initialVelocity * std::sin(this->angle);
  this->velocity.y = -1 * (initialVelocity * std::cos(this->angle)); // negative means up hurr durr

  //std::cout << this->angle << ' ' << velocity.x << ' ' << velocity.y << '\n';

  this->gravity = 1.2; // mess around with this
}

void Projectile::render(sf::RenderWindow & w) {
  w.draw(projectile);
}

void Projectile::update(float dt) {

  this->velocity.y = velocity.y + gravity;

  this->position.y = this->position.y + this->velocity.y;
  this->position.x = this->position.x + this->velocity.x;

  projectile.setPosition(position);
}

void Projectile::checkCollision() {
 // no thanks
}