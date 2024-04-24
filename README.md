# 2D Tank Shooter Game
A 2 player multiplayer game that utilizes the SFML graphics and network libraries.

Two clients are able to connect to a server through UDP sockets. The clients and server communicate via packets, where the packets resemble client status connection, projectile information, and the tank barrel rotation. 

The main menu client UI is made using the SFML graphics library, where the client is able to input their desired port, the server IP and server port. If the information was inputted correctly, they will be able to join the game.

The game ends with one of the players being hit by a projectile or exiting the game.

Inspired by Tank Wars.

# Images

# [Demo Video](https://youtu.be/AL8oMHDAfvk)

# Credits
Tank images by: www.kenney.nl
