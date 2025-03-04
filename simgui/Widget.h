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

  SDL_Rect getRect() { return { m_x, m_y, m_width, m_height }; }

  void setPosition(int x, int y) {
    m_x = x;
    m_y = y;
  }

  void setSize(int width, int height) {
    m_width = width;
    m_height = height;
  }

  void setRect(int x, int y, int width, int height) {
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
  }

  void setRect(SDL_Rect rect) {
    m_x = rect.x;
    m_y = rect.y;
    m_width = rect.w;
    m_height = rect.h;
  }

  virtual void update(Renderer& renderer, UIState& uiState) = 0;
  virtual void render(Renderer& renderer, const UIState& uiState) = 0;

  void renderDebug(Renderer& renderer, int offsetX, int offsetY, int hotItemId) const {
    renderer.drawRect(m_x + offsetX, m_y + offsetY, m_width, m_height, { 255, 255, 255, 50 });
    renderer.drawText(std::to_string(m_id), m_x + offsetX + 2, m_y + offsetY + 2, { 0, 0, 0, 255 });

    if (hotItemId == m_id) {
      renderer.drawRect(m_x + offsetX + m_width + 10, m_y + offsetY, 200, 200, { 190, 190, 190, 255 });

    }
  }

protected:
  int m_id{ 0 };
  int m_x{ 0 };
  int m_y{ 0 };
  int m_width{ 0 };
  int m_height{ 0 };
};