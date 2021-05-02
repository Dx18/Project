#pragma once

 #include <utility>

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

  struct BattleScreenData {
    const config::GameConfig &game_config;
    std::shared_ptr<world::World> world;
    UI ui;
    bool should_quit;

    BattleScreenData(const config::GameConfig &_game_config, std::shared_ptr<world::World> _world);

  };

  class IState {
   public:
    virtual ~IState() = 0;

    virtual void Init(BattleScreenData &data) = 0;
    virtual std::unique_ptr<IState> Update(BattleScreenData &data, std::chrono::microseconds delta) = 0;
    virtual std::unique_ptr<IState> OnInput(BattleScreenData &data, const frontend::InputEvent &event) = 0;

  };

  class PlayerMoveState : public IState {
   public:
    explicit PlayerMoveState(size_t current_unit);

    void Init(BattleScreenData &data) override;
    std::unique_ptr<IState> Update(BattleScreenData &data, std::chrono::microseconds delta) override;
    std::unique_ptr<IState> OnInput(BattleScreenData &data, const frontend::InputEvent &event) override;

   private:
    size_t current_unit_;

  };

  class DestinationSelectionState : public IState {
   public:
    explicit DestinationSelectionState(size_t unit_index);

    void Init(BattleScreenData &data) override;
    std::unique_ptr<IState> Update(BattleScreenData &data, std::chrono::microseconds delta) override;
    std::unique_ptr<IState> OnInput(BattleScreenData &data, const frontend::InputEvent &event) override;

   private:
    size_t unit_index_;

  };

  class TargetSelectionState : public IState {
   public:
    explicit TargetSelectionState(size_t unit_index);

    void Init(BattleScreenData &data) override;
    std::unique_ptr<IState> Update(BattleScreenData &data, std::chrono::microseconds delta) override;
    std::unique_ptr<IState> OnInput(BattleScreenData &data, const frontend::InputEvent &event) override;

   private:
    size_t unit_index_;
    size_t current_target_;
    std::vector<size_t> available_targets_;

  };

  class EnemyMoveState : public IState {
   public:
    void Init(BattleScreenData &data) override;
    std::unique_ptr<IState> Update(BattleScreenData &data, std::chrono::microseconds delta) override;
    std::unique_ptr<IState> OnInput(BattleScreenData &data, const frontend::InputEvent &event) override;

  };

  class ScriptWaitState : public IState {
   public:
    explicit ScriptWaitState(std::unique_ptr<IState> next_state);

    void Init(BattleScreenData &data) override;
    std::unique_ptr<IState> Update(BattleScreenData &data, std::chrono::microseconds delta) override;
    std::unique_ptr<IState> OnInput(BattleScreenData &data, const frontend::InputEvent &event) override;

   private:
    std::unique_ptr<IState> next_state_;

  };

 public:
  BattleScreen(const config::GameConfig &game_config, const std::shared_ptr<world::World> &world);

  std::optional<Action> Update(std::chrono::microseconds delta) override;
  Widget &Render(std::chrono::microseconds delta) override;
  std::optional<Action> OnInput(const frontend::InputEvent &event) override;

 private:
  BattleScreenData data_;

  std::unique_ptr<IState> current_state_;

  void InitUI();

};

template<typename Context>
BattleScreen<Context>::BattleScreenData::BattleScreenData(const config::GameConfig &_game_config,
                                                          std::shared_ptr<world::World> _world)
    : game_config(_game_config), world(std::move(_world)), should_quit(false) {

}

template<typename Context>
BattleScreen<Context>::IState::~IState() = default;

template<typename Context>
BattleScreen<Context>::PlayerMoveState::PlayerMoveState(size_t current_unit)
    : current_unit_(0) {

}

