#ifndef API_H
#define API_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>

#include "ErrorHandler.h"
#include "League.h"

#define BASEURL                                                                \
  "https://lm-api-reads.fantasy.espn.com/apis/v3/games/ffl/seasons/2024/"      \
  "segments/0/leagues/"
#define ESPN_S2                                                                \
  "AEAuQPHDCe1hmHENca5DlLwqkOfMmg9QwnkubRLTvzHPN31qzhBnrDfBxLWC32TQaUiqKCdEts" \
  "iUFlPdQNnlf%2BVKj%2FViaJwqU2XaK6PVtwFwtU1LwE0XOpZfn3u%"                     \
  "2FuKCg8guDZUmhlvtPGGu0RNMbhy1Qr9GFBGUMNPk%"                                 \
  "2BcipleF9uyCc6kRVQ1vNrtBZsmTsG27CFpJTmPZI%"                                 \
  "2BWpTkOsDhjDrKv6kHrTEOu8Hj0Xn9XUi1uL9Ctt9l60Uhlqqx9hx2WUidSZKgeC1NZHMi0z"   \
  "2J"                                                                         \
  "d9y22QxB5PTgk%2Ffz28Ob3klAFVvjTHEuvKTEjqlRyY48fk0%3D"
#define SWID "{A64813BD-1E7D-47C5-9E17-A7B7756D49DF}"

std::string url_decode(const std::string &encoded);

cpr::Response make_request(const std::string &);
std::string construct_url(std::string);
std::string construct_url(std::string, std::string);
std::string parseStringOrIntField(const nlohmann::json &json,
                                  const std::string &key);
std::string parseNestedField(const nlohmann::json &json,
                             const std::string &parent,
                             const std::string &child);

#endif // API_H