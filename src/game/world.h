#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <sstream>

#include "player.h"
#include "../server.h"

enum GameState {
  MAIN_MENU = 0,
  PLAYING,
  WON,
  LOST,
  HOST,
  HOSTING
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
  void clearWorld();

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
    sf::RectangleShape hostButton;
    sf::RectangleShape startServerHostButton;
    sf::RectangleShape goBackButton;

    sf::Color lightGray{200, 200, 200};
    sf::Color gray{152, 156, 155};
    sf::Color darkGray{125, 125, 125};
    sf::Color darkGreen{78, 153, 63};
    sf::Color lightGreen{109, 204, 90};

    bool attemptJoin{false};
    bool goToHostScreen{false};
    bool goBackToMain{false};
    bool attemptStartServer{false};


  public:
    void update(sf::RenderWindow&, GameState);

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
  sf::Text hostButtonText;
  sf::Text startServerHostText;
  sf::Text goBackText;
  sf::Text serverIPText;
  sf::Text hostMenuInfo;
  std::string userPortInput{};
  std::string serverIPInput{};
  std::string serverPortInput{};

  sf::Text creditsText;

  Player * player;

  sf::RectangleShape playerPowerBackGround;
  sf::RectangleShape playerPowerIndicator;

  std::vector<Player*> others;
  std::vector<Projectile> projectiles;
  std::vector<sf::RectangleShape> objects;

  std::stringstream ss;

  GameState state;

  Server server{};

  bool bothPlayersConnected{false};
};