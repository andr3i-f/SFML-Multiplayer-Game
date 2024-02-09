#include "server.h"

Server::Server() {
  serverSocket.setBlocking(false);
  serverIp = sf::IpAddress::getLocalAddress();

  std::cout << "--------------------------------\n";
  std::cout << serverIp << '\n';
  std::cout << "--------------------------------\n";

  std::cout << "Enter a port for server to bind to: ";
  std::cin >> serverPort;

  if (serverSocket.bind(serverPort) != sf::Socket::Done) {
    std::cout << "Error - server not able to bind to port." << std::endl;
  }
}

void Server::run() {
  while (true) {
    receiveData();
  }
}

void Server::receiveData() {
  sf::Packet packet;
  sf::IpAddress senderIp;
  int header;

  packet.clear();

  if (serverSocket.receive(packet, senderIp, serverPort) == sf::Socket::Done) {
    packet >> header;

    switch (Settings::PacketTypes(header)) {
      case Settings::NEW_CONNECTION: {
        float x, y;
        unsigned short senderPort;
        packet >> senderPort >> x >> y;

        Connection c;
        c.address = senderIp;
        c.port = senderPort;
        c.x = x;
        c.y = y;

        connections[c.address.toString() + std::to_string(senderPort)] = c;

        std::cout << "Made new connection with: " << senderIp << '-' << c.port << '\n';
        std::cout << "Total connections: " << connections.size() << '\n';
        break;
      }
      case Settings::POSITION_CHANGE: {
        float x, y;
        unsigned short senderPort;

        packet >> senderPort >> x >> y;
        std::cout << senderPort << " | " << x << '-' << y << '\n';
        std::string sender(std::string(senderIp.toString() + std::to_string(senderPort)));

        connections[sender].x = x;
        connections[sender].y = y;

        sf::Packet toSendPacket;
        toSendPacket << Settings::POSITION_CHANGE << sender << x << y;

        sendData(sender, toSendPacket);
        break;
      }
      case Settings::DISCONNECT: {
        break;
      }
      default:
        break;
    }
  }
  packet.clear();

}

void Server::sendData(std::string & sender, sf::Packet & p) {
  for (const auto & [key, val] : connections) {
    if (key != sender) {
      if (serverSocket.send(p, val.address, val.port) == sf::Socket::Done) {

      }
    }
  }
}