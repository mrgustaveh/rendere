#include "Selection.hpp"

namespace core {

Selection::Selection()
    : m_rect({0, 0}, {0, 0})
    , m_active(false)
{
}

bool Selection::contains(int x, int y) const {
    if (!m_active) {
        // If no selection is active, all points are considered "selected" (drawable)
        // In paint apps: no selection = draw everywhere
        return true;
    }
    return m_rect.contains({x, y});
}

void Selection::setRect(const sf::IntRect& rect) {
    m_rect = rect;
    // Normalize rect just in case (width/height positive)
    if (m_rect.size.x < 0) {
        m_rect.position.x += m_rect.size.x;
        m_rect.size.x = -m_rect.size.x;
    }
    if (m_rect.size.y < 0) {
        m_rect.position.y += m_rect.size.y;
        m_rect.size.y = -m_rect.size.y;
    }
    m_active = true;
}

const sf::IntRect& Selection::getRect() const {
    return m_rect;
}

bool Selection::isEmpty() const {
    return !m_active;
}

void Selection::clear() {
    m_active = false;
    m_rect = {{0, 0}, {0, 0}};
}

} // namespace core

