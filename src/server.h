#pragma once

#include <SFML/Network.hpp>
#include <unordered_map>
#include <iostream>
#include <string>

#include "settings.h"

struct Connection {
  sf::IpAddress address;
  unsigned short port;

  // player positions
  float rotation;
  float x;
  float y;
  int playerNumber;
  bool canShoot;
};

class Server {
public:
  Server();

  void run();

  void receiveData();
  void sendData(std::string &, sf::Packet &);
  void sendInitialData(Connection &);

private:
  sf::IpAddress serverIp;
  unsigned short serverPort;
  sf::UdpSocket serverSocket;

  std::unordered_map<std::string, Connection> connections;
};