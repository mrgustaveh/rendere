#include "BrushTool.hpp"
#include "../core/MathUtils.hpp"
#include "../core/Layer.hpp"
#include <algorithm>

namespace tools {

BrushTool::BrushTool()
    : m_color(sf::Color::Black)
    , m_size(1)
    , m_isDrawing(false)
{
}

void BrushTool::setColor(sf::Color color) {
    m_color = color;
}

void BrushTool::setSize(int size) {
    m_size = std::max(1, size);
}

void BrushTool::onPress(const sf::Vector2i& pos, core::Document& document) {
    m_isDrawing = true;
    m_lastPos = pos;
    paintAt(pos, document);
    
    if (auto* layer = document.getActiveLayer()) {
        layer->updateTexture();
    }
}

void BrushTool::onDrag(const sf::Vector2i& pos, core::Document& document) {
    if (!m_isDrawing) return;

    core::drawLine(m_lastPos.x, m_lastPos.y, pos.x, pos.y, 
        [this, &document](int x, int y) {
            paintAt({x, y}, document);
        }
    );
    
    m_lastPos = pos;
    
    if (auto* layer = document.getActiveLayer()) {
        layer->updateTexture();
    }
}

void BrushTool::onRelease(const sf::Vector2i& pos, core::Document& document) {
    if (m_isDrawing) {
        paintAt(pos, document);
        m_isDrawing = false;
        
        if (auto* layer = document.getActiveLayer()) {
            layer->updateTexture();
        }
    }
}

void BrushTool::paintAt(const sf::Vector2i& pos, core::Document& document) {
    auto* layer = document.getActiveLayer();
    if (!layer || !layer->isVisible()) return;

    // Mask check
    const auto& selection = document.getSelection();

    int halfSize = m_size / 2;
    int startX = pos.x - halfSize;
    int startY = pos.y - halfSize;
    int endX = startX + m_size;
    int endY = startY + m_size;

    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            if (x >= 0 && x < (int)document.getWidth() &&
                y >= 0 && y < (int)document.getHeight()) {
                
                // Only paint if point is in selection (or no selection active)
                if (selection.contains(x, y)) {
                    layer->setPixel(x, y, m_color);
                }
            }
        }
    }
}

} // namespace tools
