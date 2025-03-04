// App.h
#pragma once
#include "Renderer.h"
#include "LayoutManager.h"
#include "UIState.h"
#include <SDL2/SDL.h>

class App {
public:
  App() = default;
  ~App() = default;

  bool init();
  void run();

private:
  void addWidgets();

  void imguiPrepare();
  void imguiFinish();

  void render();

  Renderer m_renderer{ };

  LayoutManager m_layout;
  
  UIState m_uiState{ };
  
  int m_redValue{ 119 };
  int m_greenValue{ 119 };
  int m_blueValue{ 119 };

  bool m_running{ false };
};