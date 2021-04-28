#pragma once

#include "headquarters_model/HeadquartersModel.h"
#include "game/IScreen.h"

#include "game/message_screen/MessageScreen.h"
#include "game/squad_modification_screen/SquadModificationScreen.h"

namespace game::squad_formation_screen {

using namespace headquarters_model::tech;

/**
 * Screen used to create initial squad.
 * @tparam RenderContext Context used to render widgets.
 */
template<typename RenderContext>
class SquadFormationScreen : public game::IScreen<RenderContext> {
 private:
  using Action = typename game::IScreen<RenderContext>::Action;
  using PushScreenAction = typename game::IScreen<RenderContext>::PushScreenAction;
  using PopScreenAction = typename game::IScreen<RenderContext>::PopScreenAction;
  using QuitAction = typename game::IScreen<RenderContext>::QuitAction;

  using Widget = widget::Widget<RenderContext>;
  using GridContainerWidget = widget::GridContainerWidget<RenderContext>;
  using TextWidget = widget::TextWidget<RenderContext>;
  using SelectionWidget = widget::SelectionWidget<RenderContext>;
  using SelectionBoxWidget = widget::SelectionBoxWidget<RenderContext>;

  using GridContainerWidgetPtr = std::shared_ptr<GridContainerWidget>;
  using TextWidgetPtr = std::shared_ptr<TextWidget>;
  using SelectionBoxWidgetPtr = std::shared_ptr<SelectionBoxWidget>;

  using WidgetSystem = widget::WidgetSystem<RenderContext>;

 public:
  /**
   * Creates squad formation screen.
   * @param game_config Const reference to game config.
   * @param model Const reference to headquarters model.
   */
  explicit SquadFormationScreen(const config::GameConfig &game_config, const HeadquartersModel &model);

  std::optional<Action> Update(std::chrono::microseconds delta) override;
  Widget &Render(std::chrono::microseconds delta) override;
  std::optional<Action> OnInput(const frontend::InputEvent &event) override;

 private:
  /** Index of soldier count parameter. */
  static const size_t kSoldierCountParameter = 0;
  /** Index of drone count parameter. */
  static const size_t kDroneCountParameter = 1;
  /** Index of soldier weapon tech type parameter. */
  static const size_t kSoldierWeaponTechTypeParameter = 2;
  /** Index of soldier armor tech type parameter. */
  static const size_t kSoldierArmorTechTypeParameter = 3;
  /** Index of drone weapon tech type parameter. */
  static const size_t kDroneWeaponTechTypeParameter = 4;
  /** Index of drone armor tech type parameter. */
  static const size_t kDroneArmorTechTypeParameter = 5;
  /**
   * Count of parameters. Available parameters: soldier count, drone count, soldier weapon and armor tech types,
   * drone weapon and armor tech types.
   */
  static const size_t kParameterCount = 6;

  /** Const reference to game config. */
  const config::GameConfig &game_config_;
  /** Const reference to headquarters model. */
  const HeadquartersModel &model_;
  /** Currently researched weapon tech types. */
  std::vector<WeaponTechType> weapon_tech_types_;
  /** Currently researched armor tech types. */
  std::vector<ArmorTechType> armor_tech_types_;
  /**
   * True if squad can be formed. Squad can be formed if at least one weapon tech type and at least one armor tech type
   * is researched.
   */
  bool can_form_squad_;
  /** Current count of soldiers. */
  size_t current_soldier_count_;
  /** Current count of drones. */
  size_t current_drone_count_;
  /**
   * Current soldier weapon tech type. If `can_form_squad_` is false, then current soldier weapon tech type has no
   * value. Otherwise it has.
   */
  std::optional<WeaponTechType> current_soldier_weapon_tech_type_;
  /**
   * Current soldier armor tech type. If `can_form_squad_` is false, then current soldier armor tech type has no
   * value. Otherwise it has.
   */
  std::optional<ArmorTechType> current_soldier_armor_tech_type_;
  /**
   * Current drone weapon tech type. If `can_form_squad_` is false, then current drone weapon tech type has no
   * value. Otherwise it has.
   */
  std::optional<WeaponTechType> current_drone_weapon_tech_type_;
  /**
   * Current drone armor tech type. If `can_form_squad_` is false, then current drone armor tech type has no
   * value. Otherwise it has.
   */
  std::optional<ArmorTechType> current_drone_armor_tech_type_;

