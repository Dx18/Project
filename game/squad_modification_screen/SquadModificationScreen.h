#pragma once

#include <unit/soldier/SoldierBuilder.h>
#include <unit/drone/DroneBuilder.h>
#include "game/IScreen.h"
#include "headquarters_model/HeadquartersModel.h"
#include "object_database/WeaponInfo.h"
#include "object_database/ArmorInfo.h"

#include "unit/soldier/weapon/ISoldierWeaponFactory.h"
#include "unit/soldier/weapon/firearm/SoldierFirearmWeaponFactory.h"
#include "unit/soldier/weapon/laser/SoldierLaserWeaponFactory.h"

#include "unit/soldier/armor/ISoldierArmorFactory.h"
#include "unit/soldier/armor/standard/SoldierStandardArmorFactory.h"
#include "unit/soldier/armor/composite/SoldierCompositeArmorFactory.h"

#include "unit/drone/weapon/IDroneWeaponFactory.h"
#include "unit/drone/weapon/firearm/DroneFirearmWeaponFactory.h"
#include "unit/drone/weapon/laser/DroneLaserWeaponFactory.h"

#include "unit/drone/armor/IDroneArmorFactory.h"
#include "unit/drone/armor/standard/DroneStandardArmorFactory.h"
#include "unit/drone/armor/composite/DroneCompositeArmorFactory.h"

#include "widget/GridContainerWidget.h"
#include "widget/TextWidget.h"
#include "widget/SelectionWidget.h"
#include "widget/SelectionListWidget.h"
#include "widget/SelectionBoxWidget.h"
#include "widget/game/SoldierEquipmentWidget.h"
#include "widget/game/DroneEquipmentWidget.h"
#include "widget/WidgetSystem.h"
#include "game/battle_screen/BattleScreen.h"
#include "world/WorldGenerator.h"

namespace game::squad_modification_screen {

using namespace object_database;

/**
 * Screen used to modify squad and start battle.
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class SquadModificationScreen : public IScreen<Context> {
 private:
  using Action = typename game::IScreen<Context>::Action;
  using PushScreenAction = typename game::IScreen<Context>::PushScreenAction;
  using PopScreenAction = typename game::IScreen<Context>::PopScreenAction;
  using QuitAction = typename game::IScreen<Context>::QuitAction;

  using Widget = widget::Widget<Context>;
  using GridContainerWidget = widget::GridContainerWidget<Context>;
  using TextWidget = widget::TextWidget<Context>;
  using SelectionWidget = widget::SelectionWidget<Context>;
  using SelectionListWidget = widget::SelectionListWidget<Context>;
  using SelectionBoxWidget = widget::SelectionListWidget<Context>;
  using SoldierEquipmentWidget = widget::game::SoldierEquipmentWidget<Context>;
  using DroneEquipmentWidget = widget::game::DroneEquipmentWidget<Context>;

  using WidgetPtr = std::shared_ptr<Widget>;
  using GridContainerWidgetPtr = std::shared_ptr<GridContainerWidget>;
  using TextWidgetPtr = std::shared_ptr<TextWidget>;
  using SelectionListWidgetPtr = std::shared_ptr<SelectionListWidget>;
  using SelectionBoxWidgetPtr = std::shared_ptr<SelectionBoxWidget>;
  using SoldierEquipmentWidgetPtr = std::shared_ptr<SoldierEquipmentWidget>;
  using DroneEquipmentWidgetPtr = std::shared_ptr<DroneEquipmentWidget>;

  using WidgetSystem = widget::WidgetSystem<Context>;

 public:
  /**
   * Creates squad modification screen.
   * @param model Const reference to headquarters model.
   * @param soldier_count Count of soldiers.
   * @param drone_count Count of drones.
   * @param soldier_weapon_tech_type Soldier weapon tech type.
   * @param soldier_armor_tech_type Soldier armor tech type.
   * @param drone_weapon_tech_type Drone weapon tech type.
   * @param drone_armor_tech_type Drone armor tech type.
   */
  SquadModificationScreen(const config::GameConfig &game_config,
                          const headquarters_model::HeadquartersModel &model,
                          size_t soldier_count, size_t drone_count,
                          WeaponTechType soldier_weapon_tech_type,
                          ArmorTechType soldier_armor_tech_type,
                          WeaponTechType drone_weapon_tech_type,
                          ArmorTechType drone_armor_tech_type);

