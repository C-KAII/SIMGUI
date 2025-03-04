// App.cpp
#include "App.h"
#include "Button.h"
#include "Slider.h"
#include "TextField.h"
#include <iostream>
#include <cstdlib> // rand()

#ifdef IMGUI_SRC_ID
#define GEN_ID ((IMGUI_SRC_ID) + (__LINE__))
#else
#define GEN_ID (__LINE__)
#endif

bool App::init() {
  if (!m_renderer.init("SIMGUI", 640, 480)) {
    return false;
  }

  if (!m_renderer.initFont("assets/fonts/OpenDyslexicMono-Regular.otf", 12)) {
    return false;
  }

  return true;
}

void App::run() {
  addWidgets();

  m_running = true;
  while (m_running) {
    render();

    if (m_running) {
      m_running = m_uiState.handleEvents(m_layout, m_renderer);
    }

    if (m_layout.needsUpdate() || m_uiState.needsUpdate) {
      m_layout.applyLayout();
      m_uiState.needsUpdate = false;
    }
  }
}

// private

void App::addWidgets() {
  // Buttons
  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Blue button clicked!\n";
      int numCols = m_layout.getNumColumns() - 1;
      if (numCols >= 1) {
        m_layout.setNumColumns(numCols);
      }
    },
    SDL_Color{ 0, 0, 255, 255 }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Green button clicked!\n";
      int numCols = m_layout.getNumColumns() + 1;
      if (numCols <= m_layout.getNumWidgets()) {
        m_layout.setNumColumns(numCols);
      }
    },
    SDL_Color{ 0, 255, 0, 255 }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Pink button clicked!\n";
      m_redValue = rand() % 256;
      m_greenValue = rand() % 256;
      m_blueValue = rand() % 256;
    },
    SDL_Color{ 255, 204, 255, 255 }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Cyan button clicked!\n";
      m_running = false; // quit
    },
    SDL_Color{ 102, 255, 255, 255 }
  ));

  // Sliders
  m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_redValue));
  m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_greenValue));
  m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_blueValue));

  // Text Fields
  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));
  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));

  // Buttons
  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Blue button clicked!\n";
      int numCols = m_layout.getNumColumns() - 1;
      if (numCols >= 1) {
        m_layout.setNumColumns(numCols);
      }
    },
    SDL_Color{ 0, 0, 255, 255 }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Green button clicked!\n";
      int numCols = m_layout.getNumColumns() + 1;
      if (numCols <= m_layout.getNumWidgets()) {
        m_layout.setNumColumns(numCols);
      }
    },
    SDL_Color{ 0, 255, 0, 255 }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Pink button clicked!\n";
      m_redValue = rand() % 256;
      m_greenValue = rand() % 256;
      m_blueValue = rand() % 256;
    },
    SDL_Color{ 255, 204, 255, 255 }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Cyan button clicked!\n";
      m_running = false; // quit
    },
    SDL_Color{ 102, 255, 255, 255 }
  ));

  // Sliders
  m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_redValue));
  m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_greenValue));
  m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_blueValue));

  // Text Fields
  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));
  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));

  // Buttons
  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Blue button clicked!\n";
      int numCols = m_layout.getNumColumns() - 1;
      if (numCols >= 1) {
        m_layout.setNumColumns(numCols);
      }
    },
    SDL_Color{ 0, 0, 255, 255 }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Green button clicked!\n";
      int numCols = m_layout.getNumColumns() + 1;
      if (numCols <= m_layout.getNumWidgets()) {
        m_layout.setNumColumns(numCols);
      }
    },
    SDL_Color{ 0, 255, 0, 255 }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Pink button clicked!\n";
      m_redValue = rand() % 256;
      m_greenValue = rand() % 256;
      m_blueValue = rand() % 256;
    },
    SDL_Color{ 255, 204, 255, 255 }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    [this]() {
      std::cout << "Cyan button clicked!\n";
      m_running = false; // quit
    },
    SDL_Color{ 102, 255, 255, 255 }
  ));

  // Sliders
  m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_redValue));
  m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_greenValue));
  m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_blueValue));

  // Text Fields
  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));
  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));

  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));
  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));

  m_layout.applyLayout();
}

void App::imguiPrepare() {
  m_uiState.hotItem = 0;
}

