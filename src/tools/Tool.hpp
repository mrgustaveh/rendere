#ifndef TOOL_HPP
#define TOOL_HPP

#include <SFML/System/Vector2.hpp>
#include "../core/Document.hpp"

namespace tools {

class Tool {
public:
    virtual ~Tool() = default;

    virtual void onActivate() {}
    
    virtual void onDeactivate() {}

    virtual void onPress(const sf::Vector2i& pos, core::Document& document) = 0;
    virtual void onDrag(const sf::Vector2i& pos, core::Document& document) = 0;
    virtual void onRelease(const sf::Vector2i& pos, core::Document& document) = 0;
};

} // namespace tools

#endif // TOOL_HPP
