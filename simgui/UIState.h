// UIState.h
#pragma once
#include "LayoutManager.h"
#include <vector>
#include <memory>

struct UIState {
  UIState() {}

  ~UIState() {}

  bool handleEvents(LayoutManager& layout) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_MOUSEMOTION:
        mouseX = event.motion.x;
        mouseY = event.motion.y;
        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          mouseDown = true;
        }
        break;

      case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
          mouseDown = false;

          bool flag = false;
          for (auto& widget : layout.getWidgets()) {
            if (regionHit(widget->getDims())) {
              flag = true;
              break;
            }
          }
          if (flag == false) {
            kbdItem = -1;
          }
        }
        break;

      case SDL_KEYDOWN:
        keyEntered = event.key.keysym.sym;
        keyMod = event.key.keysym.mod;

        if (keyEntered == SDLK_TAB && kbdItem == -1) {
          keyEntered = 0;
          kbdItem = 0;
        }
        break;

      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          return false;
        }
        break;

      case SDL_QUIT:
        return false;
      }
    }
    return true;
  }

  bool regionHit(int x, int y, int w, int h) const {
    if (
      mouseX < x || mouseY < y ||
      mouseX >= x + w || mouseY >= y + h
      ) {
      return false;
    }
    return true;
  }

  bool regionHit(SDL_Rect dims) const {
    if (
      mouseX < dims.x || mouseY < dims.y ||
      mouseX >= dims.x + dims.w || mouseY >= dims.y + dims.h
      ) {
      return false;
    }
    return true;
  }

  void resetFrameState() {

  }

  void updateMouse(int x, int y, bool down) {

  }

  void processKey(int key, int mod) {

  }

  int mouseX{ 0 };
  int mouseY{ 0 };
  bool mouseDown{ false };

  int hotItem{ 0 };
  int activeItem{ 0 };

  int kbdItem{ -1 };
  int keyEntered{ 0 };
  int keyMod{ 0 };

  int lastWidget{ 0 };

  bool needsUpdate{ false };
};