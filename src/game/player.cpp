#include "player.h"

Player::Player() {
  if (!texture.loadFromFile("assets/images/tank_spritesheet.png")) {
    std::cout << "Could not load spritesheet." << std::endl;
  }

  body.setTexture(texture);
  barrel.setTexture(texture);
}

Player::Player(int num) {
  if (!texture.loadFromFile("assets/images/tank_spritesheet.png")) {
    std::cout << "Could not load spritesheet." << std::endl;
  }

  body.setTexture(texture);
  barrel.setTexture(texture);
  float rotation;
  
  std::cout << num << '\n';
  if (num == 2) {
    body.setTextureRect(sf::IntRect{0, 74, 81, 57});
    barrel.setTextureRect(sf::IntRect {0, 134, 47, 14});
    body.setOrigin(body.getTextureRect().width / 2, body.getTextureRect().height / 4);
    barrel.setOrigin(barrel.getTextureRect().width - barrel.getTextureRect().width, barrel.getTextureRect().height / 2);
    body.setPosition(1100, 757);
    body.setScale(-1, 1);
    rotation = 225;
  } else if (num == 1) {
    body.setTextureRect(sf::IntRect{0, 0, 81, 57});
    barrel.setTextureRect(sf::IntRect {0, 134, 47, 14});
    body.setOrigin(body.getTextureRect().width / 2, body.getTextureRect().height / 4);
    barrel.setOrigin(barrel.getTextureRect().width - barrel.getTextureRect().width, barrel.getTextureRect().height / 2);
    body.setPosition(100, 757);
    rotation = 315;
  }

  barrel.setPosition(body.getPosition());
  barrel.setRotation(rotation);
}

void Player::update(float dt, sf::RenderWindow & w) {
  if (w.hasFocus()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      barrel.rotate(-0.25);
      if (barrel.getRotation() <= lowerBoundAngle) {
        barrel.setRotation(lowerBoundAngle);
      }
      //std::cout << "angle: " << cannon.getRotation()  << '\n';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      barrel.rotate(0.25);
      if (barrel.getRotation() >= upperBoundAngle) {
        barrel.setRotation(upperBoundAngle);
      }
      //std::cout << "angle: " << cannon.getRotation() << '\n';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      power += 1;
      if (power > 100) {
        power = 100;
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      power -= 1;
      if (power < 0) {
        power = 0;
      }
    }

    //std::cout << power << '\n';

    this->calculationAngle = barrel.getRotation() - 270;
    if (this->calculationAngle == -270) {
      this->calculationAngle = 90;
    }
    //std::cout << calculationAngle << '\n';

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      if (this->canShoot) {
        this->canShoot = false;
        shoot();
      }
    }
  }
}

void Player::render(sf::RenderWindow & w) {
  w.draw(barrel);
  w.draw(body);
}

void Player::shoot() {
  angleInRad = static_cast<float>(calculationAngle * PI / 180);
  //std::cout << angleInRad << '\n';
  endOfCannonX = barrel.getPosition().x + barrel.getTextureRect().width * std::sin(angleInRad);
  endOfCannonY = barrel.getPosition().y - barrel.getTextureRect().width * std::cos(angleInRad);


  // call client method to shoot
  playerHasShot = true;

  //projectiles.push_back(Projectile{endOfCannonPosition, angleInRad, initialVelocity});
}

void Player::setPlayerData() {
  if (playerNumber == 1) {
    initialAngle = 315;
    upperBoundAngle = 358;
    lowerBoundAngle = 270;
    position.x = 100;
    position.y = 757;

    body.setTextureRect(sf::IntRect{0, 0, 81, 57});
    barrel.setTextureRect(sf::IntRect {0, 134, 47, 14});
    std::cout << "Set player 1 data\n";
  } else if (playerNumber == 2) {
    initialAngle = 225;
    upperBoundAngle = 270;
    lowerBoundAngle = 178;
    position.x = 1100;
    position.y = 757;

    body.setTextureRect(sf::IntRect{0, 74, 81, 57});
    barrel.setTextureRect(sf::IntRect {0, 134, 47, 14});
    body.setScale(-1, 1);
    std::cout << "Set player 2 data\n";
  } else {
    std::cout << "Player num is not 1 or 2." << std::endl;
  }

  canShoot = false;
  playerHasShot = false;
  alive = true;

  body.setOrigin(body.getTextureRect().width / 2, body.getTextureRect().height / 4);
  barrel.setOrigin(barrel.getTextureRect().width - barrel.getTextureRect().width, barrel.getTextureRect().height / 2);
  body.setPosition(position.x, position.y);
  barrel.setPosition(body.getPosition());
  barrel.setRotation(initialAngle);
}