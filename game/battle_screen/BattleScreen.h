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
  using TextWidget = widget::TextWidget<Context>;
  using WorldViewWidget = widget::game::WorldViewWidget<Context>;

  using WidgetPtr = std::shared_ptr<Widget>;
  using GridContainerWidgetPtr = std::shared_ptr<GridContainerWidget>;
  using TextWidgetPtr = std::shared_ptr<TextWidget>;
  using WorldViewWidgetPtr = std::shared_ptr<WorldViewWidget>;

  using WidgetSystem = widget::WidgetSystem<Context>;

  struct UI {
    WorldViewWidgetPtr world_view;
    TextWidgetPtr info_text;
    WidgetSystem widget_system;
  };

  class IState {
   public:
    virtual ~IState() = 0;

    virtual void Init(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui) = 0;
    virtual std::unique_ptr<IState> Update(const config::GameConfig &game_config, std::shared_ptr<world::World> world,
                                           UI &ui, std::chrono::microseconds delta) = 0;
    virtual std::unique_ptr<IState> OnInput(const config::GameConfig &game_config, std::shared_ptr<world::World> world,
                                            UI &ui, const frontend::InputEvent &event) = 0;

  };

  class PlayerMoveState : public IState {
   public:
    explicit PlayerMoveState(size_t current_unit);

    void Init(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui) override;
    std::unique_ptr<IState> Update(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui,
                                   std::chrono::microseconds delta) override;
    std::unique_ptr<IState> OnInput(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui,
                                    const frontend::InputEvent &event) override;
   private:
    size_t current_unit_;

  };

  class DestinationSelectionState : public IState {
   public:
    DestinationSelectionState(size_t unit_index);

    void Init(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui) override;
    std::unique_ptr<IState> Update(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui,
                                   std::chrono::microseconds delta) override;
    std::unique_ptr<IState> OnInput(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui,
                                    const frontend::InputEvent &event) override;

   private:
    size_t unit_index_;

  };

  class TargetSelectionState : public IState {
   public:
    TargetSelectionState(size_t unit_index);

    void Init(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui) override;
    std::unique_ptr<IState> Update(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui,
                                   std::chrono::microseconds delta) override;
    std::unique_ptr<IState> OnInput(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui,
                                    const frontend::InputEvent &event) override;

   private:
    size_t unit_index_;

  };

  class EnemyMoveState : public IState {
   public:
    void Init(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui) override;
    std::unique_ptr<IState> Update(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui,
                                   std::chrono::microseconds delta) override;
    std::unique_ptr<IState> OnInput(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui,
                                    const frontend::InputEvent &event) override;

  };

  class ScriptWaitState : public IState {
   public:
    explicit ScriptWaitState(std::unique_ptr<IState> next_state);

    void Init(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui) override;
    std::unique_ptr<IState> Update(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui,
                                   std::chrono::microseconds delta) override;
    std::unique_ptr<IState> OnInput(const config::GameConfig &game_config, std::shared_ptr<world::World> world, UI &ui,
                                    const frontend::InputEvent &event) override;

   private:
    std::unique_ptr<IState> next_state_;

  };

 public:
  BattleScreen(const config::GameConfig &game_config, std::shared_ptr<world::World> world);

  std::optional<Action> Update(std::chrono::microseconds delta) override;
  Widget &Render(std::chrono::microseconds delta) override;
  std::optional<Action> OnInput(const frontend::InputEvent &event) override;

 private:
  const config::GameConfig &game_config_;
  std::shared_ptr<world::World> world_;

  UI ui_;

  std::unique_ptr<IState> current_state_;

  void InitUI();

};

template<typename Context>
BattleScreen<Context>::IState::~IState() = default;

template<typename Context>
BattleScreen<Context>::PlayerMoveState::PlayerMoveState(size_t current_unit)
    : current_unit_(current_unit) {

}

