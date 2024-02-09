#include "world.h"

World::World(Client *& c, Player *& p) {
  window.setVerticalSyncEnabled(true);
  client = c;
  player = p;
}

void World::run() {
  sf::Clock clock;
  sf::Time t{sf::Time::Zero};
  sf::Time dt{sf::seconds(1.0f / 60.f)};

  while (window.isOpen()) {
    processEvents();
    client->receiveData(others);

    t += clock.restart();
    while (t > dt) {
      t -= dt;
      processEvents();
      client->receiveData(others);
      update(dt.asSeconds());
    }

    render();
  }
}

void World::update(float dt) {
  // update objects here
  player->update(dt, window);
  client->sendData();
}

void World::render() {
  window.clear();

  // render objects here
  player->render(window);

  for (auto & [key, value] : others) {
    value.render(window);
  }

  window.display();
}

void World::processEvents() {
  for (sf::Event event; window.pollEvent(event);) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
}