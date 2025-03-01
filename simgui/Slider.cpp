// Button.cpp
#include "Slider.h"

Slider::Slider(int id, int x, int y, int width, int height, int minValue, int maxValue, int& valueRef)
: m_minValue(minValue), m_maxValue(maxValue), m_value(valueRef) {
  m_id = id;
  m_x = x;
  m_y = y;
  m_width = width;
  m_height = height;
}

void Slider::update(Renderer& renderer, UIState& uiState) {
  // Check if button should be hot
  if (uiState.regionHit(m_x, m_y, m_width, m_height)) {
    uiState.hotItem = m_id;
    if (uiState.activeItem == 0 && uiState.mouseDown) {
      uiState.kbdItem = m_id;
      uiState.activeItem = m_id;
    }
  }

  // If no widget has keyboard focus, take it
  if (uiState.kbdItem == 0) {
    uiState.kbdItem = m_id;
  }

  // Keyboard interactions
  if (uiState.kbdItem == m_id) {
    switch (uiState.keyEntered) {
    case SDLK_TAB:
      uiState.kbdItem = 0;  // Lose focus
      if (uiState.keyMod & KMOD_SHIFT) {
        uiState.kbdItem = uiState.lastWidget;
      }
      uiState.keyEntered = 0;
      break;
    case SDLK_UP:
      if (m_value < m_maxValue) {
        m_value++;
      }
      break;
    case SDLK_DOWN:
      if (m_value > 0) {
        m_value--;
      }
      break;
    }
  }

  // Mouse drag logic
  if (uiState.activeItem == m_id) {
    int mousePos = uiState.mouseY - (m_y + 8);
    if (mousePos < 0) mousePos = 0;
    if (mousePos > m_height - m_width) mousePos = m_height - m_width;

    int newValue = (mousePos * m_maxValue) / (m_height - m_width);
    if (newValue != m_value) {
      m_value = newValue;
    }
  }

  if (m_value < m_minValue) { m_value = m_minValue; }
  if (m_value > m_maxValue) { m_value = m_maxValue; }

  uiState.lastWidget = m_id;
}

void Slider::render(Renderer& renderer, const UIState& uiState) {
  // If we have keyboard focus, show it
  if (uiState.kbdItem == m_id) {
    renderer.drawRect(
      m_x - OUTLINE_PADDING, m_y - OUTLINE_PADDING,
      m_width + (OUTLINE_PADDING * 2), m_height + (OUTLINE_PADDING * 2),
      { 255, 0, 0, 255 }
    );
  }

  // Draw slider track
  renderer.drawRect(m_x, m_y, m_width, m_height, { 117, 117, 117, 255 });

  // Handle color
  SDL_Color sliderColor = { 170, 170, 170, 255 };
  if (uiState.activeItem == m_id || uiState.hotItem == m_id) {
    sliderColor = SDL_Color{ 255, 255, 255, 255 };
  }
  // Draw slider handle
  int yPos = (m_height - m_width) * m_value / m_maxValue;
  renderer.drawRect(m_x, m_y + yPos, m_width, m_width, sliderColor);
}