template<typename Context>
void BattleScreen<Context>::PlayerMoveState::Init(const config::GameConfig &game_config,
                                                  std::shared_ptr<world::World> world, BattleScreen::UI &ui) {
  ui.info_text->SetText("Your move\n=========\nTAB: Next unit  BACKTAB: Previous unit  m: Move  a: Attack  r: Reload");

  size_t unit_id = world->Entities().PlayerUnitID(current_unit_);
  ui.world_view->SetSelectedUnit(unit_id);
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::PlayerMoveState::Update(const config::GameConfig &game_config,
                                               std::shared_ptr<world::World> world, BattleScreen::UI &ui,
                                               std::chrono::microseconds delta) {
  return nullptr;
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::PlayerMoveState::OnInput(const config::GameConfig &game_config,
                                                std::shared_ptr<world::World> world, BattleScreen::UI &ui,
                                                const frontend::InputEvent &event) {
  if (event.input.IsKey()) {
    if (event.input.GetKey() == frontend::Key::kTab) {
      size_t unit_count = world->Entities().PlayerUnits().size();
      current_unit_ = (current_unit_ + 1) % unit_count;
      size_t unit_id = world->Entities().PlayerUnitID(current_unit_);
      ui.world_view->SetSelectedUnit(unit_id);
    } else if (event.input.GetKey() == frontend::Key::kBackTab) {
      size_t unit_count = world->Entities().PlayerUnits().size();
      current_unit_ = (unit_count + current_unit_ - 1) % unit_count;
      size_t unit_id = world->Entities().PlayerUnitID(current_unit_);
      ui.world_view->SetSelectedUnit(unit_id);
    }
  } else if (event.input.IsChar()) {
    if (event.input.GetChar() == 'm') {
      return std::make_unique<DestinationSelectionState>(current_unit_);
    } else if (event.input.GetChar() == 'a') {
      return std::make_unique<TargetSelectionState>(current_unit_);
    }
  }
  return nullptr;
}

template<typename Context>
BattleScreen<Context>::DestinationSelectionState::DestinationSelectionState(size_t unit_index)
    : unit_index_(unit_index) {

}

template<typename Context>
void BattleScreen<Context>::DestinationSelectionState::Init(const config::GameConfig &game_config,
                                                            std::shared_ptr<world::World> world, BattleScreen::UI &ui) {
  ui.info_text->SetText("Select destination...\n=====================\nENTER: Move  ESCAPE: Back");

  size_t unit_id = world->Entities().PlayerUnitID(unit_index_);
  ui.world_view->SetSelectedUnit(unit_id);

  const unit::Unit &unit = world->Entities().GetUnit(unit_id);
  world::map::WorldMovementMap movement_map = unit.CreateMovementMap(*world, game_config);

  std::vector<world::map::WorldMovementMap::PositionInfo> positions = movement_map.AvailablePositions();
  std::vector<util::Vector2<size_t>> navigation_tiles;
  navigation_tiles.reserve(positions.size());
  for (const auto &position : positions) {
    navigation_tiles.push_back(position.position);
  }
  ui.world_view->SetNavigationTiles(navigation_tiles);
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::DestinationSelectionState::Update(const config::GameConfig &game_config,
                                                         std::shared_ptr<world::World> world, BattleScreen::UI &ui,
                                                         std::chrono::microseconds delta) {
  return nullptr;
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::DestinationSelectionState::OnInput(const config::GameConfig &game_config,
                                                          std::shared_ptr<world::World> world, BattleScreen::UI &ui,
                                                          const frontend::InputEvent &event) {
  if (event.input.IsKey()) {
    if (event.input.GetKey() == frontend::Key::kEscape) {
      ui.world_view->SetNavigationTiles({});
      return std::make_unique<PlayerMoveState>(unit_index_);
    } else if (event.input.GetKey() == frontend::Key::kEnter) {
      size_t unit_id = world->Entities().PlayerUnitID(unit_index_);
      unit::Unit &unit = world->Entities().GetUnit(unit_id);

      util::Vector2<double> camera_position = ui.world_view->CameraPosition();
      util::Vector3<double> position = {
          std::floor(camera_position.x) + 0.5,
          std::floor(camera_position.y) + 0.5,
          0.0
      };

      auto script = unit.CreateMovementScript(unit_id, *world, game_config, position);

      if (script) {
        ui.world_view->SetNavigationTiles({});
        world->AddScript(std::move(script));
        return std::make_unique<ScriptWaitState>(std::make_unique<EnemyMoveState>());
      }
    }
  }
  return nullptr;
}

template<typename Context>
BattleScreen<Context>::TargetSelectionState::TargetSelectionState(size_t unit_index)
    : unit_index_(unit_index) {

}

template<typename Context>
void BattleScreen<Context>::TargetSelectionState::Init(const config::GameConfig &game_config,
                                                       std::shared_ptr<world::World> world, BattleScreen::UI &ui) {
  ui.info_text->SetText("Select target...\n=====================\nENTER: Attack  ESCAPE: Back");
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::TargetSelectionState::Update(const config::GameConfig &game_config,
                                                    std::shared_ptr<world::World> world, BattleScreen::UI &ui,
                                                    std::chrono::microseconds delta) {
  return nullptr;
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::TargetSelectionState::OnInput(const config::GameConfig &game_config,
                                                     std::shared_ptr<world::World> world, BattleScreen::UI &ui,
                                                     const frontend::InputEvent &event) {
  return nullptr;
}

template<typename Context>
BattleScreen<Context>::ScriptWaitState::ScriptWaitState(std::unique_ptr<IState> next_state)
    : next_state_(std::move(next_state)) {

}

template<typename Context>
void BattleScreen<Context>::ScriptWaitState::Init(const config::GameConfig &game_config,
                                                  std::shared_ptr<world::World> world, BattleScreen::UI &ui) {
  ui.info_text->SetText("...");
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::ScriptWaitState::Update(const config::GameConfig &game_config,
                                               std::shared_ptr<world::World> world, BattleScreen::UI &ui,
                                               std::chrono::microseconds delta) {
  if (world->ScriptsFinished()) {
    return std::move(next_state_);
  }

  return nullptr;
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::ScriptWaitState::OnInput(const config::GameConfig &game_config,
                                                std::shared_ptr<world::World> world, BattleScreen::UI &ui,
                                                const frontend::InputEvent &event) {
  return {};
}

template<typename Context>
void BattleScreen<Context>::EnemyMoveState::Init(const config::GameConfig &game_config,
                                                 std::shared_ptr<world::World> world, BattleScreen::UI &ui) {

}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::EnemyMoveState::Update(const config::GameConfig &game_config,
                                              std::shared_ptr<world::World> world, BattleScreen::UI &ui,
                                              std::chrono::microseconds delta) {
  size_t unit_index = rand() % world->Entities().EnemyUnits().size();
  size_t unit_id = world->Entities().EnemyUnitID(unit_index);
  unit::Unit &unit = world->Entities().GetUnit(unit_id);

  world::map::WorldMovementMap movement_map = unit.CreateMovementMap(*world, game_config);
  std::vector<world::map::WorldMovementMap::PositionInfo> positions = movement_map.AvailablePositions();
  util::Vector2<size_t> tile_position = positions[rand() % positions.size()].position;
  util::Vector3<double> position = {
      static_cast<double>(tile_position.x) + 0.5,
      static_cast<double>(tile_position.y) + 0.5,
      0.0
  };

  auto script = unit.CreateMovementScript(unit_id, *world, game_config, position);
  if (script) {
    world->AddScript(std::move(script));
  }

  return std::make_unique<ScriptWaitState>(std::make_unique<PlayerMoveState>(0));
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::EnemyMoveState::OnInput(const config::GameConfig &game_config,
                                               std::shared_ptr<world::World> world, BattleScreen::UI &ui,
                                               const frontend::InputEvent &event) {
  return {};
}

template<typename Context>
BattleScreen<Context>::BattleScreen(const config::GameConfig &game_config, std::shared_ptr<world::World> world)
    : game_config_(game_config), world_(std::move(world)), current_state_(nullptr) {
  InitUI();

  current_state_ = std::make_unique<PlayerMoveState>(0);
  current_state_->Init(game_config_, world_, ui_);
}

template<typename Context>
std::optional<typename IScreen<Context>::Action> BattleScreen<Context>::Update(std::chrono::microseconds delta) {
  world_->Update(delta);

  std::unique_ptr<IState> new_state = current_state_->Update(game_config_, world_, ui_, delta);
  if (new_state) {
    current_state_ = std::move(new_state);
    current_state_->Init(game_config_, world_, ui_);
  }

  return {};
}

template<typename Context>
widget::Widget<Context> &BattleScreen<Context>::Render(std::chrono::microseconds delta) {
  return ui_.widget_system.Root();
}

template<typename Context>
std::optional<typename IScreen<Context>::Action> BattleScreen<Context>::OnInput(const frontend::InputEvent &event) {
  if (ui_.widget_system.HandleInput(event.input)) {
    return {};
  }

  std::unique_ptr<IState> new_state = current_state_->OnInput(game_config_, world_, ui_, event);
  if (new_state) {
    current_state_ = std::move(new_state);
    current_state_->Init(game_config_, world_, ui_);
  }

  return {};
}

template<typename Context>
void BattleScreen<Context>::InitUI() {
  GridContainerWidgetPtr main_container = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{1, 2});
  main_container->SetRenderSeparators(true);

  util::Vector2<size_t> map_size = world_->Map().Size();
  ui_.world_view = std::make_shared<WorldViewWidget>(
      world_,
      util::Vector2<double>{static_cast<double>(map_size.x) / 2.0, static_cast<double>(map_size.y) / 2.0},
      1.0
  );
  ui_.world_view->SetPreferExpand(util::Vector2<bool>{true, true});
  ui_.world_view->SetPointedTileHighlighted(true);
  main_container->Set(util::Vector2<size_t>{0, 0}, ui_.world_view);

  ui_.info_text = std::make_shared<TextWidget>("");
  ui_.info_text->SetPreferExpand(util::Vector2<bool>{true, false});
  main_container->Set(util::Vector2<size_t>{0, 1}, ui_.info_text);

  ui_.widget_system.SetRoot(main_container);
  ui_.widget_system.SetFocused(ui_.world_view);
}

}
