#include "Fantasy.h"

Fantasy::Fantasy(League &league) : league_(&league) {}

void Fantasy::retrieve_leagueInfo()
{
  auto leagueResponse = make_request(construct_url(league_->get_leagueId()));
  try {
    if (leagueResponse.status_code == 200) {
      auto json = nlohmann::json::parse(leagueResponse.text);

      parse_seasonId(json);
      parse_scoringPeriodId(json);
      parse_leagueName(json);
      parse_leagueMembers(json);
    }
  }
  catch (const nlohmann::json::exception &e) {
    e.~exception();
    logError("Error: Ran into error while parsing during Fantasy init.");
  }
  catch (const std::exception &e) {
    logError("Error: Ran into unknown error during Fantasy init.");
  }
}

void Fantasy::retrieve_roster()
{
  auto rosterResponse = make_request(construct_url(league_->get_leagueId(), "?view=mRoster"));
  try {
    if (rosterResponse.status_code == 200) {
      auto rosterJson = nlohmann::json::parse(rosterResponse.text);

      parse_teams(rosterJson);
    }
  }
  catch (const nlohmann::json::exception &e) {
    e.~exception();
    logError("Error: Ran into error while parsing during Fantasy init.");
  }
  catch (const std::exception &e) {
    logError("Error: Ran into unknown error during Fantasy init.");
  }
}

void Fantasy::retrieve_matchup()
{
  auto matchupResponse = make_request(construct_url(league_->get_leagueId(), "?view=mMatchup"));
  try {
    if (matchupResponse.status_code == 200) {
      auto matchupJson = nlohmann::json::parse(matchupResponse.text);

      parse_matchups(matchupJson);
    }
  }
  catch (const nlohmann::json::exception &e) {
    e.~exception();
    logError("Error: Ran into error while parsing during Fantasy init.");
  }
  catch (const std::exception &e) {
    logError("Error: Ran into unknown error during Fantasy init.");
  }
}

void Fantasy::parse_seasonId(const nlohmann::json &json)
{
  auto seasonId = parseStringOrIntField(json, "seasonId");
  if (seasonId != "NULL") {
    league_->set_seasonId(seasonId);
  }
}
void Fantasy::parse_scoringPeriodId(const nlohmann::json &json)
{
  auto scoringPeriodId = parseStringOrIntField(json, "scoringPeriodId");
  if (scoringPeriodId != "NULL") {
    league_->set_scoringPeriodId(scoringPeriodId);
  }
}
void Fantasy::parse_leagueName(const nlohmann::json &json)
{
  auto leagueName = parseNestedField(json, "settings", "name");
  if (leagueName != "NULL") {
    league_->set_leagueName(leagueName);
  }
}
void Fantasy::parse_leagueMembers(const nlohmann::json &json)
{
  /* loop through all members in league, parse and set team id and abbreviation.
   * creates Member object for each team */
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
    }
    else {
      logError("Warning: 'abbrev' key missing in JSON response.");
    }
  }
}
void Fantasy::parse_teams(const nlohmann::json &json)
{
  /* verify teams key exists loop through team rosters, orchastrates parsing */
  if (!json.contains("teams")) {
    logError("Warning: 'teams' key missing in JSON response.");
    return;
  }

  for (const auto &team : json["teams"]) {
    parse_team(team);
  }
}
void Fantasy::parse_team(const nlohmann::json &team)
{
  /* verify member id matches found team id, calls roster-specific parsing */
  std::string teamId = parseStringOrIntField(team, "id");
  for (Member &member : league_->get_leagueMembers()) {
    if (member.get_memberId() == teamId) {
      parse_roster(team["roster"]["entries"], member);
    }
  }
}
void Fantasy::parse_roster(const nlohmann::json &entries, Member &member)
{
  /* iterates through players in roster, calls player-specific parsing */
  for (const auto &player : entries) {
    parse_player(player, member);
  }
}
void Fantasy::parse_player(const nlohmann::json &playerJson, Member &member)
{
  /* parses entry[n], entry[n]["playerPoolEntry"] for player's id, lineup slot
   * id, full name, default position and sets for Player. creates Player object.
   * calls parsing for player stats. adds fully parsed Player to Member roster
   * vector */
  auto &playerInfo = playerJson["playerPoolEntry"];

  Player mPlayer = Player(parseStringOrIntField(playerJson, "playerId"),
                          parseStringOrIntField(playerJson, "lineupSlotId"));
  mPlayer.set_playerName(parseNestedField(playerInfo, "player", "fullName"));
  mPlayer.set_playerPos(parseNestedField(playerInfo, "player", "defaultPositionId"));
  parse_playerStats(playerInfo["player"]["stats"], mPlayer);
  member.add_player(mPlayer);
}
void Fantasy::parse_playerStats(const nlohmann::json &stats, Player &player)
{
  /* parses entry[n]["playerPoolEntry"]["player"]["stats"] for current applied
   * total, and applied average and sets for Player */
  for (const auto &stat : stats) {
    if (parseStringOrIntField(stat, "seasonId") == league_->get_seasonId()) {
      if (parseStringOrIntField(stat, "scoringPeriodId") == league_->get_scoringPeriodId() &&
          parseStringOrIntField(stat, "statSourceId") == "1") {
        player.set_playerProj(parseStringOrIntField(stat, "appliedTotal"));
      }
      if (parseStringOrIntField(stat, "scoringPeriodId") == "0" &&
          parseStringOrIntField(stat, "statSourceId") == "0") {
        player.set_playerAvg(parseStringOrIntField(stat, "appliedAverage"));
      }
    }
  }
}
void Fantasy::parse_matchups(const nlohmann::json &matchupJson)
{
  auto &schedule = matchupJson["schedule"];

  for (const auto &matchup : schedule) {
    if (parseStringOrIntField(matchup, "matchupPeriodId") == league_->get_scoringPeriodId()) {
      for (Member &member : league_->get_leagueMembers()) {
        if (parseNestedField(matchup, "home", "teamId") == member.get_memberId()) {
          member.set_opponentId(parseNestedField(matchup, "away", "teamId"));
        }
        if (parseNestedField(matchup, "away", "teamId") == member.get_memberId()) {
          member.set_opponentId(parseNestedField(matchup, "home", "teamId"));
        }
      }
    }
  }
}