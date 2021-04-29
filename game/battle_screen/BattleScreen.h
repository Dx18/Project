#pragma once

#include "world/World.h"
#include "game/IScreen.h"
#include "widget/game/WorldViewWidget.h"

namespace game::battle_screen {

template<typename Context>
class BattleScreen : public IScreen<Context> {
 private:
  using Action = typename game::IScreen<Context>::Action;
  using PushScreenAction = typename game::IScreen<Context>::PushScreenAction;
  using PopScreenAction = typename game::IScreen<Context>::PopScreenAction;
  using QuitAction = typename game::IScreen<Context>::QuitAction;

  using Widget = widget::Widget<Context>;
  using GridContainerWidget = widget::GridContainerWidget<Context>;
  using WorldViewWidget = widget::game::WorldViewWidget<Context>;

  using WidgetPtr = std::shared_ptr<Widget>;
  using GridContainerWidgetPtr = std::shared_ptr<GridContainerWidget>;
  using WorldViewWidgetPtr = std::shared_ptr<WorldViewWidget>;

  using WidgetSystem = widget::WidgetSystem<Context>;

 public:
  explicit BattleScreen(std::shared_ptr<world::World> world);

  std::optional<Action> Update(std::chrono::microseconds delta) override;
  Widget &Render(std::chrono::microseconds delta) override;
  std::optional<Action> OnInput(const frontend::InputEvent &event) override;

 private:
  std::shared_ptr<world::World> world_;

  WorldViewWidgetPtr world_view_;
  WidgetSystem widget_system_;

  void InitUI();

};

template<typename Context>
BattleScreen<Context>::BattleScreen(std::shared_ptr<world::World> world)
    : world_(std::move(world)), widget_system_() {
  InitUI();
}

template<typename Context>
std::optional<typename IScreen<Context>::Action> BattleScreen<Context>::Update(std::chrono::microseconds delta) {
  return {};
}

template<typename Context>
widget::Widget<Context> &BattleScreen<Context>::Render(std::chrono::microseconds delta) {
  return widget_system_.Root();
}

template<typename Context>
void BattleScreen<Context>::InitUI() {
  GridContainerWidgetPtr main_container = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{1, 1});

  util::Vector2<size_t> map_size = world_->Map().Size();

  world_view_ = std::make_shared<WorldViewWidget>(
      world_,
      util::Vector2<double>{static_cast<double>(map_size.x) / 2.0, static_cast<double>(map_size.y) / 2.0},
      0.5
  );
  world_view_->SetPreferExpand(util::Vector2<bool>{true, true});
  main_container->Set(util::Vector2<size_t>{0, 0}, world_view_);

  widget_system_.SetRoot(main_container);
  widget_system_.SetFocused(world_view_);
}

template<typename Context>
std::optional<typename IScreen<Context>::Action> BattleScreen<Context>::OnInput(const frontend::InputEvent &event) {
  if (widget_system_.HandleInput(event.input)) {
    return {};
  }

  return {};
}

}