  std::optional<Action> Update(std::chrono::microseconds delta) override;
  Widget &Render(std::chrono::microseconds delta) override;
  std::optional<Action> OnInput(const frontend::InputEvent &event) override;

 private:
  /** Const reference to game config. */
  const config::GameConfig &game_config_;
  /** Const reference to headquarters model. */
  const headquarters_model::HeadquartersModel &model_;
  /** Count of soldiers. */
  size_t soldier_count_;
  /** Count of drones. */
  size_t drone_count_;

  /** Soldier weapon types which can constructed determined by current soldier weapon tech type. */
  std::vector<WeaponType> soldier_weapon_types_;
  /** Soldier armor type which can constructed determined current soldier armor tech type. */
  ArmorType soldier_armor_type_;
  /** Drone weapon types which can constructed using current drone weapon tech type. */
  std::vector<WeaponType> drone_weapon_types_;
  /** Drone armor type which can constructed determined current drone armor tech type. */
  ArmorType drone_armor_type_;

  /** Soldier weapon factory. */
  std::unique_ptr<unit::soldier::weapon::ISoldierWeaponFactory> soldier_weapon_factory_;
  /** Soldier armor factory. */
  std::unique_ptr<unit::soldier::armor::ISoldierArmorFactory> soldier_armor_factory_;
  /** Drone weapon factory. */
  std::unique_ptr<unit::drone::weapon::IDroneWeaponFactory> drone_weapon_factory_;
  /** Drone armor factory. */
  std::unique_ptr<unit::drone::armor::IDroneArmorFactory> drone_armor_factory_;

  /** Widget system. */
  WidgetSystem widget_system_;
  /** Main container. */
  GridContainerWidgetPtr main_container_;
  /** Soldier equipment widgets for each soldier. */
  std::vector<SoldierEquipmentWidgetPtr> soldiers_widgets_;
  /** Drone equipment widgets for each drone. */
  std::vector<DroneEquipmentWidgetPtr> drones_widgets_;
  /** Title text. */
  TextWidgetPtr title_text_;
  /** Information text. Contains information about available amount of armory and amount of armory used. */
  TextWidgetPtr info_text_;

  /** Current selected unit. */
  size_t current_unit_;

  /** Initializes UI. */
  void InitUI();

  /**
   * Switch unit to next or previous, depending on given argument. Unit navigation is cycled.
   * @param to_next True if unit should be switched to next. Otherwise unit should be switched to previous.
   */
  void SwitchUnit(bool to_next);
  /**
   * Switches to unit with given index.
   * @param index Index of unit.
   */
  void SwitchToUnit(size_t index);
  /**
   * Switches to soldier with given index.
   * @param index Index of soldier.
   */
  void SwitchToSoldier(size_t index);
  /**
   * Switches to drone with given index.
   * @param index Index of drone.
   */
  void SwitchToDrone(size_t index);

  /** Updates information text. */
  void UpdateInfoText();

  std::unique_ptr<unit::soldier::weapon::ISoldierWeapon> BuildSoldierWeapon(WeaponClassType weapon_class);
  std::unique_ptr<unit::soldier::armor::ISoldierArmor> BuildSoldierArmor();
  std::unique_ptr<unit::drone::weapon::IDroneWeapon> BuildDroneWeapon(WeaponClassType weapon_class);
  std::unique_ptr<unit::drone::armor::IDroneArmor> BuildDroneArmor();

  std::vector<std::pair<size_t, size_t>> CalculateSoldierWeaponUsage();
  std::pair<size_t, size_t> CalculateSoldierArmorUsage();
  std::vector<std::pair<size_t, size_t>> CalculateDroneWeaponUsage();
  std::pair<size_t, size_t> CalculateDroneArmorUsage();

  /** Builds units or returns no value if building is failed. */
  std::optional<std::vector<std::unique_ptr<unit::Unit>>> BuildUnits();

};

