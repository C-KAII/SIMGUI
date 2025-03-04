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
    m_running = m_uiState.handleEvents(m_layout, m_renderer);

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
    SDL_Color{ 0, 0, 255, 255 },
    [this]() {
      std::cout << "Blue button clicked!\n";
      int numCols = m_layout.getNumColumns() - 1;
      if (numCols >= 1) {
        m_layout.setNumColumns(numCols);
      }
    }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    SDL_Color{ 0, 255, 0, 255 },
    [this]() {
      std::cout << "Green button clicked!\n";
      int numCols = m_layout.getNumColumns() + 1;
      if (numCols <= m_layout.getNumWidgets()) {
        m_layout.setNumColumns(numCols);
      }
    }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    SDL_Color{ 255, 204, 255, 255 },
    [this]() {
      std::cout << "Pink button clicked!\n";
      m_redValue = rand() % 256;
      m_greenValue = rand() % 256;
      m_blueValue = rand() % 256;
    }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    SDL_Color{ 102, 255, 255, 255 },
    [this]() {
      std::cout << "Cyan button clicked!\n";
      m_running = false; // quit
    }
  ));

  // Sliders
  //m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_redValue));
  //m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_greenValue));
  //m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_blueValue));

  // Text Fields
  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));
  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));

  // Buttons
  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    SDL_Color{ 0, 0, 255, 255 },
    [this]() {
      std::cout << "Blue button clicked!\n";
      int numCols = m_layout.getNumColumns() - 1;
      if (numCols >= 1) {
        m_layout.setNumColumns(numCols);
      }
    }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    SDL_Color{ 0, 255, 0, 255 },
    [this]() {
      std::cout << "Green button clicked!\n";
      int numCols = m_layout.getNumColumns() + 1;
      if (numCols <= m_layout.getNumWidgets()) {
        m_layout.setNumColumns(numCols);
      }
    }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    SDL_Color{ 255, 204, 255, 255 },
    [this]() {
      std::cout << "Pink button clicked!\n";
      m_redValue = rand() % 256;
      m_greenValue = rand() % 256;
      m_blueValue = rand() % 256;
    }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    SDL_Color{ 102, 255, 255, 255 },
    [this]() {
      std::cout << "Cyan button clicked!\n";
      m_running = false; // quit
    }
  ));

  // Sliders
  //m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_redValue));
  //m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_greenValue));
  //m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_blueValue));

  // Text Fields
  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));
  m_layout.addWidget(std::make_unique<TextField>(GEN_ID, 0, 0, 200, m_renderer.getFontHeight()));

  // Buttons
  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    SDL_Color{ 0, 0, 255, 255 },
    [this]() {
      std::cout << "Blue button clicked!\n";
      int numCols = m_layout.getNumColumns() - 1;
      if (numCols >= 1) {
        m_layout.setNumColumns(numCols);
      }
    }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    SDL_Color{ 0, 255, 0, 255 },
    [this]() {
      std::cout << "Green button clicked!\n";
      int numCols = m_layout.getNumColumns() + 1;
      if (numCols <= m_layout.getNumWidgets()) {
        m_layout.setNumColumns(numCols);
      }
    }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    SDL_Color{ 255, 204, 255, 255 },
    [this]() {
      std::cout << "Pink button clicked!\n";
      m_redValue = rand() % 256;
      m_greenValue = rand() % 256;
      m_blueValue = rand() % 256;
    }
  ));

  m_layout.addWidget(std::make_unique<Button>(
    GEN_ID, 0, 0, 100, 50,
    SDL_Color{ 102, 255, 255, 255 },
    [this]() {
      std::cout << "Cyan button clicked!\n";
      m_running = false; // quit
    }
  ));

  // Sliders
  //m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_redValue));
  //m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_greenValue));
  //m_layout.addWidget(std::make_unique<Slider>(GEN_ID, 0, 0, 16, 100, 0, 255, m_blueValue));

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

  // Widget rendering

  for (auto& widget : m_layout.getWidgets()) {
    widget->update(m_renderer, m_uiState);

    // Offset rendering based on scroll position
    SDL_Rect rect = widget->getRect();
    if (
      rect.x + rect.w + m_uiState.scrollX > 0 && rect.y + rect.h + m_uiState.scrollY > 0 &&
      rect.x + m_uiState.scrollX < m_renderer.getScreenWidth() && rect.y + m_uiState.scrollY < m_renderer.getScreenHeight()
      ) {
      if (m_uiState.debugMode) {
        widget->renderDebug(m_renderer, m_uiState.scrollX, m_uiState.scrollY, m_uiState.hotItem);
      } else {
        widget->render(m_renderer, m_uiState);
      }
    }
  }

  // Non-widget rendering

  if (m_uiState.debugMode) {
    // TODO - move this and other debug rending logic to a debug rendering class

    // Mouse position
    std::string mousePosText = "(" + std::to_string(m_uiState.mouseX) + ", " + std::to_string(m_uiState.mouseY) + ")";
    m_renderer.drawText(mousePosText, m_uiState.mouseX + m_uiState.scrollX, m_uiState.mouseY + m_uiState.scrollY - m_renderer.getFontHeight(), {0, 0, 0, 255});


  }

  imguiFinish();

  m_renderer.present();

  SDL_Delay(10);
}