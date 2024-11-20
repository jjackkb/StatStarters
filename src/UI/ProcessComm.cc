#include "ProcessComm.h"

League *cur_league = nullptr;

std::vector<std::string> split_command(const std::string &input_command)
{
  std::istringstream stream(input_command);
  std::vector<std::string> result;
  std::string word;

  while (stream >> word) {
    result.push_back(word);
  }

  return result;
}

void process_command(std::string input_command)
{
  std::vector<std::string> commands = split_command(input_command);

  clearInput();

  if (commands.size() > 0) {
    if (commands[0] == "test") {
      display_output("test");
    }
    else {
      display_err("Command '" + commands[0] + "' not found!");
    }
  }
  else {
    display_err("No command entered!");
  }
}