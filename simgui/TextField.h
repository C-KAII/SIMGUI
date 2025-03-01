// Slider.h
#pragma once
#include "Widget.h"
#include "UIState.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class TextField : public Widget {
public:
  TextField(int id, int x, int y, int width, int height);
  ~TextField() override = default;

  void update(Renderer& renderer, UIState& uiState) override;
  void render(Renderer& renderer, const UIState& uiState) override;

private:
  bool m_isActive{ false };
  //std::string m_text{ "" };
  std::vector<std::string> m_lines;
  int m_cursorX{ 0 }; // X position of cursor
  int m_cursorY{ 0 }; // Y position of cursor (line number)
};