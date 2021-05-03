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
class DroneEquipmentWidget : public Widget<Context> {
 private:
  using WeaponChangedListener = std::function<void(DroneEquipmentWidget &)>;
  using ArmorChangedListener = std::function<void(DroneEquipmentWidget &)>;

 public:
  /**
   * Creates drone equipment widget.
   * @param weapon Initial value of weapon.
   * @param armor True if armor is initially used.
   */
  DroneEquipmentWidget(std::optional<WeaponClassType> weapon, bool armor);

  /** Returns current weapon. */
  [[nodiscard]] std::optional<WeaponClassType> Weapon() const;
  /** Returns current armor. */
  [[nodiscard]] bool Armor() const;

  [[nodiscard]] util::Vector2<size_t> MinSize(typename Context::Resources &resources) const override;
  void Render(typename Context::RenderContext &context, typename Context::Resources &resources) override;
  bool HandleInput(const frontend::Input &input) override;

  /**
   * Adds listener for weapon change event.
   * @param listener Listener.
   */
  void AddWeaponChangedListener(WeaponChangedListener listener);
  /**
   * Adds listener for armor change event.
   * @param listener Listener.
   */
  void AddArmorChangedListener(ArmorChangedListener listener);

 private:
  /** Index of weapon parameter. */
  static const size_t kWeaponParameterIndex = 0;
  /** Index of armor parameter. */
  static const size_t kArmorParameterIndex = 1;
  /** Number of parameters. Possible parameters: weapon, armor. */
  static const size_t kParameterCount = 2;

  /** Available class of weapons for drone. */
  static const std::array<WeaponClassType, 1> kAvailableWeaponClasses;

  /** Current selected parameter. */
  size_t current_parameter_;

  /** Current value of weapon. */
  std::optional<WeaponClassType> weapon_;
  /** Current value of armor: should armor be used or not. */
  bool armor_;

  /** Listeners for weapon change event. */
  std::vector<WeaponChangedListener> weapon_changed_;
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
   * Switches value of weapon. Triggers weapon change event.
   * @param to_next Direction to switch.
   */
  void SwitchWeapon(bool to_next);
  /** Switches current use of armor. Triggers armor change event. */
  void SwitchArmor();

  /** Triggers primary weapon change event. */
  void TriggerWeaponChanged();
  /** Triggers armor changed event. */
  void TriggerArmorChanged();

};

template<typename Context>
const std::array<WeaponClassType, 1> DroneEquipmentWidget<Context>::kAvailableWeaponClasses = {
    WeaponClassType::kMachineGun
};

template<typename Context>
DroneEquipmentWidget<Context>::DroneEquipmentWidget(std::optional<WeaponClassType> weapon, bool armor)
    : weapon_(weapon), armor_(armor), current_parameter_(0) {

}

template<typename Context>
std::optional<WeaponClassType> DroneEquipmentWidget<Context>::Weapon() const {
  return weapon_;
}

template<typename Context>
bool DroneEquipmentWidget<Context>::Armor() const {
  return armor_;
}

template<typename Context>
bool DroneEquipmentWidget<Context>::HandleInput(const frontend::Input &input) {
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
void DroneEquipmentWidget<Context>::
AddWeaponChangedListener(DroneEquipmentWidget::WeaponChangedListener listener) {
  weapon_changed_.push_back(listener);
}

template<typename Context>
void DroneEquipmentWidget<Context>::
AddArmorChangedListener(DroneEquipmentWidget::ArmorChangedListener listener) {
  armor_changed_.push_back(listener);
}

template<typename Context>
void DroneEquipmentWidget<Context>::SwitchParameter(bool to_next) {
  current_parameter_ = (kParameterCount + current_parameter_ + (to_next ? 1 : -1)) % kParameterCount;
}

template<typename Context>
std::optional<WeaponClassType>
DroneEquipmentWidget<Context>::NextWeapon(std::optional<WeaponClassType> weapon) const {
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
DroneEquipmentWidget<Context>::PreviousWeapon(std::optional<WeaponClassType> weapon) const {
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
void DroneEquipmentWidget<Context>::SwitchParameterValue(bool to_next) {
  if (current_parameter_ == kWeaponParameterIndex) {
    SwitchWeapon(to_next);
  } else if (current_parameter_ == kArmorParameterIndex) {
    SwitchArmor();
  }
}

template<typename Context>
void DroneEquipmentWidget<Context>::SwitchWeapon(bool to_next) {
  weapon_ = to_next ? NextWeapon(weapon_) : PreviousWeapon(weapon_);
  TriggerWeaponChanged();
}

template<typename Context>
void DroneEquipmentWidget<Context>::SwitchArmor() {
  armor_ = !armor_;
  TriggerArmorChanged();
}

template<typename Context>
void DroneEquipmentWidget<Context>::TriggerWeaponChanged() {
  for (auto &listener : weapon_changed_) {
    listener(*this);
  }
}

template<typename Context>
void DroneEquipmentWidget<Context>::TriggerArmorChanged() {
  for (auto &listener : armor_changed_) {
    listener(*this);
  }
}

}
