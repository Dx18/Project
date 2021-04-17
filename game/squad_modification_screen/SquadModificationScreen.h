#pragma once

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

namespace game::squad_modification_screen {

using namespace object_database;

/**
 * Screen used to modify squad and start battle.
 * @tparam RenderContext Context used to render widgets.
 */
template<typename RenderContext>
class SquadModificationScreen : public IScreen<RenderContext> {
 private:
  using Action = typename game::IScreen<RenderContext>::Action;
  using PushScreenAction = typename game::IScreen<RenderContext>::PushScreenAction;
  using PopScreenAction = typename game::IScreen<RenderContext>::PopScreenAction;
  using QuitAction = typename game::IScreen<RenderContext>::QuitAction;

  using Widget = widget::Widget<RenderContext>;
  using GridContainerWidget = widget::GridContainerWidget<RenderContext>;
  using TextWidget = widget::TextWidget<RenderContext>;
  using SelectionWidget = widget::SelectionWidget<RenderContext>;
  using SelectionListWidget = widget::SelectionListWidget<RenderContext>;
  using SelectionBoxWidget = widget::SelectionListWidget<RenderContext>;
  using SoldierEquipmentWidget = widget::game::SoldierEquipmentWidget<RenderContext>;
  using DroneEquipmentWidget = widget::game::DroneEquipmentWidget<RenderContext>;

  using WidgetPtr = std::shared_ptr<Widget>;
  using GridContainerWidgetPtr = std::shared_ptr<GridContainerWidget>;
  using TextWidgetPtr = std::shared_ptr<TextWidget>;
  using SelectionListWidgetPtr = std::shared_ptr<SelectionListWidget>;
  using SelectionBoxWidgetPtr = std::shared_ptr<SelectionBoxWidget>;
  using SoldierEquipmentWidgetPtr = std::shared_ptr<SoldierEquipmentWidget>;
  using DroneEquipmentWidgetPtr = std::shared_ptr<DroneEquipmentWidget>;

  using WidgetSystem = widget::WidgetSystem<RenderContext>;

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
  SquadModificationScreen(const headquarters_model::HeadquartersModel &model,
                          size_t soldier_count, size_t drone_count,
                          WeaponTechType soldier_weapon_tech_type,
                          ArmorTechType soldier_armor_tech_type,
                          WeaponTechType drone_weapon_tech_type,
                          ArmorTechType drone_armor_tech_type);

  std::optional<Action> Update(std::chrono::microseconds delta) override;
  Widget &Render(std::chrono::microseconds delta) override;
  std::optional<Action> OnInput(const frontend::InputEvent &event) override;

 private:
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
  std::unique_ptr<unit::soldier::ISoldierWeaponFactory> soldier_weapon_factory_;
  /** Soldier armor factory. */
  std::unique_ptr<unit::soldier::ISoldierArmorFactory> soldier_armor_factory_;
  /** Drone weapon factory. */
  std::unique_ptr<unit::drone::IDroneWeaponFactory> drone_weapon_factory_;
  /** Drone armor factory. */
  std::unique_ptr<unit::drone::IDroneArmorFactory> drone_armor_factory_;

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

};

template<typename RenderContext>
SquadModificationScreen<RenderContext>::
SquadModificationScreen(const headquarters_model::HeadquartersModel &model,
                        size_t soldier_count, size_t drone_count,
                        WeaponTechType soldier_weapon_tech_type,
                        ArmorTechType soldier_armor_tech_type,
                        WeaponTechType drone_weapon_tech_type,
                        ArmorTechType drone_armor_tech_type)
    : model_(model), soldier_count_(soldier_count), drone_count_(drone_count),
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

template<typename RenderContext>
std::optional<typename IScreen<RenderContext>::Action>
SquadModificationScreen<RenderContext>::Update(std::chrono::microseconds delta) {
  return {};
}

template<typename RenderContext>
widget::Widget<RenderContext> &SquadModificationScreen<RenderContext>::Render(std::chrono::microseconds delta) {
  return widget_system_.Root();
}

template<typename RenderContext>
std::optional<typename IScreen<RenderContext>::Action>
SquadModificationScreen<RenderContext>::OnInput(const frontend::InputEvent &event) {
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
    }
  }
  return {};
}

template<typename RenderContext>
void SquadModificationScreen<RenderContext>::InitUI() {
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

template<typename RenderContext>
void SquadModificationScreen<RenderContext>::SwitchUnit(bool to_next) {
  SwitchToUnit((soldier_count_ + drone_count_ + current_unit_ + (to_next ? 1 : -1))
                   % (soldier_count_ + drone_count_));
}

template<typename RenderContext>
void SquadModificationScreen<RenderContext>::SwitchToUnit(size_t index) {
  if (index < soldier_count_) {
    SwitchToSoldier(index);
  } else if (index < soldier_count_ + drone_count_) {
    SwitchToDrone(index - soldier_count_);
  }
  current_unit_ = index;
}

template<typename RenderContext>
void SquadModificationScreen<RenderContext>::SwitchToSoldier(size_t index) {
  std::stringstream name;
  name << "Soldier " << index + 1;
  title_text_->SetText(name.str());

  main_container_->Set(util::Vector2<size_t>{0, 1}, soldiers_widgets_[index]);
  widget_system_.SetFocused(soldiers_widgets_[index]);
}

template<typename RenderContext>
void SquadModificationScreen<RenderContext>::SwitchToDrone(size_t index) {
  std::stringstream name;
  name << "Drone " << index + 1;
  title_text_->SetText(name.str());

  main_container_->Set(util::Vector2<size_t>{0, 1}, drones_widgets_[index]);
  widget_system_.SetFocused(drones_widgets_[index]);
}

template<typename RenderContext>
void SquadModificationScreen<RenderContext>::UpdateInfoText() {
  std::stringstream message;
  message << "Armory usage (used / available):\n";
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

    message << kWeaponInfo[weapon_type].name << ": " << times_used << " / " << max_available;
    if (times_used > max_available) {
      message << " (!)";
    }
    message << "\n";
  }
  {
    size_t times_used = 0;
    for (size_t soldier = 0; soldier < soldier_count_; ++soldier) {
      if (soldiers_widgets_[soldier]->Armor()) {
        ++times_used;
      }
    }

    size_t max_available = model_.GetArmory().ArmorCount(soldier_armor_type_);

    message << kArmorInfo[soldier_armor_type_].name << ": " << times_used << " / " << max_available;
    if (times_used > max_available) {
      message << " (!)";
    }
    message << "\n";
  }
  for (WeaponType weapon_type : drone_weapon_types_) {
    size_t times_used = 0;
    for (size_t drone = 0; drone < drone_count_; ++drone) {
      if (drones_widgets_[drone]->Weapon() == kWeaponInfo[weapon_type].class_type) {
        ++times_used;
      }
    }

    size_t max_available = model_.GetArmory().WeaponCount(weapon_type);

    message << kWeaponInfo[weapon_type].name << ": " << times_used << " / " << max_available;
    if (times_used > max_available) {
      message << " (!)";
    }
    message << "\n";
  }
  {
    size_t times_used = 0;
    for (size_t drone = 0; drone < drone_count_; ++drone) {
      if (drones_widgets_[drone]->Armor()) {
        ++times_used;
      }
    }

    size_t max_available = model_.GetArmory().ArmorCount(drone_armor_type_);

    message << kArmorInfo[drone_armor_type_].name << ": " << times_used << " / " << max_available;
    if (times_used > max_available) {
      message << " (!)";
    }
    message << "\n";
  }

  info_text_->SetText(message.str());
}

}