template<typename Context>
SquadModificationScreen<Context>::
SquadModificationScreen(const config::GameConfig &game_config,
                        const headquarters_model::HeadquartersModel &model,
                        size_t soldier_count, size_t drone_count,
                        WeaponTechType soldier_weapon_tech_type,
                        ArmorTechType soldier_armor_tech_type,
                        WeaponTechType drone_weapon_tech_type,
                        ArmorTechType drone_armor_tech_type)
    : game_config_(game_config), model_(model), soldier_count_(soldier_count), drone_count_(drone_count),
      soldier_weapon_types_(), drone_weapon_types_(),
      soldiers_widgets_(soldier_count), drones_widgets_(drone_count),
      soldier_weapon_factory_(), soldier_armor_factory_(),
      drone_weapon_factory_(), drone_armor_factory_(),
      current_unit_(0) {
  for (const WeaponInfo &weapon_info : kWeaponInfo) {
    if (weapon_info.tech_type == soldier_weapon_tech_type
        && weapon_info.unit_type == UnitType::kSoldier) {
      soldier_weapon_types_.push_back(weapon_info.type);
    }
    if (weapon_info.tech_type == drone_weapon_tech_type
        && weapon_info.unit_type == UnitType::kDrone) {
      drone_weapon_types_.push_back(weapon_info.type);
    }
  }
  for (const ArmorInfo &armor_info : kArmorInfo) {
    if (armor_info.tech_type == soldier_armor_tech_type
        && armor_info.unit_type == UnitType::kSoldier) {
      soldier_armor_type_ = armor_info.type;
    }
    if (armor_info.tech_type == drone_armor_tech_type
        && armor_info.unit_type == UnitType::kDrone) {
      drone_armor_type_ = armor_info.type;
    }
  }

  using namespace unit::soldier::weapon::firearm;
  using namespace unit::soldier::weapon::laser;
  using namespace unit::soldier::armor::standard;
  using namespace unit::soldier::armor::composite;
  using namespace unit::drone::weapon::firearm;
  using namespace unit::drone::weapon::laser;
  using namespace unit::drone::armor::standard;
  using namespace unit::drone::armor::composite;

  if (soldier_weapon_tech_type == WeaponTechType::kFirearm) {
    soldier_weapon_factory_ = std::make_unique<SoldierFirearmWeaponFactory>(model.GetTech());
  } else if (soldier_weapon_tech_type == WeaponTechType::kLaser) {
    soldier_weapon_factory_ = std::make_unique<SoldierLaserWeaponFactory>(model.GetTech());
  }
  if (soldier_armor_tech_type == ArmorTechType::kStandard) {
    soldier_armor_factory_ = std::make_unique<SoldierStandardArmorFactory>(model.GetTech());
  } else if (soldier_armor_tech_type == ArmorTechType::kComposite) {
    soldier_armor_factory_ = std::make_unique<SoldierCompositeArmorFactory>(model.GetTech());
  }

  if (drone_weapon_tech_type == WeaponTechType::kFirearm) {
    drone_weapon_factory_ = std::make_unique<DroneFirearmWeaponFactory>(model.GetTech());
  } else if (drone_weapon_tech_type == WeaponTechType::kLaser) {
    drone_weapon_factory_ = std::make_unique<DroneLaserWeaponFactory>(model.GetTech());
  }
  if (drone_armor_tech_type == ArmorTechType::kStandard) {
    drone_armor_factory_ = std::make_unique<DroneStandardArmorFactory>(model.GetTech());
  } else if (drone_armor_tech_type == ArmorTechType::kComposite) {
    drone_armor_factory_ = std::make_unique<DroneCompositeArmorFactory>(model.GetTech());
  }

  InitUI();
}

template<typename Context>
std::optional<typename IScreen<Context>::Action>
SquadModificationScreen<Context>::Update(std::chrono::microseconds delta) {
  return {};
}

template<typename Context>
widget::Widget<Context> &SquadModificationScreen<Context>::Render(std::chrono::microseconds delta) {
  return widget_system_.Root();
}

template<typename Context>
std::optional<typename IScreen<Context>::Action>
SquadModificationScreen<Context>::OnInput(const frontend::InputEvent &event) {
  if (widget_system_.HandleInput(event.input)) {
    return {};
  }

  if (event.input.IsKey()) {
    if (event.input.GetKey() == frontend::Key::kEscape) {
      return PopScreenAction{};
    } else if (event.input.GetKey() == frontend::Key::kTab) {
      SwitchUnit(true);
    } else if (event.input.GetKey() == frontend::Key::kBackTab) {
      SwitchUnit(false);
    } else if (event.input.GetKey() == frontend::Key::kEnter) {
      std::optional<std::vector<std::unique_ptr<unit::Unit>>> units = BuildUnits();

      if (!units.has_value()) {
        return PushScreenAction{
            std::make_unique<game::message_screen::MessageScreen<Context>>("Couldn't create squad",
                                                                           "Too many armory used")
        };
      }

      return PushScreenAction{
          std::make_unique<game::battle_screen::BattleScreen<Context>>(
              game_config_,
              std::make_shared<world::World>(
                  std::move(world::WorldGenerator(
                      game_config_,
                      std::mt19937(time(nullptr))).GenerateWorld(std::move(*units), 5.0)))
          )
      };
    }
  }
  return {};
}

