#pragma once

#include <SFML/Network.hpp>
#include <map>
#include <iostream>
#include <string>

#include "settings.h"

struct Connection {
  sf::IpAddress address;
  unsigned short port;

  // player positions
  float x;
  float y;
};

class Server {
public:
  Server();

  void run();

  void receiveData();
  void sendData(std::string &, sf::Packet &);

private:
  sf::IpAddress serverIp;
  unsigned short serverPort;
  sf::UdpSocket serverSocket;

  std::unordered_map<std::string, Connection> connections;
};