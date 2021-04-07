#include "CursesTerminalFrontend.h"

namespace frontend::terminal {

CursesTerminalFrontend::CursesTerminalFrontend() {
  initscr();

  CreateKeyMap();
  CreateColorMap();

  start_color();
  for (Color foreground : kColors) {
    for (Color background : kColors) {
      size_t index = ColorPairIndex(ColorPair(foreground, background));
      init_pair(index, color_map_[foreground], color_map_[background]);
    }
  }

  noecho();
  raw();
  set_escdelay(1);
  keypad(stdscr, true);
  nodelay(stdscr, true);
}

CursesTerminalFrontend::~CursesTerminalFrontend() noexcept {
  endwin();
}

util::Vector2<size_t> CursesTerminalFrontend::Size() const {
  size_t height, width;
  getmaxyx(stdscr, height, width);
  return {width, height};
}

void CursesTerminalFrontend::SetCursorState(bool enabled) {
  curs_set(enabled ? 1 : 0);
}

void CursesTerminalFrontend::SetCursorPosition(const util::Vector2<size_t> &position) {
  move(position.y, position.x);
}

void CursesTerminalFrontend::BeginRender() {
  flushinp();
}

void CursesTerminalFrontend::Render(const IRenderSurfaceRead &surface, const util::Vector2<ssize_t> &position) {
  util::Vector2<size_t> size = Size();
  if (size.y == 0 || size.x == 0) {
    return;
  }

  util::Vector2<size_t> surface_size = surface.Size();

  auto row_bound_lower = static_cast<ssize_t>(0);
  auto row_bound_upper = static_cast<ssize_t>(size.y - 1);
  auto column_bound_lower = static_cast<ssize_t>(0);
  auto column_bound_upper = static_cast<ssize_t>(size.x - 1);

  auto row_begin = static_cast<size_t>(util::math::clamp(position.y, row_bound_lower, row_bound_upper));
  auto row_end = static_cast<size_t>(util::math::clamp(position.y + static_cast<ssize_t>(surface_size.y) - 1,
                                                       row_bound_lower, row_bound_upper));

  auto column_begin = static_cast<size_t>(util::math::clamp(position.x, row_bound_lower, row_bound_upper));
  auto column_end = static_cast<size_t>(util::math::clamp(position.x + static_cast<ssize_t>(surface_size.x) - 1,
                                                          column_bound_lower, column_bound_upper));

  for (size_t row = row_begin; row <= row_end; ++row) {
    for (size_t column = column_begin; column <= column_end; ++column) {
      const CharData &data = surface.Get({column, row});
      size_t color_index = ColorPairIndex(data.color);

      attron(COLOR_PAIR(color_index));
      mvaddch(static_cast<int>(row - row_begin), static_cast<int>(column - column_begin), data.ch);
      attroff(COLOR_PAIR(color_index));
    }
  }
}

void CursesTerminalFrontend::EndRender() {
  refresh();
}

std::optional<Input> CursesTerminalFrontend::PollInput() {
  int ch = getch();

  if (ch == ERR) {
    return {};
  }

  auto key_iter = key_map_.find(ch);
  if (key_iter != key_map_.end()) {
    return Input(key_iter->second);
  }

  if (ch < 0b100) {
    return Input(static_cast<char>(ch));
  }

  return {};
}

void CursesTerminalFrontend::CreateKeyMap() {
  static const int ASCII_DEL = 127;
  static const int ASCII_ESC = 27;
  static const int ASCII_HT = '\t';
  static const int ASCII_LF = '\n';

  key_map_[KEY_DOWN] = Key::kDown;
  key_map_[KEY_UP] = Key::kUp;
  key_map_[KEY_LEFT] = Key::kLeft;
  key_map_[KEY_RIGHT] = Key::kRight;
  key_map_[KEY_HOME] = Key::kHome;
  key_map_[KEY_END] = Key::kEnd;
  key_map_[KEY_PPAGE] = Key::kPageUp;
  key_map_[KEY_NPAGE] = Key::kPageDown;
  key_map_[KEY_BACKSPACE] = Key::kBackspace;
  key_map_[ASCII_DEL] = Key::kBackspace;
  key_map_[KEY_DC] = Key::kDelete;
  key_map_[KEY_STAB] = Key::kTab;
  key_map_[ASCII_HT] = Key::kTab;
  key_map_[KEY_BTAB] = Key::kBackTab;
  key_map_[KEY_ENTER] = Key::kEnter;
  key_map_[ASCII_LF] = Key::kEnter;
  key_map_[ASCII_ESC] = Key::kEscape;
  key_map_[KEY_F(1)] = Key::kF1;
  key_map_[KEY_F(2)] = Key::kF2;
  key_map_[KEY_F(3)] = Key::kF3;
  key_map_[KEY_F(4)] = Key::kF4;
  key_map_[KEY_F(5)] = Key::kF5;
  key_map_[KEY_F(6)] = Key::kF6;
  key_map_[KEY_F(7)] = Key::kF7;
  key_map_[KEY_F(8)] = Key::kF8;
  key_map_[KEY_F(9)] = Key::kF9;
  key_map_[KEY_F(10)] = Key::kF10;
  key_map_[KEY_F(11)] = Key::kF11;
  key_map_[KEY_F(12)] = Key::kF12;
}

void CursesTerminalFrontend::CreateColorMap() {
  color_map_[Color::kBlack] = COLOR_BLACK;
  color_map_[Color::kRed] = COLOR_RED;
  color_map_[Color::kGreen] = COLOR_GREEN;
  color_map_[Color::kYellow] = COLOR_YELLOW;
  color_map_[Color::kBlue] = COLOR_BLUE;
  color_map_[Color::kMagenta] = COLOR_MAGENTA;
  color_map_[Color::kCyan] = COLOR_CYAN;
  color_map_[Color::kWhite] = COLOR_WHITE;
}

size_t CursesTerminalFrontend::ColorPairIndex(ColorPair color_pair) {
  return static_cast<size_t>(color_pair.foreground) * kColors.size() + static_cast<size_t>(color_pair.background) + 1;
}

}
