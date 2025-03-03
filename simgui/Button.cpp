// Button.cpp
#include "Button.h"

Button::Button(int id, int x, int y, int width, int height, std::function<void()> onClick, SDL_Color color)
  : m_onClick(onClick) {
  m_id = id;
  m_x = x;
  m_y = y;
  m_width = width;
  m_height = height;
  m_color = color;
}

void Button::update(Renderer& renderer, UIState& uiState) {
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

  // If we have keyboard focus, we'll need to process the keys
  if (uiState.kbdItem == m_id) {
    switch (uiState.keyEntered) {
    case SDLK_TAB:
      // If tab is pressed, lose keyboard focus.
      // Next widget will grab the focus.
      uiState.kbdItem = 0;
      // If shift was also pressed, we want to move focus
      // to the previous widget instead.
      if (uiState.keyMod & KMOD_SHIFT) {
        uiState.kbdItem = uiState.lastWidget;
      }
      // Also clear the key so that next widget
      // won't process it
      uiState.keyEntered = 0;
      break;
    case SDLK_RETURN:
      // Had keyboard focus, received return,
      // so we'll act as if we were clicked.
      uiState.hotItem = m_id;
      uiState.activeItem = m_id;
      if (m_onClick) {
        m_clicked = true;
      }
      break;
    }
  }

  uiState.lastWidget = m_id;

  if (uiState.debugMode) {
    m_clicked = false;
    return; // No need to process rest of update
  }

  // If button is hot and active, but mouse button is not down
  if (
    uiState.mouseDown == false &&
    uiState.hotItem == m_id &&
    uiState.activeItem == m_id &&
    m_onClick
    ) {
    m_clicked = true;
  }

  if (m_clicked) {
    m_onClick();
    m_clicked = false;
  }
}

void Button::render(Renderer& renderer, const UIState& uiState) {
  // If we have keyboard focus, show it
  if (uiState.kbdItem == m_id) {
    renderer.drawRect(
      m_x + uiState.scrollX - OUTLINE_PADDING, m_y + uiState.scrollY - OUTLINE_PADDING,
      m_width + (OUTLINE_PADDING * 2), m_height + (OUTLINE_PADDING * 2),
      {255, 0, 0, 255}
    );
  }

  // Render button
  if (uiState.hotItem == m_id && uiState.activeItem == m_id) {
    // Button is both hot and active
    renderer.drawRect(m_x + uiState.scrollX - 2, m_y + uiState.scrollY - 2, m_width, m_height, m_color);
  } else {
    // Button is not hot, but may be active
    renderer.drawRect(m_x + uiState.scrollX, m_y + uiState.scrollY, m_width, m_height, m_color);
  }
}