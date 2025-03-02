#pragma once
#include "Widget.h"
#include <vector>
#include <memory>

class LayoutManager {
public:
  enum class LayoutType { Vertical, Horizontal, Grid };

  LayoutManager(int startX = 10, int startY = 10, int spacing = 5, LayoutType type = LayoutType::Vertical)
    : m_xOffset(startX), m_yOffset(startY), m_spacing(spacing), m_layoutType(type) {}

  ~LayoutManager() = default;

  void setLayoutType(LayoutType type) {
    m_layoutType = type;
    m_needsUpdate = true;
  }
  
  void setNumColumns (int columns) {
    if (columns >= 1) {
      m_columns = columns;
      m_needsUpdate = true;
    }
  }

  int getNumColumns() const { return m_columns; }

  bool needsUpdate() const { return m_needsUpdate; }

  int getNumWidgets() const { return static_cast<int>(m_widgets.size()); }

  void addWidget(std::unique_ptr<Widget> widget) {
    m_widgets.push_back(std::move(widget));
    m_needsUpdate = true;
  }

  void applyLayout() {
    int currentX = m_xOffset;
    int currentY = m_yOffset;
    int colCount = 0;
    int rowCount = 0;

    m_rowMaxHeights.clear();
    m_rowMaxHeights.push_back(0);

    for (auto& widget : m_widgets) {
      SDL_Rect dims = widget->getDims();

      switch (m_layoutType) {
      case LayoutType::Vertical:
        widget->setPosition(m_xOffset, currentY);
        currentY += dims.h + m_spacing;
        break;

      case LayoutType::Horizontal:
        widget->setPosition(currentX, m_yOffset);
        currentX += dims.w + m_spacing;
        break;

      case LayoutType::Grid:
        widget->setPosition(currentX, currentY);

        if (rowCount >= m_rowMaxHeights.size()) {
          m_rowMaxHeights.push_back(0);
        }
        m_rowMaxHeights[rowCount] = std::max(m_rowMaxHeights[rowCount], dims.h);

        colCount++;
        if (colCount >= m_columns) {
          colCount = 0;
          currentX = m_xOffset;
          currentY += m_rowMaxHeights[rowCount] + m_spacing;
          rowCount++;
        } else {
          currentX += dims.w + m_spacing;
        }
        break;
      }
    }
    m_needsUpdate = false;
  }

  std::vector<std::unique_ptr<Widget>>& getWidgets() { return m_widgets; }

private:
  int m_xOffset;
  int m_yOffset;
  int m_spacing;
  LayoutType m_layoutType;
  bool m_needsUpdate{ false };

  // Grid-specific
  int m_columns{ 2 };
  std::vector<int> m_rowMaxHeights{ 0 };

  std::vector<std::unique_ptr<Widget>> m_widgets;
};