#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <SFML/Graphics/Rect.hpp>

namespace core {

class Selection {
public:
    Selection();

    // Check if a point is selected
    bool contains(int x, int y) const;
    
    // Set/Get the rectangular selection
    void setRect(const sf::IntRect& rect);
    const sf::IntRect& getRect() const;
    
    bool isEmpty() const;
    void clear();

private:
    sf::IntRect m_rect;
    bool m_active; // True if a selection is defined
};

} // namespace core

#endif // SELECTION_HPP

