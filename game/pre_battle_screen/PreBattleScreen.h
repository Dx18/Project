#pragma once

#include "unit/soldier/SoldierBuilder.h"
#include "unit/drone/DroneBuilder.h"
#include "headquarters_model/HeadquartersModel.h"
#include "config/GameConfig.h"
#include "game/IScreen.h"
#include "widget/WidgetSystem.h"
#include "widget/TextWidget.h"
#include "widget/SelectionListWidget.h"
#include "widget/GridContainerWidget.h"

namespace game::pre_battle_screen {

using namespace headquarters_model;
using namespace object_database;

/** Main menu screen. */
template<typename RenderContext>
class PreBattleScreen : public game::IScreen<RenderContext> {
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
  explicit PreBattleScreen(const config::GameConfig &game_config, const HeadquartersModel &model);

  std::optional<Action> Update(std::chrono::microseconds delta) override;
  Widget &Render(std::chrono::microseconds delta) override;
  std::optional<Action> OnInput(const frontend::InputEvent &event) override;

 private:
  /** Screen mode. */
  enum Mode {
    kUnitSelection,
    kSoldierActionSelection,
    kSettingSoldierPrimaryWeapon,
    kSettingSoldierSecondaryWeapon,
    kSettingSoldierArmor,
    kDroneActionSelection,
    kSettingDroneWeapon,
    kSettingDroneArmor
  };

  struct SoldierParameters {
    std::optional<WeaponType> primary_weapon;
    std::optional<WeaponType> secondary_weapon;
    std::optional<ArmorType> armor;

    SoldierParameters();
  };

  struct DroneParameters {
    std::optional<WeaponType> weapon;
    std::optional<ArmorType> armor;

    DroneParameters();
  };

  /** Const reference to game config. */
  const config::GameConfig &game_config_;
  /** Headquarters model. */
  const HeadquartersModel &model_;
  /** Current state of units. */
  std::vector<std::variant<SoldierParameters, DroneParameters>> slots_builders_;
  /** Amount of each weapon left. */
  std::array<size_t, kWeaponInfo.size()> weapon_left_;
  /** Amount of each armor left. */
  std::array<size_t, kArmorInfo.size()> armor_left_;
  /** Widget system. */
  WidgetSystem widget_system_;
  /** Root container. */
  GridContainerWidgetPtr main_container_;
  /** Container for unit slots. */
  GridContainerWidgetPtr slots_container_;
  /** Text widgets with information about slots. */
  std::vector<TextWidgetPtr> slots_data_;
  /** Message to user. */
  TextWidgetPtr message_;
  /** Current list. Meaning of it depends on current mode. */
  SelectionListWidgetPtr current_selection_list_;
  /** Action to perform on Enter key pressed. */
  std::function<void()> action_;
  /** Current mode. */
  Mode current_mode_;

  /** Initializes user interface. */
  void InitUI();
  /** Initializes unit slots. */
  void InitSlotsUI();
  /** Updates unit slot information. */
  void UpdateSlotUI(size_t slot);

  void SwitchToUnitSelectionMode();
  void SwitchToSoldierActionSelectionMode(size_t index);
  void SwitchToSettingSoldierPrimaryWeaponMode(size_t index);
  void SwitchToSettingSoldierSecondaryWeaponMode(size_t index);
  void SwitchToSettingSoldierArmorMode(size_t index);
  void SwitchToDroneActionSelectionMode(size_t index);
  void SwitchToSettingDroneWeaponMode(size_t index);
  void SwitchToSettingDroneArmorMode(size_t index);

  void InitUnitSelectionUI();
  void InitSoldierActionSelectionUI();
  void InitSettingSoldierWeaponUI();
  void InitSettingSoldierArmorUI();
  void InitDroneActionSelectionUI();
  void InitSettingDroneWeaponUI();
  void InitSettingDroneArmorUI();

