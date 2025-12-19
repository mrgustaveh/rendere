#include "SelectionTool.hpp"
#include <cmath>
#include <algorithm>

namespace tools {

SelectionTool::SelectionTool()
    : m_isSelecting(false)
{
}

void SelectionTool::onPress(const sf::Vector2i& pos, core::Document& document) {
    m_isSelecting = true;
    m_startPos = pos;
    // Clear previous selection on new press? Or maybe shift to add?
    // For now, simple behavior: new selection replaces old.
    document.getSelection().clear();
}

void SelectionTool::onDrag(const sf::Vector2i& pos, core::Document& document) {
    if (!m_isSelecting) return;

    // Calculate rect from startPos to current pos
    int left = std::min(m_startPos.x, pos.x);
    int top = std::min(m_startPos.y, pos.y);
    int width = std::abs(pos.x - m_startPos.x);
    int height = std::abs(pos.y - m_startPos.y);

    document.getSelection().setRect({{left, top}, {width, height}});
}

void SelectionTool::onRelease(const sf::Vector2i& pos, core::Document& document) {
    if (m_isSelecting) {
        // Finalize selection (already done in drag, just ensure)
        int left = std::min(m_startPos.x, pos.x);
        int top = std::min(m_startPos.y, pos.y);
        int width = std::abs(pos.x - m_startPos.x);
        int height = std::abs(pos.y - m_startPos.y);

        if (width > 0 && height > 0) {
            document.getSelection().setRect({{left, top}, {width, height}});
        } else {
            // Click without drag might clear selection
            document.getSelection().clear();
        }
        
        m_isSelecting = false;
    }
}

} // namespace tools

