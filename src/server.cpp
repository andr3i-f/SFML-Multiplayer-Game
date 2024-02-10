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
      case Settings::PacketTypes::NEW_CONNECTION: {

        if (connections.size() == 2) {
          std::cout << "Player tried connecting - game lobby is full.\n";
        } else {
          if (connections.empty()) {
            std::cout << "Player 1 Connecting\n";

            int playerOneNumber{ 1 };
            float playerOnePositionX{ 100 };
            float playerOnePositionY{ 790 };
            float playerOneInitialAngle{ 315 };
            float playerOneLowerBoundAngle{ 270 };
            float playerOneUpperBoundAngle{ 358 };
            unsigned short senderPort;

            packet >> senderPort;

            Connection c;
            c.address = senderIp;
            c.port = senderPort;

            connections[senderIp.toString() + std::to_string(senderPort)] = c;

            packet.clear();

            packet << playerOneNumber << playerOnePositionX <<
              playerOnePositionY << playerOneInitialAngle <<
              playerOneLowerBoundAngle << playerOneUpperBoundAngle;

            if (serverSocket.send(packet, senderIp, senderPort) == sf::Socket::Done) {
              std::cout << "Sent player 1 initial data.\n";
            }

            std::cout << "Made new connection with: " << senderIp << c.port << '\n';
            std::cout << "Total connections: " << connections.size() << '\n';

          } else {
            std::cout << "Player 2 Connecting\n";

            int playerTwoNumber{ 2 };
            float playerTwoPositionX{ 1100 };
            float playerTwoPositionY{ 790 };
            float playerTwoInitialAngle{ 225 };
            float playerTwoLowerBoundAngle{ 178 };
            float playerTwoUpperBoundAngle{ 270 };
            unsigned short senderPort;

            packet >> senderPort;

            Connection c;
            c.address = senderIp;
            c.port = senderPort;

            connections[senderIp.toString() + std::to_string(senderPort)] = c;

            packet.clear();

            packet << playerTwoNumber << playerTwoPositionX <<
              playerTwoPositionY << playerTwoInitialAngle <<
              playerTwoLowerBoundAngle << playerTwoUpperBoundAngle;

            if (serverSocket.send(packet, senderIp, senderPort) == sf::Socket::Done) {
              std::cout << "Sent player 2 initial data.\n";
            }

            std::cout << "Made new connection with: " << senderIp << c.port << '\n';
            std::cout << "Total connections: " << connections.size() << '\n';
          }
        }


        break;
      }
      case Settings::PacketTypes::POSITION_CHANGE: {
        float x, y;
        unsigned short senderPort;

        packet >> senderPort >> x >> y;

        std::string sender(senderIp.toString() + std::to_string(senderPort));
        if (connections.contains(sender)) {
          connections[sender].x = x;
          connections[sender].y = y;

          sf::Packet toSendPacket;
          toSendPacket << Settings::PacketTypes::POSITION_CHANGE << sender << x << y;

          sendData(sender, toSendPacket);
        }

        break;
      }
      case Settings::PacketTypes::DISCONNECT: {
        std::cout << "Player disconnected\n";
        unsigned short senderPort;

        packet >> senderPort;

        std::string sender(std::string(senderIp.toString() + std::to_string(senderPort)));
        sf::Packet toSendPacket;
        toSendPacket << Settings::DISCONNECT << sender;

        sendData(sender, toSendPacket);

        connections.erase(sender);
        std::cout << "Total connections: " << connections.size() << '\n';

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

void Server::sendInitialData(Connection & c) {
  sf::Packet p;

  for (const auto & [key, val] : connections) {
    std::string otherConnection{val.address.toString() + std::to_string(val.port)};
    p << Settings::PacketTypes::NEW_CONNECTION << otherConnection << val.x << val.y;
    if (serverSocket.send(p, c.address, c.port) == sf::Socket::Done) {

    }
    p.clear();
  }
}