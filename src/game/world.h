#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <sstream>

#include "player.h"

enum GameState {
  MAIN_MENU = 0,
  PLAYING,
  WON,
  LOST
};

class World {
public:
  World(Player *&);
  ~World();

  void run();
  void update(float dt);
  void render();
  void processEvents();
  void checkCollision();
  void deleteProjectiles();
  void clearInput();

  struct UserInputWindow {
    UserInputWindow();

    enum SelectedBox {
      userPortSelect = 0,
      serverIPSelect,
      serverPortSelect,
      none
    };

    SelectedBox currentSelected;

    sf::RectangleShape userPortBox;
    sf::RectangleShape serverIPBox;
    sf::RectangleShape serverPortBox;

    sf::RectangleShape joinButton;

    sf::Color lightGray{200, 200, 200};
    sf::Color gray{152, 156, 155};
    sf::Color darkGray{125, 125, 125};
    sf::Color darkGreen{78, 153, 63};
    sf::Color lightGreen{109, 204, 90};

    bool attemptJoin{false};


  public:
    void update(sf::RenderWindow&);

    void draw(sf::RenderWindow&);
  };

  sf::RenderWindow window;

  sf::Font font;

  sf::Text ableToShoot;
  sf::Text powerText;
  sf::Text gameName;
  sf::Text userPort;
  sf::Text serverIP;
  sf::Text serverPort;

  sf::Text gameWonText;
  sf::Text gameLostText;
  sf::Text clickToContinueText;

  UserInputWindow uiw;
  sf::Text userPortDisplay;
  sf::Text serverIPDisplay;
  sf::Text serverPortDisplay;
  sf::Text joinButtonText;
  std::string userPortInput{};
  std::string serverIPInput{};
  std::string serverPortInput{};

  sf::Text creditsText;

  Player * player;

  sf::RectangleShape playerPowerBackGround;
  sf::RectangleShape playerPowerIndicator;

  std::map<std::string , Player*> others;
  std::vector<Projectile> projectiles;
  std::vector<sf::RectangleShape> objects;

  std::stringstream ss;

  GameState state;

  bool bothPlayersConnected{false};
};