template<typename Context>
void SquadModificationScreen<Context>::InitUI() {
  main_container_ = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{1, 4});
  main_container_->SetRenderSeparators(true);

  title_text_ = std::make_shared<TextWidget>("");
  title_text_->SetPreferExpand(util::Vector2<bool>{true, false});
  main_container_->Set(util::Vector2<size_t>{0, 0}, title_text_);

  auto soldier_update_info_text_function = [this](SoldierEquipmentWidget &) {
    UpdateInfoText();
  };

  soldiers_widgets_.resize(soldier_count_);
  for (size_t soldier = 0; soldier < soldier_count_; ++soldier) {
    soldiers_widgets_[soldier] = std::make_shared<SoldierEquipmentWidget>(std::optional<WeaponClassType>{},
                                                                          std::optional<WeaponClassType>{},
                                                                          false);
    soldiers_widgets_[soldier]->SetPreferExpand(util::Vector2<bool>{true, true});
    soldiers_widgets_[soldier]->AddPrimaryWeaponChangedListener(soldier_update_info_text_function);
    soldiers_widgets_[soldier]->AddSecondaryWeaponChangedListener(soldier_update_info_text_function);
    soldiers_widgets_[soldier]->AddArmorChangedListener(soldier_update_info_text_function);
  }

  auto drone_update_info_text_function = [this](DroneEquipmentWidget &) {
    UpdateInfoText();
  };

  drones_widgets_.resize(drone_count_);
  for (size_t drone = 0; drone < drone_count_; ++drone) {
    drones_widgets_[drone] = std::make_shared<DroneEquipmentWidget>(std::optional<WeaponClassType>{}, false);
    drones_widgets_[drone]->SetPreferExpand(util::Vector2<bool>{true, true});
    drones_widgets_[drone]->AddWeaponChangedListener(drone_update_info_text_function);
    drones_widgets_[drone]->AddArmorChangedListener(drone_update_info_text_function);
  }

  info_text_ = std::make_shared<TextWidget>("");
  info_text_->SetPreferExpand(util::Vector2<bool>{true, true});
  main_container_->Set(util::Vector2<size_t>{0, 2}, info_text_);

  TextWidgetPtr hint_text = std::make_shared<TextWidget>("ESCAPE: Return  Tab: Switch unit  UP/DOWN/LEFT/RIGHT: Edit");
  hint_text->SetPreferExpand(util::Vector2<bool>{true, false});
  main_container_->Set(util::Vector2<size_t>{0, 3}, hint_text);

  widget_system_.SetRoot(main_container_);

  SwitchToUnit(0);
  UpdateInfoText();
}

template<typename Context>
void SquadModificationScreen<Context>::SwitchUnit(bool to_next) {
  SwitchToUnit((soldier_count_ + drone_count_ + current_unit_ + (to_next ? 1 : -1))
                   % (soldier_count_ + drone_count_));
}

template<typename Context>
void SquadModificationScreen<Context>::SwitchToUnit(size_t index) {
  if (index < soldier_count_) {
    SwitchToSoldier(index);
  } else if (index < soldier_count_ + drone_count_) {
    SwitchToDrone(index - soldier_count_);
  }
  current_unit_ = index;
}

template<typename Context>
void SquadModificationScreen<Context>::SwitchToSoldier(size_t index) {
  std::stringstream name;
  name << "Soldier " << index + 1;
  title_text_->SetText(name.str());

  main_container_->Set(util::Vector2<size_t>{0, 1}, soldiers_widgets_[index]);
  widget_system_.SetFocused(soldiers_widgets_[index]);
}

template<typename Context>
void SquadModificationScreen<Context>::SwitchToDrone(size_t index) {
  std::stringstream name;
  name << "Drone " << index + 1;
  title_text_->SetText(name.str());

  main_container_->Set(util::Vector2<size_t>{0, 1}, drones_widgets_[index]);
  widget_system_.SetFocused(drones_widgets_[index]);
}