  void OnUnitSelection(size_t index);
  void OnSoldierActionSelection(size_t index, size_t action);
  void OnSoldierPrimaryWeaponSelection(size_t index, size_t weapon_index);
  void OnSoldierSecondaryWeaponSelection(size_t index, size_t weapon_index);
  void OnSoldierArmorSelection(size_t index, size_t armor_index);
  void OnDroneActionSelection(size_t index, size_t action);
  void OnDroneWeaponSelection(size_t index, size_t weapon_index);
  void OnDroneArmorSelection(size_t index, size_t armor_index);

};

template<typename RenderContext>
PreBattleScreen<RenderContext>::SoldierParameters::SoldierParameters()
    :primary_weapon(), secondary_weapon(), armor() {

}

template<typename RenderContext>
PreBattleScreen<RenderContext>::DroneParameters::DroneParameters()
    :weapon(), armor() {

}

template<typename RenderContext>
PreBattleScreen<RenderContext>::PreBattleScreen(const config::GameConfig &game_config, const HeadquartersModel &model)
    : game_config_(game_config), model_(model),
      slots_builders_(game_config.SquadSize(), SoldierParameters()),
      weapon_left_(), armor_left_(),
      widget_system_(),
      current_mode_(Mode::kUnitSelection),
      action_([]() {}) {
  for (const WeaponInfo &info : kWeaponInfo) {
    weapon_left_[info.type] = model_.GetArmory().WeaponCount(info.type);
  }
  for (const ArmorInfo &info : kArmorInfo) {
    armor_left_[info.type] = model_.GetArmory().ArmorCount(info.type);
  }
  InitUI();
}

template<typename RenderContext>
std::optional<typename IScreen<RenderContext>::Action>
PreBattleScreen<RenderContext>::Update(std::chrono::microseconds delta) {
  return {};
}

template<typename RenderContext>
typename PreBattleScreen<RenderContext>::Widget &
PreBattleScreen<RenderContext>::Render(std::chrono::microseconds delta) {
  return widget_system_.Root();
}

template<typename RenderContext>
std::optional<typename IScreen<RenderContext>::Action>
PreBattleScreen<RenderContext>::OnInput(const frontend::InputEvent &event) {
  if (widget_system_.HandleInput(event.input)) {
    return {};
  }

  if (event.input.IsKey()) {
    if (event.input.GetKey() == frontend::Key::kEscape) {
      return PopScreenAction{};
    } else if (event.input.GetKey() == frontend::Key::kEnter) {
      action_();
    }
  }

  return {};
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::InitUI() {
  main_container_ = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{1, 4});
  main_container_->SetRenderSeparators(true);

  InitSlotsUI();

  message_ = std::make_shared<TextWidget>("");
  message_->SetPreferExpand(util::Vector2<bool>{true, false});
  main_container_->Set({0, 2}, message_);

  TextWidgetPtr hint = std::make_shared<TextWidget>("ENTER: Select");
  hint->SetPreferExpand(util::Vector2<bool>{true, false});
  main_container_->Set({0, 3}, hint);

  widget_system_.SetRoot(main_container_);

  SwitchToUnitSelectionMode();
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::InitSlotsUI() {
  slots_container_ = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{slots_builders_.size(), 1});
  slots_container_->SetRenderSeparators(true);

  slots_data_.resize(slots_builders_.size());

  for (size_t i = 0; i < slots_builders_.size(); ++i) {
    slots_data_[i] = std::make_shared<TextWidget>("");
    slots_data_[i]->SetPreferExpand(util::Vector2<bool>{true, false});
    slots_container_->Set({i, 0}, slots_data_[i]);
    UpdateSlotUI(i);
  }

  main_container_->Set({0, 0}, slots_container_);
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::UpdateSlotUI(size_t slot) {
  std::stringstream text;
  if (std::holds_alternative<SoldierParameters>(slots_builders_[slot])) {
    const SoldierParameters &unit = std::get<SoldierParameters>(slots_builders_[slot]);

    text << "Soldier\n"
         << "Primary weapon: " << (unit.primary_weapon.has_value()
                                   ? kWeaponInfo[unit.primary_weapon.value()].name
                                   : "none") << "\n"
         << "Secondary weapon: " << (unit.secondary_weapon.has_value()
                                     ? kWeaponInfo[unit.secondary_weapon.value()].name
                                     : "none") << "\n"
         << "Armor: " << (unit.armor.has_value()
                          ? kArmorInfo[unit.armor.value()].name
                          : "none");
  } else if (std::holds_alternative<DroneParameters>(slots_builders_[slot])) {
    const DroneParameters &unit = std::get<DroneParameters>(slots_builders_[slot]);

    text << "Drone\n"
         << "Weapon: " << (unit.weapon.has_value()
                           ? kWeaponInfo[unit.weapon.value()].name
                           : "none") << "\n"
         << "Armor: " << (unit.armor.has_value()
                          ? kArmorInfo[unit.armor.value()].name
                          : "none");
  }

  slots_data_[slot]->SetText(text.str());
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::InitUnitSelectionUI() {
  std::vector<std::string> slot_names;
  for (size_t i = 0; i < slots_builders_.size(); ++i) {
    std::stringstream name;
    name << "Slot " << i + 1;
    slot_names.push_back(name.str());
  }
  current_selection_list_ = std::make_shared<SelectionListWidget>(slot_names);
  current_selection_list_->SetPreferExpand(util::Vector2<bool>{true, true});
  widget_system_.ResetFocus();
  main_container_->Set({0, 1}, current_selection_list_);
  widget_system_.SetFocused(current_selection_list_);
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::InitSoldierActionSelectionUI() {
  current_selection_list_ = std::make_shared<SelectionListWidget>(std::vector<std::string>{
      "Assign primary weapon",
      "Assign secondary weapon",
      "Assign armor"
  });
  current_selection_list_->SetPreferExpand(util::Vector2<bool>{true, true});
  widget_system_.ResetFocus();
  main_container_->Set({0, 1}, current_selection_list_);
  widget_system_.SetFocused(current_selection_list_);
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::InitSettingSoldierWeaponUI() {
  std::vector<std::string> weapon_names;
  weapon_names.emplace_back("No weapon");
  for (const WeaponType &type : {
      WeaponType::kSoldierFirearmPistol, WeaponType::kSoldierFirearmShotgun,
      WeaponType::kSoldierFirearmSniperRifle, WeaponType::kSoldierFirearmMachineGun,
      WeaponType::kSoldierLaserPistol, WeaponType::kSoldierLaserShotgun,
      WeaponType::kSoldierLaserSniperRifle, WeaponType::kSoldierLaserMachineGun,
  }) {
    if (weapon_left_[type] > 0) {
      weapon_names.emplace_back(kWeaponInfo[type].name);
    }
  }
  current_selection_list_ = std::make_shared<SelectionListWidget>(weapon_names);
  current_selection_list_->SetPreferExpand(util::Vector2<bool>{true, true});
  widget_system_.ResetFocus();
  main_container_->Set({0, 1}, current_selection_list_);
  widget_system_.SetFocused(current_selection_list_);
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::InitSettingSoldierArmorUI() {
  std::vector<std::string> armor_names;
  armor_names.emplace_back("No armor");
  for (const ArmorType &type : {
      ArmorType::kSoldierStandardArmor, ArmorType::kSoldierCompositeArmor
  }) {
    if (armor_left_[type] > 0) {
      armor_names.emplace_back(kArmorInfo[type].name);
    }
  }
  current_selection_list_ = std::make_shared<SelectionListWidget>(armor_names);
  current_selection_list_->SetPreferExpand(util::Vector2<bool>{true, true});
  widget_system_.ResetFocus();
  main_container_->Set({0, 1}, current_selection_list_);
  widget_system_.SetFocused(current_selection_list_);
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::InitDroneActionSelectionUI() {
  current_selection_list_ = std::make_shared<SelectionListWidget>(std::vector<std::string>{
      "Assign weapon",
      "Assign armor"
  });
  current_selection_list_->SetPreferExpand(util::Vector2<bool>{true, true});
  widget_system_.ResetFocus();
  main_container_->Set({0, 1}, current_selection_list_);
  widget_system_.SetFocused(current_selection_list_);
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::InitSettingDroneWeaponUI() {
  std::vector<std::string> weapon_names;
  weapon_names.emplace_back("No weapon");
  for (const WeaponType &type : {
      WeaponType::kDroneFirearmMachineGun, WeaponType::kDroneLaserMachineGun,
  }) {
    if (weapon_left_[type] > 0) {
      weapon_names.emplace_back(kWeaponInfo[type].name);
    }
  }
  current_selection_list_ = std::make_shared<SelectionListWidget>(weapon_names);
  current_selection_list_->SetPreferExpand(util::Vector2<bool>{true, true});
  widget_system_.ResetFocus();
  main_container_->Set({0, 1}, current_selection_list_);
  widget_system_.SetFocused(current_selection_list_);
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::InitSettingDroneArmorUI() {
  std::vector<std::string> armor_names;
  armor_names.emplace_back("No armor");
  for (const ArmorType &type : {
      ArmorType::kDroneStandardArmor
  }) {
    if (armor_left_[type] > 0) {
      armor_names.emplace_back(kArmorInfo[type].name);
    }
  }
  current_selection_list_ = std::make_shared<SelectionListWidget>(armor_names);
  current_selection_list_->SetPreferExpand(util::Vector2<bool>{true, true});
  widget_system_.ResetFocus();
  main_container_->Set({0, 1}, current_selection_list_);
  widget_system_.SetFocused(current_selection_list_);
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::OnUnitSelection(size_t index) {
  if (std::holds_alternative<SoldierParameters>(slots_builders_[index])) {
    SwitchToSoldierActionSelectionMode(index);
  } else if (std::holds_alternative<DroneParameters>(slots_builders_[index])) {
    SwitchToDroneActionSelectionMode(index);
  }
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::OnSoldierActionSelection(size_t index, size_t action) {
  static const size_t kAssignPrimaryWeapon = 0;
  static const size_t kAssignSecondaryWeapon = 1;
  static const size_t kAssignArmor = 2;

  if (action == kAssignPrimaryWeapon) {
    SwitchToSettingSoldierPrimaryWeaponMode(index);
  } else if (action == kAssignSecondaryWeapon) {
    SwitchToSettingSoldierSecondaryWeaponMode(index);
  } else if (action == kAssignArmor) {
    SwitchToSettingSoldierArmorMode(index);
  }
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::OnSoldierPrimaryWeaponSelection(size_t index, size_t weapon_index) {
  static const WeaponType kSoldierWeaponType[] = {
      WeaponType::kSoldierFirearmPistol, WeaponType::kSoldierFirearmShotgun,
      WeaponType::kSoldierFirearmSniperRifle, WeaponType::kSoldierFirearmMachineGun,
      WeaponType::kSoldierLaserPistol, WeaponType::kSoldierLaserShotgun,
      WeaponType::kSoldierLaserSniperRifle, WeaponType::kSoldierLaserMachineGun,
  };

  SoldierParameters &unit = std::get<SoldierParameters>(slots_builders_[index]);

  if (unit.primary_weapon.has_value()) {
    ++weapon_left_[unit.primary_weapon.value()];
  }

  if (weapon_index == 0) {
    unit.primary_weapon = {};
  } else {
    unit.primary_weapon = kSoldierWeaponType[weapon_index - 1];
    --weapon_left_[unit.primary_weapon.value()];
  }

  SwitchToUnitSelectionMode();
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::OnSoldierSecondaryWeaponSelection(size_t index, size_t weapon_index) {
  static const WeaponType kSoldierWeaponType[] = {
      WeaponType::kSoldierFirearmPistol, WeaponType::kSoldierFirearmShotgun,
      WeaponType::kSoldierFirearmSniperRifle, WeaponType::kSoldierFirearmMachineGun,
      WeaponType::kSoldierLaserPistol, WeaponType::kSoldierLaserShotgun,
      WeaponType::kSoldierLaserSniperRifle, WeaponType::kSoldierLaserMachineGun,
  };

  SoldierParameters &unit = std::get<SoldierParameters>(slots_builders_[index]);

  if (unit.secondary_weapon.has_value()) {
    ++weapon_left_[unit.secondary_weapon.value()];
  }

  if (weapon_index == 0) {
    unit.secondary_weapon = {};
  } else {
    unit.secondary_weapon = kSoldierWeaponType[weapon_index - 1];
    --weapon_left_[unit.secondary_weapon.value()];
  }

  SwitchToUnitSelectionMode();
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::OnSoldierArmorSelection(size_t index, size_t armor_index) {
  static const ArmorType kSoldierArmorType[] = {
      ArmorType::kSoldierStandardArmor, ArmorType::kSoldierCompositeArmor
  };

  SoldierParameters &unit = std::get<SoldierParameters>(slots_builders_[index]);

  if (unit.armor.has_value()) {
    ++armor_left_[unit.armor.value()];
  }

  if (armor_index == 0) {
    unit.armor = {};
  } else {
    unit.armor = kSoldierArmorType[armor_index - 1];
    --armor_left_[unit.armor.value()];
  }

  SwitchToUnitSelectionMode();
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::OnDroneActionSelection(size_t index, size_t action) {
  static const size_t kAssignWeapon = 0;
  static const size_t kAssignArmor = 1;

  if (action == kAssignWeapon) {
    SwitchToSettingDroneWeaponMode(index);
  } else if (action == kAssignArmor) {
    SwitchToSettingDroneArmorMode(index);
  }
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::OnDroneWeaponSelection(size_t index, size_t weapon_index) {
  static const WeaponType kDroneWeaponType[] = {
      WeaponType::kDroneFirearmMachineGun, WeaponType::kDroneLaserMachineGun,
  };

  DroneParameters &unit = std::get<DroneParameters>(slots_builders_[index]);

  if (unit.weapon.has_value()) {
    ++weapon_left_[unit.weapon.value()];
  }

  if (weapon_index == 0) {
    unit.weapon = {};
  } else {
    unit.weapon = kDroneWeaponType[weapon_index - 1];
    --weapon_left_[unit.weapon.value()];
  }

  SwitchToUnitSelectionMode();
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::OnDroneArmorSelection(size_t index, size_t armor_index) {
  static const ArmorType kDroneArmorType[] = {
      ArmorType::kDroneStandardArmor
  };

  DroneParameters &unit = std::get<DroneParameters>(slots_builders_[index]);

  if (unit.armor.has_value()) {
    ++armor_left_[unit.armor.value()];
  }

  if (armor_index == 0) {
    unit.armor = {};
  } else {
    unit.armor = kDroneArmorType[armor_index - 1];
    --armor_left_[unit.armor.value()];
  }

  SwitchToUnitSelectionMode();
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::SwitchToUnitSelectionMode() {
  InitUnitSelectionUI();
  action_ = [this]() {
    OnUnitSelection(current_selection_list_->SelectedItem());
  };
  current_mode_ = Mode::kUnitSelection;
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::SwitchToSoldierActionSelectionMode(size_t index) {
  InitSoldierActionSelectionUI();
  action_ = [this, index]() {
    OnSoldierActionSelection(index, current_selection_list_->SelectedItem());
  };
  current_mode_ = Mode::kSoldierActionSelection;
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::SwitchToSettingSoldierPrimaryWeaponMode(size_t index) {
  InitSettingSoldierWeaponUI();
  action_ = [this, index]() {
    OnSoldierPrimaryWeaponSelection(index, current_selection_list_->SelectedItem());
  };
  current_mode_ = Mode::kSettingSoldierPrimaryWeapon;
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::SwitchToSettingSoldierSecondaryWeaponMode(size_t index) {
  InitSettingSoldierWeaponUI();
  action_ = [this, index]() {
    OnSoldierSecondaryWeaponSelection(index, current_selection_list_->SelectedItem());
  };
  current_mode_ = Mode::kSettingSoldierSecondaryWeapon;
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::SwitchToSettingSoldierArmorMode(size_t index) {
  InitSettingSoldierArmorUI();
  action_ = [this, index]() {
    OnSoldierArmorSelection(index, current_selection_list_->SelectedItem());
  };
  current_mode_ = Mode::kSettingSoldierArmor;
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::SwitchToDroneActionSelectionMode(size_t index) {
  InitDroneActionSelectionUI();
  action_ = [this, index]() {
    OnDroneActionSelection(index, current_selection_list_->SelectedItem());
  };
  current_mode_ = Mode::kDroneActionSelection;
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::SwitchToSettingDroneWeaponMode(size_t index) {
  InitSettingDroneWeaponUI();
  action_ = [this, index]() {
    OnDroneWeaponSelection(index, current_selection_list_->SelectedItem());
  };
  current_mode_ = Mode::kSettingDroneWeapon;
}

template<typename RenderContext>
void PreBattleScreen<RenderContext>::SwitchToSettingDroneArmorMode(size_t index) {
  InitSettingDroneArmorUI();
  action_ = [this, index]() {
    OnDroneArmorSelection(index, current_selection_list_->SelectedItem());
  };
  current_mode_ = Mode::kSettingDroneArmor;
}

}
