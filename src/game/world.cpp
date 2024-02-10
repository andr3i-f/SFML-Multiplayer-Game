#include "world.h"

World::World(Client *& c, Player *& p) {
  window.setVerticalSyncEnabled(true);

  if (!font.loadFromFile("assets/fonts/arial.ttf")) {
    std::cout << "Could not load font\n";
  }

  ableToShoot.setFont(font);
  ableToShoot.setCharacterSize(20);
  ableToShoot.setStyle(sf::Text::Bold);
  ableToShoot.setString("YOUR TURN TO SHOOT");
  ableToShoot.setPosition(sf::Vector2f{50, 50});

  client = c;
  player = p;
}

void World::run() {
  sf::Clock clock;
  sf::Time t{sf::Time::Zero};
  sf::Time dt{sf::seconds(1.0f / 60.f)};

  while (window.isOpen()) {
    processEvents();
    client->receiveData(others, projectiles);
    //std::cout << "Other size: " << others.size()  << ' ' << t.asMilliseconds() << '\n';

    t += clock.restart();
    while (t > dt) {
      t -= dt;
      processEvents();
      client->receiveData(others, projectiles);
      update(dt.asSeconds());
    }

    render();
  }
}

void World::update(float dt) {
  // update objects here
  player->update(dt, window);
  client->sendData();

  for (Projectile & p : projectiles) {
    p.update(dt);
  }
}

void World::render() {
  window.clear();

  // render objects here
  player->render(window);

  //std::cout << others.size() << '\n' << " - " << '\n';

  if (player->canShoot && !player->playerHasShot) {
    window.draw(ableToShoot);
  }

  for (auto & [key, value] : others) {
    value.render(window);
  }

  for (Projectile & p : projectiles) {
    p.render(window);
  }

  window.display();
}

void World::processEvents() {
  for (sf::Event event; window.pollEvent(event);) {
    if (event.type == sf::Event::Closed) {
      window.close();
      client->disconnect();
    }
  }
}