  /** Widget system. */
  WidgetSystem widget_system_;
  /** Selection widgets for parameters. */
  std::array<SelectionBoxWidgetPtr, kParameterCount> parameter_selectors_;
  /** Information text. Contents depend on state of parameter selectors and current chosen parameter. */
  TextWidgetPtr info_text_;
  /** Current chosen parameters. */
  size_t current_parameter_;

  /** Initializes user interface. */
  void InitUI();

  /**
   * Switches parameter to next or previous, depending on given argument. Parameter navigation is cycled.
   * @param to_next True if parameter should be switched to next. Otherwise parameter should be switched to previous.
   */
  void SwitchParameter(bool to_next);
  /**
   * Switches to parameter with given index.
   * @param index Index of parameter.
   */
  void SwitchToParameter(size_t index);

  /** Sets current count of soldiers. */
  void SetSoldierCount(size_t count);
  /** Sets current count of drones. */
  void SetDroneCount(size_t count);
  /** Sets current soldier weapon tech type. */
  void SetSoldierWeaponTechType(WeaponTechType tech_type);
  /** Sets current soldier armor tech type. */
  void SetSoldierArmorTechType(ArmorTechType tech_type);
  /** Sets current drone weapon tech type. */
  void SetDroneWeaponTechType(WeaponTechType tech_type);
  /** Sets current drone armor tech type. */
  void SetDroneArmorTechType(ArmorTechType tech_type);

  /** Updates information text. */
  void UpdateInfoText();

  /**
   * Switches to squad modification screen if possible. It's possible if current size of squad is positive and less or
   * equal to max size of squad.
   */
  std::optional<Action> OnContinue();

};

template<typename RenderContext>
SquadFormationScreen<RenderContext>::SquadFormationScreen(const config::GameConfig &game_config,
                                                          const HeadquartersModel &model)
    : game_config_(game_config), model_(model), current_parameter_(kSoldierCountParameter),
      current_soldier_count_(0), current_drone_count_(0),
      current_soldier_weapon_tech_type_(), current_soldier_armor_tech_type_(),
      current_drone_weapon_tech_type_(), current_drone_armor_tech_type_() {
  for (const WeaponTechInfo &tech_info : kWeaponTechInfo) {
    if (model.GetTech().WeaponTechLevel(tech_info.tech_type) != TechLevel::kNotResearched) {
      weapon_tech_types_.push_back(tech_info.tech_type);
    }
  }
  for (const ArmorTechInfo &tech_info : kArmorTechInfo) {
    if (model.GetTech().ArmorTechLevel(tech_info.tech_type) != TechLevel::kNotResearched) {
      armor_tech_types_.push_back(tech_info.tech_type);
    }
  }

  if (!weapon_tech_types_.empty()) {
    current_soldier_weapon_tech_type_ = weapon_tech_types_.front();
    current_drone_weapon_tech_type_ = weapon_tech_types_.front();
  }
  if (!armor_tech_types_.empty()) {
    current_soldier_armor_tech_type_ = armor_tech_types_.front();
    current_drone_armor_tech_type_ = armor_tech_types_.front();
  }

  can_form_squad_ = !weapon_tech_types_.empty() && !armor_tech_types_.empty();

  InitUI();
}

template<typename RenderContext>
std::optional<typename IScreen<RenderContext>::Action>
SquadFormationScreen<RenderContext>::Update(std::chrono::microseconds delta) {
  return std::optional<Action>();
}

template<typename RenderContext>
widget::Widget<RenderContext> &SquadFormationScreen<RenderContext>::Render(std::chrono::microseconds delta) {
  return widget_system_.Root();
}

template<typename RenderContext>
std::optional<typename IScreen<RenderContext>::Action>
SquadFormationScreen<RenderContext>::OnInput(const frontend::InputEvent &event) {
  if (widget_system_.HandleInput(event.input)) {
    return {};
  }

  if (event.input.IsKey()) {
    if (event.input.GetKey() == frontend::Key::kEscape) {
      return PopScreenAction{};
    } else if (can_form_squad_) {
      if (event.input.GetKey() == frontend::Key::kDown) {
        SwitchParameter(true);
      } else if (event.input.GetKey() == frontend::Key::kUp) {
        SwitchParameter(false);
      } else if (event.input.GetKey() == frontend::Key::kEnter) {
        return OnContinue();
      }
    }
  }

  return {};
}

template<typename RenderContext>
void SquadFormationScreen<RenderContext>::InitUI() {
  if (!can_form_squad_) {
    std::stringstream message;
    if (weapon_tech_types_.empty()) {
      message << "No weapon tech types were researched.\n";
    }
    if (armor_tech_types_.empty()) {
      message << "No armor tech types were researched.\n";
    }
    message << "Research can be made in headquarters.\n";
    message << "Press ESCAPE to return.";

    TextWidgetPtr text = std::make_shared<TextWidget>(message.str());
    text->SetPreferExpand(util::Vector2<bool>{true, true});
    widget_system_.SetRoot(text);
    return;
  }

  GridContainerWidgetPtr main_container = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{1, 3});
  main_container->SetRenderSeparators(true);

