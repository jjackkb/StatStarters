#include "player.h"

std::string playerName_;
std::string playerId_;

Player::Player(const std::string &id) : playerId_(id) {}

void Player::set_playerName(const std::string &name) { playerName_ = name; }

std::string Player::get_playerId() { return playerId_; }
std::string Player::get_playerName() { return playerName_; }