template<typename Context>
void SquadModificationScreen<Context>::UpdateInfoText() {
  std::stringstream message;
  message << "Armory usage (used / available):\n";

  std::vector<std::pair<size_t, size_t>> soldier_weapon_usage = CalculateSoldierWeaponUsage();
  size_t index = 0;
  for (WeaponType weapon_type : soldier_weapon_types_) {
    auto[times_used, max_available] = soldier_weapon_usage[index];
    message << kWeaponInfo[weapon_type].name << ": " << times_used << " / " << max_available;
    if (times_used > max_available) {
      message << " (!)";
    }
    message << "\n";

    ++index;
  }

  std::pair<size_t, size_t> soldier_armor_usage = CalculateSoldierArmorUsage();
  {
    auto[times_used, max_available] = soldier_armor_usage;
    message << kArmorInfo[soldier_armor_type_].name << ": " << times_used << " / " << max_available;
    if (times_used > max_available) {
      message << " (!)";
    }
    message << "\n";
  }

  std::vector<std::pair<size_t, size_t>> drone_weapon_usage = CalculateDroneWeaponUsage();
  index = 0;
  for (WeaponType weapon_type : drone_weapon_types_) {
    auto[times_used, max_available] = drone_weapon_usage[index];
    message << kWeaponInfo[weapon_type].name << ": " << times_used << " / " << max_available;
    if (times_used > max_available) {
      message << " (!)";
    }
    message << "\n";

    ++index;
  }

  std::pair<size_t, size_t> drone_armor_usage = CalculateDroneArmorUsage();
  {
    auto[times_used, max_available] = drone_armor_usage;
    message << kArmorInfo[drone_armor_type_].name << ": " << times_used << " / " << max_available;
    if (times_used > max_available) {
      message << " (!)";
    }
    message << "\n";
  }

  info_text_->SetText(message.str());
}

template<typename Context>
std::unique_ptr<unit::soldier::weapon::ISoldierWeapon>
SquadModificationScreen<Context>::BuildSoldierWeapon(WeaponClassType weapon_class) {
  if (weapon_class == WeaponClassType::kPistol) {
    return soldier_weapon_factory_->CreatePistol();
  } else if (weapon_class == WeaponClassType::kShotgun) {
    return soldier_weapon_factory_->CreateShotgun();
  } else if (weapon_class == WeaponClassType::kSniperRifle) {
    return soldier_weapon_factory_->CreateSniperRifle();
  } else if (weapon_class == WeaponClassType::kMachineGun) {
    return soldier_weapon_factory_->CreateMachineGun();
  }
  return nullptr;
}

template<typename Context>
std::unique_ptr<unit::soldier::armor::ISoldierArmor>
SquadModificationScreen<Context>::BuildSoldierArmor() {
  return soldier_armor_factory_->CreateArmor();
}

template<typename Context>
std::unique_ptr<unit::drone::weapon::IDroneWeapon>
SquadModificationScreen<Context>::BuildDroneWeapon(WeaponClassType weapon_class) {
  if (weapon_class == WeaponClassType::kMachineGun) {
    return drone_weapon_factory_->CreateMachineGun();
  }
  return nullptr;
}

template<typename Context>
std::unique_ptr<unit::drone::armor::IDroneArmor>
SquadModificationScreen<Context>::BuildDroneArmor() {
  return drone_armor_factory_->CreateArmor();
}

