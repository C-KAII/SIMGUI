// UIState.h
#pragma once
#include "LayoutManager.h"
#include <vector>
#include <memory>

struct UIState {
  UIState() = default;
  ~UIState() = default;

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
            if (regionHit(widget->getRect())) {
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

        if (event.key.keysym.sym == SDLK_TAB && kbdItem == -1) {
          kbdItem = 0;
          keyEntered = 0;
        }

        if (event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL) {
          layout.toggleDebug(true);
        }
        break;

      case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          return false;
        }

        if (event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL) {
          layout.toggleDebug(false);
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

  bool regionHit(SDL_Rect rect) const {
    if (
      mouseX < rect.x || mouseY < rect.y ||
      mouseX >= rect.x + rect.w || mouseY >= rect.y + rect.h
      ) {
      return false;
    }
    return true;
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