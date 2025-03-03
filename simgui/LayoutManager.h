#pragma once
#include "Widget.h"
#include <vector>
#include <memory>

class LayoutManager {
public:
  LayoutManager(int startX = 10, int startY = 10, int padding = 4)
    : m_xOffset(startX), m_yOffset(startY), m_padding(padding) {}

  ~LayoutManager() = default;
  
  void setNumColumns (int columns) {
    if (columns >= 1) {
      m_columns = columns;
      m_needsUpdate = true;
    }
  }

  int getNumColumns() const { return m_columns; }

  int getNumWidgets() const { return static_cast<int>(m_widgets.size()); }

  int getRowHeight(int index) const { return m_rowMaxHeights[index]; }

  bool needsUpdate() const { return m_needsUpdate; }

  void addWidget(std::unique_ptr<Widget> widget) {
    m_widgets.push_back(std::move(widget));
    m_needsUpdate = true;
  }

  void reorderWidget(Widget* dragged, Widget* target, bool insertBefore) {
    auto& widgets = m_widgets;

    // Find the index of dragged and target widgets
    int draggedIndex = -1, targetIndex = -1;
    for (int i = 0; i < widgets.size(); ++i) {
      if (widgets[i].get() == dragged) { draggedIndex = i; }
      if (widgets[i].get() == target) { targetIndex = i; }
    }

    if (draggedIndex == -1 || targetIndex == -1 || draggedIndex == targetIndex) {
      return; // Invalid indices, no change needed
    }

    // Extract the dragged widget safely
    std::unique_ptr<Widget> draggedWidget = std::move(widgets[draggedIndex]);
    widgets.erase(widgets.begin() + draggedIndex);

    // Adjust target index if dragged was before target (since we erased one element)
    if (draggedIndex < targetIndex) { targetIndex--; }

    // Insert dragged widget at new position
    if (insertBefore) {
      widgets.insert(widgets.begin() + targetIndex, std::move(draggedWidget));
    } else {
      widgets.insert(widgets.begin() + targetIndex + 1, std::move(draggedWidget));
    }
  }

  void applyLayout() {
    int currentX = m_xOffset;
    int currentY = m_yOffset;
    int colCount = 0;
    int rowCount = 0;

    m_rowMaxHeights.clear();
    m_rowMaxHeights.push_back(0);

    for (auto& widget : m_widgets) {
      SDL_Rect rect = widget->getRect();
        widget->setPosition(currentX, currentY);

        if (rowCount >= m_rowMaxHeights.size()) {
          m_rowMaxHeights.push_back(0);
        }
        m_rowMaxHeights[rowCount] = std::max(m_rowMaxHeights[rowCount], rect.h);

        colCount++;
        if (colCount >= m_columns) {
          colCount = 0;
          currentX = m_xOffset;
          currentY += m_rowMaxHeights[rowCount] + m_padding;
          rowCount++;
        } else {
          currentX += rect.w + m_padding;
        }
    }
    m_needsUpdate = false;
  }

  std::vector<std::unique_ptr<Widget>>& getWidgets() { return m_widgets; }

private:
  int m_xOffset;
  int m_yOffset;
  int m_padding;
  bool m_needsUpdate{ false };

  int m_columns{ 2 };
  std::vector<int> m_rowMaxHeights{ 0 };

  std::vector<std::unique_ptr<Widget>> m_widgets;
};