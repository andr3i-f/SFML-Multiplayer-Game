#include "client.h"

Client::Client(Player *& player) {
  this->player = player;
  socket.setBlocking(false);

  std::string serverAddress;
  std::cout << "Enter port for you to bind to: ";
  std::cin >> port;

  std::cout << "\n-------------------------------------\n";

  std::cout << "Enter server port: ";
  std::cin >> serverPort;
  std::cout << "Enter server IP Address: ";
  std::cin >> serverAddress;
  serverIp = serverAddress;

  if (socket.bind(port) != sf::Socket::Done) {
    std::cout << "Client unable to port to: " << port << std::endl;
  }

  sf::Packet p;
  p << Settings::PacketTypes::NEW_CONNECTION << port;

  if (socket.send(p, serverIp, serverPort) != sf::Socket::Done) {
    std::cout << "Client unable to send initial connection to server." << std::endl;
  }
  p.clear();  void update();
}

void Client::receiveData(std::map<std::string , Player> & others) {
  sf::Packet p;
  sf::IpAddress sIp;
  unsigned short sP;

  if (socket.receive(p, sIp, sP) == sf::Socket::Done) {
    int header;
    p >> header;

    switch (Settings::PacketTypes(header)) {
      case Settings::PacketTypes::NEW_CONNECTION: {
        std::string k;
        float x, y;

        p >> k >> x >> y;
        others[k] = Player{x, y};

        break;
      }
      case Settings::PacketTypes::POSITION_CHANGE: {
        std::string k;
        float x, y;

        p >> k >> x >> y;
        others[k].player.setPosition(x, y);
        std::cout << "Recieved player position: " << x << y << '\n';

        break;
      }
      default:
        break;
    }
  }

  p.clear();
}

void Client::sendData() {
  std::string msg;
  sf::Packet p;
  p << Settings::PacketTypes::POSITION_CHANGE << port << player->player.getPosition().x << player->player.getPosition().y;

  if (socket.send(p, serverIp, serverPort) == sf::Socket::Done) {

  }
}