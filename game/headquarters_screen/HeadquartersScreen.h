#pragma once

#include "headquarters_model/HeadquartersModel.h"
#include "config/GameConfig.h"
#include "game/IScreen.h"
#include "widget/WidgetSystem.h"
#include "widget/TextWidget.h"
#include "widget/SelectionListWidget.h"
#include "widget/GridContainerWidget.h"

#include "game/pre_battle_screen/PreBattleScreen.h"

namespace game::headquarters_screen {

using namespace headquarters_model;

/** Main menu screen. */
template<typename RenderContext>
class HeadquartersScreen : public game::IScreen<RenderContext> {
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

  using WidgetPtr = std::shared_ptr<Widget>;
  using GridContainerWidgetPtr = std::shared_ptr<GridContainerWidget>;
  using TextWidgetPtr = std::shared_ptr<TextWidget>;
  using SelectionListWidgetPtr = std::shared_ptr<SelectionListWidget>;

  using WidgetSystem = widget::WidgetSystem<RenderContext>;

 public:
  /**
   * Creates headquarters screen with empty headquarters model.
   * @param game_config Const reference to game config.
   */
  explicit HeadquartersScreen(const config::GameConfig &game_config);

  /**
   * Creates headquarters screen.
   * @param game_config Const reference to game config.
   * @param headquarters_info Data used to create headquarters model.
   */
  HeadquartersScreen(const config::GameConfig &game_config, const config::ConfigStructure &headquarters_info);

  std::optional<Action> Update(std::chrono::microseconds delta) override;
  Widget &Render(std::chrono::microseconds delta) override;
  std::optional<Action> OnInput(const frontend::InputEvent &event) override;

 private:
  /** Screen mode. */
  enum Mode {
    /** Tech mode: technology researching. */
    kTech,
    /** Armory mode: weapons and armor are built. */
    kArmory,
  };

  /** Const reference to game config. */
  const config::GameConfig &game_config_;
  /** Headquarters model. */
  HeadquartersModel model_;
  /** Widget system. */
  WidgetSystem widget_system_;
  /** Root container. */
  GridContainerWidgetPtr main_container_;
  /** Current mode. */
  Mode current_mode_;

  /** Root for tech mode widgets. */
  GridContainerWidgetPtr tech_root_;
  /** List of tech types. */
  SelectionListWidgetPtr tech_list_;
  /** Tech information message to user. */
  TextWidgetPtr tech_message_;
  /** Current level of selected tech type. */
  TextWidgetPtr tech_current_data_;

  /** Root for armory mode widgets. */
  GridContainerWidgetPtr armory_root_;
  /** List of armory types. */
  SelectionListWidgetPtr armory_list_;
  /** Armory information message to user. */
  TextWidgetPtr armory_message_;
  /** Current count of selected armory type. */
  TextWidgetPtr armory_current_data_;

  /** Initializes user interface. */
  void InitUI();
  /** Initializes tech mode screen. */
  void InitTechUI();
  /** Initializes armory mode screen. */
  void InitArmoryUI();
  /**
   * Switches to given mode.
   * @param mode Mode to switch to.
   */
  void SwitchMode(Mode mode);

  /** Returns selected type of tech. */
  [[nodiscard]] std::variant<object_database::WeaponTechType, object_database::ArmorTechType> SelectedTechType() const;
  /** Returns selected type of armory. */
  [[nodiscard]] std::variant<object_database::WeaponType, object_database::ArmorType> SelectedArmoryType() const;

  /** Called on research attempt. */
  void OnResearch();
  /** Called when selection of tech is changed. */
  void OnTechSelectionChanged();
  /** Called on build attempt. */
  void OnBuild();
  /** Called when selection of armory is changed. */
  void OnArmorySelectionChanged();

};

template<typename RenderContext>
HeadquartersScreen<RenderContext>::HeadquartersScreen(const config::GameConfig &game_config)
    : game_config_(game_config), model_(game_config), current_mode_(Mode::kTech), widget_system_() {
  InitUI();
}

template<typename RenderContext>
HeadquartersScreen<RenderContext>::HeadquartersScreen(const config::GameConfig &game_config,
                                                      const config::ConfigStructure &headquarters_info)
    : game_config_(game_config), model_(game_config, headquarters_info), current_mode_(Mode::kTech), widget_system_() {
  InitUI();
}

template<typename RenderContext>
std::optional<typename game::IScreen<RenderContext>::Action>
HeadquartersScreen<RenderContext>::Update(std::chrono::microseconds delta) {
  return {};
}

template<typename RenderContext>
widget::Widget<RenderContext> &HeadquartersScreen<RenderContext>::Render(std::chrono::microseconds delta) {
  return widget_system_.Root();
}

template<typename RenderContext>
std::optional<typename game::IScreen<RenderContext>::Action>
HeadquartersScreen<RenderContext>::OnInput(const frontend::InputEvent &event) {
  if (widget_system_.HandleInput(event.input)) {
    return {};
  }

  if (event.input.IsKey()) {
    if (event.input.GetKey() == frontend::Key::kEscape) {
      return PopScreenAction{};
    } else if (event.input.GetKey() == frontend::Key::kEnter) {
      if (current_mode_ == Mode::kTech) {
        OnResearch();
      } else if (current_mode_ == Mode::kArmory) {
        OnBuild();
      }
    }
  } else if (event.input.IsChar()) {
    if (event.input.GetChar() == '1') {
      SwitchMode(Mode::kTech);
    } else if (event.input.GetChar() == '2') {
      SwitchMode(Mode::kArmory);
    } else if (event.input.GetChar() == '3') {
      return PushScreenAction{
          std::make_unique<pre_battle_screen::PreBattleScreen<RenderContext>>(game_config_, model_)};
    }
  }

  return {};
}

template<typename RenderContext>
void HeadquartersScreen<RenderContext>::InitUI() {
  using namespace widget;

  main_container_ = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{1, 2});
  main_container_->SetRenderSeparators(true);

