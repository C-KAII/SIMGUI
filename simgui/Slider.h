// Slider.h
#pragma once
#include "Widget.h"
#include "UIState.h"
#include "Renderer.h"
#include <SDL2/SDL.h>

class Slider : public Widget {
public:
  Slider(int id, int x, int y, int width, int height, int minValue, int maxValue, int& valueRef);
  ~Slider() override = default;

  void update(Renderer& renderer, UIState& uiState) override;
  void render(Renderer& renderer, const UIState& uiState) override;

private:
  int m_minValue{ 0 };
  int m_maxValue{ 0 };
  int& m_value;
};