void App::imguiFinish() {
  if (m_uiState.mouseDown == 0) {
    m_uiState.activeItem = 0;
  } else if (m_uiState.activeItem == 0) {
    m_uiState.activeItem = -1;
  }

  m_uiState.keyEntered = 0;
}

void App::render() {
  m_renderer.clear({
    static_cast<unsigned char>(m_redValue),
    static_cast<unsigned char>(m_greenValue),
    static_cast<unsigned char>(m_blueValue),
    255
    });

  imguiPrepare();

  if (!m_uiState.debugMode) {
    for (auto& widget : m_layout.getWidgets()) {
      widget->update(m_renderer, m_uiState);

      // Offset rendering based on scroll position
      SDL_Rect rect = widget->getRect();
      if (
        rect.x + rect.w + m_uiState.scrollX > 0 && rect.y + rect.h + m_uiState.scrollY > 0 &&
        rect.x + m_uiState.scrollX < m_renderer.getScreenWidth() && rect.y + m_uiState.scrollY < m_renderer.getScreenHeight()
        ) {
        widget->render(m_renderer, m_uiState);
      }
    }
  } else {
    // TODO - move this and other debug rending logic to a RenderDebug class

    auto& widgets = m_layout.getWidgets();
    for (auto& widget : widgets) {
      widget->update(m_renderer, m_uiState);

      SDL_Rect rect = widget->getRect();
      if (
        rect.x + rect.w + m_uiState.scrollX > 0 && rect.y + rect.h + m_uiState.scrollY > 0 &&
        rect.x + m_uiState.scrollX < m_renderer.getScreenWidth() && rect.y + m_uiState.scrollY < m_renderer.getScreenHeight()
        ) {
        m_renderer.drawRect(rect.x + m_uiState.scrollX, rect.y + m_uiState.scrollY, rect.w, rect.h, { 255, 255, 255, 255 });
        m_renderer.drawText(std::to_string(widget->getId()), rect.x + m_uiState.scrollX + 2, rect.y + m_uiState.scrollY + 2, { 0, 0, 0, 255 });
      }
    }

    if (m_uiState.hotItem != 0) {
      for (auto& widget : widgets) {
        if (m_uiState.hotItem == widget->getId()) {
          SDL_Rect rect = widget->getRect();
          const int debugBoxX = rect.x + m_uiState.scrollX + rect.w + 10;
          const int debugBoxY = rect.y + m_uiState.scrollY;

          m_renderer.drawRect(debugBoxX - 2, debugBoxY - 2, 200 + 4, 200 + 4, { 255, 0, 0, 255 });
          m_renderer.drawRect(debugBoxX, debugBoxY, 200, 200, { 255, 255, 255, 255 });

          const int linePadding = m_renderer.getFontHeight() + 2;
          int yPos = debugBoxY + 2;
          // Render debug info text
          m_renderer.drawText(
            "real(" + std::to_string(rect.x) + ',' + std::to_string(rect.y) + ',' + std::to_string(rect.w) + ',' + std::to_string(rect.h) + ')',
            debugBoxX + 2, yPos,
            { 0, 0, 0, 255 }
          );

          yPos += linePadding;

          m_renderer.drawText(
            "screen(" + std::to_string(rect.x + m_uiState.scrollX) + ',' + std::to_string(rect.y + m_uiState.scrollY) + ',' + std::to_string(rect.w) + ',' + std::to_string(rect.h) + ')',
            debugBoxX + 2, yPos,
            { 0, 0, 0, 255 }
          );

          yPos += linePadding;

          SDL_Color color = widget->getColor();
          m_renderer.drawText(
            "rgba(" + std::to_string(color.r) + ',' + std::to_string(color.g) + ',' + std::to_string(color.b) + ',' + std::to_string(color.a) + ')',
            debugBoxX + 2, yPos,
            color
          );

          yPos += linePadding;

        }
      }
    }


    // Mouse position
    std::string mousePosText = "(" + std::to_string(m_uiState.mouseX) + ", " + std::to_string(m_uiState.mouseY) + ")";
    m_renderer.drawText(mousePosText, m_uiState.mouseX + m_uiState.scrollX, m_uiState.mouseY + m_uiState.scrollY - m_renderer.getFontHeight(), { 0, 0, 0, 255 });

  }

  imguiFinish();

  m_renderer.present();

  SDL_Delay(10);
}