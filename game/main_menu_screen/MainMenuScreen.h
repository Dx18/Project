#pragma once

#include "config/GameConfig.h"
#include "game/IScreen.h"
#include "widget/WidgetSystem.h"
#include "widget/TextWidget.h"
#include "widget/SelectionListWidget.h"
#include "widget/GridContainerWidget.h"

#include "game/headquarters_screen/HeadquartersScreen.h"

namespace game::main_menu_screen {

/** Main menu screen. */
template<typename RenderContext>
class MainMenuScreen : public game::IScreen<RenderContext> {
 private:
  using Action = typename game::IScreen<RenderContext>::Action;
  using PushScreenAction = typename game::IScreen<RenderContext>::PushScreenAction;
  using PopScreenAction = typename game::IScreen<RenderContext>::PopScreenAction;
  using QuitAction = typename game::IScreen<RenderContext>::QuitAction;

  using Widget = widget::Widget<RenderContext>;
  using GridContainerWidget = widget::GridContainerWidget<RenderContext>;
  using TextWidget = widget::TextWidget<RenderContext>;
  using SelectionListWidget = widget::SelectionListWidget<RenderContext>;

  using WidgetPtr = std::shared_ptr<Widget>;
  using GridContainerWidgetPtr = std::shared_ptr<GridContainerWidget>;
  using TextWidgetPtr = std::shared_ptr<TextWidget>;
  using SelectionListWidgetPtr = std::shared_ptr<SelectionListWidget>;

  using WidgetSystem = widget::WidgetSystem<RenderContext>;

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

template<typename RenderContext>
MainMenuScreen<RenderContext>::MainMenuScreen(const config::GameConfig &game_config)
    : game_config_(game_config), widget_system_(), menu_() {
  InitUI();
}

template<typename RenderContext>
std::optional<typename game::IScreen<RenderContext>::Action>
MainMenuScreen<RenderContext>::Update(std::chrono::microseconds delta) {
  return {};
}

template<typename RenderContext>
widget::Widget<RenderContext> &MainMenuScreen<RenderContext>::Render(std::chrono::microseconds delta) {
  return widget_system_.Root();
}

template<typename RenderContext>
std::optional<typename game::IScreen<RenderContext>::Action>
MainMenuScreen<RenderContext>::OnInput(const frontend::InputEvent &event) {
  if (widget_system_.HandleInput(event.input)) {
    return {};
  }

  if (event.input.IsKey() && event.input.GetKey() == frontend::Key::kEnter) {
    size_t selected = menu_->SelectedItem();
    if (selected == kNewGameButtonIndex) {
      return PushScreenAction{std::make_unique<headquarters_screen::HeadquartersScreen<RenderContext>>(game_config_)};
    } else if (selected == kLoadGameButtonIndex) {

    } else if (selected == kQuitButtonIndex) {
      return QuitAction{};
    }
  }

  return {};
}

template<typename RenderContext>
void MainMenuScreen<RenderContext>::InitUI() {
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
