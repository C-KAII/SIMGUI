// Widget.h
#pragma once
#include "Renderer.h"
#include <SDL2/SDL.h>

constexpr int OUTLINE_PADDING = 2;

struct UIState;

class Widget {
public:
  Widget() = default;
  virtual ~Widget() = default;

  SDL_Rect getDims() { return { m_x, m_y, m_width, m_height }; }

  void setPosition(int x, int y) {
    m_x = x;
    m_y = y;
  }

  void setSize(int width, int height) {
    m_width = width;
    m_height = height;
  }

  void setDims(int x, int y, int width, int height) {
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
  }

  void setDims(SDL_Rect dims) {
    m_x = dims.x;
    m_y = dims.y;
    m_width = dims.w;
    m_height = dims.h;
  }

  virtual void update(Renderer& renderer, UIState& uiState) = 0;
  virtual void render(Renderer& renderer, const UIState& uiState) = 0;

protected:
  int m_id{ 0 };
  int m_x{ 0 };
  int m_y{ 0 };
  int m_width{ 0 };
  int m_height{ 0 };
};