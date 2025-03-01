// App.h
#pragma once
#include "Renderer.h"
#include "LayoutManager.h"
#include "UIState.h"
#include <SDL2/SDL.h>
#include <string>

class App {
public:
  App() = default;
  ~App() = default;

  bool init();
  void run();
  void cleanUp();

private:
  void addWidgets();

  void imguiPrepare();
  void imguiFinish();
  void render();

  SDL_Window* m_window{ nullptr };
  SDL_Renderer* m_renderer{ nullptr };
  Renderer m_renderWrapper{ };

  LayoutManager m_layout;
  
  UIState m_uiState{ };
  
  int m_redValue{ 119 };
  int m_greenValue{ 119 };
  int m_blueValue{ 119 };

  bool m_running{ false };
};