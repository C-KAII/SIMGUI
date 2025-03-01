// Renderer.h
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Renderer {
public:
  Renderer() {}
  Renderer(SDL_Renderer* renderer) : m_renderer(renderer) {}

  ~Renderer() = default;

  bool initFont(const char* fontPath, const int fontSize ) {
    if (TTF_Init() == -1) {
      std::cerr << "SDL_ttf could not initialize! Error: " << TTF_GetError() << std::endl;
      return false;
    }

    m_font = TTF_OpenFont(fontPath, fontSize);
    if (!m_font) {
      std::cerr << "Failed to load font! Error: " << TTF_GetError() << std::endl;
      return false;
    }

    TTF_SizeUTF8(m_font, "A", &fontW, &fontH);
    return true;
  }

  void drawRect(int x, int y, int w, int h, SDL_Color color) {
    SDL_Rect rect{ x, y, w, h };
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_renderer, &rect);
  }

  void drawText(const std::string& text, int x, int y, SDL_Color color) {
    if (text.length() <= 0) {
      return;
    }

    // Create surface from font
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, text.c_str(), color);
    if (!textSurface) {
      std::cerr << "Text rendering failed: " << TTF_GetError() << std::endl;
      return;
    }

    // Convert surface to texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    SDL_FreeSurface(textSurface); // Free surface after converting

    if (!textTexture) {
      std::cerr << "Texture creation failed: " << SDL_GetError() << std::endl;
      return;
    }

    // Get text dimensions
    int textW = 0, textH = 0;
    TTF_SizeText(m_font, text.c_str(), &textW, &textH);

    SDL_Rect dstRect = { x, y, textW, textH };

    // Render text
    SDL_RenderCopy(m_renderer, textTexture, nullptr, &dstRect);

    SDL_DestroyTexture(textTexture); // Free texture after rendering
  }

  void cleanUp() {
    SDL_DestroyRenderer(m_renderer);
    TTF_CloseFont(m_font);
    TTF_Quit();
  }

  int fontW{ 0 };
  int fontH{ 0 };

private:
  SDL_Renderer* m_renderer{ nullptr };
  TTF_Font* m_font{ nullptr };
};