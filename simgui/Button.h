// Button.h
#pragma once
#include "Widget.h"
#include "UIState.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <functional>

class Button : public Widget {
public:
  Button(int id, int x, int y, int width, int height, SDL_Color color, std::function<void()> onClick);
  ~Button() override = default;

  void update(Renderer& renderer, UIState& uiState) override;
  void render(Renderer& renderer, const UIState& uiState) override;

private:
  SDL_Color m_color{ 255 };
  std::function<void()> m_onClick;
  bool clicked{ false };
};