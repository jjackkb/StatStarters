#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
  Player(const std::string &id);

  void set_playerName(const std::string &name);
  void set_playerProj(const std::string &proj);
  void set_playerPos(const std::string &pos);

  std::string get_playerId();
  std::string get_playerName();
  std::string get_playerProj();
  std::string get_playerPos();

private:
  std::string playerId_;
  std::string playerName_;
  std::string playerPos_;
  std::string playerProj_;
};

#endif // PLAYER_H