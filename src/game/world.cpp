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
  gameName.setCharacterSize(50);
  gameName.setString("2D Tank Shooter");
  gameName.setPosition(sf::Vector2f{410, 50});

  userPort.setFont(font);
  userPort.setStyle(sf::Text::Bold);
  userPort.setCharacterSize(20);
  userPort.setString("Enter client port: ");
  userPort.setPosition(sf::Vector2f{uiw.userPortBox.getPosition().x, 200});

  serverIP.setFont(font);
  serverIP.setStyle(sf::Text::Bold);
  serverIP.setCharacterSize(20);
  serverIP.setString("Enter server IP: ");
  serverIP.setPosition(sf::Vector2f{uiw.serverIPBox.getPosition().x, 300});

  serverPort.setFont(font);
  serverPort.setStyle(sf::Text::Bold);
  serverPort.setCharacterSize(20);
  serverPort.setString("Enter server port: ");
  serverPort.setPosition(sf::Vector2f{uiw.serverPortBox.getPosition().x, 400});

  uiw = UserInputWindow();

  userPortDisplay.setFont(font);
  userPortDisplay.setStyle(sf::Text::Bold);
  userPortDisplay.setCharacterSize(20);
  userPortDisplay.setPosition(uiw.userPortBox.getPosition());

  serverPortDisplay.setFont(font);
  serverPortDisplay.setStyle(sf::Text::Bold);
  serverPortDisplay.setCharacterSize(20);
  serverPortDisplay.setPosition(uiw.serverPortBox.getPosition());

  serverIPDisplay.setFont(font);
  serverIPDisplay.setStyle(sf::Text::Bold);
  serverIPDisplay.setCharacterSize(20);
  serverIPDisplay.setPosition(uiw.serverIPBox.getPosition());

  joinButtonText.setFont(font);
  joinButtonText.setStyle(sf::Text::Bold);
  joinButtonText.setCharacterSize(20);
  joinButtonText.setPosition(uiw.joinButton.getPosition().x + 22, uiw.joinButton.getPosition().y + 12);
  joinButtonText.setString("JOIN");

  gameWonText.setFont(font);
  gameWonText.setStyle(sf::Text::Bold);
  gameWonText.setCharacterSize(20);
  gameWonText.setPosition(sf::Vector2f{450, 300});
  gameWonText.setString("You won! Congratulations");

  gameLostText.setFont(font);
  gameLostText.setStyle(sf::Text::Bold);
  gameLostText.setCharacterSize(20);
  gameLostText.setPosition(sf::Vector2f{450, 300});
  gameLostText.setString("You lost!");

  clickToContinueText.setFont(font);
  clickToContinueText.setStyle(sf::Text::Bold);
  clickToContinueText.setCharacterSize(20);
  clickToContinueText.setPosition(sf::Vector2f{450, 400});
  clickToContinueText.setString("Click to continue to main menu");

  creditsText.setFont(font);
  creditsText.setStyle(sf::Text::Italic);
  creditsText.setCharacterSize(15);
  creditsText.setPosition(sf::Vector2f{820,780});
  creditsText.setString("2D Tank Multiplayer Game made by Andrei F. using SFML");

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
  switch (state) {
    case GameState::MAIN_MENU:

      break;
    case GameState::PLAYING:
      // update objects here
      if (!bothPlayersConnected) {
        if (others.size() != 0) {
          bothPlayersConnected = true;
        }
      }

      if (bothPlayersConnected) {
        if (others.size() == 0) {
          state = GameState::WON;
        }
      }

      player->update(dt, window);

      playerPowerIndicator.setSize(sf::Vector2f {player->power, 20});

      deleteProjectiles();
      checkCollision();

      for (Projectile & p : projectiles) {
        p.update(dt);
      }
      break;
    case GameState::LOST:
      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window.hasFocus()) {
        state = GameState::MAIN_MENU;
        //clearInput();
      }
      break;
    case GameState::WON:
      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window.hasFocus()) {
        state = GameState::MAIN_MENU;
        //clearInput();
      }
      break;
    default:
      break;
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

      window.draw(userPortDisplay);
      window.draw(serverPortDisplay);
      window.draw(serverIPDisplay);
      window.draw(joinButtonText);
      window.draw(creditsText);

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
      window.draw(gameLostText);
      window.draw(clickToContinueText);
      break;
    case GameState::WON:
      window.draw(gameWonText);
      window.draw(clickToContinueText);
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
        switch (uiw.currentSelected) {
          case UserInputWindow::SelectedBox::userPortSelect:
            if (event.text.unicode == 8 && !userPortInput.empty()) {
              userPortInput.pop_back();
            } else if (event.text.unicode != 8 ) {
              userPortInput += static_cast<char>(event.text.unicode);
            }
            userPortDisplay.setString(userPortInput);
            break;
          case UserInputWindow::SelectedBox::serverIPSelect:
            if (event.text.unicode == 8 && !serverIPInput.empty()) {
              serverIPInput.pop_back();
            } else if (event.text.unicode != 8 ) {
              serverIPInput += static_cast<char>(event.text.unicode);
            }
            serverIPDisplay.setString(serverIPInput);
            break;
          case UserInputWindow::SelectedBox::serverPortSelect:
            if (event.text.unicode == 8 && !serverPortInput.empty()) {
              serverPortInput.pop_back();
            } else if (event.text.unicode != 8 ) {
              serverPortInput += static_cast<char>(event.text.unicode);
            }
            serverPortDisplay.setString(serverPortInput);
            break;
          case UserInputWindow::SelectedBox::none:
            break;
        }
      }
    }
  }
}

