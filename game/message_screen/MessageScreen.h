#pragma once

#include "game/IScreen.h"

namespace game::message_screen {

/**
 * Basic screen with message.
 * @tparam RenderContext Render context used to draw widgets.
 */
template<typename RenderContext>
class MessageScreen : public game::IScreen<RenderContext> {
 private:
  using Action = typename game::IScreen<RenderContext>::Action;
  using PushScreenAction = typename game::IScreen<RenderContext>::PushScreenAction;
  using PopScreenAction = typename game::IScreen<RenderContext>::PopScreenAction;
  using QuitAction = typename game::IScreen<RenderContext>::QuitAction;

  using Widget = widget::Widget<RenderContext>;
  using GridContainerWidget = widget::GridContainerWidget<RenderContext>;
  using TextWidget = widget::TextWidget<RenderContext>;

  using GridContainerWidgetPtr = std::shared_ptr<GridContainerWidget>;
  using TextWidgetPtr = std::shared_ptr<TextWidget>;

  using WidgetSystem = widget::WidgetSystem<RenderContext>;

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

template<typename RenderContext>
MessageScreen<RenderContext>::MessageScreen(const std::string &title, const std::string &text) {
  InitUI(title, text);
}

template<typename RenderContext>
void MessageScreen<RenderContext>::InitUI(const std::string &title, const std::string &text) {
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

template<typename RenderContext>
std::optional<typename IScreen<RenderContext>::Action>
MessageScreen<RenderContext>::Update(std::chrono::microseconds delta) {
  return {};
}

template<typename RenderContext>
widget::Widget<RenderContext> &MessageScreen<RenderContext>::Render(std::chrono::microseconds delta) {
  return widget_system_.Root();
}

template<typename RenderContext>
std::optional<typename IScreen<RenderContext>::Action>
MessageScreen<RenderContext>::OnInput(const frontend::InputEvent &event) {
  return PopScreenAction{};
}

}
