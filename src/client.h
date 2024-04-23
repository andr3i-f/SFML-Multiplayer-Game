#pragma once

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "settings.h"
#include "game/world.h"
#include "game/player.h"

class Client {
public:
  Client(Player *&, World *&);

  void receiveData();
  void sendData();
  void disconnect();
  void shoot(float &, float &, float &, float &);

  void run();

  void attemptJoin();

private:
  sf::IpAddress serverIp;
  unsigned short serverPort;

  sf::IpAddress address;
  unsigned short port;
  sf::UdpSocket socket;

  Player * player;
  World * world;

  bool connected{false};
};