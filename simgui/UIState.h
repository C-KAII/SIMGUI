// UIState.h
#pragma once
#include "LayoutManager.h"
#include <vector>
#include <memory>

struct UIState {
  UIState() = default;
  ~UIState() = default;

  bool handleEvents(LayoutManager& layout, Renderer& renderer) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_MOUSEMOTION:
        mouseX = event.motion.x;
        mouseY = event.motion.y;
        if (debugMode && draggingWidget) {
          int newX = event.motion.x - dragOffset.x;
          int newY = event.motion.y - dragOffset.y;
          draggingWidget->setPosition(newX, newY);
        }
        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          mouseDown = true;

          if (debugMode) {
            // In debug mode, try to pick up a widget
            for (auto& widget : layout.getWidgets()) {
              SDL_Rect rect = widget->getRect();
              if (
                event.button.x >= rect.x && event.button.x < rect.x + rect.w &&
                event.button.y >= rect.y && event.button.y < rect.y + rect.h
                ) {
                draggingWidget = widget.get();
                dragOffset.x = event.button.x - rect.x;
                dragOffset.y = event.button.y - rect.y;
                break;
              }
            }
          }
        }
        break;

      case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
          mouseDown = false;

          bool flag = false;
          for (const auto& widget : layout.getWidgets()) {
            if (regionHit(widget->getRect())) {
              flag = true;
              break;
            }
          }
          if (flag == false) {
            kbdItem = -1;
          }

          if (debugMode && draggingWidget) {
            int padding = 5;
            // On drop, see if we're over another widget to swap
            Widget* dropTarget = nullptr;
            bool insertBefore = false;

            for (auto& widget : layout.getWidgets()) {
              SDL_Rect rect = widget->getRect();
              // Ignore dragged widget
              if (widget.get() == draggingWidget) { continue; }
              if (
                event.button.x >= rect.x - (padding / 2) && event.button.x < rect.x + rect.w + (padding / 2) &&
                event.button.y >= rect.y - (padding / 2) && event.button.y < rect.y + rect.h + (padding / 2)
                ) {
                dropTarget = widget.get();
                // If mouse is on LHS, insert before
                insertBefore = (mouseX < (rect.x - (padding / 2)) + ((rect.w + (padding / 2)) / 2));
                break;
              }
            }

            // Widget insertion functionality
            if (dropTarget) {
              layout.reorderWidget(draggingWidget, dropTarget, insertBefore);
            }

            draggingWidget = nullptr;
            needsUpdate = true;
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
          debugMode = true;
        }
        break;

      case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          return false;
        }

        if (event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL) {
          debugMode = false;
        }
        break;

      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
          int newWidth = event.window.data1;
          int newHeight = event.window.data2;
          renderer.updateWindowSize(newWidth, newHeight);
          needsUpdate = true;
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
  int lastWidget{ 0 };
  int keyEntered{ 0 };
  int keyMod{ 0 };

  bool needsUpdate{ false };

  bool debugMode{ false };
  Widget* draggingWidget{ nullptr };
  SDL_Point dragOffset{ 0,0 };

};