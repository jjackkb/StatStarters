#include "main.h"

int main(void)
{
    ESPNFantasyAPI fantasyApi("2030108269");

    std::cout << fantasyApi.get_league_name() << std::endl;

    for (const auto& member : fantasyApi.get_league_memebers())
    {
        std::cout << member.second + ": " + member.first << std::endl;
    }

    return 0;
}