template<typename Context>
void BattleScreen<Context>::PlayerMoveState::Init(BattleScreenData &data) {
  if (data.world->Entities().PlayerUnits().empty()) {
    data.should_quit = true;
    return;
  }

  data.ui.info_text->SetText(
      "Your move\n=========\nTAB: Next unit  BACKTAB: Previous unit  m: Move  a: Attack  r: Reload");

  size_t unit_id = data.world->Entities().PlayerUnitID(current_unit_);
  data.ui.world_view->SetSelectedUnit(unit_id);
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::PlayerMoveState::Update(BattleScreenData &data, std::chrono::microseconds delta) {
  return nullptr;
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::PlayerMoveState::OnInput(BattleScreenData &data, const frontend::InputEvent &event) {
  if (event.input.IsKey()) {
    if (event.input.GetKey() == frontend::Key::kTab) {
      size_t unit_count = data.world->Entities().PlayerUnits().size();
      current_unit_ = (current_unit_ + 1) % unit_count;
      size_t unit_id = data.world->Entities().PlayerUnitID(current_unit_);
      data.ui.world_view->SetSelectedUnit(unit_id);
    } else if (event.input.GetKey() == frontend::Key::kBackTab) {
      size_t unit_count = data.world->Entities().PlayerUnits().size();
      current_unit_ = (unit_count + current_unit_ - 1) % unit_count;
      size_t unit_id = data.world->Entities().PlayerUnitID(current_unit_);
      data.ui.world_view->SetSelectedUnit(unit_id);
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
void BattleScreen<Context>::DestinationSelectionState::Init(BattleScreenData &data) {
  data.ui.info_text->SetText("Select destination...\n=====================\nENTER: Move  ESCAPE: Back");

  size_t unit_id = data.world->Entities().PlayerUnitID(unit_index_);
  data.ui.world_view->SetSelectedUnit(unit_id);

  const unit::Unit &unit = data.world->Entities().GetUnit(unit_id);
  world::map::WorldMovementMap movement_map = unit.CreateMovementMap(*data.world, data.game_config);

  std::vector<world::map::WorldMovementMap::PositionInfo> positions = movement_map.AvailablePositions();
  std::vector<util::Vector2<size_t>> navigation_tiles;
  navigation_tiles.reserve(positions.size());
  for (const auto &position : positions) {
    navigation_tiles.push_back(position.position);
  }
  data.ui.world_view->SetNavigationTiles(navigation_tiles);
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::DestinationSelectionState::Update(BattleScreenData &data, std::chrono::microseconds delta) {
  return nullptr;
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::DestinationSelectionState::OnInput(BattleScreenData &data, const frontend::InputEvent &event) {
  if (event.input.IsKey()) {
    if (event.input.GetKey() == frontend::Key::kEscape) {
      data.ui.world_view->SetNavigationTiles({});
      return std::make_unique<PlayerMoveState>(unit_index_);
    } else if (event.input.GetKey() == frontend::Key::kEnter) {
      size_t unit_id = data.world->Entities().PlayerUnitID(unit_index_);
      unit::Unit &unit = data.world->Entities().GetUnit(unit_id);

      util::Vector2<double> camera_position = data.ui.world_view->CameraPosition();
      util::Vector3<double> position = {
          std::floor(camera_position.x) + 0.5,
          std::floor(camera_position.y) + 0.5,
          0.0
      };

      auto script = unit.CreateMovementScript(unit_id, *data.world, data.game_config, position);

      if (script) {
        data.ui.world_view->SetNavigationTiles({});
        data.world->AddScript(std::move(script));
        return std::make_unique<ScriptWaitState>(std::make_unique<EnemyMoveState>());
      }
    }
  }
  return nullptr;
}

template<typename Context>
BattleScreen<Context>::TargetSelectionState::TargetSelectionState(size_t unit_index)
    : unit_index_(unit_index), available_targets_(), current_target_(0) {

}

template<typename Context>
void BattleScreen<Context>::TargetSelectionState::Init(BattleScreenData &data) {
  size_t unit_id = data.world->Entities().PlayerUnitID(unit_index_);
  const unit::Unit &unit = data.world->Entities().GetUnit(unit_id);
  world::map::WorldVisibilityMap visibility_map = unit.CreateVisibilityMap(*data.world, data.game_config);

  for (size_t i = 0; i < data.world->Entities().EnemyUnits().size(); ++i) {
    size_t target_id = data.world->Entities().EnemyUnitID(i);
    const unit::Unit &target = data.world->Entities().GetUnit(target_id);
    util::Vector3<double> target_position = target.Position();

    util::Vector2<size_t> position = data.world->Map().TilePositionClamped({target_position.x, target_position.y});
    if (visibility_map.GetPositionInfo(position)->visibility > 0.0) {
      available_targets_.push_back(target_id);
    }
  }

  if (available_targets_.empty()) {
    data.ui.info_text->SetText("No target available...\n======================\nESCAPE: Back");
    data.ui.world_view->SetSelectedUnit({});
  } else {
    data.ui.info_text->SetText(
        "Select target...\n================\nENTER: Attack  TAB: Next target  BACKTAB: Previous target  ESCAPE: Back");
    data.ui.world_view->SetSelectedUnit(available_targets_[current_target_]);
  }
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::TargetSelectionState::Update(BattleScreenData &data, std::chrono::microseconds delta) {
  return nullptr;
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::TargetSelectionState::OnInput(BattleScreenData &data, const frontend::InputEvent &event) {
  if (event.input.IsKey()) {
    if (event.input.GetKey() == frontend::Key::kEscape) {
      data.ui.world_view->SetSelectedUnit({});
      return std::make_unique<PlayerMoveState>(unit_index_);
    } else if (!available_targets_.empty()) {
      if (event.input.GetKey() == frontend::Key::kEnter) {
        size_t unit_id = data.world->Entities().PlayerUnitID(unit_index_);
        unit::Unit &unit = data.world->Entities().GetUnit(unit_id);

        size_t target_id = available_targets_[current_target_];

        auto script = unit.CreateAttackScript(*data.world, data.game_config, target_id);

        if (script) {
          data.ui.world_view->SetNavigationTiles({});
          data.world->AddScript(std::move(script));
          return std::make_unique<ScriptWaitState>(std::make_unique<EnemyMoveState>());
        }
      } else if (event.input.GetKey() == frontend::Key::kTab) {
        size_t target_count = available_targets_.size();
        current_target_ = (current_target_ + 1) % target_count;
        data.ui.world_view->SetSelectedUnit(available_targets_[current_target_]);
      } else if (event.input.GetKey() == frontend::Key::kBackTab) {
        size_t target_count = available_targets_.size();
        current_target_ = (target_count + current_target_ - 1) % target_count;
        data.ui.world_view->SetSelectedUnit(available_targets_[current_target_]);
      }
    }
  }

  return nullptr;
}

template<typename Context>
BattleScreen<Context>::ScriptWaitState::ScriptWaitState(std::unique_ptr<IState> next_state)
    : next_state_(std::move(next_state)) {

}

template<typename Context>
void BattleScreen<Context>::ScriptWaitState::Init(BattleScreenData &data) {
  data.ui.info_text->SetText("...");
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::ScriptWaitState::Update(BattleScreenData &data, std::chrono::microseconds delta) {
  if (data.world->ScriptsFinished()) {
    return std::move(next_state_);
  }

  return nullptr;
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::ScriptWaitState::OnInput(BattleScreenData &data, const frontend::InputEvent &event) {
  return {};
}

template<typename Context>
void BattleScreen<Context>::EnemyMoveState::Init(BattleScreenData &data) {

}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::EnemyMoveState::Update(BattleScreenData &data, std::chrono::microseconds delta) {
  if (data.world->Entities().EnemyUnits().empty()) {
    data.should_quit = true;
    return nullptr;
  }

  size_t unit_index = rand() % data.world->Entities().EnemyUnits().size();
  size_t unit_id = data.world->Entities().EnemyUnitID(unit_index);
  unit::Unit &unit = data.world->Entities().GetUnit(unit_id);

  world::map::WorldMovementMap movement_map = unit.CreateMovementMap(*data.world, data.game_config);
  std::vector<world::map::WorldMovementMap::PositionInfo> positions = movement_map.AvailablePositions();
  util::Vector2<size_t> tile_position = positions[rand() % positions.size()].position;
  util::Vector3<double> position = {
      static_cast<double>(tile_position.x) + 0.5,
      static_cast<double>(tile_position.y) + 0.5,
      0.0
  };

  auto script = unit.CreateMovementScript(unit_id, *data.world, data.game_config, position);
  if (script) {
    data.world->AddScript(std::move(script));
  }

  return std::make_unique<ScriptWaitState>(std::make_unique<PlayerMoveState>(0));
}

template<typename Context>
std::unique_ptr<typename BattleScreen<Context>::IState>
BattleScreen<Context>::EnemyMoveState::OnInput(BattleScreenData &data, const frontend::InputEvent &event) {
  return {};
}

template<typename Context>
BattleScreen<Context>::BattleScreen(const config::GameConfig &game_config, const std::shared_ptr<world::World> &world)
    : data_(game_config, world), current_state_(nullptr) {
  InitUI();

  current_state_ = std::make_unique<PlayerMoveState>(0);
  current_state_->Init(data_);
}

template<typename Context>
std::optional<typename IScreen<Context>::Action> BattleScreen<Context>::Update(std::chrono::microseconds delta) {
  if (data_.should_quit) {
    return PopScreenAction{};
  }

  data_.world->Update(delta);

  std::unique_ptr<IState> new_state = current_state_->Update(data_, delta);
  if (new_state) {
    current_state_ = std::move(new_state);
    current_state_->Init(data_);
  }

  return {};
}

template<typename Context>
widget::Widget<Context> &BattleScreen<Context>::Render(std::chrono::microseconds delta) {
  return data_.ui.widget_system.Root();
}

template<typename Context>
std::optional<typename IScreen<Context>::Action> BattleScreen<Context>::OnInput(const frontend::InputEvent &event) {
  if (data_.ui.widget_system.HandleInput(event.input)) {
    return {};
  }

  std::unique_ptr<IState> new_state = current_state_->OnInput(data_, event);
  if (new_state) {
    current_state_ = std::move(new_state);
    current_state_->Init(data_);
  }

  return {};
}

template<typename Context>
void BattleScreen<Context>::InitUI() {
  GridContainerWidgetPtr main_container = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{1, 2});
  main_container->SetRenderSeparators(true);

  util::Vector2<size_t> map_size = data_.world->Map().Size();
  data_.ui.world_view = std::make_shared<WorldViewWidget>(
      data_.world,
      util::Vector2<double>{static_cast<double>(map_size.x) / 2.0, static_cast<double>(map_size.y) / 2.0},
      1.0
  );
  data_.ui.world_view->SetPreferExpand(util::Vector2<bool>{true, true});
  data_.ui.world_view->SetPointedTileHighlighted(true);
  main_container->Set(util::Vector2<size_t>{0, 0}, data_.ui.world_view);

  data_.ui.info_text = std::make_shared<TextWidget>("");
  data_.ui.info_text->SetPreferExpand(util::Vector2<bool>{true, false});
  main_container->Set(util::Vector2<size_t>{0, 1}, data_.ui.info_text);

  data_.ui.widget_system.SetRoot(main_container);
  data_.ui.widget_system.SetFocused(data_.ui.world_view);
}

}
