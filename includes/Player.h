#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
 public:
  Player(const std::string &);
  Player(const std::string &, const std::string &);

  void set_playerName(const std::string &);
  void set_playerPos(const std::string &);
  void set_playerLineupPos(const std::string &);
  void set_playerProj(const std::string &);
  void set_playerAvg(const std::string &);

  std::string get_playerId() const;
  std::string get_playerName() const;
  std::string get_playerPos() const;
  std::string get_playerLineupPos() const;
  std::string get_playerProj() const;
  std::string get_playerAvg() const;

 private:
  std::string playerId_;
  std::string playerName_;
  std::string playerPos_;
  std::string playerLineupPos_;
  std::string playerProj_;
  std::string playerAvg_;
};

#endif  // PLAYER_H