void World::checkCollision() {
  for (Projectile & p : projectiles) {
    if (p.projectile.getGlobalBounds().intersects(player->body.getGlobalBounds())) {
      player->alive = false;
      state = GameState::LOST;
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

void World::clearInput() {
  userPortInput.clear();
  serverIPInput.clear();
  serverPortInput.clear();

  userPortDisplay.setString(userPortInput);
  serverIPDisplay.setString(serverIPInput);
  serverPortDisplay.setString(serverPortInput);
}

World::UserInputWindow::UserInputWindow() {
  currentSelected = SelectedBox::none;

  userPortBox.setSize(sf::Vector2f{180, 30});
  userPortBox.setPosition(sf::Vector2f{510, 240});
  userPortBox.setFillColor(sf::Color::White);

  serverIPBox.setSize(sf::Vector2f{180, 30});
  serverIPBox.setPosition(sf::Vector2f{510, 340});
  serverIPBox.setFillColor(sf::Color::White);

  serverPortBox.setSize(sf::Vector2f{180, 30});
  serverPortBox.setPosition(sf::Vector2f {510, 440});
  serverIPBox.setFillColor(sf::Color::White);

  joinButton.setSize(sf::Vector2f {100, 50});
  joinButton.setPosition(550, 500);
  joinButton.setFillColor(sf::Color::Green);
}

void World::UserInputWindow::draw(sf::RenderWindow & w) {
  w.draw(userPortBox);
  w.draw(serverIPBox);
  w.draw(serverPortBox);
  w.draw(joinButton);
}

void World::UserInputWindow::update(sf::RenderWindow & w) {
  sf::Vector2i mousePosition{sf::Mouse::getPosition(w)};
  if (userPortBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
    userPortBox.setFillColor(gray);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      currentSelected = SelectedBox::userPortSelect;
      serverIPBox.setFillColor(darkGray);
      serverPortBox.setFillColor(darkGray);
    }
  } else {
    userPortBox.setFillColor(darkGray);
  }

  if (serverIPBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
    serverIPBox.setFillColor(gray);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      currentSelected = SelectedBox::serverIPSelect;
      serverPortBox.setFillColor(darkGray);
      userPortBox.setFillColor(darkGray);
    }
  } else {
    serverIPBox.setFillColor(darkGray);
  }

  if (serverPortBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
    serverPortBox.setFillColor(gray);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      currentSelected = SelectedBox::serverPortSelect;
      userPortBox.setFillColor(darkGray);
      serverIPBox.setFillColor(darkGray);
    }
  } else {
    serverPortBox.setFillColor(darkGray);
  }

  switch (currentSelected) {
    case SelectedBox::userPortSelect:
      userPortBox.setFillColor(lightGray);
      break;
    case SelectedBox::serverIPSelect:
      serverIPBox.setFillColor(lightGray);
      break;
    case SelectedBox::serverPortSelect:
      serverPortBox.setFillColor(lightGray);
      break;
    case SelectedBox::none:
      break;
  }

  if (joinButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
    joinButton.setFillColor(lightGreen);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      attemptJoin = true;
      currentSelected = none;
    }
  } else {
    joinButton.setFillColor(darkGreen);
  }
}