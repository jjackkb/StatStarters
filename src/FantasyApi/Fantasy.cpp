#include "Fantasy.h"

League *league_;

Fantasy::Fantasy(League &league) : league_(&league) {
  auto r = make_request(construct_url(league_->get_leagueId()));
  auto p =
      make_request(construct_url(league_->get_leagueId(), "?view=mRoster"));

  try {
    if (r.status_code == 200) {
      auto json = nlohmann::json::parse(r.text);
      auto playerJson = nlohmann::json::parse(p.text);

      parse_seasonId(json);
      parse_scoringPeriodId(json);
      parse_leagueName(json);
      parse_leagueMembers(json);
      parse_players(playerJson);

    } else {
      logError("Failed to fetch league data. Status code: " +
               std::to_string(r.status_code));
    }
  } catch (const nlohmann::json::exception &e) {
    e.~exception();
    logError("Error: Ran into error while parsing during Fantasy init.");
  } catch (const std::exception &e) {
    logError("Error: Ran into unknown error during Fantasy init.");
  }
}

void Fantasy::parse_seasonId(const nlohmann::json &json) {
  auto seasonId = parseStringOrIntField(json, "seasonId");
  if (seasonId != "NULL") {
    league_->set_seasonId(seasonId);
  }
}
void Fantasy::parse_scoringPeriodId(const nlohmann::json &json) {
  auto scoringPeriodId = parseStringOrIntField(json, "scoringPeriodId");
  if (scoringPeriodId != "NULL") {
    league_->set_scoringPeriodId(scoringPeriodId);
  }
}
void Fantasy::parse_leagueName(const nlohmann::json &json) {
  auto leagueName = parseNestedField(json, "settings", "name");
  if (leagueName != "NULL") {
    league_->set_leagueName(leagueName);
  }
}
void Fantasy::parse_leagueMembers(const nlohmann::json &json) {
  if (!json.contains("teams")) {
    logError("Warning: 'teams' key missing in JSON response.");
    return;
  }

  for (const auto &team : json["teams"]) {
    std::string id_str;
    auto teamId = parseStringOrIntField(team, "id");
    if (teamId != "NULL") {
      id_str = teamId;
    }

    if (team.contains("abbrev") && team["abbrev"].is_string()) {
      std::string abbrev = team["abbrev"].get<std::string>();
      league_->add_leagueMember(Member(id_str, abbrev));
    } else {
      logError("Warning: 'abbrev' key missing in JSON response.");
    }
  }
}
void Fantasy::parse_players(const nlohmann::json &json) {
  if (!json.contains("teams")) {
    logError("Warning: 'teams' key missing in JSON response.");
    return;
  }

  for (const auto &team : json["teams"]) {
    std::string teamId = parseStringOrIntField(team, "id");
    for (Member &member : league_->get_leagueMembers()) {
      if (member.get_memberId() == teamId) {
        for (const auto &player : team["roster"]["entries"]) {
          auto &playerInfo = player["playerPoolEntry"];
          auto playerId = parseStringOrIntField(player, "playerId");

          Player mPlayer = Player(playerId);
          mPlayer.set_playerName(
              parseNestedField(playerInfo, "player", "fullName"));
          member.add_player(mPlayer);
        }
      }
    }
  }
}