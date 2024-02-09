#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <string>

#include "settings.h"
#include "game/player.h"

class Client {
public:
  Client(Player *&);

  void receiveData(std::map<std::string, Player> &);
  void sendData();
  void disconnect();

private:
  sf::IpAddress serverIp;
  unsigned short serverPort;

  sf::IpAddress address;
  unsigned short port;
  sf::UdpSocket socket;

  Player * player;
};