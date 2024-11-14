#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
  Player(const std::string &id);

  void set_playerName(const std::string &name);

  std::string get_playerId();
  std::string get_playerName();

private:
  std::string playerId_;
  std::string playerName_;
};

#endif // PLAYER_H