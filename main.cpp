#include <fstream>

#include "config/Config.h"
#include "config/INIConfigStructureReader.h"

#include "frontend/terminal/CursesTerminalFrontend.h"
#include "frontend/terminal/TerminalEvents.h"

#include "widget/terminal/TerminalContext.h"

#include "game/Game.h"
#include "game/main_menu_screen/MainMenuScreen.h"

config::Config ReadConfig(const std::string &path) {
  std::ifstream input(path);
  return config::Config(config::INIConfigStructureReader().Read(input));
}

int main() {
  using namespace game;
  using namespace frontend::terminal;
  using namespace widget::terminal;

  config::Config config = ReadConfig("DefaultConfig.ini");

  CursesTerminalFrontend frontend;
  frontend.SetCursorState(false);

  widget::terminal::TerminalContext context(frontend, frontend, "resources/terminal");

  auto initial_screen = std::make_unique<main_menu_screen::MainMenuScreen<TerminalContext>>(config.game_config);

  Game<TerminalContext> game(context, std::move(initial_screen));
  game.Run();

  return 0;
}