  InitTechUI();
  InitArmoryUI();

  TextWidgetPtr hint_text = std::make_shared<TextWidget>("1: Tech  2: Armory  3: Battle");
  hint_text->SetPreferExpand(util::Vector2<bool>{true, false});
  main_container_->Set({0, 1}, hint_text);

  widget_system_.SetRoot(main_container_);

  SwitchMode(current_mode_);
}

template<typename RenderContext>
void HeadquartersScreen<RenderContext>::InitTechUI() {
  tech_root_ = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{2, 2});
  tech_root_->SetPreferExpand(util::Vector2<bool>{true, true});
  tech_root_->SetRenderSeparators(true);

  std::vector<std::string> tech_names;
  {
    using namespace object_database;
    for (const WeaponTechInfo &tech_info : kWeaponTechInfo) {
      tech_names.push_back(tech_info.name);
    }
    for (const ArmorTechInfo &tech_info : kArmorTechInfo) {
      tech_names.push_back(tech_info.name);
    }
  }
  tech_list_ = std::make_shared<SelectionListWidget>(tech_names);
  tech_list_->SetPreferExpand(util::Vector2<bool>{true, true});
  tech_list_->AddSelectionChangedListener([this](SelectionWidget &list) {
    tech_message_->SetText("");
    OnTechSelectionChanged();
  });
  tech_root_->Set({0, 0}, tech_list_);

  tech_message_ = std::make_shared<TextWidget>("");
  tech_message_->SetPreferExpand(util::Vector2<bool>{true, false});
  tech_root_->Set({0, 1}, tech_message_);

  tech_current_data_ = std::make_shared<TextWidget>("");
  tech_current_data_->SetPreferExpand(util::Vector2<bool>{true, true});
  tech_root_->Set({1, 0}, tech_current_data_);

  TextWidgetPtr hint = std::make_shared<TextWidget>("ENTER: Research");
  hint->SetPreferExpand(util::Vector2<bool>{true, false});
  tech_root_->Set({1, 1}, hint);

  OnTechSelectionChanged();
}

template<typename RenderContext>
void HeadquartersScreen<RenderContext>::InitArmoryUI() {
  armory_root_ = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{2, 2});
  armory_root_->SetPreferExpand(util::Vector2<bool>{true, true});
  armory_root_->SetRenderSeparators(true);

  std::vector<std::string> armory_names;
  {
    using namespace object_database;
    for (const WeaponInfo &info : kWeaponInfo) {
      armory_names.push_back(info.name);
    }
    for (const ArmorInfo &info : kArmorInfo) {
      armory_names.push_back(info.name);
    }
  }
  armory_list_ = std::make_shared<SelectionListWidget>(armory_names);
  armory_list_->SetPreferExpand(util::Vector2<bool>{true, true});
  armory_list_->AddSelectionChangedListener([this](SelectionWidget &list) {
    armory_message_->SetText("");
    OnArmorySelectionChanged();
  });
  armory_root_->Set({0, 0}, armory_list_);

  armory_message_ = std::make_shared<TextWidget>("");
  armory_message_->SetPreferExpand(util::Vector2<bool>{true, false});
  armory_root_->Set({0, 1}, armory_message_);

  armory_current_data_ = std::make_shared<TextWidget>("");
  armory_current_data_->SetPreferExpand(util::Vector2<bool>{true, true});
  armory_root_->Set({1, 0}, armory_current_data_);

  TextWidgetPtr hint = std::make_shared<TextWidget>("ENTER: Build");
  hint->SetPreferExpand(util::Vector2<bool>{true, false});
  armory_root_->Set({1, 1}, hint);

  OnArmorySelectionChanged();
}

template<typename RenderContext>
void HeadquartersScreen<RenderContext>::SwitchMode(HeadquartersScreen::Mode mode) {
  if (mode == Mode::kTech) {
    main_container_->Set({0, 0}, tech_root_);
    widget_system_.SetFocused(tech_list_);
  } else if (mode == Mode::kArmory) {
    main_container_->Set({0, 0}, armory_root_);
    widget_system_.SetFocused(armory_list_);
  }
  current_mode_ = mode;
}

