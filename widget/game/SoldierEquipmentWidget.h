#pragma once

#include <optional>
#include <algorithm>

#include "widget/Widget.h"
#include "object_database/WeaponClassInfo.h"

namespace widget::game {

using namespace object_database;

/**
 * Widget for equipping soldier.
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class SoldierEquipmentWidget : public Widget<Context> {
 private:
  using PrimaryWeaponChangedListener = std::function<void(SoldierEquipmentWidget &)>;
  using SecondaryWeaponChangedListener = std::function<void(SoldierEquipmentWidget &)>;
  using ArmorChangedListener = std::function<void(SoldierEquipmentWidget &)>;

 public:
  /**
   * Creates soldier equipment widget.
   * @param primary_weapon Initial value of primary weapon.
   * @param secondary_weapon Initial value of secondary weapon.
   * @param armor True if armor is initially used.
   */
  SoldierEquipmentWidget(std::optional<WeaponClassType> primary_weapon,
                         std::optional<WeaponClassType> secondary_weapon,
                         bool armor);

  /** Returns current primary weapon. */
  [[nodiscard]] std::optional<WeaponClassType> PrimaryWeapon() const;
  /** Returns current secondary weapon. */
  [[nodiscard]] std::optional<WeaponClassType> SecondaryWeapon() const;
  /** Returns current armor. */
  [[nodiscard]] bool Armor() const;

  [[nodiscard]] util::Vector2<size_t> MinSize(typename Context::Resources &resources) const override;
  void Render(typename Context::RenderContext &context, typename Context::Resources &resources) override;
  bool HandleInput(const frontend::Input &input) override;

  /**
   * Adds listener for primary weapon change event.
   * @param listener Listener.
   */
  void AddPrimaryWeaponChangedListener(PrimaryWeaponChangedListener listener);
  /**
   * Adds listener for secondary weapon change event.
   * @param listener Listener.
   */
  void AddSecondaryWeaponChangedListener(SecondaryWeaponChangedListener listener);
  /**
   * Adds listener for armor change event.
   * @param listener Listener.
   */
  void AddArmorChangedListener(ArmorChangedListener listener);

 private:
  /** Index of primary weapon parameter. */
  static const size_t kPrimaryWeaponParameterIndex = 0;
  /** Index of secondary weapon parameter. */
  static const size_t kSecondaryWeaponParameterIndex = 1;
  /** Index of armor parameter. */
  static const size_t kArmorParameterIndex = 2;
  /** Number of parameters. Possible parameters: primary weapon, secondary weapon, armor. */
  static const size_t kParameterCount = 3;

  /** Available class of weapons for soldier. */
  static const std::array<WeaponClassType, 4> kAvailableWeaponClasses;

  /** Current selected parameter. */
  size_t current_parameter_;

  /** Current value of primary weapon. */
  std::optional<WeaponClassType> primary_weapon_;
  /** Current value of secondary weapon. */
  std::optional<WeaponClassType> secondary_weapon_;
  /** Current value of armor: should armor be used or not. */
  bool armor_;

  /** Listeners for primary weapon change event. */
  std::vector<PrimaryWeaponChangedListener> primary_weapon_changed_;
  /** Listeners for secondary weapon change event. */
  std::vector<SecondaryWeaponChangedListener> secondary_weapon_changed_;
  /** Listeners for armor change event. */
  std::vector<ArmorChangedListener> armor_changed_;

  /**
   * Switches current parameter. Direction depends on given parameter. Parameters are cycled.
   * @param to_next True if moving to the next parameter is requested. Otherwise false.
   */
  void SwitchParameter(bool to_next);

  /**
   * Returns weapon class going after given one.
   * @param weapon Given weapon class.
   */
  [[nodiscard]] std::optional<WeaponClassType> NextWeapon(std::optional<WeaponClassType> weapon) const;
  /**
   * Returns weapon class going before given one.
   * @param weapon Given weapon class.
   */
  [[nodiscard]] std::optional<WeaponClassType> PreviousWeapon(std::optional<WeaponClassType> weapon) const;

  /**
   * Switches value of current selected parameter.
   * @param to_next Direction to switch.
   */
  void SwitchParameterValue(bool to_next);
  /**
   * Switches value of primary weapon. Triggers primary weapon change event.
   * @param to_next Direction to switch.
   */
  void SwitchPrimaryWeapon(bool to_next);
  /**
   * Switches value of secondary weapon. Triggers secondary weapon change event.
   * @param to_next Direction to switch.
   */
  void SwitchSecondaryWeapon(bool to_next);
  /** Switches current use of armor. Triggers armor change event. */
  void SwitchArmor();

  /** Triggers primary weapon change event. */
  void TriggerPrimaryWeaponChanged();
  /** Triggers secondary weapon changed event. */
  void TriggerSecondaryWeaponChanged();
  /** Triggers armor changed event. */
  void TriggerArmorChanged();

};

template<typename Context>
const std::array<WeaponClassType, 4> SoldierEquipmentWidget<Context>::kAvailableWeaponClasses = {
    WeaponClassType::kPistol,
    WeaponClassType::kShotgun,
    WeaponClassType::kSniperRifle,
    WeaponClassType::kMachineGun
};