  GridContainerWidgetPtr parameters_container = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{2, 6});
  parameters_container->SetPreferExpand(util::Vector2<bool>{true, false});
  parameters_container->SetRenderSeparators(true);

  TextWidgetPtr soldier_count_text = std::make_shared<TextWidget>("Soldier count:");
  soldier_count_text->SetPreferExpand(util::Vector2<bool>{true, false});
  parameters_container->Set(util::Vector2<size_t>{0, 0}, soldier_count_text);

  TextWidgetPtr drone_count_text = std::make_shared<TextWidget>("Drone count:");
  drone_count_text->SetPreferExpand(util::Vector2<bool>{true, false});
  parameters_container->Set(util::Vector2<size_t>{0, 1}, drone_count_text);

  TextWidgetPtr soldier_weapon_tech_type_text = std::make_shared<TextWidget>("Soldier weapon tech type:");
  soldier_weapon_tech_type_text->SetPreferExpand(util::Vector2<bool>{true, false});
  parameters_container->Set(util::Vector2<size_t>{0, 2}, soldier_weapon_tech_type_text);

  TextWidgetPtr soldier_armor_tech_type_text = std::make_shared<TextWidget>("Soldier armor tech type:");
  soldier_armor_tech_type_text->SetPreferExpand(util::Vector2<bool>{true, false});
  parameters_container->Set(util::Vector2<size_t>{0, 3}, soldier_armor_tech_type_text);

  TextWidgetPtr drone_weapon_tech_type_text = std::make_shared<TextWidget>("Drone weapon tech type:");
  drone_weapon_tech_type_text->SetPreferExpand(util::Vector2<bool>{true, false});
  parameters_container->Set(util::Vector2<size_t>{0, 4}, drone_weapon_tech_type_text);

  TextWidgetPtr drone_armor_tech_type_text = std::make_shared<TextWidget>("Drone armor tech type:");
  drone_armor_tech_type_text->SetPreferExpand(util::Vector2<bool>{true, false});
  parameters_container->Set(util::Vector2<size_t>{0, 5}, drone_armor_tech_type_text);

  std::vector<std::string> unit_count_items;
  for (int i = 0; i <= game_config_.SquadSize(); ++i) {
    std::stringstream item;
    item << i;
    unit_count_items.push_back(item.str());
  }

  std::vector<std::string> weapon_items;
  for (const WeaponTechType &tech_type : weapon_tech_types_) {
    weapon_items.push_back(kWeaponTechInfo[tech_type].name);
  }

  std::vector<std::string> armor_items;
  for (const ArmorTechType &tech_type : armor_tech_types_) {
    armor_items.push_back(kArmorTechInfo[tech_type].name);
  }

  SelectionBoxWidgetPtr soldier_count_selector = std::make_shared<SelectionBoxWidget>(unit_count_items);
  soldier_count_selector->SetPreferExpand(util::Vector2<bool>{true, false});
  soldier_count_selector->AddSelectionChangedListener([this](SelectionWidget &box) {
    SetSoldierCount(box.SelectedItem());
    UpdateInfoText();
  });
  parameters_container->Set(util::Vector2<size_t>{1, 0}, soldier_count_selector);

  SelectionBoxWidgetPtr drone_count_selector = std::make_shared<SelectionBoxWidget>(unit_count_items);
  drone_count_selector->SetPreferExpand(util::Vector2<bool>{true, false});
  drone_count_selector->AddSelectionChangedListener([this](SelectionWidget &box) {
    SetDroneCount(box.SelectedItem());
  });
  parameters_container->Set(util::Vector2<size_t>{1, 1}, drone_count_selector);

  SelectionBoxWidgetPtr soldier_weapon_tech_type_selector = std::make_shared<SelectionBoxWidget>(weapon_items);
  soldier_weapon_tech_type_selector->SetPreferExpand(util::Vector2<bool>{true, false});
  soldier_weapon_tech_type_selector->AddSelectionChangedListener([this](SelectionWidget &box) {
    SetSoldierWeaponTechType(weapon_tech_types_[box.SelectedItem()]);
  });
  parameters_container->Set(util::Vector2<size_t>{1, 2}, soldier_weapon_tech_type_selector);

  SelectionBoxWidgetPtr soldier_armor_tech_type_selector = std::make_shared<SelectionBoxWidget>(armor_items);
  soldier_armor_tech_type_selector->SetPreferExpand(util::Vector2<bool>{true, false});
  soldier_armor_tech_type_selector->AddSelectionChangedListener([this](SelectionWidget &box) {
    SetSoldierArmorTechType(armor_tech_types_[box.SelectedItem()]);
  });
  parameters_container->Set(util::Vector2<size_t>{1, 3}, soldier_armor_tech_type_selector);

  SelectionBoxWidgetPtr drone_weapon_tech_type_selector = std::make_shared<SelectionBoxWidget>(weapon_items);
  drone_weapon_tech_type_selector->SetPreferExpand(util::Vector2<bool>{true, false});
  drone_weapon_tech_type_selector->AddSelectionChangedListener([this](SelectionWidget &box) {
    SetDroneWeaponTechType(weapon_tech_types_[box.SelectedItem()]);
  });
  parameters_container->Set(util::Vector2<size_t>{1, 4}, drone_weapon_tech_type_selector);

  SelectionBoxWidgetPtr drone_armor_tech_type_selector = std::make_shared<SelectionBoxWidget>(armor_items);
  drone_armor_tech_type_selector->SetPreferExpand(util::Vector2<bool>{true, false});
  drone_armor_tech_type_selector->AddSelectionChangedListener([this](SelectionWidget &box) {
    SetDroneArmorTechType(armor_tech_types_[box.SelectedItem()]);
  });
  parameters_container->Set(util::Vector2<size_t>{1, 5}, drone_armor_tech_type_selector);

  parameter_selectors_[kSoldierCountParameter] = soldier_count_selector;
  parameter_selectors_[kDroneCountParameter] = drone_count_selector;
  parameter_selectors_[kSoldierWeaponTechTypeParameter] = soldier_weapon_tech_type_selector;
  parameter_selectors_[kSoldierArmorTechTypeParameter] = soldier_armor_tech_type_selector;
  parameter_selectors_[kDroneWeaponTechTypeParameter] = drone_weapon_tech_type_selector;
  parameter_selectors_[kDroneArmorTechTypeParameter] = drone_armor_tech_type_selector;

  main_container->Set(util::Vector2<size_t>{0, 0}, parameters_container);

  info_text_ = std::make_shared<TextWidget>("");
  info_text_->SetPreferExpand(util::Vector2<bool>{true, true});
  main_container->Set(util::Vector2<size_t>{0, 1}, info_text_);

  TextWidgetPtr hint = std::make_shared<TextWidget>(
      "ESCAPE: Return  DOWN/UP: Navigate  LEFT/RIGHT: Switch parameters  ENTER: Continue");
  hint->SetPreferExpand(util::Vector2<bool>{true, false});
  main_container->Set(util::Vector2<size_t>{0, 2}, hint);

  widget_system_.SetRoot(main_container);

  SwitchToParameter(current_parameter_);
}