template<typename RenderContext>
std::variant<object_database::WeaponTechType,
             object_database::ArmorTechType> HeadquartersScreen<RenderContext>::SelectedTechType() const {
  using namespace object_database;

  auto selected = tech_list_->SelectedItem();
  if (selected < kWeaponTechInfo.size()) {
    return kWeaponTechInfo[selected].tech_type;
  } else if (selected < kWeaponTechInfo.size() + kArmorTechInfo.size()) {
    return kArmorTechInfo[selected - kWeaponTechInfo.size()].tech_type;
  }

  throw std::runtime_error("cannot get type of selected tech type");
}

template<typename RenderContext>
std::variant<object_database::WeaponType,
             object_database::ArmorType> HeadquartersScreen<RenderContext>::SelectedArmoryType() const {
  using namespace object_database;

  auto selected = armory_list_->SelectedItem();
  if (selected < kWeaponInfo.size()) {
    return kWeaponInfo[selected].type;
  } else if (selected < kWeaponInfo.size() + kArmorInfo.size()) {
    return kArmorInfo[selected - kWeaponInfo.size()].type;
  }

  throw std::runtime_error("cannot get type of selected armory type");
}

template<typename RenderContext>
void HeadquartersScreen<RenderContext>::OnResearch() {
  using namespace object_database;
  using namespace headquarters_model::tech;

  ResearchResult result = ResearchResult::kResearched;
  auto selected = SelectedTechType();
  if (std::holds_alternative<WeaponTechType>(selected)) {
    result = model_.GetTech().ResearchWeapon(std::get<WeaponTechType>(selected));
  } else if (std::holds_alternative<ArmorTechType>(selected)) {
    result = model_.GetTech().ResearchArmor(std::get<ArmorTechType>(selected));
  }

  if (result == ResearchResult::kResearched) {
    tech_message_->SetText("Researched!");
  } else if (result == ResearchResult::kAlreadyMaxLevel) {
    tech_message_->SetText("Already max level.");
  } else if (result == ResearchResult::kNotEnoughResources) {
    tech_message_->SetText("Cannot research: not enough resources!");
  } else {
    tech_message_->SetText("");
  }
  OnTechSelectionChanged();
}

template<typename RenderContext>
void HeadquartersScreen<RenderContext>::OnTechSelectionChanged() {
  using namespace object_database;
  using namespace headquarters_model::tech;

  TechLevel tech_level = TechLevel::kNotResearched;
  auto selected = SelectedTechType();
  if (std::holds_alternative<WeaponTechType>(selected)) {
    tech_level = model_.GetTech().WeaponTechLevel(std::get<WeaponTechType>(selected));
  } else if (std::holds_alternative<ArmorTechType>(selected)) {
    tech_level = model_.GetTech().ArmorTechLevel(std::get<ArmorTechType>(selected));
  }

  if (tech_level == TechLevel::kNotResearched) {
    tech_current_data_->SetText("Current level: not researched");
  } else if (tech_level == TechLevel::kBasic) {
    tech_current_data_->SetText("Current level: basic");
  } else if (tech_level == TechLevel::kAdvanced) {
    tech_current_data_->SetText("Current level: advanced");
  } else {
    tech_current_data_->SetText("");
  }
}

template<typename RenderContext>
void HeadquartersScreen<RenderContext>::OnBuild() {
  using namespace object_database;
  using namespace headquarters_model::armory;

  BuildResult result = BuildResult::kBuilt;
  auto selected = SelectedArmoryType();
  if (std::holds_alternative<WeaponType>(selected)) {
    result = model_.GetArmory().BuildWeapon(std::get<WeaponType>(selected));
  } else if (std::holds_alternative<ArmorType>(selected)) {
    result = model_.GetArmory().BuildArmor(std::get<ArmorType>(selected));
  }

  if (result == BuildResult::kBuilt) {
    armory_message_->SetText("Built!");
  } else if (result == BuildResult::kNotResearched) {
    armory_message_->SetText("Cannot build: not researched yet!");
  } else if (result == BuildResult::kNotEnoughResources) {
    armory_message_->SetText("Cannot build: not enough resources!");
  } else {
    armory_message_->SetText("");
  }
  OnArmorySelectionChanged();
}

template<typename RenderContext>
void HeadquartersScreen<RenderContext>::OnArmorySelectionChanged() {
  using namespace object_database;
  using namespace headquarters_model::armory;

  size_t count = 0;
  auto selected = SelectedArmoryType();
  if (std::holds_alternative<WeaponType>(selected)) {
    count = model_.GetArmory().WeaponCount(std::get<WeaponType>(selected));
  } else if (std::holds_alternative<ArmorType>(selected)) {
    count = model_.GetArmory().ArmorCount(std::get<ArmorType>(selected));
  }

  {
    std::stringstream message;
    message << "Count: " << count;
    armory_current_data_->SetText(message.str());
  }
}

}
