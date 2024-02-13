#include "client.h"

Client::Client(Player *& player) {
  this->player = player;

  std::string serverAddress;
  std::cout << "Enter port for you to bind to: ";
  std::cin >> port;

  this->address = sf::IpAddress::getLocalAddress();

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

  p.clear();

  if (socket.receive(p, serverIp, serverPort) != sf::Socket::Done) {

  }

  p >> player->playerNumber >> player->canShoot;
  player->setPlayerData();

  socket.setBlocking(false);
  p.clear();
}

void Client::receiveData(std::map<std::string , Player *> & others, std::vector<Projectile> & projectiles) {
  sf::Packet p;
  sf::IpAddress sIp;
  unsigned short sP;

  if (socket.receive(p, sIp, sP) == sf::Socket::Done) {
    int header;
    p >> header;

    switch (Settings::PacketTypes(header)) {
      case Settings::PacketTypes::NEW_CONNECTION: {
        std::string k;
        int num;
        p >> k >> num;
        others[k] = new Player{num};

        break;
      }
      case Settings::PacketTypes::ROTATION_CHANGE: {
        std::string k;
        float otherRotation;

        p >> k >> otherRotation;
        if (others.contains(k)) {
          others[k]->barrel.setRotation(otherRotation);
        }

        break;
      }
      case Settings::PacketTypes::PLAYER_SHOOT: {
        std::string k;
        p >> k >> player->canShoot;
        if (player->canShoot) {
          std::cout << "YOU CAN SHOOT NOW\n";
        }
        break;
      }
      case Settings::PacketTypes::PROJECTILE_RENDER: {
        std::string k;
        float x, y, angleInRad, initialVelocity;

        p >> k >> x >> y >> angleInRad >> initialVelocity;

        projectiles.push_back(Projectile{ x, y, angleInRad, initialVelocity });
        break;
      }
      case Settings::PacketTypes::DISCONNECT: {
        std::string k;
        p >> k;
        std::cout << "Player: " << k << " disconnected.\n";

        std::cout << "Printing playes before removing: \n";
        for (const auto & [key, val] : others) {
          std::cout << key << '\n';
        }

        others.erase(k);
        std::cout << "Printing players after removing: \n";
        for (const auto & [key, val] : others) {
          std::cout << key << '\n';
        }

        //std::cout << others.size() << '\n';
        break;
      }
      default:
        break;
    }
  }

  p.clear();

  if (!player->canShoot && player->playerHasShot) {
    shoot(player->endOfCannonX, player->endOfCannonY, player->angleInRad, player->power);
  }
}

void Client::shoot(float & x, float & y, float & angleInRad, float & initalVelocity) {
  player->playerHasShot = false;
  sf::Packet p;
  std::string sender{address.toString() + std::to_string(port)};
  std::cout << sender << '\n';
  p << Settings::PacketTypes::PLAYER_SHOOT << sender << x << y << angleInRad << initalVelocity;

  if (socket.send(p, serverIp, serverPort) == sf::Socket::Done) {

  }
}

void Client::sendData() {
  std::string msg;
  sf::Packet p;
  p << Settings::PacketTypes::ROTATION_CHANGE << port << player->barrel.getRotation();

  if (socket.send(p, serverIp, serverPort) == sf::Socket::Done) {

  }
}

void Client::disconnect() {
  sf::Packet p;
  p << Settings::PacketTypes::DISCONNECT << port;

  std::cout << port << '\n';

  if (socket.send(p, serverIp, serverPort) == sf::Socket::Done) {

  }
}