template<typename RenderContext>
void SquadFormationScreen<RenderContext>::SwitchParameter(bool to_next) {
  SwitchToParameter((kParameterCount + current_parameter_ + (to_next ? 1 : -1)) % kParameterCount);
}

template<typename RenderContext>
void SquadFormationScreen<RenderContext>::SwitchToParameter(size_t index) {
  current_parameter_ = index;
  widget_system_.SetFocused(parameter_selectors_[current_parameter_]);
  UpdateInfoText();
}

template<typename RenderContext>
void SquadFormationScreen<RenderContext>::SetSoldierCount(size_t count) {
  current_soldier_count_ = count;
  UpdateInfoText();
}

template<typename RenderContext>
void SquadFormationScreen<RenderContext>::SetDroneCount(size_t count) {
  current_drone_count_ = count;
  UpdateInfoText();
}

template<typename RenderContext>
void SquadFormationScreen<RenderContext>::SetSoldierWeaponTechType(WeaponTechType tech_type) {
  current_soldier_weapon_tech_type_ = tech_type;
  UpdateInfoText();
}

template<typename RenderContext>
void SquadFormationScreen<RenderContext>::SetSoldierArmorTechType(ArmorTechType tech_type) {
  current_soldier_armor_tech_type_ = tech_type;
  UpdateInfoText();
}

