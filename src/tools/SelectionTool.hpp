#ifndef SELECTION_TOOL_HPP
#define SELECTION_TOOL_HPP

#include "Tool.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace tools {

class SelectionTool : public Tool {
public:
    SelectionTool();

    void onPress(const sf::Vector2i& pos, core::Document& document) override;
    void onDrag(const sf::Vector2i& pos, core::Document& document) override;
    void onRelease(const sf::Vector2i& pos, core::Document& document) override;

private:
    sf::Vector2i m_startPos;
    bool m_isSelecting;
};

} // namespace tools

#endif // SELECTION_TOOL_HPP