template<typename Context>
SoldierEquipmentWidget<Context>::SoldierEquipmentWidget(std::optional<WeaponClassType> primary_weapon,
                                                        std::optional<WeaponClassType> secondary_weapon,
                                                        bool armor)
    : primary_weapon_(primary_weapon), secondary_weapon_(secondary_weapon), armor_(armor),
      current_parameter_(0) {

}

template<typename Context>
std::optional<WeaponClassType> SoldierEquipmentWidget<Context>::PrimaryWeapon() const {
  return primary_weapon_;
}

template<typename Context>
std::optional<WeaponClassType> SoldierEquipmentWidget<Context>::SecondaryWeapon() const {
  return secondary_weapon_;
}

template<typename Context>
bool SoldierEquipmentWidget<Context>::Armor() const {
  return armor_;
}

template<typename Context>
bool SoldierEquipmentWidget<Context>::HandleInput(const frontend::Input &input) {
  if (input.IsKey()) {
    if (input.GetKey() == frontend::Key::kLeft) {
      SwitchParameter(false);
    } else if (input.GetKey() == frontend::Key::kRight) {
      SwitchParameter(true);
    } else if (input.GetKey() == frontend::Key::kUp) {
      SwitchParameterValue(false);
    } else if (input.GetKey() == frontend::Key::kDown) {
      SwitchParameterValue(true);
    }
  }
  return false;
}

template<typename Context>
void SoldierEquipmentWidget<Context>::
AddPrimaryWeaponChangedListener(SoldierEquipmentWidget::PrimaryWeaponChangedListener listener) {
  primary_weapon_changed_.push_back(listener);
}

template<typename Context>
void SoldierEquipmentWidget<Context>::
AddSecondaryWeaponChangedListener(SoldierEquipmentWidget::SecondaryWeaponChangedListener listener) {
  secondary_weapon_changed_.push_back(listener);
}

template<typename Context>
void SoldierEquipmentWidget<Context>::
AddArmorChangedListener(SoldierEquipmentWidget::ArmorChangedListener listener) {
  armor_changed_.push_back(listener);
}

template<typename Context>
void SoldierEquipmentWidget<Context>::SwitchParameter(bool to_next) {
  current_parameter_ = (kParameterCount + current_parameter_ + (to_next ? 1 : -1)) % kParameterCount;
}

template<typename Context>
std::optional<WeaponClassType>
SoldierEquipmentWidget<Context>::NextWeapon(std::optional<WeaponClassType> weapon) const {
  if (!weapon.has_value()) {
    return kAvailableWeaponClasses.front();
  }

  size_t index = std::find(kAvailableWeaponClasses.begin(), kAvailableWeaponClasses.end(), weapon.value())
      - kAvailableWeaponClasses.begin();
  if (index < kAvailableWeaponClasses.size() - 1) {
    return kAvailableWeaponClasses[index + 1];
  }
  return {};
}

template<typename Context>
std::optional<WeaponClassType>
SoldierEquipmentWidget<Context>::PreviousWeapon(std::optional<WeaponClassType> weapon) const {
  if (!weapon.has_value()) {
    return kAvailableWeaponClasses.back();
  }

  size_t index = std::find(kAvailableWeaponClasses.begin(), kAvailableWeaponClasses.end(), weapon.value())
      - kAvailableWeaponClasses.begin();
  if (index > 0) {
    return kAvailableWeaponClasses[index - 1];
  }
  return {};
}

template<typename Context>
void SoldierEquipmentWidget<Context>::SwitchParameterValue(bool to_next) {
  if (current_parameter_ == kPrimaryWeaponParameterIndex) {
    SwitchPrimaryWeapon(to_next);
  } else if (current_parameter_ == kSecondaryWeaponParameterIndex) {
    SwitchSecondaryWeapon(to_next);
  } else if (current_parameter_ == kArmorParameterIndex) {
    SwitchArmor();
  }
}

template<typename Context>
void SoldierEquipmentWidget<Context>::SwitchPrimaryWeapon(bool to_next) {
  primary_weapon_ = to_next ? NextWeapon(primary_weapon_) : PreviousWeapon(primary_weapon_);
  TriggerPrimaryWeaponChanged();
}

template<typename Context>
void SoldierEquipmentWidget<Context>::SwitchSecondaryWeapon(bool to_next) {
  secondary_weapon_ = to_next ? NextWeapon(secondary_weapon_) : PreviousWeapon(secondary_weapon_);
  TriggerSecondaryWeaponChanged();
}

template<typename Context>
void SoldierEquipmentWidget<Context>::SwitchArmor() {
  armor_ = !armor_;
  TriggerArmorChanged();
}

template<typename Context>
void SoldierEquipmentWidget<Context>::TriggerPrimaryWeaponChanged() {
  for (auto &listener : primary_weapon_changed_) {
    listener(*this);
  }
}

template<typename Context>
void SoldierEquipmentWidget<Context>::TriggerSecondaryWeaponChanged() {
  for (auto &listener : secondary_weapon_changed_) {
    listener(*this);
  }
}

template<typename Context>
void SoldierEquipmentWidget<Context>::TriggerArmorChanged() {
  for (auto &listener : armor_changed_) {
    listener(*this);
  }
}

}