template<typename RenderContext>
void SquadFormationScreen<RenderContext>::SetDroneWeaponTechType(WeaponTechType tech_type) {
  current_drone_weapon_tech_type_ = tech_type;
  UpdateInfoText();
}

template<typename RenderContext>
void SquadFormationScreen<RenderContext>::SetDroneArmorTechType(ArmorTechType tech_type) {
  current_drone_armor_tech_type_ = tech_type;
  UpdateInfoText();
}

template<typename RenderContext>
void SquadFormationScreen<RenderContext>::UpdateInfoText() {
  std::stringstream info;

  if (current_parameter_ == kSoldierCountParameter || current_parameter_ == kDroneCountParameter) {
    info << "Max size of squad is " << game_config_.SquadSize() << ".\n";
    info << "Current size of squad " << current_soldier_count_ + current_drone_count_ << ".";
  } else if (current_parameter_ == kSoldierWeaponTechTypeParameter) {
    info << "Weapons available for soldiers:\n";
    for (const WeaponInfo &weapon_info : kWeaponInfo) {
      if (weapon_info.tech_type != current_soldier_weapon_tech_type_.value()
          || weapon_info.unit_type != UnitType::kSoldier) {
        continue;
      }

      info << "  - " << weapon_info.name << " x " << model_.GetArmory().WeaponCount(weapon_info.type) << "\n";
    }
  } else if (current_parameter_ == kSoldierArmorTechTypeParameter) {
    info << "Armor available for soldiers:\n";
    for (const ArmorInfo &armor_info : kArmorInfo) {
      if (armor_info.tech_type != current_soldier_armor_tech_type_.value()
          || armor_info.unit_type != UnitType::kSoldier) {
        continue;
      }

      info << "  - " << armor_info.name << " x " << model_.GetArmory().ArmorCount(armor_info.type) << "\n";
    }
  } else if (current_parameter_ == kDroneWeaponTechTypeParameter) {
    info << "Weapons available for drones:\n";
    for (const WeaponInfo &weapon_info : kWeaponInfo) {
      if (weapon_info.tech_type != current_drone_weapon_tech_type_.value()
          || weapon_info.unit_type != UnitType::kDrone) {
        continue;
      }

      info << "  - " << weapon_info.name << " x " << model_.GetArmory().WeaponCount(weapon_info.type) << "\n";
    }
  } else if (current_parameter_ == kDroneArmorTechTypeParameter) {
    info << "Armor available for drones:\n";
    for (const ArmorInfo &armor_info : kArmorInfo) {
      if (armor_info.tech_type != current_drone_armor_tech_type_.value()
          || armor_info.unit_type != UnitType::kDrone) {
        continue;
      }

      info << "  - " << armor_info.name << " x " << model_.GetArmory().ArmorCount(armor_info.type) << "\n";
    }
  }

  info_text_->SetText(info.str());
}

template<typename RenderContext>
std::optional<typename IScreen<RenderContext>::Action> SquadFormationScreen<RenderContext>::OnContinue() {
  if (current_soldier_count_ + current_drone_count_ > game_config_.SquadSize()) {
    return PushScreenAction{
        std::make_unique<message_screen::MessageScreen<RenderContext>>(
            "Cannot continue",
            "Current size of your squad is greater than max possible."
        )
    };
  } else if (current_soldier_count_ + current_drone_count_ == 0) {
    return PushScreenAction{
        std::make_unique<message_screen::MessageScreen<RenderContext>>(
            "Cannot continue",
            "Your squad is empty."
        )
    };
  } else {
    return PushScreenAction{
        std::make_unique<squad_modification_screen::SquadModificationScreen<RenderContext>>(
            model_,
            current_soldier_count_,
            current_drone_count_,
            current_soldier_weapon_tech_type_.value(),
            current_soldier_armor_tech_type_.value(),
            current_drone_weapon_tech_type_.value(),
            current_drone_armor_tech_type_.value()
        )
    };
  }
}

}
