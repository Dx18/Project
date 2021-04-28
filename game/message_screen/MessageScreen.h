#pragma once

#include "game/IScreen.h"

namespace game::message_screen {

/**
 * Basic screen with message.
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class MessageScreen : public game::IScreen<Context> {
 private:
  using Action = typename game::IScreen<Context>::Action;
  using PushScreenAction = typename game::IScreen<Context>::PushScreenAction;
  using PopScreenAction = typename game::IScreen<Context>::PopScreenAction;
  using QuitAction = typename game::IScreen<Context>::QuitAction;

  using Widget = widget::Widget<Context>;
  using GridContainerWidget = widget::GridContainerWidget<Context>;
  using TextWidget = widget::TextWidget<Context>;

  using GridContainerWidgetPtr = std::shared_ptr<GridContainerWidget>;
  using TextWidgetPtr = std::shared_ptr<TextWidget>;

  using WidgetSystem = widget::WidgetSystem<Context>;

 public:
  /**
   * Creates message screen.
   * @param title Title of message.
   * @param text Contents of message.
   */
  explicit MessageScreen(const std::string &title, const std::string &text);

  std::optional<Action> Update(std::chrono::microseconds delta) override;
  Widget &Render(std::chrono::microseconds delta) override;
  std::optional<Action> OnInput(const frontend::InputEvent &event) override;

 private:
  /** Widget system. */
  WidgetSystem widget_system_;

  /** Initializes user interface. */
  void InitUI(const std::string &title, const std::string &text);

};

template<typename Context>
MessageScreen<Context>::MessageScreen(const std::string &title, const std::string &text) {
  InitUI(title, text);
}

template<typename Context>
void MessageScreen<Context>::InitUI(const std::string &title, const std::string &text) {
  GridContainerWidgetPtr main_container = std::make_shared<GridContainerWidget>(util::Vector2<size_t>{1, 2});
  main_container->SetRenderSeparators(true);

  TextWidgetPtr title_widget = std::make_shared<TextWidget>(title);
  title_widget->SetPreferExpand(util::Vector2<bool>{true, false});
  main_container->Set(util::Vector2<size_t>{0, 0}, title_widget);

  TextWidgetPtr text_widget = std::make_shared<TextWidget>(text);
  text_widget->SetPreferExpand(util::Vector2<bool>{true, true});
  main_container->Set(util::Vector2<size_t>{0, 1}, text_widget);

  widget_system_.SetRoot(main_container);
}

template<typename Context>
std::optional<typename IScreen<Context>::Action>
MessageScreen<Context>::Update(std::chrono::microseconds delta) {
  return {};
}

template<typename Context>
widget::Widget<Context> &MessageScreen<Context>::Render(std::chrono::microseconds delta) {
  return widget_system_.Root();
}

template<typename Context>
std::optional<typename IScreen<Context>::Action>
MessageScreen<Context>::OnInput(const frontend::InputEvent &event) {
  return PopScreenAction{};
}

}