template<typename Context>
std::optional<std::vector<std::unique_ptr<unit::Unit>>> SquadModificationScreen<Context>::BuildUnits() {
  std::vector<std::pair<size_t, size_t>> soldier_weapon_usage = CalculateSoldierWeaponUsage();
  for (auto[times_used, max_available] : soldier_weapon_usage) {
    if (times_used > max_available) {
      return {};
    }
  }
  std::pair<size_t, size_t> soldier_armor_usage = CalculateSoldierArmorUsage();
  {
    auto[times_used, max_available] = soldier_armor_usage;
    if (times_used > max_available) {
      return {};
    }
  }
  std::vector<std::pair<size_t, size_t>> drone_weapon_usage = CalculateDroneWeaponUsage();
  for (auto[times_used, max_available] : drone_weapon_usage) {
    if (times_used > max_available) {
      return {};
    }
  }
  std::pair<size_t, size_t> drone_armor_usage = CalculateDroneArmorUsage();
  {
    auto[times_used, max_available] = drone_armor_usage;
    if (times_used > max_available) {
      return {};
    }
  }

  std::vector<std::unique_ptr<unit::Unit>> units;

  for (size_t index = 0; index < soldier_count_; ++index) {
    unit::soldier::SoldierBuilder soldier;

    std::stringstream name;
    name << "Soldier " << index + 1;
    soldier.WithName(name.str());

    soldier.WithBaseHealth(game_config_.SoldierBaseHealth());

    std::optional<WeaponClassType> primary_weapon = soldiers_widgets_[index]->PrimaryWeapon();
    if (primary_weapon.has_value()) {
      soldier.WithPrimaryWeapon(BuildSoldierWeapon(*primary_weapon));
    }
    std::optional<WeaponClassType> secondary_weapon = soldiers_widgets_[index]->SecondaryWeapon();
    if (secondary_weapon.has_value()) {
      soldier.WithSecondaryWeapon(BuildSoldierWeapon(*secondary_weapon));
    }
    if (soldiers_widgets_[index]->Armor()) {
      soldier.WithArmor(BuildSoldierArmor());
    }

    unit::soldier::Soldier soldier_result = soldier.Build();
    soldier_result.SetHealth(soldier_result.MaxHealth());
    units.push_back(std::make_unique<unit::soldier::Soldier>(std::move(soldier_result)));
  }

  for (size_t index = 0; index < drone_count_; ++index) {
    unit::drone::DroneBuilder drone;

    std::stringstream name;
    name << "Drone " << index + 1;
    drone.WithName(name.str());

    drone.WithBaseHealth(game_config_.DroneBaseHealth());

    std::optional<WeaponClassType> weapon = drones_widgets_[index]->Weapon();
    if (weapon.has_value()) {
      drone.WithWeapon(BuildDroneWeapon(*weapon));
    }
    if (drones_widgets_[index]->Armor()) {
      drone.WithArmor(BuildDroneArmor());
    }

    unit::drone::Drone drone_result = drone.Build();
    drone_result.SetHealth(drone_result.MaxHealth());
    units.push_back(std::make_unique<unit::drone::Drone>(std::move(drone_result)));
  }

  return units;
}

template<typename Context>
std::vector<std::pair<size_t, size_t>> SquadModificationScreen<Context>::CalculateSoldierWeaponUsage() {
  std::vector<std::pair<size_t, size_t>> result;
  for (WeaponType weapon_type : soldier_weapon_types_) {
    size_t times_used = 0;
    for (size_t soldier = 0; soldier < soldier_count_; ++soldier) {
      if (soldiers_widgets_[soldier]->PrimaryWeapon() == kWeaponInfo[weapon_type].class_type) {
        ++times_used;
      }
      if (soldiers_widgets_[soldier]->SecondaryWeapon() == kWeaponInfo[weapon_type].class_type) {
        ++times_used;
      }
    }

    size_t max_available = model_.GetArmory().WeaponCount(weapon_type);

    result.emplace_back(times_used, max_available);
  }

  return result;
}

template<typename Context>
std::pair<size_t, size_t> SquadModificationScreen<Context>::CalculateSoldierArmorUsage() {
  std::vector<std::pair<size_t, size_t>> result;
  size_t times_used = 0;
  for (size_t soldier = 0; soldier < soldier_count_; ++soldier) {
    if (soldiers_widgets_[soldier]->Armor()) {
      ++times_used;
    }
  }

  size_t max_available = model_.GetArmory().ArmorCount(soldier_armor_type_);

  return {times_used, max_available};
}

template<typename Context>
std::vector<std::pair<size_t, size_t>> SquadModificationScreen<Context>::CalculateDroneWeaponUsage() {
  std::vector<std::pair<size_t, size_t>> result;
  for (WeaponType weapon_type : drone_weapon_types_) {
    size_t times_used = 0;
    for (size_t drone = 0; drone < drone_count_; ++drone) {
      if (drones_widgets_[drone]->Weapon() == kWeaponInfo[weapon_type].class_type) {
        ++times_used;
      }
    }

    size_t max_available = model_.GetArmory().WeaponCount(weapon_type);

    result.emplace_back(times_used, max_available);
  }

  return result;
}

template<typename Context>
std::pair<size_t, size_t> SquadModificationScreen<Context>::CalculateDroneArmorUsage() {
  size_t times_used = 0;
  for (size_t drone = 0; drone < drone_count_; ++drone) {
    if (drones_widgets_[drone]->Armor()) {
      ++times_used;
    }
  }

  size_t max_available = model_.GetArmory().ArmorCount(drone_armor_type_);

  return {times_used, max_available};
}

}
