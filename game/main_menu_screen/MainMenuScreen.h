#pragma once

#include "config/GameConfig.h"
#include "game/IScreen.h"
#include "widget/WidgetSystem.h"
#include "widget/TextWidget.h"
#include "widget/SelectionListWidget.h"
#include "widget/GridContainerWidget.h"

#include "game/headquarters_screen/HeadquartersScreen.h"

namespace game::main_menu_screen {

/**
 * Main menu screen.
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class MainMenuScreen : public game::IScreen<Context> {
 private:
  using Action = typename game::IScreen<Context>::Action;
  using PushScreenAction = typename game::IScreen<Context>::PushScreenAction;
  using PopScreenAction = typename game::IScreen<Context>::PopScreenAction;
  using QuitAction = typename game::IScreen<Context>::QuitAction;

  using Widget = widget::Widget<Context>;
  using GridContainerWidget = widget::GridContainerWidget<Context>;
  using TextWidget = widget::TextWidget<Context>;
  using SelectionListWidget = widget::SelectionListWidget<Context>;

  using WidgetPtr = std::shared_ptr<Widget>;
  using GridContainerWidgetPtr = std::shared_ptr<GridContainerWidget>;
  using TextWidgetPtr = std::shared_ptr<TextWidget>;
  using SelectionListWidgetPtr = std::shared_ptr<SelectionListWidget>;

  using WidgetSystem = widget::WidgetSystem<Context>;

 public:
  /**
   * Creates main menu screen.
   * @param game_config Const reference to game config.
   */
  explicit MainMenuScreen(const config::GameConfig &game_config);

  std::optional<Action> Update(std::chrono::microseconds delta) override;
  Widget &Render(std::chrono::microseconds delta) override;
  std::optional<Action> OnInput(const frontend::InputEvent &event) override;

 private:
  /** Index of "New game" button. */
  static const size_t kNewGameButtonIndex = 0;
  /** Index of "Load game" button. */
  static const size_t kLoadGameButtonIndex = 1;
  /** Index of "Quit" button. */
  static const size_t kQuitButtonIndex = 2;

  /** Const reference to game config. */
  const config::GameConfig &game_config_;
  /** Widget system. */
  WidgetSystem widget_system_;
  /** Menu list. */
  SelectionListWidgetPtr menu_;

  /** Initializes user interface. */
  void InitUI();

};

template<typename Context>
MainMenuScreen<Context>::MainMenuScreen(const config::GameConfig &game_config)
    : game_config_(game_config), widget_system_(), menu_() {
  InitUI();
}

template<typename Context>
std::optional<typename game::IScreen<Context>::Action>
MainMenuScreen<Context>::Update(std::chrono::microseconds delta) {
  return {};
}

template<typename Context>
widget::Widget<Context> &MainMenuScreen<Context>::Render(std::chrono::microseconds delta) {
  return widget_system_.Root();
}

template<typename Context>
std::optional<typename game::IScreen<Context>::Action>
MainMenuScreen<Context>::OnInput(const frontend::InputEvent &event) {
  if (widget_system_.HandleInput(event.input)) {
    return {};
  }

  if (event.input.IsKey() && event.input.GetKey() == frontend::Key::kEnter) {
    size_t selected = menu_->SelectedItem();
    if (selected == kNewGameButtonIndex) {
      return PushScreenAction{std::make_unique<headquarters_screen::HeadquartersScreen<Context>>(game_config_)};
    } else if (selected == kLoadGameButtonIndex) {

    } else if (selected == kQuitButtonIndex) {
      return QuitAction{};
    }
  }

  return {};
}

template<typename Context>
void MainMenuScreen<Context>::InitUI() {
  using namespace widget;

  GridContainerWidgetPtr container = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{1, 2});
  container->SetRenderSeparators(true);

  TextWidgetPtr title = std::make_shared<TextWidget>("Main menu");
  title->SetPreferExpand({true, false});
  container->Set({0, 0}, title);

  menu_ = std::make_shared<SelectionListWidget>(std::vector<std::string>{
      "New game",
      "Load game",
      "Quit"
  });
  menu_->SetPreferExpand({true, true});
  container->Set({0, 1}, menu_);

  widget_system_.SetRoot(container);
  widget_system_.SetFocused(menu_);
}

}
