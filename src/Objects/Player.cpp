#include "Player.h"

Player::Player(const std::string &id) : playerId_(id) {}

void Player::set_playerName(const std::string &name) { playerName_ = name; }
void Player::set_playerProj(const std::string &proj) { playerProj_ = proj; }
void Player::set_playerPos(const std::string &pos) { playerPos_ = pos; }

std::string Player::get_playerId() { return playerId_; }
std::string Player::get_playerName() { return playerName_; }
std::string Player::get_playerProj() { return playerProj_; }
std::string Player::get_playerPos() {
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