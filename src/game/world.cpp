#include "world.h"

World::World(Player *& p) {
  window.setVerticalSyncEnabled(true);

  if (!font.loadFromFile("assets/fonts/arial.ttf")) {
    std::cout << "Could not load font\n";
  }

  ableToShoot.setFont(font);
  ableToShoot.setCharacterSize(20);
  ableToShoot.setStyle(sf::Text::Bold);
  ableToShoot.setString("YOUR TURN TO SHOOT");
  ableToShoot.setPosition(sf::Vector2f{50, 50});

  powerText.setFont(font);
  powerText.setCharacterSize(20);
  powerText.setStyle(sf::Text::Bold);
  //ss << player->power;
  powerText.setString(std::string("POWER: "));
  powerText.setPosition(sf::Vector2f{ 900, 50 });

  playerPowerBackGround.setSize(sf::Vector2f{100, 20});
  playerPowerBackGround.setPosition(sf::Vector2f {900, 75});
  playerPowerBackGround.setFillColor(sf::Color::Red);

  playerPowerIndicator.setSize(sf::Vector2f{0, 20});
  playerPowerIndicator.setPosition(playerPowerBackGround.getPosition());
  playerPowerIndicator.setFillColor(sf::Color::Green);

  sf::RectangleShape wall;
  wall.setSize(sf::Vector2f {300, 350});
  wall.setOrigin(wall.getSize().x / 2, wall.getSize().y);
  wall.setPosition(sf::Vector2f {600, 800});
  wall.setFillColor(sf::Color::White);
  objects.push_back(wall);

  player = p;
}

World::~World() {
  for (auto & [key, value] : others) {
    delete value;
  }
}

void World::run() {
  sf::Clock clock;
  sf::Time t{sf::Time::Zero};
  sf::Time dt{sf::seconds(1.0f / 60.f)};

  while (window.isOpen()) {
    processEvents();
    //ptr();
    //client->receiveData(others, projectiles);
    //std::cout << "Other size: " << others.size()  << ' ' << t.asMilliseconds() << '\n';

    t += clock.restart();
    while (t > dt) {
      t -= dt;
      processEvents();
      //sPtr();
      //client->receiveData(others, projectiles);
      update(dt.asSeconds());
    }

    render();
  }
}

void World::update(float dt) {
  // update objects here
  player->update(dt, window);

  //client->sendData();

  playerPowerIndicator.setSize(sf::Vector2f {player->power, 20});

  deleteProjectiles();
  checkCollision();

  for (Projectile & p : projectiles) {
    p.update(dt);
  }
}

void World::render() {
  window.clear();

  // render objects here
  player->render(window);

  //std::cout << others.size() << '\n' << " - " << '\n';
  window.draw(powerText);
  window.draw(playerPowerBackGround);
  window.draw(playerPowerIndicator);

  if (player->canShoot) {
    window.draw(ableToShoot);
  }

  for (auto & [key, value] : others) {
    value->render(window);
  }

  for (Projectile & p : projectiles) {
    p.render(window);
  }

  for (sf::RectangleShape & o : objects) {
    window.draw(o);
  }

  window.display();
}

void World::processEvents() {
  for (sf::Event event; window.pollEvent(event);) {
    if (event.type == sf::Event::Closed) {
      window.close();
      //client->disconnect();
    }
  }
}

void World::checkCollision() {
  for (Projectile & p : projectiles) {
    if (p.projectile.getGlobalBounds().intersects(player->body.getGlobalBounds())) {
      window.close();
      //client->disconnect();
    }
  }
}

void World::deleteProjectiles() {
  for (int x{}; x < projectiles.size(); x++) {
    if (projectiles[x].position.y > 850 || projectiles[x].projectile.getGlobalBounds().intersects(objects[0].getGlobalBounds())) {
      projectiles.erase(projectiles.begin() + x);
      std::cout << "Deleted projectile\n";
    }
  }
}