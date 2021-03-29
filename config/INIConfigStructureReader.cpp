#include "INIConfigStructureReader.h"

namespace config {

ConfigStructure INIConfigStructureReader::Read(std::istream &input) {
  static const auto not_white_space = [](const char &ch) {
    return !std::isspace(ch);
  };

  ConfigStructure current_config;
  std::string current_section;

  size_t line_number = 0;
  std::string line;
  while (std::getline(input, line)) {
    ++line_number;

    auto line_end = std::find_if(line.rbegin(), line.rend(), not_white_space).base();
    if (line_end == line.begin()) {
      // Line is whitespace
      continue;
    }

    auto line_begin = std::find_if(line.begin(), line.end(), not_white_space);

    if (*line_begin == ';' || *line_begin == '#') {
      continue;
    }

    if (*line_begin == '[') {
      if (*(line_end - 1) != ']') {
        std::stringstream message;
        message << "line #" << line_number << ": opening bracket was not closed at the end of the line";
        throw std::runtime_error(message.str());
      }

      current_section = std::string(line_begin + 1, line_end - 1);
      continue;
    }

    auto separator_iter = std::find(line_begin, line_end, '=');
    if (separator_iter == line_end) {
      std::stringstream message;
      message << "line #" << line_number << ": bad formed statement";
      throw std::runtime_error(message.str());
    }

    std::string key(line_begin, separator_iter);
    std::string value(separator_iter + 1, line_end);

    current_config.sections[current_section].values.insert({key, value});
  }

  return current_config;
}

}
