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

  struct UserInputWindow {
    UserInputWindow();

    enum SelectedBox {
      userPortSelect = 0,
      serverIPSelect,
      serverPortSelect
    };

    SelectedBox currentSelected;

    sf::RectangleShape userPortBox;
    sf::RectangleShape serverIPBox;
    sf::RectangleShape serverPortBox;


  public:
    void update();

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

  UserInputWindow uiw;
  std::string userPortInput{};
  std::string serverIPInput{};
  std::string serverPortInput{};

  Player * player;

  sf::RectangleShape playerPowerBackGround;
  sf::RectangleShape playerPowerIndicator;

  std::map<std::string , Player*> others;
  std::vector<Projectile> projectiles;
  std::vector<sf::RectangleShape> objects;

  std::stringstream ss;

  GameState state;
};