#include "Player.h"

Player::Player(const std::string &id) : playerId_(id) {}
Player::Player(const std::string &id, const std::string &lineupPos)
    : playerId_(id), playerLineupPos_(lineupPos) {}

void Player::set_playerName(const std::string &name) { playerName_ = name; }
void Player::set_playerPos(const std::string &pos) { playerPos_ = pos; }
void Player::set_playerLineupPos(const std::string &lineupPos) {
  playerLineupPos_ = lineupPos;
}
void Player::set_playerProj(const std::string &proj) { playerProj_ = proj; }
void Player::set_playerAvg(const std::string &avg) { playerAvg_ = avg; }

std::string Player::get_playerId() const { return playerId_; }
std::string Player::get_playerName() const { return playerName_; }
std::string Player::get_playerPos() const {
  switch (std::stoi(playerPos_)) {
  case 1:
    return "QB";
  case 2:
    return "RB";
  case 3:
    return "WR";
  case 4:
    return "TE";
  case 5:
    return "K";
  case 16:
    return "D/ST";
  }
  return "";
}
std::string Player::get_playerLineupPos() const { return playerLineupPos_; }
std::string Player::get_playerProj() const { return playerProj_; }
std::string Player::get_playerAvg() const { return playerAvg_; }