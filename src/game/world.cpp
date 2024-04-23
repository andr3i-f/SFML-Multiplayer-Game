#include "world.h"

World::World(Player *& p) {
  window.setVerticalSyncEnabled(true);

  state = MAIN_MENU;

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

  gameName.setFont(font);
  gameName.setStyle(sf::Text::Bold);
  gameName.setCharacterSize(20);
  gameName.setString("2D Multiplayer Tank Shooter");
  gameName.setPosition(sf::Vector2f{450, 50});

  userPort.setFont(font);
  userPort.setStyle(sf::Text::Bold);
  userPort.setCharacterSize(20);
  userPort.setString("Enter client port: ");
  userPort.setPosition(sf::Vector2f{450, 200});

  serverIP.setFont(font);
  serverIP.setStyle(sf::Text::Bold);
  serverIP.setCharacterSize(20);
  serverIP.setString("Enter server IP: ");
  serverIP.setPosition(sf::Vector2f{450, 300});

  serverPort.setFont(font);
  serverPort.setStyle(sf::Text::Bold);
  serverPort.setCharacterSize(20);
  serverPort.setString("Enter server port: ");
  serverPort.setPosition(sf::Vector2f{450, 400});

  uiw = UserInputWindow();

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

  switch (state) {
    case GameState::MAIN_MENU:
      /*
       *  Game Name Menu
       *  Input for own port
       *  Input for server IP
       *  Input for server Port
       *  Join -> joined(switch to playing) / unable to join(remain in main_menu)
       * */

      window.draw(gameName);

      window.draw(userPort);
      window.draw(serverIP);
      window.draw(serverPort);

      uiw.update(window);

      uiw.draw(window);

      break;
    case GameState::PLAYING:

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
      break;
    case GameState::LOST:
      break;
    case GameState::WON:
      break;
    default:
      break;
  }

  window.display();
}

void World::processEvents() {
  for (sf::Event event; window.pollEvent(event);) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
    if (event.type == sf::Event::TextEntered) {
      if (event.text.unicode < 256) {
        std::cout << static_cast<char>(event.text.unicode) << '\n';
      }
    }
  }
}

void World::checkCollision() {
  for (Projectile & p : projectiles) {
    if (p.projectile.getGlobalBounds().intersects(player->body.getGlobalBounds())) {
      window.close();
      player->alive = false;
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

World::UserInputWindow::UserInputWindow() {
  currentSelected = SelectedBox::userPortSelect;

  userPortBox.setSize(sf::Vector2f{180, 30});
  userPortBox.setPosition(sf::Vector2f{450, 240});
  userPortBox.setFillColor(sf::Color::White);

  serverIPBox.setSize(sf::Vector2f{180, 30});
  serverIPBox.setPosition(sf::Vector2f{450, 340});
  serverIPBox.setFillColor(sf::Color::White);

  serverPortBox.setSize(sf::Vector2f{180, 30});
  serverPortBox.setPosition(sf::Vector2f {450, 440});
  serverIPBox.setFillColor(sf::Color::White);
}

void World::UserInputWindow::draw(sf::RenderWindow & w) {
  w.draw(userPortBox);
  w.draw(serverIPBox);
  w.draw(serverPortBox);
}

void World::UserInputWindow::update(sf::RenderWindow & w) {
  sf::Vector2i mousePosition{sf::Mouse::getPosition(w)};
  if (userPortBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
    userPortBox.setFillColor(gray);
  } else {
    userPortBox.setFillColor(sf::Color::White);
  }
  if (serverIPBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
    serverIPBox.setFillColor(gray);
  } else {
    serverIPBox.setFillColor(sf::Color::White);
  }
  if (serverPortBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
    serverPortBox.setFillColor(gray);
  } else {
    serverPortBox.setFillColor(sf::Color::White);
  }
}