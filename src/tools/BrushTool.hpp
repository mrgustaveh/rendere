#ifndef BRUSH_TOOL_HPP
#define BRUSH_TOOL_HPP

#include "Tool.hpp"
#include <SFML/Graphics/Color.hpp>

namespace tools {

class BrushTool : public Tool {
public:
    BrushTool();

    void onPress(const sf::Vector2i& pos, core::Document& document) override;
    void onDrag(const sf::Vector2i& pos, core::Document& document) override;
    void onRelease(const sf::Vector2i& pos, core::Document& document) override;

    void setColor(sf::Color color);
    void setSize(int size);
    
    sf::Color getColor() const { return m_color; }
    int getSize() const { return m_size; }

private:
    void paintAt(const sf::Vector2i& pos, core::Document& document);
    
    sf::Color m_color;
    int m_size;
    sf::Vector2i m_lastPos;
    bool m_isDrawing;
};

} // namespace tools

#endif // BRUSH_TOOL_HPP